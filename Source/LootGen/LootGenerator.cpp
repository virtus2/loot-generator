// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootGenerator.h"

#include "ItemWeapon.h"
#include "ItemArmor.h"
#include "LootActor.h"


#include "TreasureClass.h"

ULootGenerator::ULootGenerator(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/Weapon.Weapon'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ArmorDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/Armor.Armor'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MiscDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/Misc.Misc'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTypeDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/ItemTypes.ItemTypes'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> TreasureClassDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/TreasureClassEx.TreasureClassEx'"));
	
	bool bIsValid =
		IsValid(WeaponDataTableClass.Object) &&
		IsValid(ArmorDataTableClass.Object) &&
		IsValid(MiscDataTableClass.Object) &&
		IsValid(ItemTypeDataTableClass.Object) &&
		IsValid(TreasureClassDataTableClass.Object);
	if (!bIsValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("The UDataTable of ULootGenerator is not valid."));
		return;
	}

	TObjectPtr<UDataTable> WeaponDataTable = WeaponDataTableClass.Object;
	TObjectPtr<UDataTable> ArmorDataTable = ArmorDataTableClass.Object;
	TObjectPtr<UDataTable> MiscDataTable = MiscDataTableClass.Object;
	TObjectPtr<UDataTable> ItemTypeDataTable = ItemTypeDataTableClass.Object;
	TObjectPtr<UDataTable> TreasureClassDataTable = TreasureClassDataTableClass.Object;

	InitializeData<FD2Weapon, UWeapon>(WeaponDataTable, WeaponMap, WeaponByCode);
	InitializeData<FD2Armor, UArmor>(ArmorDataTable, ArmorMap, ArmorByCode);
	InitializeData<FD2Misc, UMisc>(MiscDataTable, MiscMap, MiscByCode);
	InitializeData<FD2ItemType, UItemType>(ItemTypeDataTable, ItemTypeMap, ItemTypeByCode);

	InitializeTreasureClassData(TreasureClassDataTable); // Must be called after the initialization of the ItemType.

	static ConstructorHelpers::FObjectFinder<UItemMeshInfo> ItemMeshInfoObj(TEXT("/Script/LootGen.ItemMeshInfo'/Game/LootGen/DA_ItemMeshInfo.DA_ItemMeshInfo'"));
	if (IsValid(ItemMeshInfoObj.Object))
	{
		ItemMeshInfo = ItemMeshInfoObj.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The ItemMeshInfo of ULootGenerator is not valid."));
	}
}

template<typename FD2, typename T>
requires std::derived_from<FD2, FTableRowBase>
void ULootGenerator::InitializeData(TObjectPtr<UDataTable> DataTable, TMap<FName, TObjectPtr<T>>& MapByName, TMap<FName, TObjectPtr<T>>& MapByCode)
{
	const FString Context;
	TArray<FName> Names = DataTable->GetRowNames();
	for (const auto& Name : Names)
	{
		FD2* Data = DataTable->FindRow<FD2>(Name, Context);
		T* Item = NewObject<T>();
		Item->Initialize(Name, Data);
		MapByName.Add(Name, Item);
		MapByCode.Add(Item->Code, Item);
	}
}

void ULootGenerator::InitializeTreasureClassData(TObjectPtr<UDataTable> TreasureClassDataTable)
{
	// Initialize the TMap<Name, TreasureClass> using TreasureClassEx.txt
	const FString Context;
	TArray<FName> TreasureClassNames = TreasureClassDataTable->GetRowNames();
	for (const auto& Name : TreasureClassNames)
	{
		FD2TreasureClass* D2TreasureClass = TreasureClassDataTable->FindRow<FD2TreasureClass>(Name, Context);
		FTreasureClass TreasureClass(D2TreasureClass);
		TreasureClassMap.Add(Name, TreasureClass);
	}

	// Generate the runtime treasureclasses using ItemType.txt
	for (const auto& ItemType : ItemTypeByCode)
	{
		if (ItemType.Value->bAutoTreasureClassGenerate == false)
		{
			continue;
		}

		for (int i = 0; i < 100; i += 3)
		{
			FTreasureClass TreasureClass;
			FName TreasureClassName = FName(*(ItemType.Value->Code.ToString() + FString::FromInt(i)));
			TreasureClass.Picks = 1;
			TreasureClass.NoDrop = 0;
			// Generate TreasureClass by using Weapon.txt
			AutoGenerateTreasureClass<UWeapon>(ItemType.Value, i, TreasureClass, WeaponMap, WeaponByCode);
			AutoGenerateTreasureClass<UArmor>(ItemType.Value, i, TreasureClass, ArmorMap, ArmorByCode);
			AutoGenerateTreasureClass<UMisc>(ItemType.Value, i, TreasureClass, MiscMap, MiscByCode);
			TreasureClassMap.Add(TreasureClassName, TreasureClass);
		}
	}
}

template<typename T>
requires std::derived_from<T, IItemInfo>
void ULootGenerator::AutoGenerateTreasureClass(TObjectPtr<UItemType> ItemTypeToGenerate, int Level, FTreasureClass& TreasureClass, TMap<FName, TObjectPtr<T>>& MapByName, TMap<FName, TObjectPtr<T>>& MapByCode)
{
	for (const auto& Item : MapByName)
	{
		// If Item's level is too low or too high, then skip.
		int ItemLevel = Item.Value->GetLevel();
		if (ItemLevel <= Level || ItemLevel > Level + 3)
		{
			continue;
		}

		UItemType* ItemType = *ItemTypeByCode.Find(Item.Value->GetType());
		if (ItemType == nullptr)
		{
			continue;
		}

		// If the type of item is the same as given ItemType(ItemTypeToGenerate), then add it to the TreasureClass.
		if (ItemType->Code.IsEqual(ItemTypeToGenerate->Code))
		{
			TreasureClass.ItemProb.Add(Item.Value->GetCode(), 1);
			TreasureClass.TotalProb += 1;
		}

		// If the type of item is not the same as given ItemType(ItemTypeToGenerate), then check the Equiv.
		// Equiv is the parent item types of this item's type.
		for (int i = 0; i < ItemType->Equiv.Num(); i++)
		{
			FName ParentItemTypeCode = ItemType->Equiv[i];
			while (ParentItemTypeCode.IsNone() == false)
			{
				if (ParentItemTypeCode == ItemTypeToGenerate->Code)
				{
					TreasureClass.ItemProb.Add(Item.Value->GetCode(), 1);
					TreasureClass.TotalProb += 1;
				}

				// If the parent item type is not the same as given ItemType(ItemTypeToGenerate), then check the parent's parent.
				UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
				if (ParentItemType == nullptr)
				{
					break;
				}
				ParentItemTypeCode = ParentItemType->Equiv[i];
			}
		}
	}
}


void ULootGenerator::SpawnLootsAt(FVector Location, TArray<FName>& TreasureClassNames)
{
	for (const auto& TreasureClassName : TreasureClassNames)
	{
		FQualityFactor QualityFactor;
		GenerateLootAt(TreasureClassName, Location, QualityFactor);
	}
}

void ULootGenerator::GenerateLootAt(FName TreasureClassNameOrItemCode, FVector& Location, FQualityFactor& QualityFactor)
{
	// If given name is TreasureClass, then roll that TreasureClass.
	FTreasureClass* TreasureClass = FindTreasureClassFromDataTable(TreasureClassNameOrItemCode);
	if (TreasureClass != nullptr)
	{
		RollTreasureClassPicks(TreasureClass, Location, QualityFactor);
	}
	else
	{
		// If given name is ItemCode, Generate that item.
		TObjectPtr<UItemBase> Item = GenerateItem(TreasureClassNameOrItemCode, QualityFactor);

		// Spawn the loot and set the item data.
		UWorld* World = GetWorld();
		if (World)
		{
			FRotator Rotator; // TODO: Set the random rotation.
			TObjectPtr<ALootActor> NewLootActor = World->SpawnActor<ALootActor>(ALootActor::StaticClass(), Location, Rotator);
			NewLootActor->SetItem(Item);

			auto Mesh = ItemMeshInfo->Meshes.Find(Item->Type);
			if (Mesh != nullptr)
			{
				NewLootActor->SetMesh(*Mesh);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%s has no mesh."), *(Item->Type.ToString()));
			}
		}
	}
}

FTreasureClass* ULootGenerator::FindTreasureClassFromDataTable(FName TreasureClassName)
{
	const FString Context;
	FTreasureClass* TreasureClass = TreasureClassMap.Find(TreasureClassName);
	return TreasureClass;
}

void ULootGenerator::RollTreasureClassPicks(FTreasureClass* TreasureClass, FVector& Location, FQualityFactor& QualityFactor)
{
	QualityFactor.Unique = FMath::Max(QualityFactor.Unique, TreasureClass->QualityFactor.Unique);
	QualityFactor.Set = FMath::Max(QualityFactor.Set, TreasureClass->QualityFactor.Set);
	QualityFactor.Rare = FMath::Max(QualityFactor.Rare, TreasureClass->QualityFactor.Rare);
	QualityFactor.Magic = FMath::Max(QualityFactor.Magic, TreasureClass->QualityFactor.Magic);

	if (TreasureClass->Picks < 0)
	{
		// If the number of picks is negative, it is used to determine exactly which items, and how many of each, to drop.
		for (int i = 0; i < -TreasureClass->Picks; i++)
		{
			for (const auto& Item : TreasureClass->ItemProb)
			{
				for (int j = 0; j < Item.Value; j++)
				{
					GenerateLootAt(Item.Key, Location, QualityFactor);
				}
			}
		}
	}
	else
	{
		// If the number of picks is positive, it is used as the number of loops to run the “pick drop” routine.
		for (int i = 0; i < TreasureClass->Picks; i++)
		{
			int Random = FMath::RandRange(0, TreasureClass->TotalProb + TreasureClass->NoDrop);
			for (const auto& Item : TreasureClass->ItemProb)
			{
				if (Random < Item.Value)
				{
					GenerateLootAt(Item.Key, Location, QualityFactor);
					break;
				}
				Random -= Item.Value;
			}
		}
	}
}

TObjectPtr<UItemBase> ULootGenerator::GenerateItem(FName ItemCode, FQualityFactor& QualityFactor)
{
	// Find the item by code.
	auto Weapon = WeaponByCode.Find(ItemCode);
	auto Armor = ArmorByCode.Find(ItemCode);
	auto Misc = MiscByCode.Find(ItemCode);

	// TODO: Set the QualityFactor.
	if (Weapon != nullptr)
	{
		TObjectPtr<UItemWeapon> Item = NewObject<UItemWeapon>();
		Item->SetWeapon(*Weapon);
		return Item;
	}
	else if (Armor != nullptr)
	{
		// TODO: Implement UItemArmor.
		TObjectPtr<UItemArmor> Item = NewObject<UItemArmor>();
		return Item;
	}
	else if (Misc != nullptr)
	{
		// TODO: Implement UItemMisc. Might UItemConsumable and UItemRune... etc. be better?
		TObjectPtr<UItemBase> Item = NewObject<UItemBase>();
		return Item;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no item with the code %s"), *(ItemCode.ToString()));
		return nullptr;
	}
	return nullptr;
}

void ULootGenerator::TestGenerateLoot(FName TreasureClassNameOrItemCode, FVector Location, int Count)
{
	for (int i = 0; i < Count; i++)
	{
		TArray<FName> TC { TreasureClassNameOrItemCode };
		SpawnLootsAt(Location, TC);
	}
}
// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootGenerator.h"

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

	Initialize<FD2Weapon, UWeapon>(WeaponDataTable, WeaponMap, WeaponByCode);
	Initialize<FD2Armor, UArmor>(ArmorDataTable, ArmorMap, ArmorByCode);
	Initialize<FD2Misc, UMisc>(MiscDataTable, MiscMap, MiscByCode);
	Initialize<FD2ItemType, UItemType>(ItemTypeDataTable, ItemTypeMap, ItemTypeByCode);

	InitializeTreasureClassData(TreasureClassDataTable); // Must be called after the initialization of the ItemType.
}

template<typename FD2, typename T>
void ULootGenerator::Initialize(TObjectPtr<UDataTable> DataTable, TMap<FName, TObjectPtr<T>>& MapByName, TMap<FName, TObjectPtr<T>>& MapByCode)
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
			for (const auto& Weapon : WeaponMap)
			{
				if (Weapon.Value->Level <= i || Weapon.Value->Level > i + 3)
				{
					continue;
				}

				UItemType* ItemTypeOfWeapon = *ItemTypeByCode.Find(Weapon.Value->Type);
				if (ItemTypeOfWeapon == nullptr)
				{
					continue;
				}

				if (ItemTypeOfWeapon->Code.IsEqual(ItemType.Value->Code))
				{
					TreasureClass.ItemProb.Add(Weapon.Value->Code, 1);
					TreasureClass.TotalProb += 1;
				}

				FName ParentItemTypeCode = ItemTypeOfWeapon->Equiv1;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Weapon.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if(ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv1;
				}

				ParentItemTypeCode = ItemTypeOfWeapon->Equiv2;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Weapon.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if (ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv2;
				}
			}

			// Generate TreasureClass by using Armor.txt
			for (const auto& Armor : ArmorMap)
			{
				if (Armor.Value->Level <= i || Armor.Value->Level >= i + 3)
				{
					continue;
				}

				UItemType* ItemTypeOfArmor = *ItemTypeByCode.Find(Armor.Value->Type);
				if (ItemTypeOfArmor == nullptr)
				{
					continue;
				}

				FName ParentItemTypeCode = ItemTypeOfArmor->Equiv1;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Armor.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if (ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv1;
				}

				ParentItemTypeCode = ItemTypeOfArmor->Equiv2;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Armor.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if (ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv2;
				}

			}

			// Generate TreasureClass by using Misc.txt
			for (const auto& Misc : MiscMap)
			{
				if (Misc.Value->Level <= i || Misc.Value->Level >= i + 3)
				{
					continue;
				}

				UItemType* ItemTypeOfMisc = *ItemTypeByCode.Find(Misc.Value->Type);
				if (ItemTypeOfMisc == nullptr)
				{
					continue;
				}

				FName ParentItemTypeCode = ItemTypeOfMisc->Equiv1;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Misc.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if (ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv1;
				}

				ParentItemTypeCode = ItemTypeOfMisc->Equiv2;
				while (ParentItemTypeCode.IsNone() == false)
				{
					if (ParentItemTypeCode == ItemType.Value->Code)
					{
						TreasureClass.ItemProb.Add(Misc.Value->Code, 1);
						TreasureClass.TotalProb += 1;
					}

					UItemType* ParentItemType = *ItemTypeByCode.Find(ParentItemTypeCode);
					if (ParentItemType == nullptr)
					{
						break;
					}
					ParentItemTypeCode = ParentItemType->Equiv2;
				}
			}
			TreasureClassMap.Add(TreasureClassName, TreasureClass);
		}
	}
}

void ULootGenerator::DetermineItemAndQuality(FName TreasureClassNameOrItemCode, FQualityFactor QualityFactor)
{
	// If given name is TreasureClass, then roll that TreasureClass.
	FTreasureClass* TreasureClass = FindTreasureClassFromDataTable(TreasureClassNameOrItemCode);
	if (TreasureClass != nullptr)
	{
		RollTreasureClassPicks(TreasureClass, QualityFactor);
		return;
	}

	// If given name is ItemCode, then Generate that item.
	GenerateLoot(TreasureClassNameOrItemCode, QualityFactor);
}

FTreasureClass* ULootGenerator::FindTreasureClassFromDataTable(FName TreasureClassName)
{
	const FString Context;
	FTreasureClass* TreasureClass = TreasureClassMap.Find(TreasureClassName);
	return TreasureClass;
}

void ULootGenerator::RollTreasureClassPicks(FTreasureClass* TreasureClass, FQualityFactor& QualityFactor)
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
					DetermineItemAndQuality(Item.Key, QualityFactor);
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
					DetermineItemAndQuality(Item.Key, QualityFactor);
					break;
				}
				Random -= Item.Value;
			}
		}
	}
}

void ULootGenerator::GenerateLoot(FName ItemCode, FQualityFactor& QualityFactor)
{
	// Find the item by code.
	auto Weapon = WeaponByCode.Find(ItemCode);
	auto Armor = ArmorByCode.Find(ItemCode);
	auto Misc = MiscByCode.Find(ItemCode);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(ItemCode.ToString()));
	if (Weapon != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon: %s"), *(Weapon->Get()->Name.ToString()));
	}
	else if (Armor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Armor: %s"), *(Armor->Get()->Name.ToString()));
	}
	else if (Misc != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Misc: %s"), *(Misc->Get()->Name.ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no item with the code %s"), *(ItemCode.ToString()));
		return;
	}
}

void ULootGenerator::TestGenerateLoot(FName TreasureClassNameOrItemCode, int Count)
{
	for (int i = 0; i < Count; i++)
	{
		DetermineItemAndQuality(TreasureClassNameOrItemCode);
	}
}
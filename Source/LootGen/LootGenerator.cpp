// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootGenerator.h"

#include "TreasureClass.h"

ULootGenerator::ULootGenerator(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ArmorDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/Armor.Armor'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemTypeDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/ItemTypes.ItemTypes'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> TreasureClassDataTableClass(TEXT("/Script/Engine.DataTable'/Game/LootGen/DataTables/TreasureClassEx.TreasureClassEx'"));
	
	bool bIsValid =
		IsValid(ArmorDataTableClass.Object) &&
		IsValid(ItemTypeDataTableClass.Object) &&
		IsValid(TreasureClassDataTableClass.Object);
	if (bIsValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("The UDataTable of ULootGenerator is not valid."));
		return;
	}

	TObjectPtr<UDataTable> ArmorDataTable = ArmorDataTableClass.Object;
	TObjectPtr<UDataTable> ItemTypeDataTable = ItemTypeDataTableClass.Object;
	TObjectPtr<UDataTable> TreasureClassDataTable = TreasureClassDataTableClass.Object;

	// TODO: Template Method is better?
	InitializeArmorData(ArmorDataTable);
	InitializeItemTypeData(ItemTypeDataTable); 
	InitializeTreasureClassData(TreasureClassDataTable); // Must be called after the initialization of the ItemType.

	Test();
}

void ULootGenerator::InitializeArmorData(TObjectPtr<UDataTable> ArmorDataTable)
{
	const FString Context;
	TArray<FName> ArmorNames = ArmorDataTable->GetRowNames();
	for (const auto& Name : ArmorNames)
	{
		FD2Armor* D2Armor = ArmorDataTable->FindRow<FD2Armor>(Name, Context);
		FArmor Armor(D2Armor); 
		ArmorMap.Add(Name, Armor);
	}
}

void ULootGenerator::InitializeItemTypeData(TObjectPtr<UDataTable> ItemTypeDataTable)
{
	const FString Context;
	TArray<FName> ItemTypes = ItemTypeDataTable->GetRowNames();
	for (const auto& ItemType : ItemTypes)
	{
		FD2ItemType* D2ItemTypeData = ItemTypeDataTable->FindRow<FD2ItemType>(ItemType, Context);
		FItemType ItemTypeData(D2ItemTypeData);
		ItemTypeMap.Add(ItemType, ItemTypeData);
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
	for (const auto& ItemType : ItemTypeMap)
	{
		if (ItemType.Value.bAutoTreasureClassGenerate == false)
		{
			continue;
		}

		for (int i = 0; i < 100; i += 3)
		{
			FTreasureClass TreasureClass;
			TreasureClass.Picks = 1;
			// TODO: Generate TreasureClass by using Armor.txt, Weapon.txt, Misc.txt
		}
	}
}

void ULootGenerator::Test()
{
	for (int i = 0; i < 5; i++)
	{
		DetermineItemAndQuality(FName("Cow_(H)"));
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
				}
				Random -= Item.Value;
			}
		}
	}
}

void ULootGenerator::GenerateLoot(FName ItemCode, FQualityFactor& QualityFactor)
{
	// Find the item by code.
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(ItemCode.ToString()));
}

﻿// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "TreasureClass.h"
#include "ItemType.h"
#include "Armor.h"
#include "Weapon.h"
#include "Misc.h"
#include "ItemInfo.h"
#include "ItemMeshInfo.h"

#include "LootGenerator.generated.h"

class UItemBase;
class ALootActor;

/**
 * 
 */
UCLASS()
class LOOTGEN_API ULootGenerator : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	ULootGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/* Data Table Initialization */
	template<typename FD2, typename T>
	requires std::derived_from<FD2, FTableRowBase>
	void InitializeData(TObjectPtr<UDataTable> DataTable, TMap<FName, TObjectPtr<T>>& MapByName, TMap<FName, TObjectPtr<T>>& MapByCode);

	void InitializeTreasureClassData(TObjectPtr<UDataTable> TreasureClassDataTable);

public:
	/* TreasureClass Auto Generation */
	template<typename T>
	requires std::derived_from<T, IItemInfo>
	void AutoGenerateTreasureClass(TObjectPtr<UItemType> ItemTypeToGenerate, int Level, FTreasureClass& TreasureClass, TMap<FName, TObjectPtr<T>>& MapByName, TMap<FName, TObjectPtr<T>>& MapByCode);

public:
	/* Item Generation */
	void SpawnLootsAt(FVector Location, TArray<FName>& TreasureClassNames);

	void GenerateLootAt(FName TreasureClassNameOrItemCode, FVector& Location, FQualityFactor& QualityFactor);

	FTreasureClass* FindTreasureClassFromDataTable(FName TreasureClassName);
	
	void RollTreasureClassPicks(FTreasureClass* TreasureClass, FVector& Location, FQualityFactor& QualityFactor);

	TObjectPtr<UItemBase> GenerateItem(FName ItemCode, FQualityFactor& QualityFactor);

public:
	/* TEST FUNCTIONS */
	UFUNCTION(BlueprintCallable)
	void TestGenerateLoot(FName TreasureClassNameOrItemCode, FVector Location, int Count);

private:
	TMap<FName, FTreasureClass> TreasureClassMap;

	UPROPERTY()
	TMap<FName, TObjectPtr<UItemType>> ItemTypeMap; // By Name
	UPROPERTY()
	TMap<FName, TObjectPtr<UItemType>> ItemTypeByCode; // By Code

	UPROPERTY()
	TMap<FName, TObjectPtr<UWeapon>> WeaponMap; // By Name
	UPROPERTY()
	TMap<FName, TObjectPtr<UWeapon>> WeaponByCode; // By Code

	UPROPERTY()
	TMap<FName, TObjectPtr<UArmor>> ArmorMap; // By Name
	UPROPERTY()
	TMap<FName, TObjectPtr<UArmor>> ArmorByCode; // By Code

	UPROPERTY()
	TMap<FName, TObjectPtr<UMisc>> MiscMap; // By Name
	UPROPERTY()
	TMap<FName, TObjectPtr<UMisc>> MiscByCode; // By Code

	UPROPERTY()
	TObjectPtr<ALootActor> LootActor; // TODO: Move to other class like Data Asset?

	UPROPERTY()
	TObjectPtr<UItemMeshInfo> ItemMeshInfo;
};

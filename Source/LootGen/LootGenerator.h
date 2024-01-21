// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "TreasureClass.h"
#include "ItemType.h"
#include "Armor.h"
#include "Weapon.h"
#include "Misc.h"

#include "LootGenerator.generated.h"

/**
 * 
 */
UCLASS()
class LOOTGEN_API ULootGenerator : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	ULootGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	void InitializeWeaponData(TObjectPtr<UDataTable> WeaponDataTable);
	void InitializeArmorData(TObjectPtr<UDataTable> ArmorDataTable);
	void InitializeMiscData(TObjectPtr<UDataTable> MiscDataTable);
	void InitializeItemTypeData(TObjectPtr<UDataTable> ItemTypeDataTable);
	void InitializeTreasureClassData(TObjectPtr<UDataTable> TreasureClassDataTable);

	void DetermineItemAndQuality(FName TreasureClassNameOrItemCode, FQualityFactor QualityFactor = FQualityFactor());
	FTreasureClass* FindTreasureClassFromDataTable(FName TreasureClassName);
	void RollTreasureClassPicks(FTreasureClass* TreasureClass, FQualityFactor& QualityFactor);
	void GenerateLoot(FName ItemCode, FQualityFactor& QualityFactor);

	UFUNCTION(BlueprintCallable)
	void TestGenerateLoot(FName TreasureClassNameOrItemCode, int Count);

private:
	TMap<FName, FTreasureClass> TreasureClassMap;

	UPROPERTY()
	TMap<FName, UItemType*> ItemTypeMap; // By Name
	UPROPERTY()
	TMap<FName, UItemType*> ItemTypeByCode; // By Code

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

};

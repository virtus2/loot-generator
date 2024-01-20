// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "TreasureClass.h"
#include "ItemType.h"
#include "Armor.h"

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
	
	void InitializeArmorData(TObjectPtr<UDataTable> ArmorDataTable);
	void InitializeItemTypeData(TObjectPtr<UDataTable> ItemTypeDataTable);
	void InitializeTreasureClassData(TObjectPtr<UDataTable> TreasureClassDataTable);

	void Test();

	void DetermineItemAndQuality(FName TreasureClassNameOrItemCode, FQualityFactor QualityFactor = FQualityFactor());
	FTreasureClass* FindTreasureClassFromDataTable(FName TreasureClassName);
	void RollTreasureClassPicks(FTreasureClass* TreasureClass, FQualityFactor& QualityFactor);
	void GenerateLoot(FName ItemCode, FQualityFactor& QualityFactor);

private:
	UPROPERTY()
	TMap<FName, FTreasureClass> TreasureClassMap;

	UPROPERTY()
	TMap<FName, FItemType> ItemTypeMap;

	UPROPERTY()
	TMap<FName, FArmor> ArmorMap;

};

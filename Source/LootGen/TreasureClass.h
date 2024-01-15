// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TreasureClass.generated.h"

/**
 * 
 */
UCLASS()
class LOOTGEN_API UTreasureClass : public UDataTable
{
	GENERATED_BODY()
	
	uint8 Group;
	uint8 Level;
	uint8 Picks;
	uint16 Unique;
	uint16 Set;
	uint16 Rare;
	uint16 Magic;
	uint16 NoDrop;

};

// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class LOOTGEN_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName Name;
	
};

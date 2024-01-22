// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInfo.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LOOTGEN_API IItemInfo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual FName GetName() = 0;

	UFUNCTION()
	virtual int GetLevel() = 0;
	
	UFUNCTION()
	virtual FName GetType() = 0;

	UFUNCTION()
	virtual FName GetCode() = 0;


};

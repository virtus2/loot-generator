// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"

#include "Weapon.h"

#include "ItemWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LOOTGEN_API UItemWeapon : public UItemBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	int MinDam;

	UPROPERTY()
	int MaxDam;

	UPROPERTY()
	int Level;

	UPROPERTY()
	int LevelReq;

public:
	void SetWeapon(TObjectPtr<UWeapon> Weapon)
	{
		Name = Weapon->Name;
		Type = Weapon->Type;
		MinDam = Weapon->MinDam;
		MaxDam = Weapon->MaxDam;
		Level = Weapon->Level;
		LevelReq = Weapon->LevelReq;
	}
	
};

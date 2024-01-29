// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemMeshInfo.generated.h"

/**
 * 
 */
UCLASS()
class LOOTGEN_API UItemMeshInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<FName, class USkeletalMesh*> Meshes;
};

// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Armor.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2Armor : public FTableRowBase
{
	GENERATED_BODY() 

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSpawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ReqStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameStr;
	
	// TODO: Add More Fields
};

USTRUCT(BlueprintType)
struct FArmor
{
	GENERATED_BODY()

	public:
	

};
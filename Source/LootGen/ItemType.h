// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "ItemType.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2ItemType : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Equiv1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Equiv2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TreasureClass;

	// TODO: Add more fields 
	// https://d2mods.info/forum/kb/viewarticle?a=369
};

USTRUCT(BlueprintType)
struct FItemType : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemType()
	{
		UE_LOG(LogTemp, Warning, TEXT("Default Constructor of FItemType should not be called!"));
	}

	FItemType(FD2ItemType* D2ItemType)
	{
		Code = D2ItemType->Code;
		ParentItemType.Add(D2ItemType->Equiv1);
		ParentItemType.Add(D2ItemType->Equiv2);
		bAutoTreasureClassGenerate = (bool)D2ItemType->TreasureClass;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FName> ParentItemType; /* Equiv1, Equiv2 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoTreasureClassGenerate; /* TreasureClass */

};

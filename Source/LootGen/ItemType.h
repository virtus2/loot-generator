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

UCLASS()
class LOOTGEN_API UItemType : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(FName InName, FD2ItemType* ItemType)
	{
		Name = InName;
		Code = ItemType->Code;
		Equiv.Add(ItemType->Equiv1);
		Equiv.Add(ItemType->Equiv2);
		bAutoTreasureClassGenerate = (bool)ItemType->TreasureClass;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Equiv;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoTreasureClassGenerate; /* TreasureClass */
};


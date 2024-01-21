// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Misc.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2Misc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Belt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnStack;
};

UCLASS()
class LOOTGEN_API UMisc : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(FName InName, FD2Misc* D2Misc)
	{
		Name = InName;
		Level = D2Misc->Level;
		LevelReq = D2Misc->LevelReq;
		Rarity = D2Misc->Rarity;
		Spawnable = D2Misc->Spawnable;
		Code = D2Misc->Code;
		Type = D2Misc->Type;
		Type2 = D2Misc->Type2;
		Belt = D2Misc->Belt;
		Stackable = D2Misc->Stackable;
		MinStack = D2Misc->MinStack;
		MaxStack = D2Misc->MaxStack;
		SpawnStack = D2Misc->SpawnStack;
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Belt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnStack;
};
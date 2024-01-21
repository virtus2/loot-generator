// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "Weapon.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2Weapon : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinDam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

};

UCLASS()
class LOOTGEN_API UWeapon : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(FName InName, FD2Weapon* D2Weapon)
	{
		Name = InName;
		Type = D2Weapon->Type;
		Type2 = D2Weapon->Type2;
		Code = D2Weapon->Code;
		NameStr = D2Weapon->NameStr;
		Version = D2Weapon->Version;
		Rarity = D2Weapon->Rarity;
		Spawnable = D2Weapon->Spawnable;
		MinDam = D2Weapon->MinDam;
		MaxDam = D2Weapon->MaxDam;
		Level = D2Weapon->Level;
		LevelReq = D2Weapon->LevelReq;
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinDam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxDam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;
};
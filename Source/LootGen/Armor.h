// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "ItemInfo.h"

#include "Armor.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2Armor : public FTableRowBase
{
	GENERATED_BODY() 

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ReqStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;
	
	// TODO: Add more fields 
	// https://d2mods.info/forum/kb/viewarticle?a=2
};

UCLASS()
class LOOTGEN_API UArmor : public UObject, public IItemInfo
{
	GENERATED_BODY()

public:
	void Initialize(FName InName, FD2Armor* D2Armor)
	{
		Name = InName;
		Version = D2Armor->Version;
		Rarity = D2Armor->Rarity;
		bSpawnable = (bool)D2Armor->Spawnable;
		MinAC = D2Armor->MinAC;
		MaxAC = D2Armor->MaxAC;
		Speed = D2Armor->Speed;
		ReqStr = D2Armor->ReqStr;
		Level = D2Armor->Level;
		LevelReq = D2Armor->LevelReq;
		Code = D2Armor->Code;
		NameStr = D2Armor->NameStr;
		Type = D2Armor->Type;
	};

	virtual FName GetName() override
	{
		return Name;
	}

	virtual int GetLevel() override
	{
		return Level;
	}

	virtual FName GetType() override
	{
		return Type;
	}

	virtual FName GetCode() override
	{
		return Code;
	}
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
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelReq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Type;

	// TODO: Add more fields 
	// https://d2mods.info/forum/kb/viewarticle?a=2
};

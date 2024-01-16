﻿// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "Engine/DataTable.h"

#include "TreasureClass.generated.h"

USTRUCT(BlueprintType)
struct FTreasureClass : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Group = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Picks = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Unique= 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Set = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rare = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Magic = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NoDrop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob1 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob2 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob3 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob4 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob5 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob6 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob7 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob8 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob9 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob10 = 0;
};

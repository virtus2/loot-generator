// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "Engine/DataTable.h"

#include "TreasureClass.generated.h"

/* The original data structure used by Diablo II (Used to import .txt data) */
USTRUCT(BlueprintType)
struct FD2TreasureClass : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Group = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Picks = 0;

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
	FName Item1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob1 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob2 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob3 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob4 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob5 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob6 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob7 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob8 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob9 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Item10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Prob10 = 0;
};


/* Custom data structure to handle Diablo II data easier.
   POD structure about the chance of item quality in TreasureClass */
USTRUCT(BlueprintType)
struct FQualityFactor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Unique = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Set = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rare = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Magic = 0;

};

/* Custom data structure to handle Diablo II data easier.
TreasureClass with QualityFactor and Total probability */
USTRUCT(BlueprintType)
struct FTreasureClass
{
	GENERATED_BODY()

public:
	FTreasureClass() 
	{
		// UE_LOG(LogTemp, Warning, TEXT("Default Constructor of FTreasureClass should not be called!"));
	}

	FTreasureClass(FD2TreasureClass* D2TreasureClass)
	{
		Group = D2TreasureClass->Group;
		Level = D2TreasureClass->Level;
		Picks = D2TreasureClass->Picks;
		QualityFactor = FQualityFactor();
		QualityFactor.Unique = D2TreasureClass->Unique;
		QualityFactor.Set = D2TreasureClass->Set;
		QualityFactor.Rare = D2TreasureClass->Rare;
		QualityFactor.Magic = D2TreasureClass->Magic;
		NoDrop = D2TreasureClass->NoDrop;
		if (D2TreasureClass->Item1.IsNone() == false) ItemProb.Add(D2TreasureClass->Item1, D2TreasureClass->Prob1);
		if (D2TreasureClass->Item2.IsNone() == false) ItemProb.Add(D2TreasureClass->Item2, D2TreasureClass->Prob2);
		if (D2TreasureClass->Item3.IsNone() == false) ItemProb.Add(D2TreasureClass->Item3, D2TreasureClass->Prob3);
		if (D2TreasureClass->Item4.IsNone() == false) ItemProb.Add(D2TreasureClass->Item4, D2TreasureClass->Prob4);
		if (D2TreasureClass->Item5.IsNone() == false) ItemProb.Add(D2TreasureClass->Item5, D2TreasureClass->Prob5);
		if (D2TreasureClass->Item6.IsNone() == false) ItemProb.Add(D2TreasureClass->Item6, D2TreasureClass->Prob6);
		if (D2TreasureClass->Item7.IsNone() == false) ItemProb.Add(D2TreasureClass->Item7, D2TreasureClass->Prob7);
		if (D2TreasureClass->Item8.IsNone() == false) ItemProb.Add(D2TreasureClass->Item8, D2TreasureClass->Prob8);
		if (D2TreasureClass->Item9.IsNone() == false) ItemProb.Add(D2TreasureClass->Item9, D2TreasureClass->Prob9);
		if (D2TreasureClass->Item10.IsNone() == false) ItemProb.Add(D2TreasureClass->Item10, D2TreasureClass->Prob10);
		for (const auto& ItemProbPair : ItemProb)
		{
			TotalProb += ItemProbPair.Value;
		}
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Group = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Picks = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQualityFactor QualityFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NoDrop = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int> ItemProb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalProb = 0;

};

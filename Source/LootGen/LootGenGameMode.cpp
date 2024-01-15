// Copyright Epic Games, Inc. All Rights Reserved.

#include "LootGenGameMode.h"
#include "LootGenCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALootGenGameMode::ALootGenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

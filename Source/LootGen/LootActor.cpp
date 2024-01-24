// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootActor.h"

#include "ItemBase.h"

// Sets default values
ALootActor::ALootActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALootActor::SetItem(TObjectPtr<UItemBase> InItemInstance)
{
	this->ItemInstance = InItemInstance;
	SetActorLabel(*(ItemInstance->Name.ToString()));
}

// Called when the game starts or when spawned
void ALootActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALootActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootActor.h"

#include "ItemBase.h"

// Sets default values
ALootActor::ALootActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMesh>(TEXT("Skeletal Mesh"));
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


// Copyright © 2023. KIM HYUN DEOK. All rights reserved.


#include "LootActor.h"

#include "Components/BoxComponent.h"

#include "ItemBase.h"

// Sets default values
ALootActor::ALootActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CapsuleComponent"));
	BoxComponent->InitBoxExtent({1.0f, 1.0f, 5.0f});
	BoxComponent->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->CanCharacterStepUpOn = ECB_Yes;
	RootComponent = BoxComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}

void ALootActor::SetItem(TObjectPtr<UItemBase> InItemInstance)
{
	this->ItemInstance = InItemInstance;
	SetActorLabel(*(ItemInstance->Name.ToString()));
}

void ALootActor::SetMesh(TObjectPtr<USkeletalMesh> InMesh)
{
	this->SkeletalMeshComponent->SetSkeletalMesh(InMesh);
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


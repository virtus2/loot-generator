// Copyright © 2023. KIM HYUN DEOK. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LootActor.generated.h"

class UItemBase;
class USkeletalMesh;

UCLASS()
class LOOTGEN_API ALootActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootActor();

	void SetItem(TObjectPtr<UItemBase> InItemInstance);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemBase> ItemInstance;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMesh> Mesh;

};

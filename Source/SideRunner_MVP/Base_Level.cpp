// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Level.h"

#include "Components/BoxComponent.h"

// Sets default values
ABase_Level::ABase_Level()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABase_Level::BeginPlay()
{
	Super::BeginPlay();

	if (Trigger != nullptr) {
		Trigger->bHiddenInGame = true;
	}
	
}

// Called every frame
void ABase_Level::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * ABase_Level::GetTrigger()
{
	return Trigger;
}

UBoxComponent * ABase_Level::GetSpawnLocation()
{
	return SpawnLocation;
}


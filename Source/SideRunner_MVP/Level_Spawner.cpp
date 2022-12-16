// Fill out your copyright notice in the Description page of Project Settings.


#include "Level_Spawner.h"

#include "Base_Level.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
ALevel_Spawner::ALevel_Spawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevel_Spawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);

}

// Called every frame
void ALevel_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevel_Spawner::SpawnLevel(bool isFirst)
{
	
	SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	SpawnRotation = FRotator(0, 90, 0);

	if (!isFirst) {
		ABase_Level* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(1, 5);
	ABase_Level* NewLevel = nullptr;

	
	//if hit trigger get new level
	if (NewLevel) {
		if (NewLevel->GetTrigger()) {
			NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevel_Spawner::OnOverlapBegin);
		}
	}

	//each level spawn selects a random number and then spawns a new level
	if (RandomLevel == 1) {
		NewLevel = GetWorld()->SpawnActor<ABase_Level>(Blueprint_Level1, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 2) {
		NewLevel = GetWorld()->SpawnActor<ABase_Level>(Blueprint_Level2, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 3) {
		NewLevel = GetWorld()->SpawnActor<ABase_Level>(Blueprint_Level3, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 4) {
		NewLevel = GetWorld()->SpawnActor<ABase_Level>(Blueprint_Level4, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	else if (RandomLevel == 5) {
		NewLevel = GetWorld()->SpawnActor<ABase_Level>(Blueprint_Level5, SpawnLocation, SpawnRotation, SpawnInfo);
	}
	if (NewLevel) {
		if (NewLevel->GetTrigger()) {
			NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ALevel_Spawner::OnOverlapBegin);
		}
	}

	//adds the new level to the level list
	LevelList.Add(NewLevel);

	//removes old levels so that they dont take up room in list
	if (LevelList.Num() > 5) {
		LevelList.RemoveAt(0);
	}
	

}

void ALevel_Spawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
}

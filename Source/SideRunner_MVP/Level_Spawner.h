// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Level_Spawner.generated.h"

class ABase_Level;

UCLASS()
class SIDERUNNER_MVP_API ALevel_Spawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevel_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
		void SpawnLevel(bool isFirst);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	APawn* Player;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABase_Level> Blueprint_Level1;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABase_Level> Blueprint_Level2;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABase_Level> Blueprint_Level3;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABase_Level> Blueprint_Level4;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABase_Level> Blueprint_Level5;

	TArray<ABase_Level*> LevelList;

public:

	int RandomLevel;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

};

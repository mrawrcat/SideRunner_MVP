// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spike.h"
#include "Death_Wall.generated.h"

/**
 * 
 */
UCLASS()
class SIDERUNNER_MVP_API ADeath_Wall : public ASpike
{
	GENERATED_BODY()
	
public:
	ADeath_Wall();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
};

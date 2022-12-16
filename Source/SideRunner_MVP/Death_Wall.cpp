// Fill out your copyright notice in the Description page of Project Settings.


#include "Death_Wall.h"

ADeath_Wall::ADeath_Wall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADeath_Wall::BeginPlay()
{
	Super::BeginPlay();
	this->GetRootComponent()->ComponentVelocity = FVector(0, 25, 0);
}

void ADeath_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + FVector(0, 350 * DeltaTime, 0));
}

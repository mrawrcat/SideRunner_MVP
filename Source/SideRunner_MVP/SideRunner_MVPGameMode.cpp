// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SideRunner_MVPGameMode.h"
#include "SideRunner_MVPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideRunner_MVPGameMode::ASideRunner_MVPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

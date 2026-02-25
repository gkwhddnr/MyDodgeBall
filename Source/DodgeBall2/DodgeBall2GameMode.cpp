// Copyright Epic Games, Inc. All Rights Reserved.

#include "DodgeBall2GameMode.h"
#include "DodgeBall2Character.h"
#include "UObject/ConstructorHelpers.h"

ADodgeBall2GameMode::ADodgeBall2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

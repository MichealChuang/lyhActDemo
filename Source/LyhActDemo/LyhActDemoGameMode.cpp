// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "LyhActDemoGameMode.h"
#include "LyhActDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALyhActDemoGameMode::ALyhActDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Common/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

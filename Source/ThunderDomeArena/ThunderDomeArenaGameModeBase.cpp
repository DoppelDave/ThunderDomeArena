// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThunderDomeArenaGameModeBase.h"
#include "Public/PlayerPawn.h"
#include "Public/InputController.h"
#include "Public/PlayerHud.h"

AThunderDomeArenaGameModeBase::AThunderDomeArenaGameModeBase()
{
	PlayerControllerClass = AInputController::StaticClass();
	DefaultPawnClass = APlayerPawn::StaticClass();
	HUDClass = APlayerHud::StaticClass();
}

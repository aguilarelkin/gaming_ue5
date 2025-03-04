// Copyright Epic Games, Inc. All Rights Reserved.

#include "Leyenda.h"

#include "MyCharacter.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, Leyenda, "Leyenda");

ALeyenda::ALeyenda()
{
	DefaultPawnClass =  AMyCharacter::StaticClass();
}

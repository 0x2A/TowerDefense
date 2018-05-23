// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerDefenseGameModeBase.h"
#include "Controllers/TDPlayerController.h"
#include "UI/TowerDefenseHUD.h"
#include "Pawns/TDPlayerPawn.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	PlayerControllerClass = ATDPlayerController::StaticClass();
	HUDClass = ATowerDefenseHUD::StaticClass();
	DefaultPawnClass = ATDPlayerPawn::StaticClass();

	
}


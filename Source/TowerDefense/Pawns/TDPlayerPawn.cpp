// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPlayerPawn.h"
#include "Camera\CameraComponent.h"


// Sets default values
ATDPlayerPawn::ATDPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mainCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mainCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ATDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATDPlayerPawn::UpdateCameraLocationAndRotation()
{
	
}

FVector ATDPlayerPawn::PointOnASphere(float radius, float angle, float height)
{
	float x = radius * FMath::Cos(angle) * FMath::Sin(height);
	float y = radius * FMath::Sin(angle) * FMath::Sin(height);
	float z = radius * FMath::Cos(height);
}


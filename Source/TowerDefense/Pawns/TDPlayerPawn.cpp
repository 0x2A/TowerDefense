// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ATDPlayerPawn::ATDPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mainCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	mainCamera->bUsePawnControlRotation = false;

	bRotateCamera = false;
	CameraRadius = 256.0f;
	CameraZAngle = 0.0f;
	CameraHeightAngle = 45.0f;
	RotateSpeed = 2.0f;
	ZoomSpeed = 16.0f;
	RadiusMin = 128.0f;
	RadiusMax = 2048.0f;
	MovementSpeed = 5.0f;
	EdgeForwardAxis = 0.0f;
	EdgeRightAxis = 0.0f;
}

// Called when the game starts or when spawned
void ATDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateCameraLocationAndRotation();
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

	PlayerInputComponent->BindAction("WheelMouseUp", IE_Pressed, this, &ATDPlayerPawn::OnWheelMouseUp);
	PlayerInputComponent->BindAction("WheelMouseDown", IE_Pressed, this, &ATDPlayerPawn::OnWheelMouseDown);

	PlayerInputComponent->BindAction("RotateCamera", IE_Pressed, this, &ATDPlayerPawn::OnRotateCameraPressed);
	PlayerInputComponent->BindAction("RotateCamera", IE_Released, this, &ATDPlayerPawn::OnRotateCameraReleased);

	PlayerInputComponent->BindAxis("MouseX", this, &ATDPlayerPawn::OnMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &ATDPlayerPawn::OnMouseY);
}


void ATDPlayerPawn::OnWheelMouseUp()
{
	 CameraRadius = FMath::Clamp(CameraRadius - ZoomSpeed, RadiusMin, RadiusMax);
	 UpdateCameraLocationAndRotation();
}

void ATDPlayerPawn::OnWheelMouseDown()
{
	CameraRadius = FMath::Clamp(CameraRadius + ZoomSpeed, RadiusMin, RadiusMax);
	UpdateCameraLocationAndRotation();
}


void ATDPlayerPawn::OnRotateCameraPressed()
{
	bRotateCamera = true;
}

void ATDPlayerPawn::OnRotateCameraReleased()
{
	bRotateCamera = false; 
}

void ATDPlayerPawn::OnMouseX(float dir)
{
	if (!bRotateCamera) return;

	CameraZAngle = dir * RotateSpeed + CameraZAngle;
	UpdateCameraLocationAndRotation();
}

void ATDPlayerPawn::OnMouseY(float dir)
{
	if (!bRotateCamera) return;

	CameraHeightAngle = FMath::Clamp(dir * RotateSpeed + CameraHeightAngle, 10.0f, 90.0f);
	UpdateCameraLocationAndRotation();
}

void ATDPlayerPawn::UpdateCameraLocationAndRotation()
{
	FVector location = PointOnASphere(CameraRadius, CameraZAngle, CameraHeightAngle);
	mainCamera->SetRelativeLocation(location);

	
	FRotator targetRotation = FRotationMatrix::MakeFromX(-mainCamera->RelativeLocation).Rotator();
	mainCamera->SetRelativeRotation(targetRotation);
}

FVector ATDPlayerPawn::PointOnASphere(float radius, float angle, float height)
{
	float angleRad = FMath::DegreesToRadians(angle);
	float heightRad = FMath::DegreesToRadians(height);
	float x = radius * FMath::Cos(angleRad) * FMath::Sin(heightRad);
	float y = radius * FMath::Sin(angleRad) * FMath::Sin(heightRad);
	float z = radius * FMath::Cos(heightRad);

	return FVector(x, y, z);
}



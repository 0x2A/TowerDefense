// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDPlayerPawn.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnWheelMouseUp();

	UFUNCTION(BlueprintCallable)
		void OnWheelMouseDown();

	UFUNCTION(BlueprintCallable)
		void OnRotateCameraPressed();
	
	UFUNCTION(BlueprintCallable)
		void OnRotateCameraReleased();

	UFUNCTION(BlueprintCallable)
		void OnMouseX(float dir);

	UFUNCTION(BlueprintCallable)
		void OnMouseY(float dir);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void UpdateCameraLocationAndRotation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraZAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraHeightAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		bool bRotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float RotateSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float ZoomSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float RadiusMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float RadiusMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float EdgeForwardAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float EdgeRightAxis;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent *mainCamera;

	FVector PointOnASphere(float radius, float angle, float height);
};

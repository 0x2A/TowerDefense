// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
		void OnShootTriggerOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
		void OnShootTriggerOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category="Gameplay")
		void UpdateGunRotation(float DeltaTIme);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ShootingRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool TargetLocked;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:



#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY(VisibleAnywhere)
		AActor* Target;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TowerBase;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TowerGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* ShootTriggerVolume;
};

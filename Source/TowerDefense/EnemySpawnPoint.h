// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void SpawnEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool SpawnAllowed;
	
	//Spawntime in ms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TSubclassOf<class AEnemyBase> TargetEnemyType;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* Arrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UBillboardComponent* Billboard;

	float timePassed;
};

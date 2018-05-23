// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnPoint.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "EnemyBase.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnAllowed = true;

	SpawnTime = 2000.0f;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	timePassed = 0;
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timePassed += DeltaTime;
	if (timePassed >= SpawnTime)
	{
		timePassed = 0;

	}
}



void AEnemySpawnPoint::SpawnEnemy()
{
	if (TargetEnemyType)
	{
		AEnemyBase *b = GetWorld()->SpawnActor<AEnemyBase>(TargetEnemyType, GetActorTransform(), FActorSpawnParameters());
		b->SetActorRotation(FRotationMatrix::MakeFromX(Arrow->GetForwardVector()).Rotator());
	}
}
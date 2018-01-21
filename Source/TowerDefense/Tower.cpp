// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShootingRange = 600.0f;

	TowerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TowerBase->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TowerGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerGun"));
	TowerGun->AttachToComponent(TowerBase, FAttachmentTransformRules::KeepWorldTransform, "GunSocket");

	ShootTriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("ShootTriggerVolume"));
	ShootTriggerVolume->SetRelativeLocation(FVector(0, 0, 270.0f));
	ShootTriggerVolume->AttachToComponent(TowerBase, FAttachmentTransformRules::KeepRelativeTransform);
	ShootTriggerVolume->SetSphereRadius(ShootingRange);
	
	
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR

void ATower::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);

	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ATower, ShootingRange)) {
		/* Because you are inside the class, you should see the value already changed */
		ShootTriggerVolume->SetSphereRadius(ShootingRange);
	}
}


#endif
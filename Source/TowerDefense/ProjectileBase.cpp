// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "TowerDefense.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetMobility(EComponentMobility::Movable);
	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetCollisionObjectType(COLLISION_PROJECTILE);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHitObject);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->UpdateComponentVelocity();
	

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::SetSpeed(float speed)
{
	ProjectileMovement->InitialSpeed = speed;
	ProjectileMovement->MaxSpeed = speed;
	ProjectileMovement->UpdateComponentVelocity();
}

void AProjectileBase::OnHitObject_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!(OtherActor && (OtherActor != this) && OtherComp)) return;

	if (OtherActor->IsA(APawn::StaticClass()))
	{
		APawn *p = Cast<APawn>(OtherActor);
		FDamageEvent damageEvent;
		
		p->TakeDamage(BaseDamage, damageEvent, nullptr, this);
	}
}


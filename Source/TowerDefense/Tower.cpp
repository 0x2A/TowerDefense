// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "TowerDefense.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectileBase.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShootingRange = 600.0f;

	InitialShootDelay = 1.0f;
	ShootDelay = 0.5f;
	ProjectileSpeed = 2000.0f;

	TowerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TowerBase->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TowerGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerGun"));
	TowerGun->AttachToComponent(TowerBase, FAttachmentTransformRules::KeepWorldTransform, "GunSocket");

	ShootTriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("ShootTriggerVolume"));
	ShootTriggerVolume->SetRelativeLocation(FVector(0, 0, 270.0f));
	ShootTriggerVolume->AttachToComponent(TowerBase, FAttachmentTransformRules::KeepRelativeTransform);
	ShootTriggerVolume->SetSphereRadius(ShootingRange);
	ShootTriggerVolume->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Ignore);

	ShootTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnShootTriggerOverlapBegin);
	ShootTriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATower::OnShootTriggerOverlapEnd);
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

	UpdateGunRotation(DeltaTime);

}


void ATower::UpdateGunRotation(float DeltaTime)
{
	if (TargetLocked && Target)
	{
		//lock rotation to target
		FRotator rot = FRotationMatrix::MakeFromX(Target->GetActorLocation() - TowerGun->GetComponentLocation()).Rotator();
		rot.Roll = 0; //dont roll our gun, this will look stupid ;)
		rot.Pitch = FMath::Clamp(rot.Pitch, -30.0f, 30.0f);
		TowerGun->SetWorldRotation(UKismetMathLibrary::RInterpTo(TowerGun->GetComponentRotation(), rot, DeltaTime, 10.f));
	}
	else
	{
		//return to "idle" position
		FRotator rot = TowerGun->GetComponentRotation();
		rot.Roll = 0.0f;
		rot.Pitch = 0.0f;
		rot.Yaw = rot.Yaw + 2.0f;

		TowerGun->SetWorldRotation(UKismetMathLibrary::RInterpTo(TowerGun->GetComponentRotation(), rot, DeltaTime, 10.f));
	}
}

void ATower::Shoot()
{
	GetWorldTimerManager().SetTimer(ShootingDelayTimer, this, &ATower::InternalShoot, ShootDelay, true, InitialShootDelay);
}


void ATower::InternalShoot()
{

	if (ProjectileClass)
	{
		FTransform trans = TowerGun->GetSocketTransform("BarrelEnd");
		AProjectileBase *a = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, trans, FActorSpawnParameters());
		a->SetSpeed(ProjectileSpeed);
	}

	if (!TargetLocked)
		GetWorldTimerManager().ClearTimer(ShootingDelayTimer);
}

void ATower::OnShootTriggerOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		Target = OtherActor;
		TargetLocked = true;
		UpdateGunRotation(GetWorld()->GetDeltaSeconds());
		Shoot();
	}
}

void ATower::OnShootTriggerOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp && Target == OtherActor)
	{
		TargetLocked = false;
		Target = nullptr;
	}
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
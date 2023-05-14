// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Character/MyALSCharacter.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{

	PrimaryActorTick.bCanEverTick = false;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->InitialSpeed = 1000.f;
    ProjectileMovementComponent->MaxSpeed = 2000.f;

}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage
		(
			OtherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass
		);

		Destroy();
	}
}


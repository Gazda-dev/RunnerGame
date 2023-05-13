// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Character/MainCharacter.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{

	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
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
	
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
		{
			auto MyOwnerInstigator = MyOwner->GetInstigatorController();
			auto DamageTypeClass = UDamageType::StaticClass();
			
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
}

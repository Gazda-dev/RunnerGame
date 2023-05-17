// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthSausage.h"
#include "Components/CapsuleComponent.h"
#include "Character/MyALSCharacter.h"
#include "Kismet/GameplayStatics.h"

AHealthSausage::AHealthSausage()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule collider"));
	RootComponent = CapsuleCollider;

	SausageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh"));
	SausageMesh->SetupAttachment(GetRootComponent());

}

void AHealthSausage::BeginPlay()
{
	Super::BeginPlay();
	
	UCapsuleComponent* CapsuleCollision = Cast<UCapsuleComponent>(RootComponent);
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthSausage::OnOverlapBegin);
}


void AHealthSausage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AHealthSausage::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyALSCharacter::StaticClass()))
	{
		if (CollectSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
		}
		if (AMyALSCharacter* MainCharacter = Cast<AMyALSCharacter>(OtherActor))
		{
			MainCharacter->Health++;
			UE_LOG(LogTemp, Display, TEXT("Health added: %f"), MainCharacter->Health);
			Destroy();
		}
	}
}
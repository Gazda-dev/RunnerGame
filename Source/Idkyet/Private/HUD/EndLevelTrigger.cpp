// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EndLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Character/MyALSCharacter.h"

AEndLevelTrigger::AEndLevelTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelTrigger::OnBoxColliderOverlap);

}

void AEndLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEndLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLevelTrigger::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyALSCharacter* Character = Cast<AMyALSCharacter>(OtherActor))
	{
		Character->SavingGame(true);
	}
	//widget
}


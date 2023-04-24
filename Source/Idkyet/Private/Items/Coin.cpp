// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Coin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Character/MainCharacter.h"


// Sets default values
ACoin::ACoin()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(50.f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	Value = 1;
}

void ACoin::SetScoreManager(UScoreManager* InScoreManager)
{
	ScoreManager = InScoreManager;
}


void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
	USphereComponent* CollisionComponent = Cast<USphereComponent>(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		MainCharacter->AddCoins(Value);
		Destroy();
	}
}





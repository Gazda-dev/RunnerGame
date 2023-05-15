// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Collider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MyALSCharacter.h"

ACollider::ACollider()
{

	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ACollider::OnBoxColliderOverlap);

}


void ACollider::BeginPlay()
{
	Super::BeginPlay();

}

void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveWall();
}
void ACollider::MoveWall()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation + FVector(WallSpeed, 0.f, 0.f);
	SetActorLocation(TargetLocation);
}

void ACollider::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMyALSCharacter* MainCharacter = Cast<AMyALSCharacter>(OtherActor))
	{
		if (MainCharacter->bIsInLevel)
		{
			MainCharacter->SetActorLocation(MainCharacter->StartPosition);
			UE_LOG(LogTemp, Display, TEXT("bisinlevel true, teleporting..."));
			MainCharacter->RagdollEnd();
		}
	}
}





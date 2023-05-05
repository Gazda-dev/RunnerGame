// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Collider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


ACollider::ACollider()
{

	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}


void ACollider::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, [this]() { MoveWall(GetWorld()->GetDeltaSeconds()); }, 0.2f, true);
}

void ACollider::MoveWall(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation + FVector(WallSpeed, 0.f, 0.f);
	FVector InterpolatedLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, InterpolatedSpeed);
	SetActorLocation(InterpolatedLocation);
}


void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


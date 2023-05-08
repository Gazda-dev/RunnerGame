// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Collider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


ACollider::ACollider()
{

	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxCollider;

}


void ACollider::BeginPlay()
{
	Super::BeginPlay();

}

void ACollider::MoveWall()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation + FVector(WallSpeed, 0.f, 0.f);
	SetActorLocation(TargetLocation);
}


void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveWall();
}


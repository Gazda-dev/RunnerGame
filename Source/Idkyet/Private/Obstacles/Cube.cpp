// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Cube.h"
#include "Components/BoxComponent.h"

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = Box;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ItemMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	AddActorWorldOffset(FVector(TransformedCos(), 0.f, TransformedSin()));
}

float ACube::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float ACube::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}



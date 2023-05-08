// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/RotationObject.h"

// Sets default values
ARotationObject::ARotationObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = ItemMesh;
}

// Called when the game starts or when spawned
void ARotationObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotationObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotator = GetActorRotation();
	FRotator NewRotator = FRotator(CurrentRotator.Pitch, CurrentRotator.Yaw + YawRotation, CurrentRotator.Roll);
	SetActorRotation(NewRotator);
}


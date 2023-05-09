// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Trampoline.h"
#include "Character/MainCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrampoline::ATrampoline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ItemMesh->SetupAttachment(GetRootComponent());

	JumpForce = 2000.f;
}

// Called when the game starts or when spawned
void ATrampoline::BeginPlay()
{
	Super::BeginPlay();
	
	UBoxComponent* CollisionComponent = Cast<UBoxComponent>(RootComponent);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATrampoline::OnOverlapBegin);
}

void ATrampoline::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Overlapppped"));
		FVector JumpDirection = SweepResult.Normal;
		JumpDirection.Z = FMath::Abs(JumpDirection.Z);
		MainCharacter->LaunchCharacter(JumpDirection * JumpForce, false, false);
	}
}

// Called every frame
void ATrampoline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


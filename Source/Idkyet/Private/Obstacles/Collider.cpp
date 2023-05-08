// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Collider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/SG_SaveGame.h"
#include "Character/MainCharacter.h"

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
	USG_SaveGame* SaveGame = Cast<USG_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveGame"), 0));
	UE_LOG(LogTemp, Warning, TEXT("Loaded"));
	int32 BestDistance = 0;
	int32 BestCoins = 0;
	if (SaveGame)
	{
		BestDistance = SaveGame->BestDistance;
		BestCoins = SaveGame->BestCoins;
	}

	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor))
	{
		int32 CurrentDistance = MainCharacter->GetTotalDistancemoved();
		int32 CurrentCoins = MainCharacter->GetTotalValue();
		if (CurrentDistance > BestDistance)
		{
			BestDistance = CurrentDistance;
		}
		if (CurrentCoins > BestCoins)
		{
			BestCoins = CurrentCoins;
		}
	}
	
	USG_SaveGame* NewScoreSaveGame = Cast<USG_SaveGame>(UGameplayStatics::CreateSaveGameObject(USG_SaveGame::StaticClass()));
	NewScoreSaveGame->BestDistance = BestDistance;
	NewScoreSaveGame->BestCoins = BestCoins;
	UGameplayStatics::SaveGameToSlot(NewScoreSaveGame, TEXT("ScoreSaveGame"), 0);
	UE_LOG(LogTemp, Warning, TEXT("Saved"));


	UE_LOG(LogTemp, Warning, TEXT("BestDistance %d"), BestDistance);
	UE_LOG(LogTemp, Warning, TEXT("BestCoins %d"), BestCoins);


	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		Character->Destroy();
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
	}
}





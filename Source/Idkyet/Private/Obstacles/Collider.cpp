// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Collider.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Saving/SG_SaveGame.h"
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
	USG_SaveGame* SaveGame = Cast<USG_SaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("ScoreSaveGame"), 0));
	UE_LOG(LogTemp, Warning, TEXT("Loaded"));
	int32 BestDistance = 0;
	int32 BestCoins = 0;
	if (SaveGame)
	{
		BestDistance = SaveGame->BestDistance;
		BestCoins = SaveGame->BestCoins;
	}

	if (AMyALSCharacter* MainCharacter = Cast<AMyALSCharacter>(OtherActor))
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

		if (MainCharacter->bIsInLevel)
		{
			MainCharacter->SetActorLocation(MainCharacter->StartPosition);
			UE_LOG(LogTemp, Display, TEXT("bisinlevel true, teleporting..."));
		}
	}
	
	USG_SaveGame* NewScoreSaveGame = Cast<USG_SaveGame>(UGameplayStatics::CreateSaveGameObject(USG_SaveGame::StaticClass()));
	NewScoreSaveGame->BestDistance = BestDistance;
	NewScoreSaveGame->BestCoins = BestCoins;
	UGameplayStatics::SaveGameToSlot(NewScoreSaveGame, TEXT("ScoreSaveGame"), 0);
	UE_LOG(LogTemp, Warning, TEXT("Saved"));


}





// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class UScoreManager;
class USphereComponent;
class UStaticMeshComponent;
//class USoundBase;

UCLASS()
class IDKYET_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ACoin();

	void SetScoreManager(UScoreManager* InScoreManager);

protected:
	
	virtual void BeginPlay() override;
 
private:

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Coin_cpp")
	int32 Value;

	UScoreManager* ScoreManager;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Coin #cpp")
	USoundBase* CollectSound;
};

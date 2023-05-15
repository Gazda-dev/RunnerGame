// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndLevelTrigger.generated.h"

UCLASS()
class IDKYET_API AEndLevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	

	AEndLevelTrigger();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components #cpp")
	class UBoxComponent* BoxCollider;

	UFUNCTION()
		void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

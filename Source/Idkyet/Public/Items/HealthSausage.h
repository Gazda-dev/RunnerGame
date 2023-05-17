// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthSausage.generated.h"

class UCapsuleComponent;

UCLASS()
class IDKYET_API AHealthSausage : public AActor
{
	GENERATED_BODY()
	
public:	

	AHealthSausage();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleCollider;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SausageMesh;

	UPROPERTY(EditAnywhere, Category = "Heatlh #cpp")
	USoundBase* CollectSound;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

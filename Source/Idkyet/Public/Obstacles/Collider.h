// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collider.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class IDKYET_API ACollider : public AActor
{
	GENERATED_BODY()
	
public:	

	ACollider();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_cpp")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components_cpp")
	UBoxComponent* BoxCollider;

	void MoveWall();

	UPROPERTY(EditAnywhere, Category = "Wall_cpp")
	float WallSpeed = 100.f;

private:

	UFUNCTION()
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

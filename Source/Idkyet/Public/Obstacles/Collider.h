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

	void MoveWall(float DeltaTime);

	UPROPERTY(EditAnywhere, Category = "Wall_cpp")
	float WallSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Wall_cpp")
	float InterpolatedSpeed = 1000.f;

private:
	FTimerHandle TimerHandle;




};

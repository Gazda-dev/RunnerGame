// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class IDKYET_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	float TransformedSin();

	UFUNCTION()
	float TransformedCos();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine params")
	float Amplitude = 0.25f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine params")
	float TimeConstant = 5.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Params", meta = (AllowPrivateAccess = "true"))
	float RunningTime;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/JumpMontageEndNotify.h"
#include "Character/MyALSCharacter.h"

void UJumpMontageEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* Actor = MeshComp->GetOwner();
	if (!Actor) return;
	if (AMyALSCharacter* Character = Cast<AMyALSCharacter>(Actor))
	{
		Character->OnJumpMontageEnd();
	}
}

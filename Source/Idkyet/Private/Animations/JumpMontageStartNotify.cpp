// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/JumpMontageStartNotify.h"
#include "Character/MyALSCharacter.h"

void UJumpMontageStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* Actor = MeshComp->GetOwner();
	if (!Actor) return;
	if (AMyALSCharacter* Character = Cast<AMyALSCharacter>(Actor))
	{
		Character->OnJumpMontageStart();
	}
}

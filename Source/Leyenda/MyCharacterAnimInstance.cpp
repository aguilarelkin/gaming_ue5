// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	// Obtener referencia al personaje
	APawn* OwnerPawn = TryGetPawnOwner();
	if (!OwnerPawn) return;

	// Obtener la velocidad del personaje
	Speed = OwnerPawn->GetVelocity().Size();
	
	ACharacter* Character = Cast<ACharacter>(OwnerPawn);
	if (!Character) return;

	// Obtener velocidad y determinar si se está moviendo
	Speed = Character->GetVelocity().Size();
	bIsMoving = Speed > 3.0f;

	// Determinar si está en el aire
	bIsInAir = Character->GetCharacterMovement()->IsFalling();

	// Determinar si está agachado
	bIsCrouching = Character-> bIsCrouched;
}

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

	const ACharacter* Character = Cast<ACharacter>(OwnerPawn);
	if (!Character) return;

	// Obtener velocidad y determinar si se está moviendo
	Speed = Character->GetVelocity().Size();
	bIsMoving = Speed > 3.0f && Speed <= 200.0f;

	// Determinar si está en el aire
	bIsInAir = Character->GetCharacterMovement()->IsFalling();
	// Determinar si está agachado
	bIsCrouching = Character->bIsCrouched;
	/*if (bIsCrouching && Speed < 3.0f)
	{
		Speed = 0.0f; // Para asegurar que entre en el estado de Crouched Idle
	}*/
	// Verificar si el personaje está corriendo (por ejemplo, si la velocidad es mayor a 600)
	bIsRunning = Speed > 200.0f;

	/*UE_LOG(LogTemp, Warning, TEXT("Velocidad en Animation BP: %hhd"), bIsInAir);
	UE_LOG(LogTemp, Warning, TEXT("Velocidadss en Animation BP: %hhd"), bIsCrouching);*/
}

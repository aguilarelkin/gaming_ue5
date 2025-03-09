// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEYENDA_API UMyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Variables para las animaciones
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsCrouching;

	// Actualizar variables cada frame
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

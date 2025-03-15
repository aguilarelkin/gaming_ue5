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
	// Velocidad del personaje
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float Speed;

	// Indica si el personaje se está moviendo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsMoving;

	// Indica si el personaje está en el aire
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsInAir;

	// Indica si el personaje está agachado
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool bIsRunning;
	// Función de actualización por frame
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

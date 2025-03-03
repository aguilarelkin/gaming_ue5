// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class LEYENDA_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Funciones para caminar
	void MoveForward(float Value);
	void MoveRight(float Value);
	// Funciones para controlar la cámara con el mouse
	void Turn(float Value);
	void LookUp(float Value);

	//Variable de sensibilidad del mouse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float MouseSensitivity = 1.5f; // 🔥 Valor por defecto (ajústalo a tu gusto)

	//Funciones para saltar
	void StartJump();
	void StopJump();
};

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 900.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bLsRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bLsCrouchToggled = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Variable de sensibilidad del mouse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float MouseSensitivity = 1.5f; // Valor por defecto
private:
	float DefaultCapsuleHalfHeight;
	// Cámara en tercera persona
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FollowCamera;
	// Para acumular el offset del yaw de la cámara cuando el personaje está quieto
	float CameraYawOffset = 0.0f;
	// Para saber si se está moviendo (asegúrate de que esté declarado)
	bool bIsMoving = false;

	// Funciones para caminar
	void MoveForward(float Value);
	void MoveRight(float Value);
	// Funciones para controlar la cámara con el mouse
	void Turn(float Value);
	void LookUp(float Value);

	//Funciones para saltar
	void StartJump();
	void StopJump();
	// Funciones para agacharse
	void ToggleCrouch();
	/*void StartCrouch();
	void StopCrouch();*/

	//funciones para run
	void StartRunning();
	void StopRunning();
	void ToggleRun();
};

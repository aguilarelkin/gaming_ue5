// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crear el brazo de la cámara (SpringArm) para tercera persona
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // Distancia de la cámara al personaje
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 150.0f);
	CameraBoom->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;

	// Crear la cámara de seguimiento
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	// Configuración de rotación del personaje
	bUseControllerRotationYaw = false; // El personaje no debe rotar automáticamente con el controlador

	// Configuración del movimiento del personaje
	GetCharacterMovement()->bOrientRotationToMovement = true; // El personaje rota hacia la dirección del movimiento
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // Velocidad de rotación del personaje

	//velocidad al caminar
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	// Guardar la altura original de la cápsula
	DefaultCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bindear los eventos de mover o caminar
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	// Bindear los eventos de entrada del mouse
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	// Bindear el salto
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJump);
	// Bindear el agachado
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::ToggleCrouch);
	/*PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);*/

	//Binder run
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::ToggleRun);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRunning);
}

void AMyCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
		bIsMoving = true;
	}
	else
	{
		bIsMoving = false;
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
		bIsMoving = true;
	}
	else
	{
		bIsMoving = false;
	}
}

void AMyCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::StartJump()
{
	if (bLsCrouchToggled)
	{
		bLsCrouchToggled = false;
		UnCrouch();
	}
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::ToggleCrouch()
{
	bLsCrouchToggled = !bLsCrouchToggled;
	if (bLsCrouchToggled) // Si ya está agachado, se levanta
	{
		Crouch();
	}
	else // Si no está agachado, se agacha
	{
		UnCrouch();
	}
}

/*void AMyCharacter::StartRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	UE_LOG(LogTemp, Warning, TEXT("Velocidad en Animation BP: start"));
}

void AMyCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	UE_LOG(LogTemp, Warning, TEXT("Velocidad en Animation BP: stop"));
}*/

void AMyCharacter::ToggleRun()
{
	bLsRunning = !bLsRunning;
	GetCharacterMovement()->MaxWalkSpeed = bLsRunning ? RunSpeed : WalkSpeed;
}

/*void AMyCharacter::StartCrouch()
{
	Crouch();
}

void AMyCharacter::StopCrouch()
{
	UnCrouch();
	//GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight);
}*/

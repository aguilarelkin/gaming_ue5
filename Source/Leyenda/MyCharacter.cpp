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
	CameraBoom->TargetArmLength = 210.0f; // Distancia de la cámara al personaje
	CameraBoom->bUsePawnControlRotation = true;

	// Configuración del SpringArm
	CameraBoom->bUsePawnControlRotation = true; // El SpringArm debe rotar con el controlador
	CameraBoom->bInheritPitch = true; // Heredar rotación de pitch (arriba/abajo)
	CameraBoom->bInheritYaw = true; // Heredar rotación de yaw (izquierda/derecha)
	CameraBoom->bInheritRoll = false; // No heredar rotación de roll

	// Crear la cámara de seguimiento
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // La cámara no debe rotar con el controlador

	// Configuración de rotación del personaje
	bUseControllerRotationYaw = false; // El personaje no debe rotar automáticamente con el controlador
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	// Configuración del movimiento del personaje
	GetCharacterMovement()->bOrientRotationToMovement = true; // El personaje rota hacia la dirección del movimiento
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 140.0f, 0.0f); // Velocidad de rotación del personaje


	//velocidad al caminar
	GetCharacterMovement()->MaxWalkSpeed = 700.f;
	// Permitir que el personaje use control de rotación basado en el controlador
	// Guardar la altura original de la cápsula
	DefaultCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	// Asegurar que el MeshComponent esté disponible
	MeshComponent = GetMesh();

	// Asignar el Skeletal Mesh del maniquí
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/StarterContent/Maniqui"));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetSkeletalMesh(MeshAsset.Object);
		MeshComponent->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);
}

void AMyCharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		FVector Direction = GetActorForwardVector();

		// Evitar que el personaje rote si está moviéndose hacia atrás
		if (Value < 0.0f)
		{
			GetCharacterMovement()->bOrientRotationToMovement = false;
		}
		else
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}

		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
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
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::StartCrouch()
{
	Crouch();
	// Reducir la cápsula al 50% de su tamaño original
	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight * 0.5f);
}

void AMyCharacter::StopCrouch()
{
	UnCrouch();
	// Restaurar la altura original al 100%
	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleHalfHeight);
}

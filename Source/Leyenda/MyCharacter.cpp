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

	/*// Configuración del SpringArm
	CameraBoom->bInheritPitch = false; // Heredar rotación de pitch (arriba/abajo)
	CameraBoom->bInheritYaw = true; // Heredar rotación de yaw (izquierda/derecha)
	CameraBoom->bInheritRoll = false; // No heredar rotación de roll
	CameraBoom->bEnableCameraLag = true; // Retraso suave al seguir al personaje
	CameraBoom->CameraLagSpeed = 5.0f; // Velocidad de ajuste de la cámara*/

	// Crear la cámara de seguimiento
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	// Configuración de rotación del personaje
	bUseControllerRotationYaw = false; // El personaje no debe rotar automáticamente con el controlador
	/*bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;*/
	// Configuración del movimiento del personaje
	GetCharacterMovement()->bOrientRotationToMovement = true; // El personaje rota hacia la dirección del movimiento
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // Velocidad de rotación del personaje


	//velocidad al caminar
	GetCharacterMovement()->MaxWalkSpeed = 900.f;
	// Guardar la altura original de la cápsula
	DefaultCapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

	/*// Asegurar que el MeshComponent esté disponible
	MeshComponent = GetMesh();

	// Asignar el Skeletal Mesh del maniquí
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/StarterContent/Maniqui/Unarmed_Grab_Torch_From_Wall"));

	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetSkeletalMesh(MeshAsset.Object);
		MeshComponent->SetupAttachment(RootComponent);
	}*/
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

	/*if (Controller)
	{
		if (bIsMoving)
		{
			// Cuando se mueve: 
			// - El actor rota hacia la rotación del controlador.
			FRotator ControlRotation = Controller->GetControlRotation();
			FRotator TargetRotation(0.0f, ControlRotation.Yaw, 0.0f);
			SetActorRotation(TargetRotation);

			// Reiniciamos el offset de la cámara para que quede justo detrás del actor.
			CameraYawOffset = 0.0f;

			// Fijamos la cámara (spring arm) con rotación relativa cero para que esté detrás.
			CameraBoom->SetRelativeRotation(FRotator::ZeroRotator);
		}
		/*else
		{
			// Cuando está quieto: el actor conserva su rotación.
			// Actualizamos la rotación relativa del CameraBoom según el offset acumulado.
			FRotator RelativeRotation = FRotator(0.0f, CameraYawOffset, 0.0f);
			CameraBoom->SetRelativeRotation(RelativeRotation);
		}#1#
	}*/
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
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);

		// Solo girar si el personaje se está moviendo
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

		// Solo girar si el personaje se está moviendo
		bIsMoving = true;
	}
	else
	{
		bIsMoving = false;
	}
}

void AMyCharacter::Turn(float Value)
{
	/*if (bIsMoving)
	{
		// Si se mueve, aplicamos la entrada al controlador (y por ende al actor)
		AddControllerYawInput(Value);
	}
	else
	{
		// Si está quieto, acumulamos el offset para la cámara
		CameraYawOffset += Value;
	}*/
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

#include "COAAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"

ACOAAvatar::ACOAAvatar()
{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->TargetArmLength = 300.0f;
	mSpringArm->SetupAttachment(RootComponent);
	mSpringArm->SocketOffset = FVector(0.0f, 0.0f, 75.0f);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	StaminaGainRate = 10.0f;
	StaminaDrainRate = 20.0f;
	RunSpeed = 600.0f;
	bStaminaDrained = false;
	bRunning = false;
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bIsWalkingOnGround = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking;
	bool bIsMoving = GetVelocity().Size() > 0;

	if (bRunning && bIsMoving && bIsWalkingOnGround && !bStaminaDrained)
	{
		Stamina = FMath::Clamp(Stamina - (StaminaDrainRate * DeltaTime), 0.0f, MaxStamina);

		if (Stamina <= 0.0f)
		{
			bStaminaDrained = true;
			UpdateMovementParams();
		}
	}
	else
	{
		Stamina = FMath::Clamp(Stamina + (StaminaGainRate * DeltaTime), 0.0f, MaxStamina);

		if (bStaminaDrained && Stamina >= MaxStamina)
		{
			bStaminaDrained = false;
			UpdateMovementParams();
		}
	}
}

void ACOAAvatar::UpdateMovementParams()
{
	if (bStaminaDrained || !bRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ACOAAvatar::RunPressed()
{
	bRunning = true;
	UpdateMovementParams();
}

void ACOAAvatar::RunReleased()
{
	bRunning = false;
	UpdateMovementParams();
}

void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void ACOAAvatar::MoveForward(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACOAAvatar::MoveRight(float Value)
{
	if (Controller && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
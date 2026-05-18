#include "COABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ACOABaseCharacter::ACOABaseCharacter() :
	bDead(false),
	Health(100.0f),
	MaxHealth(100.0f),
	HealingRate(0.0f),
	WalkSpeed(300.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead)
	{
		Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
	}
}
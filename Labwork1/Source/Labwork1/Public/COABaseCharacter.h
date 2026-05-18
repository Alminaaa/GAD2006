#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "COABaseCharacter.generated.h"

UCLASS()
class LABWORK1_API ACOABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACOABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	float Health;

	UPROPERTY(EditAnywhere, Category = "COA")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float HealingRate;

	UPROPERTY(EditAnywhere, Category = "COA")
	float WalkSpeed;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"

UCLASS()
class LABWORK1_API ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()

public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* mSpringArm;

	UPROPERTY(EditAnywhere, Category = "COA")
	float RunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "COA")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "COA")
	float StaminaGainRate;

	UPROPERTY(EditAnywhere, Category = "COA")
	float StaminaDrainRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	bool bStaminaDrained;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	bool bRunning;

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void RunPressed();
	void RunReleased();

	void UpdateMovementParams();
};
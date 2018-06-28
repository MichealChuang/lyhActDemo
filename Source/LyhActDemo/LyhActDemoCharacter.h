// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerStats.h"
#include "LyhActDemoCharacter.generated.h"

UCLASS(config=Game)
class ALyhActDemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALyhActDemoCharacter();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Jump() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	int32 ComboNum = 0;
	int8 LeftVector = 0;
	int8 RightVextor = 0;
	int32 MaxMagic;
	UPROPERTY(BlueprintReadWrite)
	FPlayerStats PlayerStates;
	/***********************state********************/
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsDodging = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsDefencing = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsDeath = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsAttacking = false;
	bool bIsAttacked = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bCanDamage = 0;
	/***********************state********************/

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Fast_One;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Fast_Two;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Fast_Three;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Back;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_HeadTop_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_HeadTop_Right;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_HeadDown_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_HeadDown_Right;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Torso_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Torso_Right;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Torso_Front;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Leg_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Hit_Leg_Right;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Dodge_Left;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Dodge_Right;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Dodge_Behind;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Defence_Start;
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* Defence_Succeed;

	FTimerHandle ComboHandle;
	FTimerHandle DodgeHandle;
	FTimerHandle HurtHandle;
	FTimerHandle RegainHandle;
public:
	UFUNCTION(BlueprintCallable)
	void AttackEnemy();
	void Dodge();
	UFUNCTION(BlueprintCallable)
	void OnAttacked(FVector AttackPoint);
	UFUNCTION()
	void OnAttackComplete();
	UFUNCTION()
	void OnDodgeComplete();
	UFUNCTION()
	void Defence_Begin();
	UFUNCTION()
	void Defence_End();
	UFUNCTION(BlueprintCallable)
	void OnBounced();
	UFUNCTION()
	void OnHurtComplete();
	UFUNCTION()
	void RegainMagic();

	UFUNCTION(BlueprintImplementableEvent)
	void DeathToReborn();
	UFUNCTION(BlueprintCallable)
	ACharacter* CheckAI(float RotationRate, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);

};


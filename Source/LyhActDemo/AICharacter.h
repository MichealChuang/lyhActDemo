// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerStats.h"
#include "AICharacter.generated.h"

UCLASS(config = Game)
class AAICharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AAICharacter();
public:
	int32 ComboNum = 0;
	int8 LeftVector = 0;
	int8 RightVextor = 0;
	UPROPERTY(BlueprintReadWrite)
	FPlayerStats AIStats;

	/***********************state********************/
	bool bIsDodging = false;
	bool bIsDefencing = false;
	bool bIsDeath = false;
	bool bIsAttacked = false;
	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bIsAttacking = false;
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
	void OnHurtComplete();
	UFUNCTION()
	void Defence_Begin();
	UFUNCTION()
	void Defence_End();
	UFUNCTION(BlueprintCallable)
	void OnBounced();
	UFUNCTION(BlueprintImplementableEvent)
	void DeathToReborn();
};


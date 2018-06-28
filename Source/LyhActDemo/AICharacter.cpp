// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AICharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "ConstructorHelpers.h"


AAICharacter::AAICharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	static ConstructorHelpers::FObjectFinder<UDataTable> AIDataObject(TEXT("/Game/Common/stats"));
	if (AIDataObject.Object)
	{
		AIStats = *AIDataObject.Object->FindRow<FPlayerStats>(TEXT("AI"), TEXT(""));
	}
}

void AAICharacter::AttackEnemy()
{
	if (bIsAttacking || GetMovementComponent()->IsFalling() || bIsDodging || bIsDefencing || bIsAttacked)
	{
		return;
	}
	bIsAttacking = true;
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("LeftButton"));
	bCanDamage = 0;

	switch (ComboNum)
	{
	case 0:
		if (Fast_One)
		{
			float Deruction = PlayAnimMontage(Fast_One);
			ComboNum++;
			GetWorldTimerManager().SetTimer(ComboHandle, this, &AAICharacter::OnAttackComplete, Deruction);
		}
		break;
	case 1:
		if (Fast_Two)
		{
			GetWorldTimerManager().ClearTimer(ComboHandle);
			float Deruction = PlayAnimMontage(Fast_Two);
			ComboNum++;
			GetWorldTimerManager().SetTimer(ComboHandle, this, &AAICharacter::OnAttackComplete, Deruction);
		}
		break;
	case 2:
		if (Fast_Three)
		{
			GetWorldTimerManager().ClearTimer(ComboHandle);
			PlayAnimMontage(Fast_Three);
			ComboNum = 0;
		}
		break;
	}

}

void AAICharacter::Dodge()
{
	if (bIsDefencing || GetMovementComponent()->IsFalling() || bIsDodging)
	{
		return;
	}
	GetMesh()->Stop();
	if (bIsAttacking)
	{
		OnAttackComplete();
		bIsAttacking = false;
		bCanDamage = 0;
	}
	bIsAttacked = false;
	GetWorldTimerManager().ClearTimer(HurtHandle);
	bIsDodging = true;
	float Duration = 0;
	if (RightVextor > LeftVector)
	{
		if (Dodge_Right)
		{
			Duration = PlayAnimMontage(Dodge_Right);
		}
	}
	else if (RightVextor < LeftVector)
	{
		Duration = PlayAnimMontage(Dodge_Left);
	}
	else
	{
		Duration = PlayAnimMontage(Dodge_Behind);
	}
	GetWorldTimerManager().SetTimer(DodgeHandle, this, &AAICharacter::OnDodgeComplete, Duration);
}

void AAICharacter::OnAttacked(FVector AttackPoint)
{
	if (bIsDodging)
	{
		return;
	}
	if (bIsDefencing)
	{
		if (Defence_Succeed)
		{
			PlayAnimMontage(Defence_Succeed);
		}
		Defence_End();
	}
	else
	{
		if (bIsAttacking)
		{
			bIsAttacking = false;
			bCanDamage = false;
		}
		bIsAttacked = true;
		GetWorldTimerManager().SetTimer(HurtHandle, this, &AAICharacter::OnHurtComplete, 1.5f);
		GetMesh()->Stop();
		FTransform CharacterTrans = GetActorTransform();
		FVector CharacterLocation = CharacterTrans.GetLocation();
		FVector Direction = UKismetMathLibrary::InverseTransformLocation(CharacterTrans, AttackPoint);;
		if (AttackPoint.Z > CharacterLocation.Z + 53)
		{
			if (Direction.Y > 0)
			{
				if (Direction.X > 0)
				{
					if (Hit_HeadTop_Left) PlayAnimMontage(Hit_HeadTop_Left);
				}
				else
				{
					if (Hit_HeadTop_Right) PlayAnimMontage(Hit_HeadTop_Right);
				}
			}
			else
			{
				if (Hit_Back) PlayAnimMontage(Hit_Back);
			}
			AIStats.Blood -= 10 * 2;
		}
		else if (AttackPoint.Z > CharacterLocation.Z + 36)
		{
			if (Direction.Y > 0)
			{
				if (Direction.X > 0)
				{
					if (Hit_HeadDown_Left) PlayAnimMontage(Hit_HeadDown_Left);
				}
				else
				{
					if (Hit_HeadDown_Right) PlayAnimMontage(Hit_HeadDown_Right);
				}
			}
			else
			{
				if (Hit_Back) PlayAnimMontage(Hit_Back);
			}
			AIStats.Blood -= 10 * 2;
		}
		else if (AttackPoint.Z > CharacterLocation.Z)
		{
			if (Direction.Y > 0)
			{
				if (Direction.X > 10)
				{
					if (Hit_Torso_Left) PlayAnimMontage(Hit_Torso_Left);
				}
				else if (Direction.X < -10)
				{
					if (Hit_Torso_Right) PlayAnimMontage(Hit_Torso_Right);
				}
				else
				{
					if (Hit_Torso_Front) PlayAnimMontage(Hit_Torso_Front);
				}
			}
			else
			{
				if (Hit_Back) PlayAnimMontage(Hit_Back);
			}
			AIStats.Blood -= 10;
		}
		else
		{
			if (Direction.X > 0)
			{
				if (Hit_Leg_Left) PlayAnimMontage(Hit_Leg_Left);
			}
			else
			{
				if (Hit_Leg_Right) PlayAnimMontage(Hit_Leg_Right);
			}
			AIStats.Blood -= 10;
		}
		if (AIStats.Blood <= 0)
		{
			DeathToReborn();
		}
	}
}

void AAICharacter::OnAttackComplete()
{
	GetWorldTimerManager().ClearTimer(ComboHandle);
	ComboNum = 0;
}

void AAICharacter::OnDodgeComplete()
{
	bIsDodging = false;
	GetWorldTimerManager().ClearTimer(DodgeHandle);
}

void AAICharacter::OnHurtComplete()
{
	bIsAttacked = false;
	GetWorldTimerManager().ClearTimer(HurtHandle);
}

void AAICharacter::Defence_Begin()
{
	if (bIsAttacking || GetMovementComponent()->IsFalling() || bIsDodging || bIsDefencing || bIsAttacked)
	{
		return;
	}
	bIsDefencing = true;
	if (Defence_Start)
	{
		PlayAnimMontage(Defence_Start);
	}
	GetCharacterMovement()->MaxWalkSpeed = 200;
}

void AAICharacter::Defence_End()
{
	bIsDefencing = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AAICharacter::OnBounced()
{
	GetMesh()->Stop();
	bIsAttacking = false;
	if (Hit_Torso_Front)
	{
		PlayAnimMontage(Hit_Torso_Front);
	}
	OnAttackComplete();
}



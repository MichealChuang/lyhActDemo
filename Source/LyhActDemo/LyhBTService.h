// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LyhBTService.generated.h"

/**
 * 
 */
UCLASS()
class LYHACTDEMO_API ULyhBTService : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	class ALyhActDemoCharacter* CheckEnemy(const FVector Start, const FVector End, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex, ETraceTypeQuery TraceChannel, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime);
	
	
};

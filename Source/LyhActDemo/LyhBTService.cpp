// Fill out your copyright notice in the Description page of Project Settings.

#include "LyhBTService.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "LyhActDemoCharacter.h"





ALyhActDemoCharacter* ULyhBTService::CheckEnemy(const FVector Start, const FVector End, float Radius, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex, ETraceTypeQuery TraceChannel, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
	TArray<FHitResult> OutHits;
	FHitResult OutHit;
	//检测玩家
	UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, End, Radius, ObjectTypes, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
	if (OutHits.Num() > 0)
	{
		for (TArray<FHitResult>::TIterator It = OutHits.CreateIterator(); It; ++It)
		{
			//检测与玩家之间有没有障碍物
			UKismetSystemLibrary::LineTraceSingle(this, Start, It->GetActor()->GetActorLocation(), TraceChannel, 0, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
			if (ALyhActDemoCharacter* Target = Cast<ALyhActDemoCharacter>(OutHit.GetActor()))
			{
				return Target;
			}
		}
	}
	return nullptr;
}

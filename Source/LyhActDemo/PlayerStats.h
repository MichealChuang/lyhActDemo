// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlayerStats.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LYHACTDEMO_API FPlayerStats : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
		int32 Blood;
	UPROPERTY(BlueprintReadWrite)
		int32 Magic;
	UPROPERTY(BlueprintReadWrite)
		int32 MagicRegain;
};
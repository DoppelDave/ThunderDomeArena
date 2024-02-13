// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPlayerData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct THUNDERDOMEARENA_API FPlayerData
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	float fHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float fShield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float fSpeed;

	FPlayerData();
	~FPlayerData();
};

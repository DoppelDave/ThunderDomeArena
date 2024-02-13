// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHud.generated.h"

/**
 * 
 */
UCLASS()
class THUNDERDOMEARENA_API APlayerHud : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerHud();

	virtual void BeginPlay() override;

	UPROPERTY()
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

private:
};

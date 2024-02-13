// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THUNDERDOMEARENA_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	static class AUIManager* GetUIManager(const UObject* a_pTarget);

public:
			UFUNCTION(BlueprintCallable,
			meta = (DisplayName = "Get Fullscreen Mode", Category = "UI Functions"))
			static const bool GetFullscreenMode(const UObject* a_pGameTarget);

			UFUNCTION(BlueprintCallable,
			meta = (DisplayName = "Set Fullscreen Mode", Category = "UI Functions"))
			static void SetFullscreenMode(const UObject* a_pGameTarget, const bool& a_bIsChecked);

			UFUNCTION(BlueprintCallable,
				meta = (DisplayName = "Get is Paused", Category = "UI Functions"))
			static const bool GetGameIsPaused(const UObject* a_pGameTarget);

			UFUNCTION(BlueprintCallable,
				meta = (DisplayName = "Set is Paused", Category = "UI Functions"))
			static void SetGameIsPaused(const UObject* a_pGameTarget, const bool& a_bIsGamePaused);

			UFUNCTION(BlueprintCallable,
				meta = (DisplayName = "Start Game", Category = "UI Functions"))
			static void OpenLevel(const UObject* a_pGameTarget, const FString& a_sLevelName);

			UFUNCTION(BlueprintCallable,
				meta = (DisplayName = "Close Game", Category = "UI Functions"))
			static void CloseGame(const UObject* a_pGameTarget);

			UFUNCTION(BlueprintCallable,
				meta = (DisplayName = "Toggle Pause", Category = "UI Functions"))
			static void TogglePause(const UObject* a_pGameTarget);
};

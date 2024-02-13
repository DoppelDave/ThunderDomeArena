// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class THUNDERDOMEARENA_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	//Getter/Setter
	const bool GetFullscreenMode(void) const;
	void SetFullScreenMode(const bool& a_bIsChecked);

	const bool GetIsGamePaused(void) const;
	void SetIsGamePaused(const bool& m_bIsGamePaused);

	void OpenLevel(const FString& a_sLevelName);
	void CloseGame(void) const;

	void TogglePauseMenu(void) const;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	//TSubclassOf<UUserWidget> YourWidgetClass;

private:

	//Member
	bool m_bIsGamePaused = false;
	const FString m_sLevelName = "Arena";

	UPROPERTY()
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

};


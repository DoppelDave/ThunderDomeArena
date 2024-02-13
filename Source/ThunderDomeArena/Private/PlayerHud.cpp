// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerHud.h"
#include "Blueprint/UserWidget.h"

APlayerHud::APlayerHud()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>HUDWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_GameHUD.BP_GameHUD'"));
	HUDWidgetClass = HUDWidgetClassFinder.Class;
    if (HUDWidgetClass)
    {
        // Erzeuge eine Instanz des Widgets
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        // Füge das Widget dem Viewport hinzu
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport();
        }
    }
}

void APlayerHud::BeginPlay()
{
    Super::BeginPlay();


}

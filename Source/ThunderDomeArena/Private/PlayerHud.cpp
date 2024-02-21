// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerHud.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "PlayerPawn.h"
#include "FPlayerData.h"
#include "Kismet/GameplayStatics.h"

APlayerHud::APlayerHud()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>HUDWidgetClassFinder(TEXT("WidgetBlueprint'/Game/Blueprints/BP_GameHUD'"));
    //APlayerPawn* PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
   
	HUDWidgetClass = HUDWidgetClassFinder.Class;

    if (HUDWidgetClass)
    {
        // Erzeuge eine Instanz des Widgets
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        // Füge das Widget dem Viewport hinzu
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport();

            UWidgetTree* WidgetTree = CurrentWidget->WidgetTree;

            if (WidgetTree)
            {
                HealthBar = WidgetTree->FindWidget<UProgressBar>(TEXT("HealthBar"));

                if (HealthBar) HealthBar->SetPercent(100);
            }
        }
    }
}


void APlayerHud::BeginPlay()
{
    Super::BeginPlay();

}

void APlayerHud::UpdateHealthbar(float a_fHealth, float a_fMaxHealth)
{
    if (HealthBar)
    {
        float MaxHealth = a_fMaxHealth;
        float CurrentHealth = a_fHealth;
        float HealthPercentage = CurrentHealth / MaxHealth;
        HealthBar->SetPercent(HealthPercentage);

    }
}


#include "UIManager.h"
#include "ActorUtils.h"
#include <GameFramework/GameUserSettings.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

AUIManager::AUIManager()
{
	m_bIsGamePaused = false;

	//static ConstructorHelpers::FClassFinder<UUserWidget>HUDWidgetClassFinder(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_GameHUD.BP_GameHUD'"));
	//HUDWidgetClass = HUDWidgetClassFinder.Class;
	//if (HUDWidgetClass)
	//{
	//	// Erzeuge eine Instanz des Widgets
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

	//	// Füge das Widget dem Viewport hinzu
	//	if (CurrentWidget)
	//	{
	//		CurrentWidget->AddToViewport();
	//	}
	//}
}


const bool AUIManager::GetFullscreenMode(void) const
{
	return GEngine->GetGameUserSettings()->GetFullscreenMode() ? true : false;
}

void AUIManager::SetFullScreenMode(const bool& a_bIsChecked)
{
	auto pSettings = GEngine->GetGameUserSettings();

	auto fullscreenMode = a_bIsChecked ? EWindowMode::Type::Fullscreen : EWindowMode::Type::Windowed;

	pSettings->SetFullscreenMode(fullscreenMode);
	pSettings->ApplyResolutionSettings(false);
	pSettings->SaveSettings();
}

const bool AUIManager::GetIsGamePaused(void) const
{
	return m_bIsGamePaused;
}

void AUIManager::SetIsGamePaused(const bool& a_bIsGamePaused)
{
	m_bIsGamePaused = a_bIsGamePaused;
}

void AUIManager::OpenLevel(const FString& a_sLevelName)
{
	UGameplayStatics::OpenLevel(this, FName(*a_sLevelName), true);
}

void AUIManager::CloseGame(void) const
{
	
}

void AUIManager::TogglePauseMenu(void) const
{
	UE_LOG(LogTemp, Warning, TEXT("OpenMenu"));
}


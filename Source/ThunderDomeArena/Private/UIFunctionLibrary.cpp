#include "UIFunctionLibrary.h"
#include "GameDataManager.h"
#include "UIManager.h"

AUIManager* UUIFunctionLibrary::GetUIManager(const UObject* a_pTarget)
{
	if (!a_pTarget)
	{
		UE_LOG(LogTemp, Error, TEXT("Target of UI - Manager - Getter was a nullptr - Exception"));
	}

	UGameDataManager* pGM = UGameDataManager::Instantiate(*a_pTarget);

	if (pGM->GetUIManager())
	{
		return pGM->GetUIManager();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UI - Manager of GameManager-Object was a nullptr-Exception"));
		return nullptr;
	}
}

const bool UUIFunctionLibrary::GetFullscreenMode(const UObject* a_pGameTarget)
{
	return GetUIManager(a_pGameTarget)->GetFullscreenMode();
}

void UUIFunctionLibrary::SetFullscreenMode(const UObject* a_pGameTarget, const bool& a_bIsChecked)
{
	GetUIManager(a_pGameTarget)->SetFullScreenMode(a_bIsChecked);
}

const bool UUIFunctionLibrary::GetGameIsPaused(const UObject* a_pGameTarget)
{
	return GetUIManager(a_pGameTarget)->GetIsGamePaused();
}

void UUIFunctionLibrary::SetGameIsPaused(const UObject* a_pGameTarget, const bool& a_bIsGamePaused)
{
	GetUIManager(a_pGameTarget)->SetIsGamePaused(a_bIsGamePaused);
}

void UUIFunctionLibrary::OpenLevel(const UObject* a_pGameTarget, const FString& a_sLevelName)
{
	GetUIManager(a_pGameTarget)->OpenLevel(a_sLevelName);
}

void UUIFunctionLibrary::CloseGame(const UObject* a_pGameTarget)
{
	GetUIManager(a_pGameTarget)->CloseGame();
}

void UUIFunctionLibrary::TogglePause(const UObject* a_pGameTarget)
{
	GetUIManager(a_pGameTarget)->TogglePauseMenu();
}

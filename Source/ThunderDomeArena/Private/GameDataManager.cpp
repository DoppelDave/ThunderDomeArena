#include "GameDataManager.h"
#include "UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

/// <summary>
/// Gamemanager übernommen von Marcus Schaal
/// </summary>
/// <param name="a_target"></param>
/// <returns></returns>
/// 

auto UGameDataManager::GetGameInstance(const UObject& a_target) -> UGameInstance* const
{
	if (a_target.GetWorld() && a_target.GetWorld()->GetGameInstance())
	{
		return UGameplayStatics::GetGameInstance(a_target.GetWorld());
	}
	else if (a_target.IsA(AActor::StaticClass()))
	{
		if (Cast<AActor>(&a_target)->GetGameInstance()) return GEngine->GetWorld()->GetGameInstance();
	}
	return nullptr;
}

auto UGameDataManager::Instantiate(const UObject& a_target) -> UGameDataManager*
{
	auto pInstance = GetGameInstance(a_target);
	if (pInstance) return pInstance->GetSubsystem<UGameDataManager>();
	else return nullptr;
}

AUIManager* UGameDataManager::GetUIManager(void)
{
	return m_pUI;
}

void UGameDataManager::SetUIManager(AUIManager* a_pUI)
{
	m_pUI = a_pUI;
}

//APlayerPawn* UGameDataManager::GetPlayerPawn(void)
//{
//	return m_pPlayerPawn;
//}
//
//void UGameDataManager::SetPlayerPawn(APlayerPawn* a_pPlayerPawn)
//{
//	m_pPlayerPawn = a_pPlayerPawn;
//}

bool UGameDataManager::GetIsPaused()
{
	return m_bIsPaused;
}

void UGameDataManager::SetIsPaused(bool a_bIsPaused)
{
	m_bIsPaused = a_bIsPaused;
}

void UGameDataManager::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Manager is initialized"));
}

void UGameDataManager::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Input Controller is initialized"));
}

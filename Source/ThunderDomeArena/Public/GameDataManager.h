// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UIManager.h"
#include "GameDataManager.generated.h"

/**
 * 
 */
UCLASS()
class THUNDERDOMEARENA_API UGameDataManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	static auto GetGameInstance(const UObject& a_target) -> UGameInstance* const;
public:
	static auto Instantiate(const UObject& a_target) -> UGameDataManager*;
	
	//Getter/Setter
	AUIManager* GetUIManager(void);
	void SetUIManager(AUIManager* a_pUI);
	bool GetIsPaused();
	void SetIsPaused(bool a_bIsPaused);

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize();

	
	//member
	class AUIManager* m_pUI = nullptr;
	bool m_bIsPaused = false;
};

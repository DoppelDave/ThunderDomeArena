// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameDataManager.h"
#include "SoundManager.generated.h"

UCLASS()
class THUNDERDOMEARENA_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();
	void PlayStartLoop(void);
	void PlayStartSound(void);
	void PlayBackgroundMusic(void);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UGameDataManager* m_pGameDataManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	const FString M_S_COUNTDOWN_SOUND = TEXT("/Script/Engine.SoundWave'/Game/Audio/95-Countdown_3_2_1.95-Countdown_3_2_1'");
	const FString M_S_START_SOUND = TEXT("/Script/Engine.SoundWave'/Game/Audio/96-Countdown_start.96-Countdown_start'");
	const FString M_S_SOUND_TRACK = TEXT("/Script/Engine.SoundWave'/Game/Audio/background_music.background_music'");

};

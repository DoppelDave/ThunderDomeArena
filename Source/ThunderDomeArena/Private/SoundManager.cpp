#include "SoundManager.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASoundManager::PlayStartLoop(void)
{
		USoundBase* LoadedSound = LoadObject<USoundBase>(nullptr, *M_S_COUNTDOWN_SOUND);

		if (LoadedSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, GetActorLocation());
			float SoundDuration = LoadedSound->GetDuration();
			float Delay = SoundDuration + 0.5f;
			FTimerHandle SoundTimerHandle;
			GetWorldTimerManager().SetTimer(SoundTimerHandle, this, &ASoundManager::PlayStartSound, Delay, false);
		}
}

void ASoundManager::PlayStartSound(void)
{
	USoundBase* LoadedSound = LoadObject<USoundBase>(nullptr, *M_S_START_SOUND);

	if (LoadedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, GetActorLocation());
		float SoundDuration = LoadedSound->GetDuration();
		float Delay = SoundDuration + 0.5f;
		FTimerHandle SoundTimerHandle;
		GetWorldTimerManager().SetTimer(SoundTimerHandle, this, &ASoundManager::PlayBackgroundMusic, Delay, false);
		m_pGameDataManager->SetIsPaused(false);
	}
}

void ASoundManager::PlayBackgroundMusic(void)
{
	USoundBase* LoadedSound = LoadObject<USoundBase>(nullptr, *M_S_SOUND_TRACK);

	if (LoadedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, GetActorLocation());
	}
}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	m_pGameDataManager = UGameDataManager::Instantiate(*this);
	m_pGameDataManager->SetIsPaused(true);	
	PlayStartLoop();
}

// Called every frame
void ASoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


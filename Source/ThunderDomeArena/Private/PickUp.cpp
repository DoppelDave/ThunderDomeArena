#include "PickUp.h"
#include "ActorUtils.h"
#include "PlayerPawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APickUp::APickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	Spawn();
}

void APickUp::Spawn()
{
	float fRandomValue = FMath::FRandRange(0.0f, 1.0f);

	m_pickUpType = (fRandomValue < 0.5f) ? EPickUpType::ShieldPickUp : EPickUpType::HealthPickUp;


	switch (m_pickUpType)
	{
	case EPickUpType::ShieldPickUp:
		InitComponents(*M_S_SPU, *M_S_MESH_SPU_NAME, *M_S_SPU_MAT);
		break;
	case EPickUpType::HealthPickUp:
		InitComponents(*M_S_HPU, *M_S_MESH_HPU_NAME, *M_S_HPU_MAT);
		break;
	default:
		break;

	};
}

void APickUp::InitComponents(FString a_fMeshPath, FString a_fMeshName, FString a_fMaterialPath)
{
	if (!m_pMaterial) m_pMaterial = InitMaterial(a_fMaterialPath);
	if (!m_pMesh) m_pMesh = InitMesh(a_fMeshPath, a_fMeshName);
}

UMaterialInterface* APickUp::InitMaterial(FString a_fPath)
{
	auto pMaterial = FindObject<UMaterialInterface>(*a_fPath);
	return pMaterial;
}


UStaticMeshComponent* APickUp::InitMesh(FString a_fMeshPath, FString a_fMeshName)
{
	auto pMesh = CreateDefaultSubobject<UStaticMeshComponent>(*a_fMeshName);
	pMesh->SetupAttachment(RootComponent);
	pMesh->SetStaticMesh(FindObject<UStaticMesh>(*a_fMeshPath));
	pMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh->SetMaterial(0, m_pMaterial);
	return pMesh;
}

void APickUp::PlayParticleEffect(void)
{
	ParticleSystem = LoadObject<UParticleSystem>(nullptr, *M_S_PARTICLE);

	if (ParticleSystem) PickUpParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);
	PickUpParticle->Activate();
}

void APickUp::PlaySound(void)
{
	USoundBase* LoadedSound = LoadObject<USoundBase>(nullptr, *M_S_PICK_UP_SOUND);

	if (LoadedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, GetActorLocation());
	}
}

void APickUp::Rotate(float DeltaTime)
{
	FRotator newRotation = FRotator(0.0f, m_fRotationSpeed * DeltaTime, 0.0f);

	AddActorLocalRotation(newRotation);
}


void APickUp::CreateTrigger(UStaticMeshComponent* a_pMesh)
{
	m_pTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	m_pTriggerBox->SetupAttachment(a_pMesh);
	m_pTriggerBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	m_pTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, +50.0f));
	m_pTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlap);
}

void APickUp::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);
}

void APickUp::SetPickUpType(EPickUpType a_pickUpType)
{
	m_pickUpType = a_pickUpType;
}

void APickUp::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);

	if (PlayerPawn)
	{
		PlayerPawn->OnPickUpEvent();
		PlayParticleEffect();
		PlaySound();
	}

	Destroy();
}


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

	InitComponents();
}

void APickUp::InitComponents(void)
{
	InitMaterial();
	InitWeaponMesh();
}

void APickUp::InitMaterial(void)
{
	m_pMaterial = FindObject<UMaterialInterface>(*M_S_MAT);
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

UStaticMeshComponent* APickUp::InitWeaponMesh(void)
{
	auto pMesh_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_WEAPON_2_NAME);

	pMesh_Weapon->SetupAttachment(RootComponent);
	pMesh_Weapon->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_WEAPON_2));
	pMesh_Weapon->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	pMesh_Weapon->SetMaterial(0, m_pMaterial);

	CreateTrigger(pMesh_Weapon);

	return pMesh_Weapon;
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


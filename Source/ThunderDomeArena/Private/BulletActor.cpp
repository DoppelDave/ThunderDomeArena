// Fill out your copyright notice in the Description page of Project Settings.
#include "BulletActor.h"
#include "ActorUtils.h"
#include "Components/BoxComponent.h"
#include "BoxActor.h"
#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABulletActor::ABulletActor(FPlayerData* a_pData)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pPlayerdata = a_pData;
	if(!m_pMesh) m_pMesh = InitBaseMesh();
	
	m_fSpeed = 5000.0f;

	

}

void ABulletActor::OnBulletHit(UPrimitiveComponent* HitComonent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
		ABoxActor* target = Cast<ABoxActor>(OtherActor);
		APlayerController* player = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		APlayerPawn* pawn = Cast<APlayerPawn>(player);

		if (target)
		{
			m_pPlayerdata->fScore += 1;

			if (m_pPlayerdata->fScore == 15)
			{
				if (pawn) pawn->LoadEndScreen();
			}
		}

		Destroy();
	
}


void ABulletActor::InitMaterial(void)
{
	m_pMaterial = FindObject<UMaterialInterface>(*M_S_MAT);
}

void ABulletActor::CreateTrigger(UStaticMeshComponent* a_pMesh)
{
	m_pTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	m_pTriggerBox->SetupAttachment(a_pMesh);
	m_pTriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	m_pTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	m_pTriggerBox->OnComponentHit.AddDynamic(this, &ABulletActor::OnBulletHit);
}

UStaticMeshComponent* ABulletActor::InitBaseMesh(void)
{
	auto pMesh_Base = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_BULLET_NAME);
	//Initialisierung
	pMesh_Base->SetupAttachment(RootComponent);
	pMesh_Base->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_BULLET));
	pMesh_Base->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_Base->SetMaterial(0, m_pMaterial);
	pMesh_Base->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	CreateTrigger(pMesh_Base);
	return pMesh_Base;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector DirectionVector = GetActorForwardVector();
	SetActorLocation(GetActorLocation() + DirectionVector * m_fSpeed * DeltaTime);
}



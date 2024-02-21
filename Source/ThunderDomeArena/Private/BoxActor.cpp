// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "ActorUtils.h"
#include <BulletActor.h>


// Sets default values
ABoxActor::ABoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//InitComponents();
}

void ABoxActor::InitComponents()
{
	if (!m_pMaterial) m_pMaterial = FindObject<UMaterialInterface>(*M_S_MAT);
	if (!m_pMesh) m_pMesh = InitWeaponMesh();
}

void ABoxActor::CreateTrigger(UStaticMeshComponent* a_pMesh)
{
	m_pTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxBox"));
	m_pTriggerBox->SetupAttachment(a_pMesh);
	m_pTriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	m_pTriggerBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

UStaticMeshComponent* ABoxActor::InitWeaponMesh(void)
{
	auto pMesh_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_NAME);

	pMesh_Weapon->SetupAttachment(RootComponent);
	pMesh_Weapon->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH));
	pMesh_Weapon->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_Weapon->SetMaterial(0, m_pMaterial);
	CreateTrigger(pMesh_Weapon);
	

	return pMesh_Weapon;
}

void ABoxActor::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA<ABulletActor>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hier ist eine Nachricht, die in der Konsole angezeigt wird!"));
		OtherActor->Destroy();
	}

}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();

	if (m_pMesh)
	{
		m_pMesh->OnComponentHit.AddDynamic(this, &ABoxActor::OnBulletHit);
	}
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


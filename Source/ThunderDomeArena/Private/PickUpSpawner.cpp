// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSpawner.h"
#include "ActorUtils.h"

// Sets default values
APickUpSpawner::APickUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitComponents();
}

void APickUpSpawner::InitComponents(void)
{
	if (!m_pMaterial_1) m_pMaterial_1 = InitMaterial(*M_S_MAT_1);
	if (!m_pMaterial_2) m_pMaterial_2 = InitMaterial(*M_S_MAT_2);
	if (!m_pMaterial_3) m_pMaterial_3 = InitMaterial(*M_S_MAT_3);
	if (!m_pMesh) m_pMesh = InitPlattformMesh();
}

void APickUpSpawner::SpawnPickUp(void)
{
	if (GetWorld())
	{
		if (m_pPickUp) m_pPickUp = nullptr;
		
		FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, +10.0f);
		FRotator SpawnRotation = GetActorRotation();

		if (!m_pPickUp) m_pPickUp = GetWorld()->SpawnActor<APickUp>(APickUp::StaticClass(), SpawnLocation, SpawnRotation);
		if (m_pPickUp)
		{
			//m_pPickUp->SetPickUpType(EPickUpType::ShieldPickUp);
			//m_pPickUp->Spawn();
			FVector NewSize = FVector(0.15f, 0.3f, 0.3f);
			m_pPickUp->SetActorScale3D(NewSize);
		}

	}
}

UMaterialInterface* APickUpSpawner::InitMaterial(FString a_sMaterial_Path)
{	
	auto pMaterial = FindObject<UMaterialInterface>(*a_sMaterial_Path);
	return pMaterial;
}


UStaticMeshComponent* APickUpSpawner::InitPlattformMesh(void)
{
	auto pMesh = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_PLATTFORM_NAME);

	pMesh->SetupAttachment(RootComponent);
	pMesh->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_PLATTFORM));
	pMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	pMesh->SetMaterial(0, m_pMaterial_1);
	pMesh->SetMaterial(1, m_pMaterial_2);
	pMesh->SetMaterial(2, m_pMaterial_3);

	return pMesh;
}


// Called when the game starts or when spawned
void APickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnPickUp();
}

// Called every frame
void APickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


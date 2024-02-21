// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.h"
#include "PickUpSpawner.generated.h"


UCLASS()
class THUNDERDOMEARENA_API APickUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpSpawner();

private:
	UStaticMeshComponent* InitPlattformMesh(void);
	UMaterialInterface* InitMaterial(FString a_sMaterial_Path);
	void InitComponents(void);
	void SpawnPickUp(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

private:

	// Consts
	const FString M_S_MAT_1 = TEXT("/Script/Engine.Material'/Game/Materials/M_Black.M_Black'");
	const FString M_S_MAT_2 = TEXT("/Script/Engine.Material'/Game/Materials/M_White.M_White'");
	const FString M_S_MAT_3 = TEXT("/Script/Engine.Material'/Game/Materials/M_Grey.M_Grey'");

	const FString M_S_MESH_PLATTFORM = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/SpawnPlattform.SpawnPlattform'");

	const FString M_S_MESH_PLATTFORM_NAME = TEXT("Plattform");

	// Materials & Meshes
	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material 1", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial_1 = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material 2", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial_2 = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material 3", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial_3 = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "BaseMesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> m_pMesh = nullptr;

	APickUp* m_pPickUp = nullptr;
	EPickUpType m_pickUpType = EPickUpType::None;

};

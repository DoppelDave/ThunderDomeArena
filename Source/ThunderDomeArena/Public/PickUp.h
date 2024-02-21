// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

enum class EPickUpType : uint8
{
	None,
	HealthPickUp,
	ShieldPickUp
};

UCLASS()
class THUNDERDOMEARENA_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();


private:
	void InitComponents(FString a_fMeshPath, FString a_fMeshName, FString a_fMaterialPath);
	void CreateTrigger(UStaticMeshComponent* a_pMesh);
	void PlayParticleEffect(void);
	void PlaySound(void);
	void Rotate(float DeltaTime);
	UStaticMeshComponent* InitMesh(FString a_fMeshPath, FString a_fMeshName);
	UMaterialInterface* InitMaterial(FString a_fPath);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPickUpType(EPickUpType a_pickUpType);
	void Spawn();
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:

	const FString M_S_MAT = TEXT("/Script/Engine.Material'/Game/Materials/M_Black.M_Black'");
	const FString M_S_MESH_WEAPON_2 = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Weapon_2.Weapon_2'");
	const FString M_S_PARTICLE = TEXT("/Script/Engine.ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	const FString M_S_PICK_UP_SOUND = TEXT("/Script/Engine.SoundWave'/Game/Audio/PickUp_1.PickUp_1'");

	const FString M_S_SPU = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/ShieldPickUp.ShieldPickUp'");
	const FString M_S_SPU_MAT = (TEXT("/Script/Engine.Material'/Game/Materials/M_Blue.M_Blue'"));

	const FString M_S_HPU = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/HealthPickUp.HealthPickUp'");
	const FString M_S_HPU_MAT = TEXT("/Script/Engine.Material'/Game/Materials/M_Green.M_Green'");

	const FString M_S_MESH_SPU_NAME = TEXT("Shield Pick Up");
	const FString M_S_MESH_HPU_NAME = TEXT("Health Pick Up");
	const FString M_S_MESH_WEAPON_2_NAME = TEXT("Weapon");


	//member
	float m_fRotationSpeed = 90.0f;

	EPickUpType m_pickUpType = EPickUpType::None;

	// Materials & Meshes
	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "BaseMesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> m_pMesh = nullptr;

	class UBoxComponent* m_pTriggerBox;

protected:
	UPROPERTY(EditAnywhere, Category = "Particles")
	UParticleSystem* ParticleSystem;

	UPROPERTY()
	UParticleSystemComponent* PickUpParticle;
};

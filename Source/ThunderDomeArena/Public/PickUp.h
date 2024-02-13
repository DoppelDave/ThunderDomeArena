// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"


UCLASS()
class THUNDERDOMEARENA_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

private:
	void InitComponents(void);
	void CreateTrigger(UStaticMeshComponent* a_pMesh);
	void InitMaterial(void);
	void PlayParticleEffect(void);
	void PlaySound(void);
	UStaticMeshComponent* InitWeaponMesh(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:

	const FString M_S_MAT = TEXT("/Script/Engine.Material'/Game/Materials/M_Black.M_Black'");
	const FString M_S_MESH_WEAPON_2 = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Weapon_2.Weapon_2'");
	const FString M_S_MESH_WEAPON_2_NAME = TEXT("Weapon");
	const FString M_S_PARTICLE = TEXT("/Script/Engine.ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	const FString M_S_PICK_UP_SOUND = TEXT("/Script/Engine.SoundWave'/Game/Audio/PickUp_1.PickUp_1'");

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

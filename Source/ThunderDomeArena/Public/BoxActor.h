// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"

UCLASS()
class THUNDERDOMEARENA_API ABoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxActor();

private:

	void InitComponents();
	void CreateTrigger(UStaticMeshComponent* a_pMesh);
	UStaticMeshComponent* InitWeaponMesh(void);

	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	const FString M_S_MAT = TEXT("/Script/Engine.Material'/Game/Meshes/Material.Material'");
	const FString M_S_MESH = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Box_3.Box_3'");
	const FString M_S_MESH_NAME = TEXT("Box");

	// Materials & Meshes
	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "BaseMesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> m_pMesh = nullptr;

	class UBoxComponent* m_pTriggerBox;
};

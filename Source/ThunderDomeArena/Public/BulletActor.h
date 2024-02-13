// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class THUNDERDOMEARENA_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();
	
	//UFUNCTION()
	//void OnBulletHit(UPrimitiveComponent* HitComonent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void InitMaterial(void);
	//void CreateTrigger(UStaticMeshComponent* a_pMesh);
	UStaticMeshComponent* InitBaseMesh(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float m_fSpeed = 100.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const FString M_S_MAT = TEXT("/Script/Engine.Material'/Game/Materials/M_Black.M_Black'");
	const FString M_S_MESH_BULLET = TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Bullet.Bullet'");
	const FString M_S_MESH_BULLET_NAME = TEXT("Bullet");

	//class UBoxComponent* m_pTriggerBox;

	// Materials & Meshes
	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Material", Category = "Components"))
	TObjectPtr<UMaterialInterface> m_pMaterial = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "BaseMesh", Category = "Components"))
	TObjectPtr<UStaticMeshComponent> m_pMesh = nullptr;
};

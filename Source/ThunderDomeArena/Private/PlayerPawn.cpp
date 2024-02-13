// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "ActorUtils.h"
#include "BulletActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameDataManager.h"
#include "UIFunctionLibrary.h"
#include "Sound/SoundCue.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pInput = Cast<AInputController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	InitComponents();

	if (m_fSpeed == 0.0f) m_fSpeed = 400.0f;
	m_fShotCooldown = 0.1f;
	m_bCanShoot = true;

	Playerdata.fHealth = 50.0f;

	//m_pCharacterMovement = GetCharacterMovement();
}



void APlayerPawn::InitMaterials(void)
{
	// Instanzierung
	m_pMaterial_Base = FindObject <UMaterialInterface>(*M_S_MAT_BASE);
	m_pMaterial_Decoration = FindObject <UMaterialInterface>(*M_S_MAT_DEC);
	m_pMaterial_Window = FindObject<UMaterialInterface>(*M_S_MAT_WIN);
}

UStaticMeshComponent* APlayerPawn::InitBaseMesh(void)
{
	//Instanziierung
	auto pMesh_Base = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_BASE_NAME);
	//Initialisierung
	pMesh_Base->SetupAttachment(RootComponent);
	pMesh_Base->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_BASE));
	pMesh_Base->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_Base->SetMaterial(0, m_pMaterial_Base);
	pMesh_Base->SetMaterial(1, m_pMaterial_Window);
	pMesh_Base->SetMaterial(2, m_pMaterial_Decoration);

	return pMesh_Base;
}

UStaticMeshComponent* APlayerPawn::InitWeapon2Mesh(void)
{

	//Instanziierung
	auto pMesh_Weapon_2 = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_WEAPON_2_NAME);
	//Initialisierung
	pMesh_Weapon_2->SetupAttachment(m_pMesh_WeaponHolder);
	pMesh_Weapon_2->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_WEAPON_2));
	pMesh_Weapon_2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_Weapon_2->SetMaterial(0, m_pMaterial_Base);
	pMesh_Weapon_2->SetMaterial(1, m_pMaterial_Decoration);
	pMesh_Weapon_2->SetMaterial(2, m_pMaterial_Decoration);
	pMesh_Weapon_2->SetVisibility(false);

	return pMesh_Weapon_2;
}

UStaticMeshComponent* APlayerPawn::InitWeaponBaseMesh(void)
{

	//Instanziierung
	auto pMesh_WeaponHolder = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_WEAPON_BASE_NAME);

	//Initialisierung
	pMesh_WeaponHolder->SetupAttachment(m_pMesh_Base);
	pMesh_WeaponHolder->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_WEAPON_BASE));
	pMesh_WeaponHolder->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_WeaponHolder->SetMaterial(0, m_pMaterial_Decoration);

	return pMesh_WeaponHolder;
}

UStaticMeshComponent* APlayerPawn::InitWeaponMesh(void)
{
	//Instanziierung
	auto pMesh_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(*M_S_MESH_WEAPON_NAME);
	//Initialisierung
	pMesh_Weapon->SetupAttachment(m_pMesh_WeaponHolder);
	pMesh_Weapon->SetStaticMesh(FindObject<UStaticMesh>(*M_S_MESH_WEAPON));
	pMesh_Weapon->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	pMesh_Weapon->SetMaterial(0, m_pMaterial_Base);
	pMesh_Weapon->SetMaterial(1, m_pMaterial_Decoration);
	pMesh_Weapon->SetMaterial(2, m_pMaterial_Decoration);

	return pMesh_Weapon;
}




UCameraComponent* APlayerPawn::InitCamera(void)
{
	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_pCamera->SetupAttachment(m_pMesh_WeaponHolder);
	m_pCamera->SetRelativeLocation(m_cameraLocation);
	m_pCamera->SetRelativeRotationExact(m_cameraRotation);
	return m_pCamera;
}

void APlayerPawn::InitComponents(void)
{
	//Init Meshes & Materials
	if (!m_pMaterial_Base && !m_pMaterial_Decoration && !m_pMaterial_Window) InitMaterials();
	if (!m_pMesh_Base) m_pMesh_Base = InitBaseMesh();
	if (!m_pMesh_WeaponHolder) m_pMesh_WeaponHolder = InitWeaponBaseMesh();
	if (!m_pMesh_Weapon) m_pMesh_Weapon = InitWeaponMesh();
	if (!m_pCamera) m_pCamera = InitCamera();
	if (!m_pMesh_2_Weapon) m_pMesh_2_Weapon = InitWeapon2Mesh();
}

void APlayerPawn::MovePlayer(float a_fDeltaTime)
{
	auto rotation = GetActorRotation() + m_baseRotation * m_fRotationSpeed * a_fDeltaTime;
	SetActorRotation(rotation);

	FVector forwardVector = GetActorRightVector();

	auto location = GetActorLocation() + forwardVector * m_fSpeed * a_fDeltaTime;
	SetActorLocation(location);

}


void APlayerPawn::HandleForwardMoving(float a_fInput)
{
	if (a_fInput > 0)
	{
		m_fSpeed = 500.0f;
	}
	else if (a_fInput < 0)
	{
		m_fSpeed = -500.0f;
	}
	else
	{
		m_fSpeed = 0.0f;
	}
}

void APlayerPawn::HandleRightMoving(float a_fInput)
{
	m_baseRotation.Yaw = a_fInput;
}

void APlayerPawn::OpenMenuAction()
{
	//bool bIsGamePaused = UUIFunctionLibrary::GetGameIsPaused(this);
	UUIFunctionLibrary::TogglePause(this);
}

void APlayerPawn::ShootAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
	if (m_bCanShoot)
	{
		ShootBullets();
		m_bCanShoot = false;
		//GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APlayerPawn::EnableShooting, ShotTimerHandle, false);
		GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APlayerPawn::EnableShooting, m_fShotCooldown, false);
	}
}

void APlayerPawn::ShootBullets()
{
	USoundBase* LoadedSound = LoadObject<USoundBase>(nullptr, *M_S_SHOOT_SOUND);



	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = m_pMesh_WeaponHolder->GetRelativeRotation();

	FRotator CameraRotation = m_pCamera->GetComponentRotation();
	ABulletActor* pBullet = GetWorld()->SpawnActor<ABulletActor>(ABulletActor::StaticClass(), SpawnLocation, CameraRotation);

	if (LoadedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LoadedSound, SpawnLocation);
	}
	pBullet->SetLifeSpan(2.0f);

	m_fRecoilAngle = m_fRecoilAmount;
}

void APlayerPawn::EnableShooting()
{
	m_bCanShoot = true;
}

float APlayerPawn::GetHealth() const
{
	return Playerdata.fHealth;
}

void APlayerPawn::SetHealth(float a_fHealth)
{
	Playerdata.fHealth = a_fHealth;
}

void APlayerPawn::AimAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Aim"));
}

void APlayerPawn::GetMousePositions()
{
	m_pInput->GetMousePosition(m_fMousePosX, m_fMousePosY);


	//FRotator NewCameraRotation = FRotator(0,m_fMousePosX, 0.0f);

	FRotator NewCameraRotation = FRotator(0, m_fMousePosX, m_fRecoilAngle);

	m_pMesh_WeaponHolder->SetRelativeRotation(NewCameraRotation);

	m_fRecoilAngle -= m_fRecoilDecreaseRate * GetWorld()->GetDeltaSeconds();
	m_fRecoilAngle = FMath::Max(m_fRecoilAngle, 0.0f);
}




// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	m_pInput->SetViewTarget(this);

	FString WidgetPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/WP_Crosshair.WP_Crosshair'");
	UE_LOG(LogTemp, Warning, TEXT("Text1"));

	if (!CrosshairWidgetClass)
	{
		CrosshairWidgetClass = LoadClass<UUserWidget>(nullptr, *WidgetPath);

		if(CrosshairWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("Hello, Text2"));
		// Erstellen Sie das Widget und weisen Sie es der CrosshairWidgetInstance zu
		CrosshairWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidgetInstance)
		{
			// Fügen Sie das Widget zum Viewport hinzu
			CrosshairWidgetInstance->AddToViewport();
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer(DeltaTime);
	GetMousePositions();

	/*if (CrosshairWidgetInstance)
	{
		FVector2D ViewportSize;
		GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
		FVector2D CrosshairPosition = FVector2D(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);
		CrosshairWidgetInstance->SetPositionInViewport(CrosshairPosition);
	}*/
}

void APlayerPawn::OnPickUpEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("PickUp Event Triggered!"));
	if (m_pMesh_Weapon)
	{
		
		m_pMesh_Weapon->SetVisibility(false);
		m_pMesh_2_Weapon->SetVisibility(true);
	}

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!m_pInput) return;
	PlayerInputComponent->BindAxis(m_pInput->GetForwardAxisName(), this, &APlayerPawn::HandleForwardMoving);
	PlayerInputComponent->BindAxis(m_pInput->GetRightAxisName(), this, &APlayerPawn::HandleRightMoving);
	PlayerInputComponent->BindAction(m_pInput->GetOpenMenuActionName(),IE_Pressed, this, &APlayerPawn::OpenMenuAction);
	PlayerInputComponent->BindAction(m_pInput->GetShootActionName(), IE_Pressed, this, &APlayerPawn::ShootAction);
	PlayerInputComponent->BindAction(m_pInput->GetAimActionName(), IE_Pressed, this, &APlayerPawn::AimAction);
}


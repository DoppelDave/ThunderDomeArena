// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

/**
 * 
 */
UCLASS()
class THUNDERDOMEARENA_API AInputController : public APlayerController
{
	GENERATED_BODY()

public:
	AInputController();

	void InitInputMapping(void);
	void InitDefaultKeys(void);
	void UpdateMappingSettings(void);
	void FinalizeMappingSettings(void);


private:
	void SetAction(FInputActionKeyMapping& a_action, const FName& a_sActionName,
					const FKey& a_key, const bool& a_bIsShiftKey,
					const bool& a_bIsCtrlKey, const bool& a_bisAltKey,
					const bool& a_bIsCmdKey,
					const bool& a_bShouldUpdate = true );

	void SetAxis(FInputAxisKeyMapping& a_axis,
					const FName& a_sAxisName,
					const FKey& a_key,
					const float& a_fScale,
					const bool& a_bShouldRemove = true,
					const bool& a_bShouldUpdate = true);

public:
	const FInputActionKeyMapping GetShootAction(void) const;
	void SetShootAction(const FKey& a_key, const bool& a_bShouldUpdate = true );

	const FInputActionKeyMapping GetAimAction(void) const;
	void SetAimAction(const FKey& a_key, const bool& a_bShouldUpdate = true);

	const FInputActionKeyMapping GetOpenMenuAction(void) const;
	void SetOpenMenuAction(const FKey& a_key, const bool& a_bShouldUpdate = true);

	const FInputAxisKeyMapping GetForwardAxis(void) const;
	void SetForwardAxis(const FKey& a_key, 
						const float& a_fScale,
						const bool& a_bShouldRemove,
						const bool& a_bSouldUpdate = true);

	const FInputAxisKeyMapping GetRightAxis(void) const;
	void SetRightAxis(const FKey& a_key,
					  const float& a_fScale,
					  const bool& a_bShouldRemove,
					  const bool& a_bSouldUpdate = true);

	const FInputAxisKeyMapping GetMouseAxis(void) const;
	void SetMouseAxis(const FKey& a_key,
		const float& a_fScale,
		const bool& a_bShouldRemove,
		const bool& a_bSouldUpdate = true);

	const FName GetForwardAxisName(void) const;
	const FName GetRightAxisName(void) const;
	const FName GetShootActionName(void) const;
	const FName GetOpenMenuActionName(void) const;
	const FName GetAimActionName(void) const;

private:
	// consts
	const FName M_S_SHOOT_ACTION_NAME = TEXT("ShootAction");
	const FName M_S_AIM_ACTION_NAME = TEXT("AimAction");
	const FName M_S_OPEN_MENU_ACTION_NAME = TEXT("OpenMenuAction");
	const FName M_S_FORWARD_AXIS_NAME = TEXT("ForwardAxis");
	const FName M_S_RIGHT_AXIS_NAME = TEXT("RightAxis");

	const float M_F_POSITIVE_SCALE = 1.0f;
	const float M_F_NEGATIVE_SCALE = -1.0f;
	


	// members
	FInputActionKeyMapping m_shootAction = {};
	FInputActionKeyMapping m_aimAction = {};
	FInputActionKeyMapping m_openMenuAction = {};

	FInputAxisKeyMapping m_forward = {};
	FInputAxisKeyMapping m_right = {};
	UPROPERTY(EditAnywhere,
			meta = (DisplayName = "InputSettings", Category = "System"))
	class UInputSettings* m_pInputSettings = nullptr;

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Action List", Category = "Input"))
	TArray<FInputActionKeyMapping> m_actionList = {};

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Axis List", Category = "Input"))
	TArray<FInputAxisKeyMapping> m_axisList = {};

};

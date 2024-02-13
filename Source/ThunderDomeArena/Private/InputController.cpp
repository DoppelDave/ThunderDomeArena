// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"
#include <GameFramework/InputSettings.h>

AInputController::AInputController()
{
	UE_LOG(LogTemp, Warning, TEXT("Input Controller is initialized"));

	InitInputMapping();
	FinalizeMappingSettings();
	InitDefaultKeys();
	UpdateMappingSettings();
}

void AInputController::InitInputMapping(void)
{
	if (!m_pInputSettings) m_pInputSettings = UInputSettings::GetInputSettings();

	if (m_pInputSettings)
	{
		m_actionList = m_pInputSettings->GetActionMappings();
		m_axisList = m_pInputSettings->GetAxisMappings();
	}
}

void AInputController::InitDefaultKeys(void)
{
	SetShootAction(EKeys::LeftMouseButton, false);
	SetAimAction(EKeys::RightMouseButton, false);
	SetOpenMenuAction(EKeys::Enter, false);
	

	SetForwardAxis(EKeys::W, M_F_POSITIVE_SCALE, true, false);
	SetForwardAxis(EKeys::S, M_F_NEGATIVE_SCALE, false, false);

	SetRightAxis(EKeys::D, M_F_POSITIVE_SCALE, true, false);
	SetRightAxis(EKeys::A, M_F_NEGATIVE_SCALE, false, false);

}

void AInputController::UpdateMappingSettings(void)
{
	FConfigCacheIni::LoadGlobalIniFile(GInputIni, TEXT("Input"), nullptr, true, false);

	if (m_pInputSettings)
	{
		m_pInputSettings->SaveConfig();
		m_pInputSettings->ReloadConfig(m_pInputSettings->GetClass(), *GInputIni, UE::LCPF_PropagateToInstances);
		m_pInputSettings->ForceRebuildKeymaps();
		m_pInputSettings->SaveKeyMappings();
	}

}

void AInputController::FinalizeMappingSettings(void)
{
	if (!m_pInputSettings) return;

	for (auto&& axis : m_axisList)
	{
		m_pInputSettings->RemoveAxisMapping(axis, false);
	}

	for (auto&& action : m_actionList)
	{
		m_pInputSettings->RemoveActionMapping(action, false);
	}

	m_pInputSettings->SaveKeyMappings();
}

void AInputController::SetAction(FInputActionKeyMapping& a_action, 
								const FName& a_sActionName, 
								const FKey& a_key,
								const bool& a_bIsShiftKey, 
								const bool& a_bIsCtrlKey, 
								const bool& a_bisAltKey, 
								const bool& a_bIsCmdKey,
								const bool& a_bShouldUpdate)
{
	if (m_pInputSettings) m_pInputSettings->RemoveActionMapping(a_action, false);
	a_action = FInputActionKeyMapping(a_sActionName, a_key, a_bIsShiftKey, a_bIsCtrlKey, a_bisAltKey, a_bIsCmdKey);

	if (m_pInputSettings)
	{
		m_pInputSettings->AddActionMapping(a_action);
		if (a_bShouldUpdate) UpdateMappingSettings();
	}
	else UPlayerInput::AddEngineDefinedActionMapping(a_action);
}

void AInputController::SetAxis(FInputAxisKeyMapping& a_axis,
								const FName& a_sAxisName, 
								const FKey& a_key,
								const float& a_fScale, 
								const bool& a_bShouldRemove,
								const bool& a_bShouldUpdate)
{
	if (m_pInputSettings && a_bShouldRemove) m_pInputSettings->RemoveAxisMapping(a_axis);
	a_axis = FInputAxisKeyMapping(a_sAxisName, a_key, a_fScale);

	if (m_pInputSettings)
	{
		m_pInputSettings->AddAxisMapping(a_axis);
		if (a_bShouldUpdate) UpdateMappingSettings();
	}
	else UPlayerInput::AddEngineDefinedAxisMapping(a_axis);
}

const FInputActionKeyMapping AInputController::GetShootAction(void) const
{
	return m_shootAction;
}

void AInputController::SetShootAction(const FKey& a_key, const bool& a_bShouldUpdate )
{
	SetAction(m_shootAction, M_S_SHOOT_ACTION_NAME, a_key, false, false, false, false, a_bShouldUpdate);
}

const FInputActionKeyMapping AInputController::GetAimAction(void) const
{
	return m_aimAction;
}

void AInputController::SetAimAction(const FKey& a_key, const bool& a_bShouldUpdate)
{
	SetAction(m_aimAction, M_S_AIM_ACTION_NAME, a_key, false, false, false, false, a_bShouldUpdate);
}

const FInputActionKeyMapping AInputController::GetOpenMenuAction(void) const
{
	return m_openMenuAction;
}

void AInputController::SetOpenMenuAction(const FKey& a_key, const bool& a_bShouldUpdate)
{
	SetAction(m_openMenuAction, M_S_OPEN_MENU_ACTION_NAME, a_key, false, false, false, false, a_bShouldUpdate);
}

const FInputAxisKeyMapping AInputController::GetForwardAxis(void) const
{
	return m_forward;
}

void AInputController::SetForwardAxis(const FKey& a_key,
									  const float& a_fScale,
									  const bool& a_bShouldRemove, 
									  const bool& a_bSouldUpdate)
{
	SetAxis(m_forward, M_S_FORWARD_AXIS_NAME, a_key, a_fScale, a_bShouldRemove, a_bSouldUpdate);
}

const FInputAxisKeyMapping AInputController::GetRightAxis(void) const
{
	return m_right;
}


void AInputController::SetRightAxis(const FKey& a_key,
									const float& a_fScale,
									const bool& a_bShouldRemove, 
									const bool& a_bSouldUpdate)
{
	SetAxis(m_right, M_S_RIGHT_AXIS_NAME, a_key, a_fScale, a_bShouldRemove, a_bSouldUpdate);
}

const FName AInputController::GetForwardAxisName(void) const
{
	return M_S_FORWARD_AXIS_NAME;
}

const FName AInputController::GetRightAxisName(void) const
{
	return M_S_RIGHT_AXIS_NAME;
}

const FName AInputController::GetShootActionName(void) const
{
	return M_S_SHOOT_ACTION_NAME;
}

const FName AInputController::GetOpenMenuActionName(void) const
{
	return M_S_OPEN_MENU_ACTION_NAME;
}

const FName AInputController::GetAimActionName(void) const
{
	return M_S_AIM_ACTION_NAME;
}



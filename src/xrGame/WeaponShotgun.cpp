#include "stdafx.h"
#include "script_game_object.h"
#include "weaponshotgun.h"
#include "entity.h"
#include "inventory.h"
#include "level.h"
#include "actor.h"
#include "script_game_object.h"

CWeaponShotgun::CWeaponShotgun()
{
	m_eSoundClose			= ESoundTypes(SOUND_TYPE_WEAPON_SHOOTING);
	m_eSoundAddCartridge	= ESoundTypes(SOUND_TYPE_WEAPON_SHOOTING);
	bStopReloadSignal		= false;
}

CWeaponShotgun::~CWeaponShotgun()
{
}

void CWeaponShotgun::net_Destroy()
{
	inherited::net_Destroy();
}

void CWeaponShotgun::Load	(LPCSTR section)
{
	inherited::Load		(section);

	if(pSettings->line_exist(section, "tri_state_reload")){
		m_bTriStateReload = !!pSettings->r_bool(section, "tri_state_reload");
	};
	if(m_bTriStateReload)
	{
		m_sounds.LoadSound(section, "snd_open_weapon", "sndOpen", false, m_eSoundOpen);
		m_sounds.LoadSound(section, "snd_add_cartridge", "sndAddCartridge", false, m_eSoundAddCartridge);

		if (WeaponSoundExist(section, "snd_add_cartridge_empty"))
			m_sounds.LoadSound(section, "snd_add_cartridge_empty", "sndAddCartridgeEmpty", false, m_eSoundAddCartridge);

		m_sounds.LoadSound(section, "snd_close_weapon", "sndClose", false, m_eSoundClose);

		if (WeaponSoundExist(section, "snd_close_weapon_empty"))
			m_sounds.LoadSound(section, "snd_close_weapon_empty", "sndCloseEmpty", false, m_eSoundClose);

		if (pSettings->line_exist(hud_sect, "add_cartridge_in_open"))
			m_bAddCartridgeOpen = pSettings->r_bool(hud_sect, "add_cartridge_in_open");

		if (pSettings->line_exist(hud_sect, "empty_preload_mode"))
			m_bEmptyPreloadMode = pSettings->r_bool(hud_sect, "empty_preload_mode");

		if (m_bAddCartridgeOpen)
			m_sounds.LoadSound(section, "snd_open_weapon_empty", "sndOpenEmpty", false, m_eSoundOpen);

		if (m_bEmptyPreloadMode)
		{
			m_sounds.LoadSound(section, "snd_add_cartridge_preloaded", "sndAddCartridgePreloaded", false, m_eSoundOpen);
			m_sounds.LoadSound(section, "snd_close_weapon_preloaded", "sndClosePreloaded", false, m_eSoundClose);
		}
	};

}

void CWeaponShotgun::switch2_Fire()
{
	inherited::switch2_Fire	();
	bWorking = false;
}

void CWeaponShotgun::OnAnimationEnd(u32 state) 
{
	bool isGuns = EngineExternal()[EEngineExternalGunslinger::EnableGunslingerMode];
	if (!m_bTriStateReload || state != eReload || (IsMisfire() && isGuns || IsMisfire() && HudAnimationExist("anm_reload_misfire")))
	{
		bStopReloadSignal = false;
		bPreloadAnimAdapter = false;
		return inherited::OnAnimationEnd(state);
	}

	if (CActor* pActor = smart_cast<CActor*>(H_Parent()))
	{
		pActor->callback(GameObject::eActorHudAnimationEnd)(lua_game_object(), hud_sect.c_str(), m_current_motion.c_str(), state, animation_slot());
	}

	switch (m_sub_state)
	{
	case eSubstateReloadBegin:
	{
		m_sub_state = eSubstateReloadInProcess;
		SwitchState(eReload);
	}break;
	case eSubstateReloadInProcess:
	{
		if (0 != AddCartridge(1) || bStopReloadSignal)
			m_sub_state = eSubstateReloadEnd;

		SwitchState(eReload);
	}break;
	case eSubstateReloadEnd:
	{
		bStopReloadSignal = false;
		bReloadKeyPressed = false;
		bAmmotypeKeyPressed = false;
		SwitchState(eIdle);
	}break;

	};
}

bool CWeaponShotgun::TryReload()
{
	if (m_bTriStateReload)
		return TriStateReload();

	return inherited::TryReload();
}

bool CWeaponShotgun::TriStateReload()
{
	if (m_magazine.size() == (u32)iMagazineSize || !HaveCartridgeInInventory(1))
		return false;

	m_sub_state = eSubstateReloadBegin;
	SwitchState(eReload);
	return true;
}

void CWeaponShotgun::OnStateSwitch(u32 S)
{
	bool isGuns = EngineExternal()[EEngineExternalGunslinger::EnableGunslingerMode];
	if (!m_bTriStateReload || S != eReload || (IsMisfire() && isGuns || IsMisfire() && HudAnimationExist("anm_reload_misfire")))
	{
		bStopReloadSignal = false;
		bPreloadAnimAdapter = false;
		inherited::OnStateSwitch(S);
		return;
	}

	CWeapon::OnStateSwitch(S);

	if (m_magazine.size() == (u32)iMagazineSize || !HaveCartridgeInInventory(1))
	{
		switch2_EndReload();
		m_sub_state = eSubstateReloadEnd;
		return;
	};

	switch (m_sub_state)
	{
	case eSubstateReloadBegin:
	{
		if (HaveCartridgeInInventory(1))
		{
			switch2_StartReload();
			bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;
			if (TempTest && m_bAddCartridgeOpen || !bPreloadAnimAdapter)
				AddCartridge(1);
		}
	}break;
	case eSubstateReloadInProcess:
	{
		if (HaveCartridgeInInventory(1))
			switch2_AddCartgidge();
	}break;
	case eSubstateReloadEnd:
		switch2_EndReload();
		break;
	};
}

void CWeaponShotgun::switch2_StartReload()
{
	PlayAnimOpenWeapon();
	SetPending(TRUE);

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	if (m_sounds.FindSoundItem("sndOpenEmpty", false) && m_bAddCartridgeOpen && TempTest)
		PlaySound("sndOpenEmpty", get_LastFP());
	else
		PlaySound("sndOpen", get_LastFP());
}

void CWeaponShotgun::switch2_AddCartgidge()
{
	PlayAnimAddOneCartridgeWeapon();
	SetPending(TRUE);

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	if (m_sounds.FindSoundItem("sndAddCartridgeEmpty", false) && !m_bAddCartridgeOpen && TempTest)
		PlaySound("sndAddCartridgeEmpty", get_LastFP());
	else if (m_bEmptyPreloadMode && bPreloadAnimAdapter)
		PlaySound("sndAddCartridgePreloaded", get_LastFP());
	else
		PlaySound("sndAddCartridge", get_LastFP());
}

void CWeaponShotgun::switch2_EndReload()
{
	SetPending(TRUE);
	PlayAnimCloseWeapon();

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	if (m_sounds.FindSoundItem("sndCloseEmpty", false) && !m_bAddCartridgeOpen && TempTest)
		PlaySound("sndCloseEmpty", get_LastFP());
	else if (m_bEmptyPreloadMode && bPreloadAnimAdapter)
		PlaySound("sndClosePreloaded", get_LastFP());
	else
		PlaySound("sndClose", get_LastFP());
}

void CWeaponShotgun::PlayAnimOpenWeapon()
{
	VERIFY(GetState() == eReload);

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	xr_string anm_name = "anm_open";

	if (m_bEmptyPreloadMode && TempTest)
	{
		anm_name += "_empty";
		bPreloadAnimAdapter = true;
	}

	PlayHUDMotion(anm_name, false, this, GetState(), false);
}

void CWeaponShotgun::PlayAnimAddOneCartridgeWeapon()
{
	VERIFY(GetState() == eReload);

	xr_string anm_name = "anm_add_cartridge";

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	if (m_bEmptyPreloadMode && bPreloadAnimAdapter)
	{
		if (TempTest)
			anm_name += "_empty_preloaded";
		else
			anm_name += "_preloaded";

		bPreloadAnimAdapter = false;
	}
	else if (!m_bAddCartridgeOpen && TempTest)
		anm_name += "_empty";

	PlayHUDMotion(anm_name, false, this, GetState(), false);
}

void CWeaponShotgun::PlayAnimCloseWeapon()
{
	VERIFY(GetState() == eReload);

	xr_string anm_name = "anm_close";

	bool TempTest = m_bAmmoInChamber ? iAmmoElapsed == 0 && iAmmoInChamberElapsed == 0 : iAmmoElapsed == 0;

	if (m_bEmptyPreloadMode && bPreloadAnimAdapter)
	{
		if (TempTest)
			anm_name = "anm_add_cartridge_empty_preloaded";
		else
			anm_name += "_preloaded";

		bPreloadAnimAdapter = false;
	}
	else if (!m_bAddCartridgeOpen && TempTest)
		anm_name = "anm_add_cartridge_empty";

	PlayHUDMotion(anm_name, false, this, GetState(), false);
}

void	CWeaponShotgun::net_Export	(NET_Packet& P)
{
	inherited::net_Export(P);	
	P.w_u8(u8(m_magazine.size()));	
	for (u32 i=0; i<m_magazine.size(); i++)
	{
		CCartridge& l_cartridge = *(m_magazine.begin()+i);
		P.w_u8(l_cartridge.m_LocalAmmoType);
	}
}

void	CWeaponShotgun::net_Import	(NET_Packet& P)
{
	inherited::net_Import(P);	
	u8 AmmoCount = P.r_u8();
	for (u32 i=0; i<AmmoCount; i++)
	{
		u8 LocalAmmoType = P.r_u8();
		if (i>=m_magazine.size()) continue;
		CCartridge& l_cartridge = *(m_magazine.begin()+i);
		if (LocalAmmoType == l_cartridge.m_LocalAmmoType) continue;
#ifdef DEBUG
		Msg("! %s reload to %s", *l_cartridge.m_ammoSect, m_ammoTypes[LocalAmmoType].c_str());
#endif
		l_cartridge.Load( m_ammoTypes[LocalAmmoType].c_str(), LocalAmmoType );
	}
}

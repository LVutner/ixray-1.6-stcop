#pragma once
#include "inventory_item_object.h"
#include "hudsound.h"
#include "customzone.h"
#include "artefact.h"
#include "../xrSound/ai_sounds.h"

#include "CustomDetectorZones.h"

class CUIArtefactDetectorBase;

class CCustomDetector :		public CHudItemObject
{
	typedef	CHudItemObject	inherited;
protected:
	CUIArtefactDetectorBase*			m_ui;
	bool			m_bFastAnimMode;
	bool			m_bNeedActivation;

public:
					CCustomDetector		();
	virtual			~CCustomDetector	();

	virtual BOOL 	net_Spawn			(CSE_Abstract* DC);
	virtual void 	Load				(LPCSTR section);

	virtual void 	OnH_A_Chield		();
	virtual void 	OnH_B_Independent	(bool just_before_destroy);

	virtual void 	shedule_Update		(u32 dt);
	virtual void 	UpdateCL			();


			bool 	IsWorking			();

	virtual void 	OnMoveToSlot		(const SInvItemPlace& prev);
	virtual void 	OnMoveToRuck		(const SInvItemPlace& prev);

	virtual void	OnActiveItem		();
	virtual void	OnHiddenItem		();
	virtual void	OnStateSwitch		(u32 S);
	virtual void	OnAnimationEnd		(u32 state);
	virtual	void	UpdateXForm			();

	void			ToggleDetector		(bool bFastMode);
	void			HideDetector		(bool bFastMode);
	void			ShowDetector		(bool bFastMode);
	float			m_fAfDetectRadius;
	virtual bool	CheckCompatibility	(CHudItem* itm);

	virtual u32		ef_detector_type	() const	{return 1;};

	virtual bool	NeedActivation		() const	{return m_bNeedActivation;};

	void 	TurnDetectorInternal		(bool b);
	void	ForceHide					() { SwitchState(eHiding); }

protected:
			bool	CheckCompatibilityInt		(CHudItem* itm, u16* slot_to_activate);
	void 			UpdateNightVisionMode		(bool b_off);
	void			UpdateVisibility			();
	virtual void	UpfateWork					();
	virtual void 	UpdateAf					()				{};
	virtual void 	CreateUI					()				{};
	void SetHideDetStateInWeapon() const;

	bool			m_bWorking;
	float			m_fAfVisRadius;
	bool			isTryToToggle;
	bool			bNeedHideDet;

	CAfList			m_artefacts;
};
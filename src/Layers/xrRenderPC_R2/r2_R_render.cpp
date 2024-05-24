#include "stdafx.h"
#include "../../xrEngine/igame_persistent.h"
#include "../xrRender/FBasicVisual.h"
#include "../../xrEngine/customhud.h"
#include "../../xrEngine/xr_object.h"

void CRender::render_main	(bool deffered, bool zfill)
{
//	Msg						("---begin");
	marker					++;
	bool dont_test_sectors = Sectors.size() <= 1;
	// Calculate sector(s) and their objects
	if (pLastSector)		{
		//!!!
		//!!! BECAUSE OF PARALLEL HOM RENDERING TRY TO DELAY ACCESS TO HOM AS MUCH AS POSSIBLE
		//!!!
		if(deffered)
		{
			// Traverse object database
			g_SpatialSpace->q_frustum
				(
				lstRenderablesMain,
				ISpatial_DB::O_ORDERED,
				STYPE_RENDERABLE + STYPE_RENDERABLESHADOW + STYPE_PARTICLE + STYPE_LIGHTSOURCE,
				ViewBase
				);

			// (almost) Exact sorting order (front-to-back)
			std::sort(lstRenderablesMain.begin(), lstRenderablesMain.end(), [](ISpatial* _1, ISpatial* _2) {
			float d1 = _1->spatial.sphere.P.distance_to_sqr(Device.vCameraPosition);
			float d2 = _2->spatial.sphere.P.distance_to_sqr(Device.vCameraPosition);
			return d1 < d2;
			});

			// Determine visibility for dynamic part of scene
			set_Object							(0);
			u32 uID_LTRACK						= 0xffffffff;
			if (phase==CRender::PHASE_NORMAL)
			{
				// update light-vis for current entity / actor
				if (CObject* O = g_pGameLevel->CurrentViewEntity())
				{
					if(!O->getDestroy())
					{
						if (CROS_impl*	R = (CROS_impl*)O->ROS())
							R->update(O);
					}
				}

				if (lstRenderablesMain.size())
				{
					uLastLTRACK	++;
					uID_LTRACK = uLastLTRACK%lstRenderablesMain.size();

					// update light-vis for selected entity
					// track lighting environment
					if (IRenderable* renderable = (IRenderable*)lstRenderablesMain[uID_LTRACK]->dcast_Renderable())
					{
						if (CROS_impl* T = (CROS_impl*)renderable->renderable_ROS())
							T->update(renderable);
					}
				}
			}
		}
		Fmatrix mftrans;
		if(zfill)
		{
			Fmatrix m_project;
			m_project.build_projection(
				deg2rad(Device.fFOV/* *Device.fASPECT*/), 
				Device.fASPECT, VIEWPORT_NEAR, 
				ps_r2_zfill * g_pGamePersistent->Environment().CurrentEnv->far_plane);
			mftrans.mul(m_project,Device.mView);
		}
		else
			mftrans = Device.mFullTransform;
		// Traverse sector/portal structure
		if (!dont_test_sectors)
		{
			PortalTraverser.traverse	
				(
				pLastSector,
				ViewBase,
				Device.vCameraPosition,
				mftrans,
				CPortalTraverser::VQ_HOM + CPortalTraverser::VQ_SSA + CPortalTraverser::VQ_FADE
				//. disabled scissoring (HW.Caps.bScissor?CPortalTraverser::VQ_SCISSOR:0)	// generate scissoring info
				);
		}
		// Determine visibility for static geometry hierrarhy
		if(psDeviceFlags.test(rsDrawStatic))
		{
			if (dont_test_sectors)
			{
				CSector*	sector		= (CSector*)Sectors[0];
				set_Frustum			(&ViewBase);
				add_Geometry		(sector->root());
			}
			else
			{
				for (u32 s_it=0; s_it<PortalTraverser.r_sectors.size(); s_it++)
				{
					CSector*	sector		= (CSector*)PortalTraverser.r_sectors[s_it];
					dxRender_Visual*	root	= sector->root();
					for (u32 v_it=0; v_it<sector->r_frustums.size(); v_it++)	{
						set_Frustum			(&(sector->r_frustums[v_it]));
						add_Geometry		(root);
					}
				}
			}
		}

		// Traverse frustums
		for (u32 o_it=0; o_it<lstRenderablesMain.size(); o_it++)
		{
			ISpatial*	spatial	= lstRenderablesMain[o_it];
			if	(0==spatial) continue; spatial->spatial_updatesector();
			CSector* sector = (CSector*)spatial->spatial.sector;
			if	(0==sector) continue;
			Fbox sp_box;
			sp_box.setb(spatial->spatial.sphere.P,Fvector().set(spatial->spatial.sphere.R, spatial->spatial.sphere.R, spatial->spatial.sphere.R));
			if(!HOM.visible(sp_box)) continue;

			if ((spatial->spatial.type & STYPE_LIGHTSOURCE) && deffered)
			{
				// lightsource
				if(light* L = (light*)(spatial->dcast_Light()))
				{
					if (L->get_LOD()>EPS_L)
					{
						if (dont_test_sectors)
							Lights.add_light(L);
						else
						{
							xr_vector<IRender_Sector*> m_sectors = {};
							bool traversed = false;
							if(L->flags.type == IRender_Light::SPOT || L->flags.type == IRender_Light::DIRECT)
							{
								LR.compute_xf_spot	(L);
								CFrustum	temp;
								temp.CreateFromMatrix			(L->X.S.combine,	FRUSTUM_P_ALL &(~FRUSTUM_P_NEAR));

								m_sectors = detectSectors_frustum(sector, &temp);
								for (u32 s_it = 0; s_it < m_sectors.size(); s_it++)
								{
									CSector* sector_ = (CSector*)m_sectors[s_it];
									if(PortalTraverser.i_marker == sector_->r_marker)
										traversed = true;
								}
								
							}
							else
							{
								m_sectors = detectSectors_sphere(sector, L->position, Fvector().set(L->range, L->range, L->range));
								for (u32 s_it = 0; s_it < m_sectors.size(); s_it++)
								{
									CSector* sector_ = (CSector*)m_sectors[s_it];
									if(PortalTraverser.i_marker == sector_->r_marker)
										traversed = true;
								}
							}

							if(!m_sectors.size())
								traversed = true;
							else
							{
								if(L->flags.type == IRender_Light::POINT && spatial->spatial.sphere.P.distance_to_sqr(Device.vCameraPosition) < _sqr(spatial->spatial.sphere.R))
									traversed = true;
							}
							


							if(traversed)
							{
								//dbg_light_renderer(L, color_rgba(0,255,100,255), m_sectors.size());
								Lights.add_light(L);
							}
							//else
							//{
							//	dbg_light_renderer(L, color_rgba(255,0,100,255), m_sectors.size());
							//}
						}
					}
				}
				continue;
			}
			if (dont_test_sectors)
			{
				if (spatial->spatial.type & STYPE_RENDERABLE && psDeviceFlags.test(rsDrawDynamic))
				{
					// renderable
					if	(IRenderable* renderable = spatial->dcast_Renderable())
					{
						// Rendering
						set_Object						(renderable);
						renderable->renderable_Render();
						set_Object						(0);
					}
				}

				if (spatial->spatial.type & STYPE_PARTICLE && !deffered)
				{
					// renderable
					if	(IRenderable* renderable = spatial->dcast_Renderable())
					{
						// Rendering
						set_Object						(renderable);
						renderable->renderable_Render();
						set_Object						(0);
					}
				}
			}
			else
			{
				if	(PortalTraverser.i_marker != sector->r_marker)	continue;	// inactive (untouched) sector
				for (u32 v_it=0; v_it<sector->r_frustums.size(); v_it++)
				{
					CFrustum&	view	= sector->r_frustums[v_it];
					if (!view.testSphere_dirty(spatial->spatial.sphere.P,spatial->spatial.sphere.R))	continue;

					if (spatial->spatial.type & STYPE_RENDERABLE && psDeviceFlags.test(rsDrawDynamic))
					{
						// renderable
						if	(IRenderable* renderable = spatial->dcast_Renderable())
						{
							// Rendering
							set_Object						(renderable);
							renderable->renderable_Render();
							set_Object						(0);
						}
					}

					if (spatial->spatial.type & STYPE_PARTICLE && !deffered)
					{
						// renderable
						if	(IRenderable* renderable = spatial->dcast_Renderable())
						{
							// Rendering
							set_Object						(renderable);
							renderable->renderable_Render();
							set_Object						(0);
						}
					}
				}
			}
		}
		if (g_pGameLevel && psDeviceFlags.test(rsDrawDynamic) && (phase==PHASE_NORMAL))	g_hud->Render_Last();		// HUD
	}
	else
	{
		set_Object									(0);
		if (g_pGameLevel && psDeviceFlags.test(rsDrawDynamic) && (phase==PHASE_NORMAL))	g_hud->Render_Last();		// HUD
	}
}

void CRender::render_menu	()
{
	//	Globals
	RCache.set_CullMode				(CULL_CCW);
	RCache.set_Stencil				(FALSE);
	RCache.set_ColorWriteEnable		();

	// Main Render
	{
		Target->u_setrt						(Target->rt_Generic_0,0,0,RDepth);		// LDR RT
		g_pGamePersistent->OnRenderPPUI_main()	;	// PP-UI
	}
	// Distort
	{
		Target->u_setrt						(Target->rt_Generic_1,0,0,RDepth);		// Now RT is a distortion mask
		CHK_DX(RDevice->Clear			( 0L, nullptr, D3DCLEAR_TARGET, color_rgba(127,127,0,127), 1.0f, 0L));
		g_pGamePersistent->OnRenderPPUI_PP	()	;	// PP-UI
	}

	// Actual Display
	Target->u_setrt					( RCache.get_width(),RCache.get_height(),RTarget,nullptr,nullptr,RDepth);
	RCache.set_Shader				( Target->s_menu	);
	RCache.set_Geometry				( Target->g_menu	);

	Fvector2						p0,p1;
	u32								Offset;
	u32		C						= color_rgba	(255,255,255,255);
	float	_w						= float(RCache.get_width());
	float	_h						= float(RCache.get_height());
	float	d_Z						= EPS_S;
	float	d_W						= 1.f;
	p0.set							(.5f/_w, .5f/_h);
	p1.set							((_w+.5f)/_w, (_h+.5f)/_h );

	FVF::TL* pv						= (FVF::TL*) RCache.Vertex.Lock	(4,Target->g_menu->vb_stride,Offset);
	pv->set							(EPS,			float(_h+EPS),	d_Z,	d_W, C, p0.x, p1.y);	pv++;
	pv->set							(EPS,			EPS,			d_Z,	d_W, C, p0.x, p0.y);	pv++;
	pv->set							(float(_w+EPS),	float(_h+EPS),	d_Z,	d_W, C, p1.x, p1.y);	pv++;
	pv->set							(float(_w+EPS),	EPS,			d_Z,	d_W, C, p1.x, p0.y);	pv++;
	RCache.Vertex.Unlock			(4,Target->g_menu->vb_stride);
	RCache.Render					(D3DPT_TRIANGLELIST,Offset,0,4,0,2);
}

extern u32 g_r;
void CRender::Render		()
{
	g_r						= 1;
	VERIFY					(0==mapDistort.size());

	bool	_menu_pp		= g_pGamePersistent?g_pGamePersistent->OnRenderPPUI_query():false;
	if (_menu_pp)			{
		render_menu			()	;
		return					;
	};

	IMainMenu*	pMainMenu = g_pGamePersistent?g_pGamePersistent->m_pMainMenu:0;
	bool	bMenu = pMainMenu?pMainMenu->CanSkipSceneRendering():false;

	if (!(g_pGameLevel && g_hud) || bMenu) {
		Target->u_setrt(RCache.get_width(), RCache.get_height(), RTarget, nullptr, nullptr, RDepth);
		return;
	}

	if( m_bFirstFrameAfterReset )
	{
		m_bFirstFrameAfterReset = false;
		return;
	}

//.	VERIFY					(g_pGameLevel && g_pGameLevel->pHUD);

	// Configure
	RImplementation.o.distortion				= FALSE;		// disable distorion
	Fcolor					sun_color			= ((light*)Lights.sun_adapted._get())->color;
	bool					bSUN				= !o.sunstatic && (u_diffuse2s(sun_color.r,sun_color.g,sun_color.b)>EPS);
	// Msg						("sstatic: %s, sun: %s",o.sunstatic?"true":"false", bSUN?"true":"false");

	// HOM
	ViewBase.CreateFromMatrix					(Device.mFullTransform, FRUSTUM_P_LRTB + FRUSTUM_P_FAR);
	View										= 0;
	if (!ps_r2_ls_flags.test(R2FLAG_EXP_MT_CALC))	{
		HOM.Enable									();
		HOM.Render									(ViewBase);
	}

	//******* Z-prefill calc - DEFERRER RENDERER
	if (ps_r2_ls_flags.test(R2FLAG_ZFILL))		{
		Device.Statistic->RenderCALC.Begin			();
		r_pmask										(true,false);	// enable priority "0"
		set_Recorder								(nullptr)		;
		phase										= PHASE_SMAP;
		render_main									(false,true)	;
		r_pmask										(true,false);	// disable priority "1"
		Device.Statistic->RenderCALC.End				( )			;

		// flush
		Target->phase_scene_prepare					();
		RCache.set_ColorWriteEnable					(FALSE);
		r_dsgraph_render_graph						(0);
		RCache.set_ColorWriteEnable					( );
	} else {
		Target->phase_scene_prepare					();
	}

	//*******
	// Sync point
	Device.Statistic->RenderDUMP_Wait_S.Begin	();
	if (1)
	{
		CTimer	T;							T.Start	();
		BOOL	result						= FALSE;
		HRESULT	hr							= S_FALSE;
		while	((hr=q_sync_point[q_sync_count]->GetData	(&result,sizeof(result),D3DGETDATA_FLUSH))==S_FALSE) {
			if (!SwitchToThread())			Sleep(ps_r2_wait_sleep);
			if (T.GetElapsed_ms() > 500)	{
				result	= FALSE;
				break;
			}
		}
	}
	Device.Statistic->RenderDUMP_Wait_S.End		();
	q_sync_count								= (q_sync_count+1)%Caps.iGPUNum;
	CHK_DX										(q_sync_point[q_sync_count]->Issue(D3DISSUE_END));

	//******* Main calc - DEFERRER RENDERER
	// Main calc
	Device.Statistic->RenderCALC.Begin			();
	r_pmask										(true,false,true);	// enable priority "0",+ capture wmarks
	if (bSUN)									set_Recorder	(&main_coarse_structure);
	else										set_Recorder	(nullptr);
	phase										= PHASE_NORMAL;
	render_main									(true);
	set_Recorder								(nullptr);
	r_pmask										(true,false);	// disable priority "1"
	Device.Statistic->RenderCALC.End			();

	BOOL	split_the_scene_to_minimize_wait		= FALSE;
	if (ps_r2_ls_flags.test(R2FLAG_EXP_SPLIT_SCENE))	split_the_scene_to_minimize_wait=TRUE;

	//******* Main render :: PART-0	-- first
	if (!split_the_scene_to_minimize_wait)
	{
		// level, DO NOT SPLIT
		Target->phase_scene_begin				();
		r_dsgraph_render_hud					();
		r_dsgraph_render_graph					(0);
		r_dsgraph_render_lods					(true,true);
		if(Details)	Details->Render				();
		Target->phase_scene_end					();
	} else {
		// level, SPLIT
		Target->phase_scene_begin				();
		r_dsgraph_render_graph					(0);
		Target->disable_aniso					();
	}

	//******* Occlusion testing of volume-limited light-sources
	Target->phase_occq							();
	LP_normal.clear								();
	LP_pending.clear							();
	{
		// perform tests
		size_t count = 0;
		light_Package& LP = Lights.package;

		// stats
		stats.l_shadowed = (u32)LP.v_shadowed.size();
		stats.l_unshadowed = (u32)LP.v_point.size() + (u32)LP.v_spot.size();
		stats.l_total = stats.l_shadowed + stats.l_unshadowed;

		// perform tests
		count = std::max(count, LP.v_point.size());
		count = std::max(count, LP.v_spot.size());
		count = std::max(count, LP.v_shadowed.size());

		for (size_t it = 0; it < count; it++) {
			if (it < LP.v_point.size()) {
				light* L = LP.v_point[it];
				L->vis_prepare();
				if (L->vis.pending)	LP_pending.v_point.push_back(L);
				else				LP_normal.v_point.push_back(L);
			}

			if (it < LP.v_spot.size()) {
				light* L = LP.v_spot[it];
				L->vis_prepare();
				if (L->vis.pending)	LP_pending.v_spot.push_back(L);
				else				LP_normal.v_spot.push_back(L);
			}

			if (it < LP.v_shadowed.size()) {
				light* L = LP.v_shadowed[it];
				L->vis_prepare();
				if (L->vis.pending)	LP_pending.v_shadowed.push_back(L);
				else				LP_normal.v_shadowed.push_back(L);
			}
		}
	}
	LP_normal.sort							();
	LP_pending.sort							();

	//******* Main render :: PART-1 (second)
	if(split_the_scene_to_minimize_wait) {
		// level
		Target->phase_scene_begin();
		r_dsgraph_render_hud();
		r_dsgraph_render_lods(true, true);
		if(Details)	Details->Render();
		Target->phase_scene_end();
	}

	if (g_hud && g_hud->RenderActiveItemUIQuery())
	{
		Target->phase_wallmarks();
		r_dsgraph_render_hud_ui();
	}

	// Wall marks
	if(Wallmarks)	{
		Target->phase_wallmarks					();
		g_r										= 0;
		Wallmarks->Render						();				// wallmarks has priority as normal geometry
	}

	// Update incremental shadowmap-visibility solver
	{
		u32 it=0;
		for (it=0; it<Lights_LastFrame.size(); it++)	{
			if (0==Lights_LastFrame[it])	continue	;
			try {
				Lights_LastFrame[it]->svis.flushoccq()	;
			} catch (...)
			{
				Msg	("! Failed to flush-OCCq on light [%d] %X",it,*(u32*)(&Lights_LastFrame[it]));
			}
		}
		Lights_LastFrame.clear	();
	}

	// Directional light - fucking sun
	if (bSUN)	{
		RImplementation.stats.l_visible		++;
		render_sun_cascades					();
	}

	{
		Target->phase_accumulator					();
		// Render emissive geometry, stencil - write 0x0 at pixel pos
		RCache.set_xform_project					(Device.mProject); 
		RCache.set_xform_view						(Device.mView);
		// Stencil - write 0x1 at pixel pos - 
		RCache.set_Stencil							( TRUE,D3DCMP_ALWAYS,0x01,0xff,0xff,D3DSTENCILOP_KEEP,D3DSTENCILOP_REPLACE,D3DSTENCILOP_KEEP);
		//RCache.set_Stencil						(TRUE,D3DCMP_ALWAYS,0x00,0xff,0xff,D3DSTENCILOP_KEEP,D3DSTENCILOP_REPLACE,D3DSTENCILOP_KEEP);
		RCache.set_CullMode							(CULL_CCW);
		RCache.set_ColorWriteEnable					();
		RImplementation.r_dsgraph_render_emissive	();

		// Stencil	- draw only where stencil >= 0x1
		RCache.set_Stencil					(TRUE,D3DCMP_LESSEQUAL,0x01,0xff,0x00);
		RCache.set_CullMode					(CULL_NONE);
		RCache.set_ColorWriteEnable			();
	}

	// Lighting, non dependant on OCCQ
	Target->phase_accumulator				();
	HOM.Disable								();
	render_lights							(LP_normal);
	
	// Lighting, dependant on OCCQ
	render_lights							(LP_pending);

	// Postprocess
	Target->phase_combine					();
	VERIFY	(0==mapDistort.size());
}

void CRender::render_forward				()
{
	VERIFY	(0==mapDistort.size());
	RImplementation.o.distortion				= RImplementation.o.distortion_enabled;	// enable distorion

	//******* Main render - second order geometry (the one, that doesn't support deffering)
	//.todo: should be done inside "combine" with estimation of of luminance, tone-mapping, etc.
	{
		HOM.Enable();
		// level
		r_pmask									(false,true);			// enable priority "1"
		phase									= PHASE_NORMAL;
		render_main								(false);//
		//	Igor: we don't want to render old lods on next frame.
		mapLOD.clear							();
		r_dsgraph_render_graph					(1)	;					// normal level, secondary priority
		PortalTraverser.fade_render				()	;					// faded-portals
		r_dsgraph_render_sorted					()	;					// strict-sorted geoms
		g_pGamePersistent->Environment().RenderLast()	;					// rain/thunder-bolts
	}

	RImplementation.o.distortion				= FALSE;				// disable distorion
}

void CRender::BeforeWorldRender() {}

void CRender::AfterWorldRender()
{
	if (Device.m_SecondViewport.IsSVPFrame())
	{
		IDirect3DSurface9* pBackBuffer = NULL;
		RDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		//D3DXLoadSurfaceFromSurface(Target->rt_secondVP->pRT, 0, 0, pBackBuffer, 0, 0, D3DX_DEFAULT, 0);
		RDevice->StretchRect(pBackBuffer, NULL, Target->rt_secondVP->pRT, NULL, D3DTEXF_NONE);
		pBackBuffer->Release();
	}
}
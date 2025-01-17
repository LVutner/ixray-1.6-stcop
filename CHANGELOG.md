# Changelog

Full changelog of _IX-Ray_ 1.6 project

## Release 0.10 (April 2024)

### Common

- Improved CMake projects structure (@ForserX)
- Implemented changelog builder (@Drombeys)
- Published RelWithDebInfo configuration in `publish-engine` job (@Drombeys)
- Disabled ImGui debug render on Release build (@ForserX)
- Updated `magic_enum` dependency (@ForserX)
- Moved MagicFM into 3rd Party directory (@ForserX)
- Replaced DirectPlay 8 with GameNetworkingSockets in xrNetServer (@ForserX, @acidicMercury8)
- Added LuaUtf8 plugin (@ForserX)
- Updated application icon (@Drombeys)
- Fixed warnings (@Drombeys, @ForserX)
- Replaced `xr_new` use with redefined allocator (@ForserX)
- Added LuaPanda sources (@ForserX)
- Added LuaSocket sources (@ForserX)
- Added LZO sources (@ForserX)
- Added LuaXML plugin (@ForserX)
- Added upgraded OPCODE files (@ForserX)
- Added GDB config (@ForserX, @vertver)
- Implemented basic Linux support (@ForserX)
- Added compressor option to CMake (@ForserX)
- Added oneTBB NuGet package (@ForserX, @acidicMercury8)

### Engine

- Initialized gamepad support (@ForserX)
- Moved logging in separate thread (@Drombeys, @Giperion, @ForserX)
- Implemented XMLOverride subsystem (@ForserX)
- Implemented DLTX support (@ForserX)
- Fixed iterators definition (@Drombeys)
- Resolved multiple memory corruption issues (@ForserX)
- Refactored `g_actor` external (@Hozar2002)
- Fixed xrCore build on ARM64 (@ForserX)
- Fixed application not closing on window manager request (@ggGhosTt)
- Added `$arch_dir_addons$` for addons (@ForserX)
- Removed `.0000` from `float`/`double` to `xr_string` conversion (@ForserX)
- Fixed XML Expression work without Actor ptr (@ForserX)
- Reworked `Core.Params` using (@ForserX)
- Deleted dead code in `NET_Packet` (@ForserX)
- Replaced `__super` with inherited in `CGamePersistent` class (@ugozapad)
- Fixed flushing log on application close (@Hozar2002)
- Added objects iterator to luabind (@ForserX)
- Reworked ImGUI integration (@ForserX, @ugozapad)
- Added UTF8 helper functions (@ForserX)
- Fixed valid function in `_cylinder` module (@Drombeys)
- Implemented thread-safe casting for UTF-8 conversions (@ForserX)
- Made `CObjectSpace` thread-safe (@ForserX)
- Fixed `CLocatorAPI::Recurse` method (@ForserX)
- Used fonts from X-Ray file system for ImGUI (@ForserX, @Drombeys)
- Fixed Discord activation on game start (@ForserX)
- Transferred code to base X-Ray types and functions (@ForserX)
- Added calculation for file size (@ForserX)
- Enabled `/sdl` compile option (@Drombeys)
- Fixed double UTF8 cast (@ForserX)
- Fixed incorrect hook stack using (@ForserX)
- Added Win1252 codepage support (@ForserX, @ggGhosTt)
- Added `parallel_for` to `compute_static_cover` method (@ForserX)
- Added base multi-threading types (@ForserX)
- Implemented spawn particles console command (@v2v3v4)
- Implemented FPS counter (@OldSerpskiStalker, @ForserX)
- Implemented safeguards for user settings handling (@ForserX)
- Deleted deprecated Lua debug tools (@ForserX)
- Implemented support for LuaSockets and LuaPanda (@ForserX)
- Implemented CDB caching system (@ForserX, @Drombeys)
- Made `ray_collider` non-template (@ForserX)
- Updated xrCDB to use new OPCODE (@ForserX)
- Deleted `D3D9-Null` project (@ForserX)
- Enabled file exclusion support in filesystem (@ForserX)
- Used new LZO project (@ForserX)
- Reworked doug lea allocator (@ForserX)
- Deleted deprecated `__stdcall` use (@ForserX)
- Improved output of StackTrace log (@OldSerpskiStalker)
- Enabled printing GPU info to log (@v2v3v4)
- Fixed `Alt+I` and `Ctrl+Alt+I` hotkeys work (@ForserX)
- Used Steam Sockets only on enabled `IXRAY_MP` option (@ForserX)
- Replaced `GetTickCount` callings with `SDL_GetTicks` (@ForserX)
- Added null game factory (@ForserX)
- Implemented heterogeneous lookup for `shared_str` and `xr_string` (@ForserX)
- Implemented device overloading (@ForserX)
- Performed cleanup on xrPhysics (@ForserX)

### Render

- Fixed fullscreen behaviour (@ggGhosTt, @Drombeys, @ugozapad)
- Fixed bullet tracer rendering (@Hozar2002)
- Fixed debug render (@ugozapad)
- Fixed console drawing in debug mode (@ugozapad)
- Fixed volumetric fog working without texture (@ForserX)
- Replaced D3DX with DirectXTex for texture creating (@Drombeys, @Hozar2002)
- Replaced D3DX with DirectXTex for texture loading (@Drombeys, @Hozar2002, @ugozapad)
- Implemented `D3D9FindShaderComment` function and shader utils (@Drombeys)
- Added forced window synchronization (@Drombeys, @ForserX)
- Fixed window resizing (@ugozapad)
- Added 32bit animations support (@ForserX)
- Fixed display mode enumeration (@ugozapad)
- Made shader cache usage optional (@MAYLAYSHEZ)
- Fixed detail positioning on curved surfaces (@v2v3v4)
- Removed hardcoded wallmarks type (@ForserX)
- Added optional particle effect lifetimes in real delta time mode (@v2v3v4)
- Disabled shedule optimizations for `CTorridzone::net_destroy()` method (@v2v3v4)
- Reworked particles update switcher (@ForserX)
- Added `mtParticles` console command (@v2v3v4)
- Added `r_particles_real_dt` console command (@v2v3v4)
- Restored parallel texture loading (@ForserX, @Drombeys)
- Fixed memory leaks in font creation (@Drombeys)
- Refactored `dx9Texture` module (@Drombeys)
- Omitted container creation from stack (@ForserX)
- Implemented geometry culling (@tatarinrafa, @ggGhosTt)
- Implemented loading screen in XML (@ggGhosTt)
- Fixed cursor dragging when centered (@ggGhosTt)
- Implemented multi-threaded processing for particles (@ForserX)
- Integrated DxErr library for DirectX errors debugging (@ForserX)

### Gameplay

- Fixed shooting state (@Shtrecker)
- Fixed shooting from weapons on `CWeaponRPG7` and `CWeaponRG6` class (@Shtrecker)
- Bypassed actor's death during surge in god mode (@ggGhosTt)
- Added configurable respawn time to smart covers (@OldSerpskiStalker)
- Fixed actor's car animations (@ggGhosTt, @v2v3v4)
- Added camera-switch control to change between car cameras (@ggGhosTt)
- Added custom car use callbacks (@ForserX)
- Skipped incorrect action names (@ForserX)
- Added multi spawn loadouts feature (@OldSerpskiStalker)
- Made car dashboard (@ForserX)
- Made car doors usable (@ForserX, @v2v3v4)
- Made monster looting optional (@ForserX)
- Fixed artefact condition in inventory (@OldSerpskiStalker)
- Added speed multiplier for hud motions (@ggGhosTt)
- Added name and icon of car (@ForserX)
- Added car light indicator (@ForserX)
- Implemented UI panel of vehicle (@ForserX)
- Enabled `hud_adjust` on RelWithDebInfo configuration (@ForserX)
- Added usable car trunk feature (@ForserX)
- Added multiple item spawning to `g_spawn` console command (@Drombeys)
- Deleted verify in `CExplosive::GenExplodeEvent` method (@Drombeys)
- Added weapon inertion (@Shtrecker, @ShokerStlk)
- Added weapon collision system (@Shtrecker, @ShokerStlk)
- Fixed grenade mode incorrect fire method usage (@Shtrecker)
- Fixed parameters reset on travel to location event (@Shtrecker, @mortany)
- Fixed pseudogiant's stomp damage on actor`s jump (@Shtrecker)
- Reworked actor state getter (@Shtrecker)
- Optimized font texture atlas generation (@Hozar2002)
- Fixed weapon reloading (@Shtrecker)
- Fixed flash period time for simple detector (@Shtrecker, @gunslingermod)
- Added workaround for `border.empty()` crash (@ForserX, @Alundaio)
- Fixed crash at `CCC_ALifeTimeFactor::Info` method (@ugozapad)
- Fixed misfire status reset on load (@Shtrecker)
- Fixed zoom factor reset on load (@Shtrecker)
- Made autoreload optional (@Shtrecker)
- Made sprint block while reloading optional (@Shtrecker)
- Refactored stopping run in shooting (@Shtrecker)
- Refactored tri state reload (@Shtrecker)
- Fixed `CWeaponRG6` class weapons shooting method (@Shtrecker)
- Removed reload pause on first animation (@Shtrecker)
- Fixed empty barrel shooting for `CWeaponRG6` class weapons (@Shtrecker)
- Added motion-based weapon tilt (@ShokerStlk)
- Fixed `explosion_hit_types` parameter parsing (@Shtrecker)
- Fixed incorrect AI load call (@ForserX)
- Fixed night vision deactivation on helmet drop (@Shtrecker)
- Added localizable strings to saves (@Drombeys)
- Fixed issues with grenades (@ForserX)
- Added ability to enable NPCs look at actor (@ggGhosTt, @v2v3v4)
- Added ability to enable anomalies reaction to NPC (@MAYLAYSHEZ)
- Fixed trader sound plays from him, not in actor head (@MAYLAYSHEZ)
- Stopped `damage_particles` if car explode (@MAYLAYSHEZ)
- Fixed NPC reaction in `CarWeapon` module (@MAYLAYSHEZ)
- Fixed error when actor die in vehicle (@MAYLAYSHEZ)
- Fixed hiding animation (@Shtrecker)
- Fixed movement of fixed elements (@v2v3v4)
- Fixed elevator bug (@v2v3v4)
- Fixed scrollbar size after scripted window change (@ForserX)
- Fixed basic vehicle bugs (@ForserX)
- Fixed `cannot find rank for` crash error (@Drombeys)
- Fixed hands ancor load (@ForserX)
- Added `disable_bore` parameter (@Shtrecker)

### Scripts

- Tweaked Lua surge manager (@ggGhosTt)
- Tweaked Lua weather manager (@ggGhosTt)
- Added data files when corresponding saves are deleted (@ggGhosTt)
- Created savegames directory if none is present (@ggGhosTt)
- Matched saves and serialized tables (@ggGhosTt)
- Exported save/load events and retrieved save names in Lua (@ggGhosTt)
- Stored data in savegames folder as single file (@ggGhosTt)
- Implemented Lua Marshal save/load utility functions (@ggGhosTt)
- Added weather control exports (@ggGhosTt)
- Exported god mode state check to lua (@ggGhosTt)
- Exported boosters to Lua scripts (@Shtrecker)
- Exported weapons methods to Lua scripts (@ForserX, @Alundaio)
- Moved Lua export of basic types from xrGame to xrScripts (@ForserX)
- Added export `kQUICK_SAVE` and `kQUICK_LOAD` button to scripts (@Drombeys)
- Added `hide_detector` function export to Lua (@ForserX)
- Reworked fetching dependencies script (@ForserX)
- Replaced old bitwise operations with native LuaJIT 2 implementations (@ForserX)
- Added ability to change `CSE_AlifeObject` variables in Lua (@ForserX)
- Exported actor movement states (@Shtrecker)

### Multiplayer

- Fixed multiplayer server functionality (@ForserX)
- Added base mutant synchronization (@Hozar2002, @pavelspitsin)
- Removed artefact particle drawing on actor in MP (@ForserX)
- Fixed dedicated server functionality (@ForserX)
- Fixed dedicated server working (@ForserX)
- Added FreeMP mode (@ForserX)
- Enhanced FreeMP mode functionality (@ForserX)
- Fixed `tfGetRelationType` working (@ForserX)

### Sound

- Applied `psSoundRolloff` to linear fade (@ForserX)
- Added optional hud sound overlapping (@Shtrecker, @ggGhosTt)
- Increased sound targets size (@Shtrecker)
- Deleted `snd_targets` and `snd_cache_size` commands (@Shtrecker)
- Added default sound device change system event (@ForserX)

### UI

- Fixed UI debug text (@ugozapad)
- Fixed engine version text aligment (@ugozapad)
- Added XML Expression support to `CUIStatic` class (@ForserX)
- Fixed 4:3 slots coordinates (@ForserX)
- Fixed incorrect addons position drawing in UI (@ForserX)

### In-game tools

- Added `trees_amplitude` parameter to weather editor (@ForserX)
- Added Lua Code window (@ForserX)
- Implemented output of given InfoPortion (@ForserX)
- Fixed weather editor sun position adjustment (@ggGhosTt)
- Added ability to disable InfoPortion in `Actor InfoPortions` view (@Drombeys)
- Implemented ImGui scenes viewer (@Drombeys)
- Fixed inversion of sky colors in weather editor (@Drombeys)

### Utilities

- Implemented decompressor (@ForserX)
- Implemented texture copy utility (@Hozar2002)
- Implemented non-recursive version of `OA_Unwarp` method (@ForserX, @range-vs)
- Enabled `IXRAY_USE_R1` option in utilities presets (@Drombeys, @acidicMercury8)

### Editors

- Ported base xrECore code (@ForserX)
- Added base props for editors (@ForserX)
- Added EditorRender and EditorEngineAPI projects (@ForserX)
- Implemented base PPE UI (@ForserX)
- Added EditorsProps project (@ForserX)
- Fixed `CPostProcessValue::get_value` method work (@ForserX)

### Resources

- Added icon to `m_burer_e` section (@Drombeys)
- Deleted strafe in aiming (@VOIN101)
- Fixed shotgun animations (@VOIN101)
- Exported torch click sound into config (@ForserX)
- Moved script edits to `_g` script (@Drombeys)
- Added `graffiti22` value (@ForserX)
- Reverted changes in `ui_sleep_dialog` script (@Drombeys)

## Release 0.9 (March 2024)

### Common

- Improved CMake projects structure (@ForserX)
- Updated pack artifacts script (@acidicMercury8)
- Fixed warnings (@Drombeys, @ForserX)
- Deleted old weather editor code (@ForserX)
- Deleted xrCPU_Pipe project (@v2v3v4, @ForserX)
- Added xrScripts project (@ForserX)
- Added GPU SDK files (@ForserX)
- Added magic_enum dependency (@Drombeys)
- Implemented GitParser with CMake and Git commands (@acidicMercury8)

### Engine

- Implemented SDL3 support (@Vertver)
- Implemented `CCC_Boolean` class for boolean console variables (@ForserX)
- Fixed some memory leaks and copy-pastes (@MAYLAYSHEZ)
- Implemented `OrthographicOffCenterLH` method in matrix module (@v2v3v4)
- Implemented `invert44` method in matrix module (@v2v3v4)
- Deleted `SetThreadAffinityMask` function call (@v2v3v4)
- Added `xr_shared_ptr` and `xr_unique_ptr` aliases and helpers (@ForserX)
- Implemented weather editor with ImGUI (@ForserX)
- Simplify event API (@ForserX)
- Replaced C-style enumerations reflection with magic_enum (@ForserX)
- Added colors for debug console (@Vertver)
- Added tokens for console variables (@Vertver)
- Added in-game debug toolbar (@Vertver)
- Implemented transition to unified SDL input (@ggGhosTt)

### Render

- Implemented AMD AGS support on D3D11 (@ForserX)
- Added ImGUI rendering (@Vertver)
- Refactored render hardware refactoring on D3D9 and D3D11 (@Vertver)
- Enabled actor shadow on dynamic lighting (@MAYLAYSHEZ)
- Implemented font system with FreeType (@ForserX)
- Added debug renderer for RelWithDebInfo configuration (@ForserX)
- Implemented graphical debugging for ImGUI (@Vertver)
- Implemented debugging for ImGUI (@Vertver, @Hozar2002)

### Gameplay

- Moved `read_sun_config` command to `engine_external` config (@Drombeys)
- Set torso pitch to zero for unarmed actor in third person view (@ggGhosTt)
- Fixed weapon delay at low FPS (@v2v3v4)
- Added `ray` function for `CObject` in Lua (@ForserX)
- Added compass device class (@ForserX)
- Implemented new noclip movement (@v2v3v4)
- Fixed input in `bind_console` console (@v2v3v4)
- Added thirst and sleepiness to external features (@ForserX)
- Migrated alcohol features to new system (@ForserX)
- Added simplified addiction system (@ForserX)
- Added nearest namespace in Lua (@ForserX)
- Extended `level` namespace in Lua (@ForserX)
- Extended `alife` namespace in Lua (@ForserX)
- Added Lua callbacks (@ForserX)
- Implemented inventory customization (@ForserX)
- Simplified update registration (@ForserX)
- Added method exports from `CEatableItem` class (@ForserX)
- Implemented dynamic `slots_count` calculation (@ForserX)
- Added method exports from `CUIWindow` class (@ForserX)
- Added INI namespaces (@ForserX)
- Added marshalling and LFS namespaces in Lua (@ForserX)
- Fixed working of `eMonsterSoundIdle` in multiplayer (@ForserX)
- Fixed parsing in `CCC_Vector3::Execute` method (@ForserX)
- Added `get_compass_direction` function export to Lua (@ForserX)
- Fixed bug with aura of psi dog (@OldSerpskiStalker)
- Replaced `THROW` with `VERIFY` in `CSpaceRestrictionAbstract` and `UIGameTutorial` (@MAYLAYSHEZ)
- Added return to `WeaponMagazined` when `inventory_owner` doesn't have `active_item` (@MAYLAYSHEZ)
- Fixed idle animation playing after unload (@Shtrecker)
- Fixed inversion of cartridges and saving them (@Shtrecker)
- Fixed ammo type changing (@Shtrecker)
- Fixed missing grenade from grenade launcher (@MAYLAYSHEZ)
- Fixed incorrect displaying two more ammo types (@MAYLAYSHEZ)
- Fixed incorrect weapon weight calculations (@MAYLAYSHEZ)
- Added safety checks (@MAYLAYSHEZ)
- Fixed stucked running animation (@MAYLAYSHEZ)
- Fixed bug with infinite zoom when aiming (@MAYLAYSHEZ)
- Implemented blocking all slots when climbing (@ggGhosTt)
- Fixed idle animation when climbing in third person view (@ggGhosTt)
- Ported camera noise support from `CCameraFirstEye` to `CCameraLook2` (@ggGhosTt)
- Disabled sprint inertia for third person view (@ggGhosTt)
- Fixed cutscene handling in third person view (@ggGhosTt)
- Added exports for camera states in Lua (@ggGhosTt)
- Implemented config `CCameraLook2` offset parsing (@ggGhosTt)
- Deleted autoaim code (@ggGhosTt)
- Implemented `CCameraLook2` shoulder offset save  (@ggGhosTt)
- Implemented visible strapped weapon models in third person (@ggGhosTt)
- Fixed weapon handling in third person view (@ggGhosTt)
- Fixed third person view gameplay functional work (@ggGhosTt)
- Implemented camera position change instead of looking out in third person view (@ggGhosTt)
- Implemented camera position and type save (@ggGhosTt)
- Added collision for `CCameraLook2` (@ggGhosTt, @v2v3v4)
- Fixed actor third person view animations (@ggGhosTt)
- Merged and clean `-psp` functional (@ggGhosTt)
- Added camera-switch control to change between `cam_1` and `cam_2` (@ggGhosTt)
- Implemented `xr_strconcat` function (@ForserX)
- Added script callbacks for pressing, releasing and holding button events (@ggGhosTt)
- Implemented UI auto slot system (@ForserX)

### Multiplayer

- Merged A-Life singleplayer and multiplayer functionality (@ForserX)
- Implemented A-Life simulation support in multiplayer (@ForserX)
- Implemented loading spawn in multiplayer with `alife` (@ForserX)

## Release 0.8 (March 2024)

### Common

- Improved CMake projects structure (@ForserX)
- Updated pack artifacts script (@acidicMercury8)
- Fixed warnings (@Drombeys, @ForserX)
- Added Shipping config in CMake (@ForserX)
- Replaced original icon (@Drombeys, @Z3SA)
- Replaced original splash (@Z3SA)
- Implemented UnityBuild support for xrGame project (@ForserX)
- Added pipeline for non-Unity build (@acidicMercury8)
- Implemented Discord Game SDK support (@ForserX, @Drombeys)
- Added Native Visualization config (@ForserX)

### Engine

- Implemented XML expression system (@ForserX, @Giperion)
- Implemented `png` splash screen (@MAYLAYSHEZ, @ForserX)
- Fixed file mapping on x64 configuration (@ForserX)
- Added info for potential `xr_ini` error (@MAYLAYSHEZ)
- Fixed corruption in `CConsole::ExecuteCommand` on typed wrong name (@MAYLAYSHEZ)
- Printed name off command when `Command disabled` (@MAYLAYSHEZ)
- Disabled texture dump output on Release configuration (@Drombeys)
- Implemented x64 compatibility of `doug_lea_allocator` (@ForserX)
- Disabled assert message in ODE project (@Drombeys)
- Fixed `parse_level_version` method (@ForserX)
- Fixed stack overflow in `CConsole::ExecuteCommand` * Debug conf. was crashing on x64 with this one (@MAYLAYSHEZ)
- Fixed potential stack overflow (@MAYLAYSHEZ)
- Removed redundant check in `CDestroyablePhysicsObject::OnChangeVisual` (@MAYLAYSHEZ)
- Added device active state control via `rs_device_active` console command (@MAYLAYSHEZ, @ForserX)
- Fixed window initialization problems (@ForserX, @MAYLAYSHEZ)
- Implemented `CStringTable` singleton (@ForserX)
- Correct callstack printing on debug (@ForserX)
- Enabled debug break for defer assert (@ForserX)
- Disabled `dump_file_mappings` on Debug build (@ForserX)
- Implemented ability to play without xrGameSpy library (@ForserX)

### Render

- Added SMAP size control `r__smap_size` [1024 > 4096] (@MAYLAYSHEZ)
- Replaced `D3DFORMAT` with `DxgiFormat` in xrRender_R4 project (@Vertver, @Drombeys)
- Disabled showing SMAA on xrRender_R1 (@Drombeys)
- Added multiplication by sun color for sunshafts (@MAYLAYSHEZ)
- Fixed `parallax_h` not hardcoded and console command workaround (@MAYLAYSHEZ)
- Fixed incorrect depth stencil initialization in `dx10StateUtils::ValidateState` (@MAYLAYSHEZ)
- Fixed memory leak for vertex buffers in `dx103DFluidGrid` (@MAYLAYSHEZ)
- Enabled printing THM names when loading on Debug (@MAYLAYSHEZ)
- Enabled `NO_MULTI_INSTANCES` macro for Release configurations (@Drombeys)
- Reimplement actor shadow for R2-R4 (@MAYLAYSHEZ, @v2v3v4)
- Rework mipmap control (@Drombeys)
- Release system cursor when `rsDeviceActive` (@MAYLAYSHEZ)
- Deleted option control `rs_refresh_60hz` from resources (@MAYLAYSHEZ)
- Fixed point lights virtual size (@MAYLAYSHEZ)
- Fixed initialization order of `L_spot_s` array (@MAYLAYSHEZ)
- Let `DXGI` calculate refresh rate for itself for performance (@MAYLAYSHEZ)
- Cleaning G-buffer every frame to avoid `ghostings` (@MAYLAYSHEZ)
- Maked fonts not change state if there is no text to render (@MAYLAYSHEZ)
- Fixed comparing values of different enum types in `dxUIRender::StartPrimitive` (@MAYLAYSHEZ)
- Fixed broken initialization in `VertexCache` default constructor (@MAYLAYSHEZ)
- Returned `FORCE_GLOSS` shader definition for R4 (@MAYLAYSHEZ)
- Fixed enumeration of option definitions on D3D10+ (@Drombeys)
- Fixed attachment rotation display (@v2v3v4)
- Fixed foging in `model_distort4ghost` shader (@ForserX)
- Fixed limits for `r__detail_density` (@MAYLAYSHEZ)
- Fixed loading of unsupported textures (@Hozar2002)
- Bind wallmark life time on dynamic objects to `r__wallmark_ttl` (@MAYLAYSHEZ)
- Fixed game crash when rendering wallmarks (@MAYLAYSHEZ)
- Added ability to control loadscreen tips via `engine_external.ltx` (@MAYLAYSHEZ)
- Fixed `occRasterizer` clearing (@ForserX)
- Added landscape render phase (@ForserX)
- Fixed failed shader compilation error window and message (@MAYLAYSHEZ)
- Optimized dynamic objects rendering (@VaIeroK)

### Gameplay

- Added initializer for doors (@Drombeys)
- Ensured accurate results for `npc:path_completed()` method (@Drombeys)
- Added check for object existence in `CheckObjectVisibility` method (@Drombeys)
- Fixed calculation of the shift for IK (@ForserX)
- Added locking and unlocking `level_vertex_id` (@Drombeys)
- Added `is_accessible_vertex_id` function export in Lua (@Drombeys)
- Added `valid_vertex_id` function export in Lua (@Drombeys)
- Fixed crash in `CPlanner::update` method (@Drombeys)
- Fixed mutants running in place (@Drombeys)
- Fixed crash if enemy is unavailable (@Drombeys)
- Moved descriptions of detector's eye zones in one place (@ForserX)
- Added actor smooth slopes (@MAYLAYSHEZ)
- Added actor smooth crouch (@MAYLAYSHEZ)
- Fixed crash when NPC trying use destroyed object (@v2v3v4)
- Disabled cheats command on Release configuration (@Drombeys)
- Implemented XML expressions for MP mode (@ForserX)
- Enabled calculating distance to enemy by monsters that created sound they hear (@MAYLAYSHEZ)
- Fixed crash when trying to stop inactive script profile timer (@MAYLAYSHEZ)
- Fixed monsters cant hit actor through object (@MAYLAYSHEZ)
- Removed duplicate `mstate_r1&mcLanding` in condition in ActorAnimation (@MAYLAYSHEZ)
- Fixed for Demo Record will not start if the level is not loaded (@MAYLAYSHEZ)
- Fixed weapon camera effector (@MAYLAYSHEZ)
- Fixed for bolt and grenades not allowing to throw them while in `bore` animation (@MAYLAYSHEZ)
- Fixed error in `stalker_animation_global` module when there is no weapon in NPC (@MAYLAYSHEZ)
- Fixed duplicated Lua export for `set_smart_cover_target_idle` function (@MAYLAYSHEZ)
- Decreased actor movement speed after jump (@MAYLAYSHEZ)
- Fixed incorrect Lua export name in `CALifeMonsterDetailPathManager` (@MAYLAYSHEZ)
- Fixed `CCameraManager::UpdatePPEffectors()` method (@Drombeys)
- Corrected zooming in/out command handler (@MAYLAYSHEZ)
- Fixed monsters sometimes running on the spot (@MAYLAYSHEZ)
- Added `crow` counter fix (@MAYLAYSHEZ)
- Applied various fixes to `crow` class (@MAYLAYSHEZ)
- Fixed `CHangingLamp` crash (@MAYLAYSHEZ)
- Added early exit in `NvStripifier::RemoveSmallStrips` with empty list (@MAYLAYSHEZ)
- Fixed potential error after load save with dead `psy-dog` (@MAYLAYSHEZ)
- Fixed luminocity indicator after save load (@MAYLAYSHEZ)
- Fixed incorrect count of load stages (@MAYLAYSHEZ)
- Fixed redundant `list_idx == e_outfit` check in `UIMpTradeWnd_misc` (@MAYLAYSHEZ)
- Fixed zero `scope_zoom_factor` (@xrEugene)
- Fixed printing `UICost` value (@ForserX)
- Added `enable_dof_reload` console command (@ForserX)
- Added Lua export to control global time factor (@MAYLAYSHEZ)
- Fixed torch light rotation on `cam_2` (@ForserX)
- Disabled useless and unnecessary `item place` spam (@ForserX)
- Fixed incorrect NPC memory loading (@MAYLAYSHEZ)
- Fixed run animations of NPC in panic state (@MAYLAYSHEZ)
- Maked clear levels vector on quit (@MAYLAYSHEZ)
- Fixed memory error when trying to load level, while any level is currently loaded (@MAYLAYSHEZ)
- Prevented crash due `reserve()` call with `arg < 0` (@MAYLAYSHEZ)
- Added ability to reload system config via `reload_system_ltx` console command (@MAYLAYSHEZ)
- Restored ability to set more than one wallmark to entity or ammo and explosive (@MAYLAYSHEZ)
- Enabled clearing objects and models pools between level loads (@MAYLAYSHEZ)
- Fixed incorrect zoom after attaching custom scope to weapon (@MAYLAYSHEZ)
- Fixed crash on incompatible save click (@MAYLAYSHEZ)
- Fixed message order in PDA (@MAYLAYSHEZ)

### Sound

- Added global time factor influence on sound (@MAYLAYSHEZ)
- Added torch switch sound (@ForserX)
- Disabled EFX for video and music (@ForserX)
- Added `SNDENV_VER_IXR` and cast EAX values to EFX in `SoundRender` (@ForserX)
- Added default sound device to sound devices list (@ForserX)
- Implemented ability to disable EFX (@ForserX)
- Applied sound effects zones for sound source (@ForserX)
- Added weapon aim sound (@xrEugene)
- Forced mute all sounds when loading save (@MAYLAYSHEZ)
- Fixed ambiguity with `set_volume` in `HudSound` module (@MAYLAYSHEZ)

### Utilities

- Implemented skipping lightmap textures compression (@Drombeys)
- Implemented skipping tesselate geometry (@Drombeys)
- Implemented skipping subdivide geometry (@Drombeys)

## Release 0.7 (March 2024)

### Common

- Improved projects structure (@ForserX, @Drombeys, @acidicMercury8)
- Enabled C++20 for all projects (@ForserX)
- Enabled Unicode globally (@ForserX)
- Fixed x64 runtime issues (@ForserX, @Drombeys)
- Fixed utilities building issues (@ForserX, @Drombeys, @acidicMercury8, @vadvalskiy)
- Restructured render folders with refactoring (@Drombeys)
- Restructured building workflows and pipelines (@acidicMercury8, @Drombeys)
- Enabled printing compressor log on pipeline (@Drombeys)
- Replaced Luabind with non-Boost version (@ForserX)
- Deleted Boost files (@ForserX)
- Reworked memory allocator and memory modules (@ForserX)

### Packages

- Replaced LuaJIT with NuGet package (@ForserX, @acidicMercury8)
- Replaced DirectXTex with nvtt in xrDXT project (@ForserX)
- Replaced FreeImage with NuGet package (@ForserX, @acidicMercury8)

### Engine

- Disabled reading `user.ltx` config in root folder (@Drombeys)
- Moved xrXMLParser to xrCore (@ForserX)
- Rewritten CPUID module (@ForserX)
- Rewritten CRC32 without Boost (@ForserX)
- Implemented new stack walker (@ForserX)
- Deleted `ttapi` module (@Drombeys)
- Rewritten renders iterator (@Drombeys, @Hozar2002)
- Optimized weapon sounds update (@VaIeroK)
- Added invalidate state for rain (@MAYLAYSHEZ)
- Fixed rain sound after loading or changing level (@MAYLAYSHEZ)
- Enabled window minimization on `do_exit` and `terminate` calls (@MAYLAYSHEZ)
- Set special function for terminate (@MAYLAYSHEZ)
- Fixed window minimization unhandled error (@MAYLAYSHEZ)
- Fixed infinite unhandled crash handler execution (@MAYLAYSHEZ)
- Fixed game closing after error on not connected debugger (@MAYLAYSHEZ)
- Fixed weather cycles loading (@MAYLAYSHEZ)
- Enabled weather logging macros on non `MASTER_GOLD` configurations (@MAYLAYSHEZ)
- Fixed sound buffer size (@ForserX)
- Fixed wrong variable name assignment in sound environment (@johncurley)
- Rewritten timers (@mortany, @ForserX)
- Added defferred `R_ASSERT` event (@ForserX)
- Fixed drop FPS for not valid spawn position of object (@OldSerpskiStalker)
- Enabled printing Lua stack information and variables to log (@ForserX)
- Enabled printing class ID error to log on release configuration (@ForserX)
- Fixed to use normal system devices by OpenAL Soft (@ForserX)
- Deleted hardcode for level box (@ForserX)
- Implemented rain and thunderbolt starting delay (@MAYLAYSHEZ)

### Render

- Implemented FXAA on static lightning (@Hozar2002)
- Implemented SMAA in xrRender_R2 (@Hozar2002)
- Fixed crash on bones synchronization (@xrLil-Batya)
- Implemented disabling of shader cache reading (@Hozar2002)
- Fixed mipmap loading (@Drombeys)
- Fixed distorted glass displaying on static lighting (@Hozar2002)
- Deleted unused `ConsoleRender` module (@Drombeys)
- Deleted `xrSkin2W_SSE` module (@Drombeys)
- Deleted `advancedpp` option (@Drombeys)
- Deleted `*_nomsaa` related shaders (@Drombeys)
- Implemented rendertarget resolution acquisition (@Vertver, @Drombeys)
- Deleted `albedo_wo` option (@Drombeys)
- Deleted `blur` option (@Drombeys)
- Implemented `r2_cloud_shadows` command  (@Drombeys, @Hozar2002)
- Fixed sun shadows on xrRender_R2 (@Drombeys)
- Implemented `r2_def_aref_quality` command (@Drombeys, @Hozar2002)
- Implemented displaying window node name by cursor focus (@Hrusteckiy)
- Implemented `D3D_FEATURE_LEVEL_11_1` support (@Vertver)
- Deleted MSAA in resources (@Drombeys)
- Deleted MSAA in render (@Drombeys)
- Deleted `r3_msaa_alphatest` command (@Drombeys)
- Deleted `r__supersample` command (@Drombeys)
- Implemented RenderDoc support (@ForserX)
- Implemented optional parallel textures loading (@MAYLAYSHEZ)
- Added support volumemap to D3D11 render (@Vertver)
- Implemented texture stagging control for all renders (@MAYLAYSHEZ)
- Added `-dxdebug` key instead DirectX debug flag (@Drombeys)
- Increased value of `rsDVB_Size` variable (@Drombeys)
- Fixed wallmarks on dynamic objects (@OldSerpskiStalker)
- Fixed memory leak in `CDetailManager` class (@Drombeys)
- Set maximum textures quality by default (@MAYLAYSHEZ)
- Fixed double `ShaderResourceView` creation (@Vertver)
- Set initial values of `CROS_impl` class variables (@Drombeys)

### Gameplay

- Implemented crosshair control in adjust interface (@Shtrecker)
- Fixed spawn grenade after grenade change (@Shtrecker)
- Fixed `hud_fov` command (@Shtrecker)
- Added `checkout_bones` parameter for `CMissile` class (@Shtrecker)
- Fixed opening doors by NPC (@ForserX)
- Implemented custom mark feature (@Hrusteckiy)
- Implemented custom text feature (@Hrusteckiy)
- Fixed incorrect head rotation of trader (@Hrusteckiy)
- Fixed load last save button behavior after loading level (@Hrusteckiy)
- Added developer float commands (@Hrusteckiy)
- Implemented customization of `UICursor` control (@Hrusteckiy)
- Implemented customization of `UITrackBar` control (@Hrusteckiy)
- Fixed crashes on `UIItemInfo` non-existent node (@Hrusteckiy)
- Added method for quick adding any custom static (@Hrusteckiy)
- Fixed NPC dispersion by rank (@Hrusteckiy, @SurDno)
- Deleted R_ASSERT2 in `CUIDialogWnd::HideDialog` method (@ForserX)
- Deleted duplicated `Fvector2` in `CUICellContainer::PlaceItemAtPos` method (@ForserX)
- Fixed moving items to fast slot if grid larger than grid of slot (@ForserX)
- Fixed weapon highlights (@ForserX)
- Added left hand transform matrix (@Hozar2002, @ForserX)
- Fixed displaying addons on weapons (@OldSerpskiStalker)
- Made IK stop further than 100m from actor position (@MAYLAYSHEZ)
- Fixed `get_wnd_pos` function export (@Drombeys)
- Added exception message to `SetCharacterCommunity` method (@Drombeys)
- Fixed incorrect type passed `GameObject::eDeath` callback (@Drombeys)
- Added object existence check (@Drombeys)
- Fixed spawn paths related errors (@Drombeys)
- Fixed message output in `show_dialog` function (@Drombeys)
- Deleted `dump_infos` command from `actor_binder:update` function (@ForserX)
- Fixed mutants logic in restrictors broke down (@ForserX)
- Fixed triggering of adding monsters contacts (@ForserX)
- Enabled ragdoll for deadbody (@ForserX)
- Implemented new external features system (@ForserX)
- Fixed level graph invalid vertex ID error (@ForserX)
- Implemented `hud_fov_zoom` weapon parameter (@Drombeys, @Hozar2002)
- Added underrun buffer checking to fix playback bug (@johncurley)
- Fixed walking in `mcLookout` states (@Shtrecker)
- Set initial values of `CStreamReader` class variables (@OldSerpskiStalker)
- Fixed HUD models clipping (@Shtrecker)
- Implemented grenade explosion on hit (@Shtrecker)
- Implemented stopping animation of getting detector (@ForserX)
- Replaced missing sound with stub on using scripts (@Drombeys)
- Moved actor to beginning of spawn (@ForserX)
- Fixed calculating position of items in inventory grid (@ForserX)
- Implemented timer for new game and save loading (@MAYLAYSHEZ)

### Utilities

- Fixed EFC building issues (@ForserX)
- Added EFC utility source code (@acidicMercury8, @ForserX)
- Implemented new lightmap saving algorithm (@DimaKuzmin)
- Deleted threads limit in utilities (@ForserX)
- Added MagicFM CMake project (@acidicMercury8)
- Ported MagicFM to C++20 (@ForserX)
- Replaceed `-keep_temp_files` with `-clear_temp_files` key (@ForserX)
- Implemented show of all missing TGA textures and THM files (@ForserX)
- Replaced MMX with SSE in `Place_Perpixel` function (@ForserX)
- Fixed loop in `CGraphMerger` method (@Drombeys)
- Deleted duplicated and dead files from xrAI (@ForserX)
- Added `-all` key to compilers and enable `-do -ai -lc` modes  (@ForserX)
- Merged compilers into one project (@ForserX)
- Fixed saving `build.cform` file in xrLC (@ForserX)
- Implemented skipping invalid faces in xrLC (@Drombeys)
- Fixed xrCompress to support multibyte WinAPI functions (@ForserX)
- Enabled reserving memory for compressed nodes in `xrSaveNodes` (@abramcumner)
- Enabled using static buffer in `setup_recalculationflags_file` (@abramcumner)
- Fixed progress set in `xrPhase_UVmap` (@abramcumner)
- Changed algorithm for calculating the area of a triangle (@abramcumner)

### Plugins

- Updated 3D SDK (@DJYar, @ForserX)
- Ported plugins to х64 (@DJYar, @ForserX)
- Ported plugins to C++20 (@ForserX)
- Updated LW Server project (@ForserX)
- Created plugin folder in CMake (@ForserX)
- Applied minor fixes for Max Export plugin (@DJYar, @ForserX)
- Ported Max Material plugin to C++20 (@ForserX)
- Added Max Material CMake project (@ForserX)
- Applied patches to plugins (@DJYar, @ForserX)

## Release 0.6.1 (September 2023)

### Common

- Added logo icons and TortoiseGit config (@acidicMercury8)
- Fixed incorrect including of `FastDelegate` header (@Drombeys)
- Fixed project references and links (@acidicMercury8)
- Replaced `_snprintf` with `_snprintf_s` in ODE (@Drombeys)
- Deleted `IsPCAccessAllowed` function (@Drombeys)
- Deleted `ComputeModuleHash` function (@Drombeys)
- Deleted `is_enough_address_space_available` function (@Drombeys)
- Deleted unused `ttapi` includes (@Drombeys)
- Deleted unused `pSettingsAuth` pointer (@Drombeys)

### Engine

- Deleted `CopyProtection` module (@Drombeys)

### Render

- Fixed incorrect including of header files in renders projects (@Drombeys)

### Gameplay

- Fixed shotgun reload (@Shtrecker)
- Fixed incorrect including of header files in xrGame project (@Drombeys)
- Deleted `boost::noncopyable` related code from xrGame (@Drombeys)

### Resources

- Fixed fog displaying on static lighting (@Hozar2002)
- Unified shaders refactoring with IX-Ray 1.5 (@Drombeys)

## Release 0.6 (August 2023)

### Common

- Fixed most part of warnings (@acidicMercury8, @Drombeys)
- Fixed ignoring temp and metadata files by locator (@MAYLAYSHEZ)
- Fixed error skipping process troubles (@MAYLAYSHEZ)
- Fixed `std::unique_ptr` use cases (@acidicMercury8)
- Added __Visual Studio__ solution filters (@acidicMercury8)
- Added __Visual Studio Install__ config (@acidicMercury8)
- Enabled NuGet packages getting and caching in __GitHub Actions__ (@acidicMercury8)
- Enabled output log for debugger connected (@MAYLAYSHEZ)
- Set latest __Windows SDK__ version (@acidicMercury8)
- Splitted project configuration paths (@acidicMercury8)
- Refactored color math module (@Drombeys)
- Replaced `D3DCOLOR_RGBA`, `D3DCOLOR_ARGB` and `D3DCOLOR_XRGB` macroses (@Drombeys)
- Replaced legacy __DirectX Math__ with __DirectXMath__ analog (@Drombeys)
- Replaced `__uuidof` with `IID_PPV_ARGS` (@Drombeys)
- Replaced `__interface` keyword with `class` (@Drombeys)
- Replaced `STATIC_CHECK` with `static_assert` (@Drombeys)
- Replaced `__asm int 3` with `__debugbreak` (@Drombeys)
- Replaced `__asm pause` with `_mm_pause` (@Drombeys)
- Replaced `GetCLK` function with unified analog (@Drombeys)
- Replaced `GetTickCount` with `GetTickCount64` function (@Drombeys)
- Replaced `_snprintf` with `_snprintf_s` function (@Drombeys)
- Replaced `std::auto_ptr` pointers with `std::unique_ptr` (@Drombeys)
- Replaced `std::bind1st` and `std::bind2nd` with lambda functions (@Drombeys)
- Replaced linker directives with project references (@acidicMercury8)
- Replaced `FS_DEBUG` macro with `DEBUG` (@Drombeys)
- Renamed `xrDebugNew` module to `xrDebug` (@MAYLAYSHEZ)
- Deleted pragma deprecations (@acidicMercury8)
  - `strcpy`, `strcpy_s`, `sprintf`, `sprintf_s`, `strcat`, `strcat_s`
- Deleted `get_ref_count` function (@Drombeys)
- Deleted scripts for getting dependencies (@acidicMercury8)
- Deleted __ATI MGPU__ library with related code (@Drombeys)
- Deleted __NVAPI__ library with related code (@Drombeys)
- Deleted redundant `DEBUG_INVOKE` (@MAYLAYSHEZ)
- Deleted `boost::noncopyable` use cases from editor and xrPhysics (@Drombeys)
- Deleted `std::binary_function` use cases (@Drombeys)
- Deleted `std::unary_function` use cases (@Drombeys)
- Deleted unused `dwFrame` field of `xrCore` class (@Drombeys)
- Deleted unused `_GPA_ENABLED` blocks (@Drombeys)

### Packages

- Replaced __Flobbster.Windows.Forms__ with NuGet package (@acidicMercury8)
- Replaced __DockPanelSuite__ with NuGet package (@acidicMercury8)
- Replaced __DirectX SDK__ with NuGet package and __Windows SDK__ (@acidicMercury8, @Drombeys)
- Replaced __DirectXTex__ with NuGet package (@acidicMercury8, @Drombeys)
- Replaced __DirectXMesh__ with NuGet package (@acidicMercury8, @Drombeys)
- Replaced __Xiph__ libraries with NuGet packages (@acidicMercury8)
- Replaced __zlib__ with NuGet package (@acidicMercury8)

### Engine

- Fixed `cam_inert` console command (@MAYLAYSHEZ)
- Fixed bones synchronization (@xrLil-Batya)
- Fixed OGG related code of xrSound (@vadvalskiy)
- Deleted `xrTheora_Surface_mmx` module (@Drombeys)
- Deleted __SecuROM__ related code (@Drombeys)
- Deleted unused modules from xrSound (@vadvalskiy)
- Deleted `mailSlot` module (@Drombeys)
- Deleted launcher related code (@Drombeys)
- Deleted `no_single` module (@Drombeys)
- Deleted `dedicated_server_only` module and `PROTECT_API` macros (@Drombeys)
- Implemented `hud_fov` item parameter (@Shtrecker)
- Implemented `g_info` and `d_info` console commands (@Drombeys)
- Implemented `g_money` console command (@Drombeys)
- Implemented `g_spawn` and `g_spawn_inv` console command (@Drombeys, @Hozar2002)
- Integrated __OpenAL Soft__ with __EFX__ extensions (@johncurley)
- Unified xrEngine refactoring with __IX-Ray 1.5__ (@Drombeys)
- Splitted engine and server applications (@acidicMercury8)
- Replaced `-nointro` key with `keypress_on_start` command (@Drombeys)
- Refactored some sound modules (@johncurley, @vadvalskiy)

### Editors

- Fixed floating types converting in weather editor (@vadvalskiy)
- Fixed weather editor project (@vadvalskiy)
- Deleted unused resource files from weather editor (@vadvalskiy)

### Render

- Fixed wrong attenuation of far sun shadows (@Hozar2002)
- Fixed __HDAO__ crashing on disabled G-Buffer optimization (@morrazzzz)
- Fixed texture quality changing in D3D11 (@Drombeys, @Hozar2002, @mortany)
- Fixed sun flares for __FXAA__ (@OldSerpskiStalker)
- Fixed `MaxAnisotropy` parameter for __Shader Model 5__ (@OldSerpskiStalker)
- Fixed some memory leaks (@OldSerpskiStalker, @Drombeys)
- Fixed enumeration of option definitions on __Direct3D 10+__ (@OldSerpskiStalker)
- Fixed sunshafts on enabled `accum_sun_near_nomsaa_minmax` shader (@OldSerpskiStalker)
- Fixed transparent on static lightning (@Hozar2002)
- Fixed indentation of texture memory message (@MAYLAYSHEZ)
- Added `r2_use_bump` command to disable bumps on R2+ renderers (@DanceManiac)
- Activated `R2FLAG_USE_BUMP` flag by default (@Drombeys)
- Set `DXGI_ENUM_MODES_INTERLACED` flag (@Drombeys)
- Replaced `asm` block with standard math functions (@Drombeys)
- Replaced legacy __DirectX Tex__ with __DirectXTex__ analog (@Drombeys)
- Replaced deprecated shader compiler with __Windows SDK__ analog (@Drombeys)
- Refactored `dx11Texture` class (@Drombeys)
- Decomposed screenshot creation methods (@Drombeys)
- Deleted duplicated `END_EPS` constant (@Drombeys)
- Deleted __Direct3D 10__ dependencies (@Drombeys)
- Deleted unused mipped noise (@Drombeys)
- Deleted __Intel GMA__ related code (@Drombeys)
- Deleted unused `sunfilter` option (@Drombeys)
- Deleted unused `accum_direct` methods (@Drombeys)
- Deleted `bug` option in all renders (@Drombeys)
- Deleted `sjitter` option in all renders (@Drombeys)
- Deleted `depth16` option in all renders (@Drombeys)
- Improved depth buffer format handling (@Drombeys)
- Implemented disabling of anisotropic filtering in __Direct3D 10+__ (@Drombeys)
- Implemented `mipLodBias` property setter for __Direct3D 10+__ (@Drombeys)
- Implemented textures reloading directly in game (@MAYLAYSHEZ)
- Implemented __FXAA__ support (@OldSerpskiStalker, @Drombeys, @Hozar2002)
- Implemented __SMAA__ support (@OldSerpskiStalker, @Drombeys, @Hozar2002)
- Implemented shader-based fog on static lightning (@Hozar2002)
- Unlocked __MSAA x8__ (@OldSerpskiStalker)

### Gameplay

- Fixed refreshing of trade list (@mortany)
- Fixed actor visibility indicator after quickload (@Hrusteckiy)
- Fixed offset for answer numbers (@Hrusteckiy)
- Fixed detector animation playing (@Shtrecker)
- Fixed stuttering after reloading grenade launcher (@Shtrecker)
- Fixed rows and columns of artifact belt (@DanceManiac)
- Fixed animation playing on attached grenade launcher (@Shtrecker)
- Fixed playing idle animation on empty state (@Shtrecker)
- Fixed reload animation playing on active detector (@Shtrecker)
- Fixed switch animation playing (@Shtrecker)
- Fixed grenade launcher action (@Shtrecker)
- Fixed crashing of sliding type doors (@Drombeys)
- Fixed crashing in adjust hud mode (@Shtrecker)
- Fixed flickering after game item usage (@Drombeys)
- Fixed loading ammo in grenade mode (@Shtrecker)
- Fixed flight grenade (@Shtrecker)
- Enabled inertia control from HUD section (@Hozar2002, @Drombeys)
- Implemented 100x100 icons support (@Hrusteckiy, @DanceManiac)
- Implemented custom autoreloading for weapons (@Shtrecker)
- Implemented custom autoreloading for grenade launcher (@Shtrecker)
- Implemented full and partial weapon reloading (@Shtrecker)
- Implemented misfire of weapon (@Shtrecker)
- Implemented reloadings in grenade launcher weapons (@Shtrecker)
- Implemented delay before reloading on active detector (@Shtrecker)
- Implemented scripted key blocking (@Drombeys)
- Implemented blocking actor movement (@Drombeys)
- Refactored some weapons and detectors methods (@Shtrecker)

### Resources

- Fixed text line alignment for talk dialogs (@Hrusteckiy)
- Fixed `object_alive` condition in `bind_monster` script (@Hozar2002)
- Set weapon autoreloading settings (@Shtrecker)
- Implemented __SMAA__ support in assets (@OldSerpskiStalker, @Drombeys, @Hozar2002)
- Implemented __FXAA__ support in assets (@OldSerpskiStalker, @Drombeys, @Hozar2002)
- Updated shaders to Shader Model 3.0 (@Drombeys, @Hozar2002)

## Release 0.5 (March 2023)

### Common

- Enabled assets packing
- Replaced `dxerr` with Windows SDK analog
- Replaced `stricmp` with POSIX analog
- Simplificated `get-dependencies` script launching
- Incompletely integrated __DirectXMesh__

### Engine

- Fixed autosaves
- Fixed switching ingame console language layout
- Fixed playing animation of getting weapons
- Fixed character info for deadbody color
- Fixed progress bar for optional using of `middle_color`
- Enabled screenshots capturing in windowed mode on __Direct3D 9__
- Enabled clearing highlight lists on each inventory action
- Enabled changing items condition by Num7 and Num8
- Implemented `ui_reload` command
- Allowed to use min and max colors for double progress bar
- Allowed to change upgrade icon color by config
- Replaced crashing with warning when there is no sound
- Disabled ammo highlights for knife and binocular
- Disabled stats by class and not by section

### Render

- Fixed inverted sky colors and sky bluring on __Direct3D 10+__
- Fixed potential memory leak in __DirectX 10__ resource manager
- Fixed fog accounting for campfire and anomalies
- Fixed water displaying on static lightning
- Fixed particles displaying on shooting
- Fixed `sload` for correct nearest bumps displaying
- Fixed `s_distort` parameter for `particles_xadd` blender on __Direct3D 10+__
- Enabled fog accounting for grass on static lightning
- Enabled fog accounting for wallmarks on static lightning
- Enabled fog accounting for particles
- Enabled static sun shadows on disabled cascades
- Enabled `Ldynamic_dir` counting for `accum_direct_volumetric()` on __Direct3D 9__
- Restored grass shadow
- Implemented __Direct3D 10__ initialization over __Direct3D 11__
- Implemented actor shadow
- Prevented writing alpha-blended geometry to depth buffer
- Deleted __xrRender_R3__
- Deleted old TSM algorithms in all renders
- Deleted`r2_shadow_cascede_old` console command

### Dependencies

- Replaced `delete` operator with `xr_delete()` function in __xrXMLParser__

### Resources

- Implemented knife parameters class and and related features
- Implemented `use_condition` parameter
- Implemented notification restarting for `r2_sun` command

## Release 0.4 (September 2022)

### Common

- Added basic editorconfig
- Normalized line endings for the root files

### Engine

- Disabled use cases of `MSAA_ATEST_DX10_1_NATIVE`
- Disabled `r3_minmax_sm` by default
- Fixed crash when rendering volumetric fog on __Direct3D 11__
- Fixed sequence of initialization of API videocards
- Fixed screen resolution selection on missed `user.ltx`
- Fixed engine closing from taskbar menu
- Fixed displaying of transparent surfaces on HUD
- Fixed sunshafts for different sun quality
- Fixed transparent on static lightning
- Fixed comparison resulting in endless creation of new objects on __Direct3D 10+__
- Fixed camera glitches
- Implemented ability to switch entry point to a specific version of __Shader Model__
- Enabled teleport using `demo_record`
- Enabled `reload_dof` on weapons reloading
- Enabled __EAX__
- Added support for capturing cube map and location map on __Direct3D 10+__
- Added terrain mask support on static lighting
- Added inventory for ransacking monsters
- Added additional `set_weather` console command
- Added additional `read_sun_config` console command
- Added `trees_amplitude` option to weather settings
- Set FPS limit on UI rendering
- Increased range of near cascade

### Resources

- Normalized encoding of shaders
- Fixed _MSAA_ (redefinition of `Texture2DMS`)
- Fixed dynamic wet surfaces
- Fixed displaying of water foam
- Fixed skycube displaying on water surface
- Added shader to correct displaying of _LODs_ when _MSAA_ alphatest is enabled in classic __Direct3D 10__
- Added hint for ransacking monsters
- Implemented skyblend accumulation for sunshafts
- Implemented fog accounting for water on __Direct3D 9__
- Implemented light accounting for water foam
- Overrided entry point in _3D Fluid_ shaders
- Enabled `water_soft` shader for `water_studen` and `water_ryaska`

## Release 0.3 (May 2022)

### Common

- Migration to __Visual Studio 2022__
- Fixed compilation errors
- Fixed a lot of issues with linking
- Enabled multicore building for all projects
- Enabled __x86-64__ toolchain for all projects
- Enabled __GitHub Actions__
- Disabled debug and incremental info for all projects

### Core

- Replaced custom `xr_deque<T>` and `xr_vector<T>` with aliases of `std::deque<T>` and `std::vector<T>`
- Placed `clear_and_reserve()` method of `xr_vector<T>` class in a separate function
- Partially replaced STL extension aliases with `using` analogs
- Deleted `DEF_*` and `DEFINE_*` macroses from STL extensions

### Engine

- Replaced path to `shaders_cache` in all renders
- Fixed bug with exporting light to render
- Fixed __VSync__ on all renders
- Fixed blurring fonts on D3D11
- Fixed dialog window of level changer

### Dependencies

- Replaced `Flobbster.Windows.Forms` binary
- Replaced `dockpanelsuite` and bumped to `3.1`
- Deleted unused __Intel VTune__ functionality
- Deleted unused __OpenAutomate__ functionality
- Bumped `TargetFramework` to __.NET Framework__ 4.7.2

### Resources

- Added resources
- Normalized encoding of scripts

## Release 0.2 (November 2021)

### Common

- Migration to __Visual Studio 2015__
- Fixed compilation errors
- Replaced deprecated functions to safe and modern analogs
- Replaced some custom functions and types to standard library analog
- Disabled hardcoded _GUID_ of __DirectX__
- Replaced `debug::make_final<T>` class to _C++11_ `final` specifier

### Core

- Removed __BugTrap__ and __minizip__
- Fixed `Debug` configuration workability
- Fixed window focus error

### Engine

- Fixed `-nointro` key
- Unlocked console commands: `hud_fov`, `fov`, `jump_to_level`, `g_god`, `g_unlimitedammo`, `run_script`, `run_string`, `time_factor`
- Changed viewing angle coefficient to `67.5`

### Utilities

- Incompletely integrated __DirectXTex__

## Release 0.1 (March 2021)

### Common

- Migration to __Visual Studio 2013__
- Fixed compilation errors
- Fixed windows displaying in editor projects
- Configured engine and editor projects building
- Configured audio libraries and __OpenAutomate__ projects building

### Core

- Fixed looping and breaking the stack on `NODEFAULT`

### Engine

- Fixed skyboxes stretching

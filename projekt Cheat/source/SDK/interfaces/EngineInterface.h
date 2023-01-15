#pragma once
#include "../math/matrix.h"
#include "../math/qangle.h"

class IVEngineClient
{
private:
	virtual int                   GetIntersectingSurfaces() = 0;
	virtual void                  GetLightForPoint() = 0;
	virtual void*				  TraceLineMaterialAndLighting() = 0;
	virtual const char*			  ParseFile(const char* data, char* token, int maxlen) = 0;
	virtual bool                  CopyFile(const char* source, const char* destination) = 0;
public:
	virtual void                  GetScreenSize(int& width, int& height) = 0;
private:
	virtual void                  ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
	virtual void                  ClientCmd(const char* szCmdString) = 0;
	virtual bool                  GetPlayerInfo() = 0;
	virtual int                   GetPlayerForUserID(int userID) = 0;
	virtual void*				  TextMessageGet(const char* pName) = 0; // 10
public:
	virtual bool                  Con_IsVisible(void) = 0;
	virtual int                   GetLocalPlayer(void) = 0;
private:
	virtual const void*			  LoadModel(const char* pName, bool bProp = false) = 0;
	virtual float                 GetLastTimeStamp(void) = 0;
	virtual void*				  GetSentence() = 0; // 15
	virtual float                 GetSentenceLength() = 0;
	virtual bool                  IsStreaming() const = 0;
public:
	virtual void                  GetViewAngles(qangle_t* va) = 0;
	virtual void                  SetViewAngles(qangle_t* va) = 0;
	virtual int                   GetMaxClients(void) = 0; // 20
	virtual const char*			  Key_LookupBinding(const char* pBinding) = 0;
private:
	virtual const char*			  Key_BindingForKey(int& code) = 0;
	virtual void                  Key_SetBinding(int, char const*) = 0;
	virtual void                  StartKeyTrapMode(void) = 0;
	virtual bool                  CheckDoneKeyTrapping(int& code) = 0;
public:
	virtual bool                  IsInGame(void) = 0;
	virtual bool                  IsConnected(void) = 0;
	virtual bool                  IsDrawingLoadingImage(void) = 0;
	virtual void                  HideLoadingPlaque(void) = 0;
private:
	virtual void                  Con_NPrintf(int pos, const char* fmt, ...) = 0; // 30
	virtual void                  Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;
	virtual int                   IsBoxVisible() = 0;
	virtual int                   IsBoxInViewCluster() = 0;
	virtual bool                  CullBox() = 0;
	virtual void                  Sound_ExtraUpdate(void) = 0;
public:
	virtual const char*			  GetGameDirectory(void) = 0;
	virtual const v_matrix&		  WorldToScreenMatrix() = 0;
	virtual const v_matrix&		  WorldToViewMatrix() = 0;
private:
	virtual int                   GameLumpVersion(int lumpId) const = 0;
	virtual int                   GameLumpSize(int lumpId) const = 0; // 40
	virtual bool                  LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
	virtual int                   LevelLeafCount() const = 0;
	virtual void*				  GetBSPTreeQuery() = 0;
	virtual void                  LinearToGamma(float* linear, float* gamma) = 0;
	virtual float                 LightStyleValue(int style) = 0; // 45
	virtual void                  ComputeDynamicLighting() = 0;
	virtual void                  GetAmbientLightColor() = 0;
	virtual int                   GetDXSupportLevel() = 0;
	virtual bool                  SupportsHDR() = 0;
	virtual void                  Mat_Stub() = 0; // 50
	virtual void                  GetChapterName(char* pchBuff, int iMaxLength) = 0;
	virtual char const*			  GetLevelName(void) = 0;
	virtual char const*			  GetLevelNameShort(void) = 0;
	virtual char const*			  GetMapGroupName(void) = 0;
	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
	virtual void                  SetVoiceCasterID(unsigned int someint) = 0; // 56
	virtual void                  EngineStats_BeginFrame(void) = 0;
	virtual void                  EngineStats_EndFrame(void) = 0;
	virtual void                  FireEvents() = 0;
	virtual int                   GetLeavesArea(unsigned short* pLeaves, int nLeaves) = 0;
	virtual bool                  DoesBoxTouchAreaFrustum() = 0; // 60
	virtual int                   GetFrustumList() = 0;
	virtual bool                  ShouldUseAreaFrustum(int i) = 0;
	virtual void                  SetAudioState() = 0;
	virtual int                   SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
	virtual int                   SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
	virtual int                   SentenceIndexFromName(const char* pSentenceName) = 0;
	virtual const char*			  SentenceNameFromIndex(int sentenceIndex) = 0;
	virtual int                   SentenceGroupIndexFromName(const char* pGroupName) = 0;
	virtual const char*			  SentenceGroupNameFromIndex(int groupIndex) = 0;
	virtual float                 SentenceLength(int sentenceIndex) = 0;
	virtual void                  ComputeLighting() = 0;
	virtual void                  ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
	virtual bool                  IsOccluded() = 0; // 74
	virtual int                   GetOcclusionViewId(void) = 0;
	virtual void*				  SaveAllocMemory(size_t num, size_t size) = 0;
	virtual void                  SaveFreeMemory(void* pSaveMem) = 0;
	virtual void*				  GetNetChannelInfo(void) = 0;
	virtual void                  DebugDrawPhysCollide() = 0; //79
	virtual void                  CheckPoint(const char* pName) = 0; // 80
	virtual void                  DrawPortals() = 0;
	virtual bool                  IsPlayingDemo(void) = 0;
	virtual bool                  IsRecordingDemo(void) = 0;
	virtual bool                  IsPlayingTimeDemo(void) = 0;
	virtual int                   GetDemoRecordingTick(void) = 0;
	virtual int                   GetDemoPlaybackTick(void) = 0;
	virtual int                   GetDemoPlaybackStartTick(void) = 0;
	virtual float                 GetDemoPlaybackTimeScale(void) = 0;
	virtual int                   GetDemoPlaybackTotalTicks(void) = 0;
public:
	virtual bool                  IsPaused(void) = 0; // 90
private:
	virtual float                 GetTimescale(void) const = 0;
public:
	virtual bool                  IsTakingScreenshot(void) = 0;
	virtual bool                  IsHLTV(void) = 0;
private:
	virtual bool                  IsLevelMainMenuBackground(void) = 0;
	virtual void                  GetMainMenuBackgroundName(char* dest, int destlen) = 0;
	virtual void                  SetOcclusionParameters(const int /*OcclusionParams_t*/& params) = 0; // 96
	virtual void                  GetUILanguage(char* dest, int destlen) = 0;
	virtual int                   IsSkyboxVisibleFromPoint() = 0;
	virtual const char*			  GetMapEntitiesString() = 0;
	virtual bool                  IsInEditMode(void) = 0; // 100
	virtual float                 GetScreenAspectRatio(int viewportWidth, int viewportHeight) = 0;
	virtual bool                  REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
	virtual bool                  REMOVED_SteamProcessCall(bool& finished) = 0;
	virtual unsigned int          GetEngineBuildNumber() = 0; // engines build
	virtual const char*			  GetProductVersionString() = 0; // mods version number (steam.inf)
	virtual void                  GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
	virtual bool                  IsHammerRunning() const = 0;
	virtual void                  ExecuteClientCmd(const char* szCmdString) = 0; //108
	virtual bool                  MapHasHDRLighting(void) = 0;
	virtual bool                  MapHasLightMapAlphaData(void) = 0;
	virtual int                   GetAppID() = 0;
	virtual void				  GetLightForPointFast() = 0;
	virtual void                  ClientCmd_Unrestricted(char  const*, int, bool) = 0;
	virtual void                  ClientCmd_Unrestricted(const char* szCmdString) = 0; // 114
	virtual void                  SetRestrictServerCommands(bool bRestrict) = 0;
	virtual void                  SetRestrictClientCommands(bool bRestrict) = 0;
	virtual void                  SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;
	virtual bool                  CopyFrameBufferToMaterial(const char* pMaterialName) = 0;
	virtual void                  ReadConfiguration(const int iController, const bool readDefault) = 0;
	virtual void                  SetAchievementMgr() = 0;
	virtual void*				  GetAchievementMgr() = 0;
	virtual bool                  MapLoadFailed(void) = 0;
	virtual void                  SetMapLoadFailed(bool bState) = 0;
	virtual bool                  IsLowViolence() = 0;
	virtual const char*			  GetMostRecentSaveGame(void) = 0;
	virtual void                  SetMostRecentSaveGame(const char* lpszFilename) = 0;
	virtual void                  StartXboxExitingProcess() = 0;
	virtual bool                  IsSaveInProgress() = 0;
	virtual bool                  IsAutoSaveDangerousInProgress(void) = 0;
	virtual unsigned int          OnStorageDeviceAttached(int iController) = 0;
	virtual void                  OnStorageDeviceDetached(int iController) = 0;
	virtual const char*			  GetSaveDirName(void) = 0;
	virtual void                  WriteScreenshot(const char* pFilename) = 0;
	virtual void                  ResetDemoInterpolation(void) = 0;
	virtual int                   GetActiveSplitScreenPlayerSlot() = 0;
	virtual int                   SetActiveSplitScreenPlayerSlot(int slot) = 0;
	virtual bool                  SetLocalPlayerIsResolvable(char const* pchContext, int nLine, bool bResolvable) = 0;
	virtual bool                  IsLocalPlayerResolvable() = 0;
	virtual int                   GetSplitScreenPlayer(int nSlot) = 0;
	virtual bool                  IsSplitScreenActive() = 0;
	virtual bool                  IsValidSplitScreenSlot(int nSlot) = 0;
	virtual int                   FirstValidSplitScreenSlot() = 0; // -1 == invalid
	virtual int                   NextValidSplitScreenSlot(int nPreviousSlot) = 0; // -1 == invalid
	virtual void*				  GetSinglePlayerSharedMemorySpace(const char* szName, int ent_num = (1 << 11)) = 0;
	virtual void                  ComputeLightingCube() = 0;
	virtual void                  RegisterDemoCustomDataCallback() = 0;
	virtual void                  RecordDemoCustomData() = 0;
	virtual void                  SetPitchScale(float flPitchScale) = 0;
	virtual float                 GetPitchScale(void) = 0;
	virtual bool                  LoadFilmmaker() = 0;
	virtual void                  UnloadFilmmaker() = 0;
	virtual void                  SetLeafFlag(int nLeafIndex, int nFlagBits) = 0;
	virtual void                  RecalculateBSPLeafFlags(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomNew(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomChanged(void) = 0;
	virtual bool                  DSPGetCurrentDASRoomSkyAbove(void) = 0;
	virtual float                 DSPGetCurrentDASRoomSkyPercent(void) = 0;
	virtual void                  SetMixGroupOfCurrentMixer(const char* szgroupname, const char* szparam, float val, int setMixerType) = 0;
	virtual int                   GetMixLayerIndex(const char* szmixlayername) = 0;
	virtual void                  SetMixLayerLevel(int index, float level) = 0;
	virtual int                   GetMixGroupIndex(char  const* groupname) = 0;
	virtual void                  SetMixLayerTriggerFactor(int i1, int i2, float fl) = 0;
	virtual void                  SetMixLayerTriggerFactor(char  const* char1, char  const* char2, float fl) = 0;
	virtual bool                  IsCreatingReslist() = 0;
	virtual bool                  IsCreatingXboxReslist() = 0;
	virtual void                  SetTimescale(float flTimescale) = 0;
	virtual void                  SetGamestatsData() = 0;
	virtual void*				  GetGamestatsData() = 0;
	virtual void                  GetMouseDelta(int& dx, int& dy, bool b) = 0; // unknown
	virtual   const char*		  Key_LookupBindingEx(const char* pBinding, int iUserId = -1, int iStartCount = 0, int iAllowJoystick = -1) = 0;
	virtual int                   Key_CodeForBinding(char  const*, int, int, int) = 0;
	virtual void                  UpdateDAndELights(void) = 0;
	virtual int                   GetBugSubmissionCount() const = 0;
	virtual void                  ClearBugSubmissionCount() = 0;
	virtual bool                  DoesLevelContainWater() const = 0;
	virtual float                 GetServerSimulationFrameTime() const = 0;
	virtual void                  SolidMoved() = 0;
	virtual void                  TriggerMoved(class IClientEntity* pTriggerEnt, bool accurateBboxTriggerChecks) = 0;
	virtual void                  ComputeLeavesConnected() = 0;
	virtual bool                  IsInCommentaryMode(void) = 0;
	virtual void                  SetBlurFade(float amount) = 0;
	virtual bool                  IsTransitioningToLoad() = 0;
	virtual void                  SearchPathsChangedAfterInstall() = 0;
	virtual void                  ConfigureSystemLevel(int nCPULevel, int nGPULevel) = 0;
	virtual void                  SetConnectionPassword(char const* pchCurrentPW) = 0;
	virtual void*				  GetSteamAPIContext() = 0;
	virtual void                  SubmitStatRecord(char const* szMapName, unsigned int uiBlobVersion, unsigned int uiBlobSize, const void* pvBlob) = 0;
	virtual void                  ServerCmdKeyValues() = 0; // 203
	virtual void                  SpherePaintSurface() = 0;
	virtual bool                  HasPaintmap(void) = 0;
	virtual void                  EnablePaintmapRender() = 0;
	//virtual void                TracePaintSurface( const model_t *model, const Vector& position, float radius, CUtlVector<Color>& surfColors ) = 0;
	virtual void                  SphereTracePaintSurface() = 0;
	virtual void                  RemoveAllPaint() = 0;
	virtual void                  PaintAllSurfaces(unsigned char uchr) = 0;
	virtual void                  RemovePaint() = 0;
public:
	virtual bool                  IsActiveApp() = 0;
	virtual bool                  IsClientLocalToActiveServer() = 0;
private:
	virtual void                  TickProgressBar() = 0;
	virtual void				  GetInputContext(int /*EngineInputContextId_t*/ id) = 0;
	virtual void                  GetStartupImage(char* filename, int size) = 0;
	virtual bool                  IsUsingLocalNetworkBackdoor(void) = 0;
	virtual void                  SaveGame(const char*, bool, char*, int, char*, int) = 0;
	virtual void                  GetGenericMemoryStats(/* GenericMemoryStat_t */ void**) = 0;
	virtual bool                  GameHasShutdownAndFlushedMemory(void) = 0;
	virtual int                   GetLastAcknowledgedCommand(void) = 0;
	virtual void                  FinishContainerWrites(int i) = 0;
	virtual void                  FinishAsyncSave(void) = 0;
	virtual int                   GetServerTick(void) = 0;
	virtual const char*			  GetModDirectory(void) = 0;
	virtual bool                  AudioLanguageChanged(void) = 0;
	virtual bool                  IsAutoSaveInProgress(void) = 0;
	virtual void                  StartLoadingScreenForCommand(const char* command) = 0;
	virtual void                  StartLoadingScreenForKeyValues() = 0;
	virtual void                  SOSSetOpvarFloat(const char*, float) = 0;
	virtual void                  SOSGetOpvarFloat(const char*, float&) = 0;
	virtual bool                  IsSubscribedMap(const char*, bool) = 0;
	virtual bool                  IsFeaturedMap(const char*, bool) = 0;
	virtual void                  GetDemoPlaybackParameters(void) = 0;
public:
	virtual int                   GetClientVersion(void) = 0;
private:
	virtual bool                  IsDemoSkipping(void) = 0;
	virtual void                  SetDemoImportantEventData() = 0;
	virtual void                  ClearEvents(void) = 0;
	virtual int                   GetSafeZoneXMin(void) = 0;
	virtual bool                  IsVoiceRecording(void) = 0;
	virtual void                  ForceVoiceRecordOn(void) = 0;
public:
	virtual bool                  IsReplay(void) = 0;
};
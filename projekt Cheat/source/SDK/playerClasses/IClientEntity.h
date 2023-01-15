#pragma once

#include "BaseHandle.h"
#include "classes/player.h"


//check if those are included in one of the included headers
#include "..\recvDatatable.h"
#include "..\math\math.h"
#include "IModelRender.h"

enum e_solid_type {
	solid_none,
	solid_bsp,
	solid_bbox,
	solid_obb,
	solid_obb_yaw,
	solid_custom,
	solid_vphysics,
	solid_last
};

//forward declaration
class IClientUnknown;
class CBaseHandle;

//unused without ray_t
//struct ray_t;
//class CGameTrace;

class ICollideable {
public:
	virtual IHandleEntity*		GetEntityHandle() = 0;
	virtual c_vec3&				ObbMins() const = 0;
	virtual c_vec3&				ObbMaxs() const = 0;
	virtual void				WorldSpaceTriggerBounds(c_vec3* mins, c_vec3* maxs) const = 0;
	virtual bool				TestCollision(void /*const ray_t& ray, unsigned int mask, c_game_trace& trace*/) = 0;
	virtual bool				TestHitboxes(void /*const ray_t& ray, unsigned int mask, c_game_trace& trace*/) = 0;
	virtual int					GetCollisionModelIndex() = 0;
	virtual const model_t*		GetCollisionModel() = 0;
	virtual const c_vec3&		GetCollisionOrigin() const = 0;
	virtual const qangle_t&		GetCollisionAngles() const = 0;
	virtual const matrix_t&		CollisionToWorldTransform() const = 0;
	virtual e_solid_type		GetSolid() const = 0;
	virtual int					GetSolidFlags() const = 0;
	virtual IClientUnknown*		GetClientUnknown() = 0;
	virtual int					GetCollisionGroup() const = 0;
	virtual void				WorldSpaceSurroundingBounds(c_vec3* mins, c_vec3* maxs) = 0;
	virtual bool				ShouldTouchTrigger(int flags) const = 0;
	virtual const matrix_t*		GetRootParentToWorldTransform() const = 0;
};

class IClientThinkable {
public:
	virtual IClientUnknown* GetClientUnknown() = 0;
	virtual void			ClientThink() = 0;
	virtual void*			GetThinkHandle() = 0;
	virtual void			SetThinkHandle(void* think) = 0;
	virtual void			Release() = 0;
};

class IClientNetworkable {
public:
	virtual IClientUnknown*		GetClientUnknown() = 0;
	virtual void				Release() = 0;
	virtual ClientClass*		GetClientClass() = 0;
	virtual void				NotifyShouldTransmit(int state) = 0;
	virtual void				OnPreDataChanged(int update_type) = 0;
	virtual void				OnDataChanged(int update_type) = 0;
	virtual void				PreDataUpdate(int update_type) = 0;
	virtual void				PostDataUpdate(int update_type) = 0;
	virtual void				unknown0() = 0;
	virtual bool				IsDormant() = 0;
	virtual int					GetIndex() const = 0;
	virtual void				ReceiveMessage(void /*int class_id, c_bf_read& msg*/) = 0;
	virtual void*				GetDataTableBasePtr() = 0;
	virtual void				SetDestroyedOnRecreateEntities() = 0;
};

//-----------------------------------------------------------------------------
// Purpose: All client entities must implement this interface.
//-----------------------------------------------------------------------------
class IClientRenderable {
public:
	virtual IClientUnknown*			GetClientUnknown() = 0;
	virtual c_vec3	 const&			GetRenderOrigin() = 0;
	virtual qangle_t const&			GetRenderAngles() = 0;
	virtual bool					ShouldDraw() = 0;
	virtual int						GetRenderFlags() = 0;
	virtual void					Unknown0() const = 0;
	virtual uint16_t				GetShadowHandle() const = 0;
	virtual uint16_t&				GetRenderHandle() = 0;
	virtual const model_t*			GetModel() const = 0;
	virtual int						DrawModel(int flags, uint8_t alpha) = 0;
	virtual int						GetBody() = 0;
	virtual void					GetColorModulation(float* color) = 0;
	virtual bool					LodTest() = 0;
	virtual bool					SetupBones(matrix_t* bones, int max, int mask, float time) = 0;
	virtual void					SetupWeights(const matrix_t* bones, int count, float* weights, float* delayed_weights) = 0;
	virtual void					DoAnimationEvents() = 0;
	virtual void*					GetPvsNotifyInterface() = 0;
	virtual void					GetRenderBounds(c_vec3& mins, c_vec3& maxs) = 0;
	virtual void					GetRenderBoundsWorldspace(c_vec3& mins, c_vec3& maxs) = 0;
	virtual void					GetShadowRenderBounds(c_vec3& mins, c_vec3& maxs, int type) = 0;
	virtual bool					ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool					GetShadowCastDistance(float* dist, int type) const = 0;
	virtual bool					GetShadowCastDirection(c_vec3* direction, int type) const = 0;
	virtual bool					IsShadowDirty() = 0;
	virtual void					MarkShadowDirty(bool dirty) = 0;
	virtual IClientRenderable*		GetShadowParent() = 0;
	virtual IClientRenderable*		FirstShadowChild() = 0;
	virtual IClientRenderable*		NextShadowPeer() = 0;
	virtual int						ShadowCastType() = 0;
	virtual void					CreateModelInstance() = 0;
	virtual uint16_t				GetModelInstance() = 0;
	virtual const matrix_t&			RenderableToWorldTransform() = 0;
	virtual int						LookupAttachment(const char* name) = 0;
	virtual bool					GetAttachment(int index, c_vec3& origin, c_vec3& angles) = 0;
	virtual bool					GetAttachment(int index, matrix_t& matrix) = 0;
	virtual float*					GetRenderClipPlane() = 0;
	virtual int						GetSkin() = 0;
	virtual void					OnThreadedDrawSetup() = 0;
	virtual bool					UsesFlexDelayedWeights() = 0;
	virtual void					RecordToolMessage() = 0;
	virtual bool					ShouldDrawForSplitScreenUser(int slot) = 0;
	virtual uint8_t					OverrideAlphaModulation(uint8_t alpha) = 0;
	virtual uint8_t					OverrideShadowAlphaModulation(uint8_t alpha) = 0;
};

//forward declaration
class CBaseEntity;
class CBasePlayer;
class IClientEntity;
class IClientAlphaProperty;

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable *		GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual IClientEntity*		GetIClientEntity() = 0;
	virtual CBaseEntity*		GetBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};

//-----------------------------------------------------------------------------
// Purpose: Main Entity Class (everything is accessable from this class)
//-----------------------------------------------------------------------------
class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	// Delete yourself.
	virtual void			Release(void) = 0;

	// Network origin + angles
	virtual const c_vec3&	GetAbsOrigin(void) const = 0;
	virtual const qangle_t& GetAbsAngles(void) const = 0;
};
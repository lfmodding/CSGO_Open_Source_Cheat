#pragma once
#include "..\math\vec3.h"
#include "..\math\matrix.h"

struct model_t {
	char			pad0[4]{};
	char			m_name[260]{};
	int				m_load_flags{};
	int				m_server_count{};
	int				m_type{};
	int				m_flags{};
	c_vec3			m_mins{};
	c_vec3			m_maxs{};
	float			m_radius{};
	void*			m_key_values{};
	char			pad1[24]{};
};

class IModelRender {
public:
	virtual int				DrawModel(int flags, void* renderable, unsigned short instance, int entity_index, void* model, c_vec3 const& origin, c_vec3 const& angles, int skin, int body, int hitboxset, const matrix_t* modelToWorld = NULL, const matrix_t* pLightingOffset = NULL) = 0;
	virtual void			ForceMaterial(void /*IMaterial* mat, int nOverrideType = 0, int nOverrides = 0*/) = 0;
	virtual bool			IsForcedMaterial(void) = 0;
	virtual void			SetViewTarget(const class c_studio_hdr* studio_hdr, int body_index, const c_vec3& target) = 0;
	virtual unsigned short	CreateInstance(void* renderable, void* cache = nullptr) = 0;
	virtual void			DestroyInstance(unsigned short handle) = 0;
	virtual void			SetStaticLighting(unsigned short handle, void* _handle) = 0;
	virtual void*			GetStaticLighting(unsigned short handle) = 0;
	virtual bool			ChangeInstance(unsigned short handle, void* renderable) = 0;
	virtual void			AddDecal(unsigned short handle, struct ray_t& ray, const c_vec3& decal_ip, int decal_index, int body, bool no_poke_throuh, int max_LOD_to_decal) = 0;
	virtual void			RemoveAllDecals(unsigned short handle) = 0;
	virtual bool			ModelHasDecals(unsigned short handle) = 0;
	virtual void			RemoveAllDecalsFromAllModels() = 0;
	virtual matrix_t*		DrawModelShadowSetup(void* renderable, int body, int skin, void* info, matrix_t* custom_bone_to_world = nullptr) = 0;
	virtual void			DrawModelShadow(void* renderable, void* info, matrix_t* custom_bone_to_world = nullptr) = 0;
	virtual bool			RecomputeStaticLighting(unsigned short handle) = 0;
	virtual void			ReleaseAllStaticPropColorData(void) = 0;
	virtual void			RestoreAllStaticPropColorData(void) = 0;
	virtual int				DrawModelEx(void /*model_render_info_t& info*/) = 0;
	virtual int				DrawModelExStaticProp(/*model_render_info_t& info*/) = 0;
	virtual bool			DrawModelSetup(void /*model_render_info_t& info, void* state, matrix_t* bone_to_world_out*/) = 0;
	virtual void			DrawModelExecute(void /*void* ctx, void* state, const model_render_info_t& info, matrix_t* custom_bone_to_world = nullptr*/) = 0;
	virtual void			SetupLighting(const c_vec3& center) = 0;
	virtual int				DrawStaticPropArrayFast(void* props, int count, bool shadow_depth) = 0;
	virtual void			SuppressEngineLighting(bool suppress) = 0;
	virtual void			SetupColorMeshes(int total_verts) = 0;
	virtual void			SetupLightingEx(const c_vec3& center, unsigned short handle) = 0;
	virtual bool			GetBrightestShadowingLightSource(const c_vec3& center, c_vec3& light_pos, c_vec3& light_brightness, bool allow_non_tagged_lights) = 0;
	virtual void			ComputeLightingState(int count, const void* query, void* state, void* env_cubemap_texture) = 0;
	virtual void			GetModelDecalHandles(void* decals, int decal_stride, int count, const unsigned short* handles) = 0;
	virtual void			ComputeStaticLightingState(int count, const void* query, void* state, void* decal_state, void* static_lightning, void* env_cubemap_texture, void* color_mesh_handles) = 0;
	virtual void			CleanupStaticLightingState(int count, void* color_mesh_handles) = 0;
};
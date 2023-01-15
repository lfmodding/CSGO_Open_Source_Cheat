#pragma once
#include "..\CBaseEntity.h"

class CBasePlayer : public CBaseEntity
{
public:
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", int)
	NETVAR(GetHealth, "CBasePlayer->m_iHealth", int)

	c_vec3 GetHitboxPosition(const int hitboxId)
	{
		const auto StudioModel
	}
};
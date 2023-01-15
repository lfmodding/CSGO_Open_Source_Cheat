#pragma once
#include "IClientEntity.h"
#include "..\..\core\NetVars\NetVarManager\NetVarManager.h"


class CBaseEntity : public IClientEntity {
public:
	NETVAR(GetTeam, "CBaseEntity->m_iTeamNum", int)
	NETVAR(GetCollisionGroup, "CBaseEntity->m_CollisionGroup", int)
};
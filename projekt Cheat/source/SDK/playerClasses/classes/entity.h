#pragma once
//#include "..\CBaseEntity.h"
#include "..\..\..\core\NetVars\NetVarManager\NetVarManager.h"

class CBaseEntity : public IClientEntity {
public:
	NETVAR(GetTeam, "CBaseEntity->m_iTeamNum", int)
	NETVAR(GetCollisionGroup, "CBaseEntity->m_CollisionGroup", int)

	//TODO:
	//GET_NETVAR_OFFSET(e_move_type, get_move_type, _("DT_BaseEntity"), _("m_nRenderMode"), 0x1);
	//GET_NETVAR_OFFSET(const matrix_t, get_coordinate_frame, _("DT_BaseEntity"), _("m_CollisionGroup"), -0x30);
};
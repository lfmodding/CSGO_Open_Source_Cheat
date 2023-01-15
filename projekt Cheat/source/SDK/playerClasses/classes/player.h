#pragma once
//#include "..\..\..\core\NetVars\NetVarManager\NetVarManager.h"
#include "entity.h"

class CBasePlayer : public CBaseEntity
{
public:
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", int);
};
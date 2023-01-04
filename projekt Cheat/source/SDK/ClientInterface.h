#pragma once
#include "..\core\NetVars\entity.h"
#include "datatable.h"

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(unsigned long hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(unsigned long hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual CEntity* GetClientEntity(int entnum) = 0;
};


class IClient
{
private:
	virtual void Unused_0() = 0;
	virtual void Unused_1() = 0;
	virtual void Unused_2() = 0;
	virtual void Unused_3() = 0;
	virtual void Unused_4() = 0;
	virtual void Unused_5() = 0;
	virtual void Unused_6() = 0;
	virtual void Unused_7() = 0;
public:
	virtual ClientClass* GetAllClasses(void) = 0;
};

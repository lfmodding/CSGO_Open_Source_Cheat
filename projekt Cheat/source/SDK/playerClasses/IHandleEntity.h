#pragma once

class CBaseHandle;

class IHandleEntity {
public:
	virtual ~IHandleEntity() {
	}

	virtual void				SetRefEhandle(const CBaseHandle& handle)= 0;
	virtual const CBaseHandle&	GetRefEhandle()						const = 0;
};

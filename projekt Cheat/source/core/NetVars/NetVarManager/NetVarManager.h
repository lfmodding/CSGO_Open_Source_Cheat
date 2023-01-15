#pragma once
#include "..\..\..\SDK\recvDatatable.h"
#include "..\..\..\Dependencies\fnv.h"


#include <iostream>
#include <unordered_map>


void SetupNetvars();

void Dump(const char* baseClass, RecvTable* table, uint32_t offset = 0);

namespace netvarDev
{
	void PrintAllBaseClasses();

	void RecursivePrintNetvars(const char* baseClass, RecvTable* recvTable);
	void PrintNetvarsOfBaseClass(const char* baseClass);
	void PrintAllNetvarsAndBaseClasses();
}

inline std::unordered_map<std::uint32_t, std::uint32_t> netvars;

#define NETVAR(func_name, netvar, type) type& func_name() \
{ \
	static auto offset = netvars[fnv::HashConst(netvar)]; \
	return *reinterpret_cast<type*>(std::uint32_t(this) +  offset); \
}
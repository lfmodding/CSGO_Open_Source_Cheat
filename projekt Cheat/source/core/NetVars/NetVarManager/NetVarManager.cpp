#include "netvarManager.h"

#include "..\..\..\SDK\ClientInterface.h"

#include "..\..\Interfaces\interfaces.h"

#include <format>

void SetupNetvars()
{
	for (auto clientClass = client->GetAllClasses(); clientClass; clientClass = clientClass->next)
		if (clientClass->recvTable)
			Dump(clientClass->networkName, clientClass->recvTable);
}

void Dump(const char* baseClass, RecvTable* table, uint32_t offset)
{
	for (auto i = 0; i < table->propsCount; i++)
	{
		const auto prop = &table->props[i];

		if (!prop || isdigit(prop->varName[0]))
			continue;

		if (fnv::Hash(prop->varName) == fnv::HashConst("baseclass"))
			continue;

		if (prop->recvType == SendPropType::DATATABLE &&
			prop->dataTable &&
			prop->dataTable->tableName[0] == 'D')
		{
			Dump(baseClass, prop->dataTable, offset + prop->offset);
		}

		const auto netvarName = std::format("{}->{}", baseClass, prop->varName);

		netvars[fnv::Hash(netvarName.c_str())] = offset + prop->offset;
	}
}

void netvarDev::PrintAllBaseClasses()
{
	for (auto currnode = client->GetAllClasses(); currnode; currnode = currnode->next)
		std::cout << currnode->networkName << std::endl;
}

void netvarDev::RecursivePrintNetvars(const char* baseClass, RecvTable* recvTable)
{
	for (auto i = 0; i < recvTable->propsCount; i++)
	{
		auto prop = &recvTable->props[i];

		if (isdigit(prop->varName[0]))
			continue;

		if (prop->dataTable &&
			prop->recvType == SendPropType::DATATABLE
			&& prop->varName[0] == 'D')
			RecursivePrintNetvars(baseClass, prop->dataTable);

		if (!prop->dataTable &&
			!(prop->recvType == SendPropType::DATATABLE))
			std::cout << std::format("{}->{}", baseClass, prop->varName) << std::endl;
	}
}

void netvarDev::PrintNetvarsOfBaseClass(const char* baseClass)
{
	for (auto currnode = client->GetAllClasses(); currnode; currnode = currnode->next)
		if (currnode->networkName == baseClass)
			RecursivePrintNetvars(baseClass, currnode->recvTable);
}

void netvarDev::PrintAllNetvarsAndBaseClasses()
{
	for (auto currnode = client->GetAllClasses(); currnode; currnode = currnode->next)
		RecursivePrintNetvars(currnode->networkName, currnode->recvTable);
}

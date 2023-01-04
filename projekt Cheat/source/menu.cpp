#include "menu.h"
#include "NetVars/entity.h"
#include "Interfaces/interfaces.h"

void menu::render()
{
	ImGui::Begin("Projekt Cheat");

	if (entityList->GetClientEntity(1)->health())
		ImGui::Value("ent1 health: ", entityList->GetClientEntity(1)->health());

	ImGui::End();
}

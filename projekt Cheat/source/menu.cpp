#include "menu.h"
#include "NetVars/entity.h"
#include "NetVars/interfaces.h"

void menu::render()
{
	ImGui::Begin("Projekt Cheat");
	ImGui::Value("ent1 health: ", entityList->GetClientEntity(1)->health());
	ImGui::End();
}

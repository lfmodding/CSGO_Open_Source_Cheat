#include "menu.h"
#include "SDK/playerClasses/CBaseEntity.h"
#include "core/Interfaces/interfaces.h"

void menu::render()
{
	ImGui::Begin("Projekt Cheat");
	ImGui::Value("idk", entityList->GetClientEntity(1)->GetBaseEntity()->GetTeam());
	ImGui::End();
}

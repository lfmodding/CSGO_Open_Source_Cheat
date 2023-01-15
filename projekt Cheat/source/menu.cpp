#include "menu.h"
#include "SDK/playerClasses/classes/player.h"
#include "core/Interfaces/interfaces.h"

void menu::render()
{
	auto entity = static_cast<CBasePlayer*>(entityList->GetClientEntity(1));

	ImGui::Begin("Projekt Cheat");
	ImGui::Value("Health", entity->GetHealth());
	ImGui::Value("Team", entityList->GetClientEntity(1)->GetBaseEntity()->GetTeam());
	ImGui::End();
}

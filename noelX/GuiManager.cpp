#include "GuiManager.h"

GuiManager::GuiManager()
{
	IMGUI_CHECKVERSION();
	ImGuiContext* ctx = ImGui::CreateContext();
	ImGui::SetCurrentContext(ctx);
	ImGui::StyleColorsDark();
}

GuiManager::~GuiManager()
{
	ImGui::DestroyContext();
}
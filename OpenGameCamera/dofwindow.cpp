#define NOMINMAX
#include "dofwindow.h"
#include <Windows.h>

DofWindow::DofWindow()
{
	printf("Initializing DofWindow\n");
}

bool DofWindow::IsEnabled()
{
	return Settings::homeMenu;
}

void DofWindow::SetEnabled(bool enabled)
{
	Settings::dofMenu = enabled;
}

void DofWindow::Draw()
{
	ImGui::Begin("WateredDownCamera", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox(std::string("Enable Depth of Field [" + Keys::enableDof.name + "]").c_str(), &Settings::enableDof);
	ImGui::Checkbox("Enable Foreground Blur", &Settings::dofEnableForeground);
	ImGui::Checkbox("Blur Half Resolution", &Settings::spriteHalfResolution);
	ImGui::SliderFloat("Max Blur", &Settings::dofBlurMax, 0, 6, "%.3f", 1.0F);
	ImGui::SliderFloat("Near Start", &Settings::dofNearStart, 0, 32, "%.3f", 1.0F);
	ImGui::SliderFloat("Near End", &Settings::dofNearEnd, 0, 32, "%.3f", 1.0F);
	ImGui::SliderFloat("Focus Distance", &Settings::focusDistance, 0, 128, "%.3f", 1.0F);
	ImGui::SliderFloat("Far Start", &Settings::dofFarStart, 0, 32, "%.3f", 1.0F);
	ImGui::SliderFloat("Far End", &Settings::dofFarEnd, 0, 32, "%.3f", 1.0F);
	ImGui::Checkbox(std::string("Enable Resolution Scale [" + Keys::enableResScale.name + "]").c_str(), &Settings::enableResScale);
	ImGui::InputFloat("Resolution Scale", &Settings::resScale, 1.f, 0.25f, "%.3f", 1.0F);
	Settings::resScale = std::min(5.f, std::max(0.25f, Settings::resScale));
	ImGui::End();
}
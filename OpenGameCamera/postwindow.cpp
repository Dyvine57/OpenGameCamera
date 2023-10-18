#define NOMINMAX
#include "postwindow.h"
#include <Windows.h>
#include <algorithm>

PostWindow::PostWindow()
{
	printf("Initializing PostWindow\n");
}

bool PostWindow::IsEnabled()
{
	return Settings::homeMenu && Settings::postMenu;
}

void PostWindow::SetEnabled(bool enabled)
{
	Settings::cameraMenu = enabled;
}

void PostWindow::Draw()
{
	ImGui::Begin("Post Process", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	//ImGui::Checkbox("Force Post Process Settings", &Settings::enablePost);
	ImGui::Checkbox("Enable Bloom", &Settings::forceBloomEnable);
	ImGui::Checkbox("Enable Vignette", &Settings::VignetteEnable);
	ImGui::Checkbox("Enable Color Grading", &Settings::enableGrading);
	ImGui::Checkbox("Enable Film Grain", &Settings::FilmGrainEnable);
	ImGui::Checkbox("Enable Chromatic Aberration", &Settings::ChromaticAberrationAllowed);
	ImGui::Checkbox("Enable Lens Distortion", &Settings::LensDistortionAllowed);
	ImGui::Checkbox("SSR Enable", &Settings::ssrEnable);
	ImGui::Checkbox("SSR Full Res Enable", &Settings::ssrFullResEnable);
	ImGui::Checkbox(std::string("Enable Resolution Scale [" + Keys::enableResScale.name + "]").c_str(), &Settings::enableResScale);
	ImGui::InputFloat("Resolution Scale", &Settings::resScale, 1.f, 0.25f, "%.3f", 1.0F);
	Settings::resScale = std::min(5.f, std::max(0.25f, Settings::resScale));
	ImGui::End();
}
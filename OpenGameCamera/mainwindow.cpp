#include "mainwindow.h"
#include <Windows.h>
#include "camerawindow.h"
#include "dofwindow.h"
#include "matchinfowindow.h"
#include "postwindow.h"

MainWindow::MainWindow()
{
	if (gpMainWindow)
	{
		MessageBox(0, "MainWindow is already initialized.", "Error", MB_ICONERROR);
		ExitProcess(EXIT_FAILURE);
	}
	gpMainWindow = this;
	new DofWindow();
	new PostWindow();
}

bool MainWindow::IsEnabled()
{
	return Settings::homeMenu;
}

void MainWindow::SetEnabled(bool enabled)
{
	Settings::homeMenu = enabled;
}

void MainWindow::Draw()
{
	//ImGui::BeginMainMenuBar();
	ImGui::Begin("OpenGameCamera", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Checkbox(std::string("Show Menu [" + Keys::showMenuKey.name + "]").c_str(), &Settings::homeMenu)) {
		Settings::updateMouseState = true;
	}
	ImGui::Checkbox("Show DoF Menu", &Settings::dofMenu);
	ImGui::Checkbox("Show Post Process Menu", &Settings::postMenu);
	ImGui::End();
}
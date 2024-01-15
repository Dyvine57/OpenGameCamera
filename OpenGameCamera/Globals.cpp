#include "Globals.hpp"

// read a key with a minimum time required before it is read again
bool Globals::ReadKeyOnce(unsigned int keycode, unsigned int timer) {
	// if foreground is required, check if the window is in the foreground
	if (Globals::requireActive && !Globals::isWindowActive()) return false;

	// get the current time - the last keypress time AND
	// check if the key is being pressed
	if ((clock() - lastTime > timer) && GetAsyncKeyState(keycode)) {
		// set the last clock time, then return true
		Globals::lastTime = clock();
		return true;
	}
	// return false if the previous clock time wasn't within the minimum required, or the key wasn't pressed
	return false;
}

// call the above function
bool Globals::ReadKeyOnce(KeyDef keyDef, unsigned int timer) {
	return Globals::ReadKeyOnce(keyDef.keyCode, timer);
}

// read a key without giving a damn about how many times it was pressed, or if it's being held
bool Globals::ReadKey(unsigned int keycode) {
	// check the active window
	if (Globals::requireActive && !Globals::isWindowActive()) return false;

	// return the keystate
	return GetAsyncKeyState(keycode);
}

// call the above
bool Globals::ReadKey(KeyDef keyDef) {
	return Globals::ReadKey(keyDef.keyCode);
}

// return if the game window is in the foreground
bool Globals::isWindowActive() {
	// if the window handle is invalid, 
	if (Globals::windowHandle == NULL) {
		// call our EnumWindows function to get the window
		EnumWindows(Globals::EnumWindowsProc, NULL);
	}
	// then return a check if the active window is the game window
	return GetActiveWindow() == Globals::windowHandle;
}

// enumerate all windows
BOOL CALLBACK Globals::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	// check if it's our console window, if so skip
	if (hwnd == GetConsoleWindow()) return TRUE;

	// get the process ID of the window
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);

	// if the process ID is our own,
	if (lpdwProcessId == GetCurrentProcessId())
	{
		// set our static window handle and exit EnumWindow
		Globals::windowHandle = hwnd;
		return FALSE;
	}
	return TRUE;
}

// the current window handle
HWND Globals::windowHandle = NULL;

// require the foreground to be active
bool Globals::requireActive = false;

// the last clock
time_t Globals::lastTime = clock();

Vec4 Globals::g_CameraPosition = { 0, 0, 0, 0 };

// actual key definitions for our preset keys
KeyDef Keys::showMenuKey = { "F6", VK_F6 };
KeyDef Keys::enableDof = { "F9", VK_F9 };
KeyDef Keys::enableResScale = { "F10", VK_F10 };

// old stuff
KeyDef Keys::enableFreeCam = { "F5", VK_F5 };
KeyDef Keys::freezePlayer = { "F6", VK_F6 };
KeyDef Keys::speedUpCamera = { "SHIFT", VK_SHIFT };
KeyDef Keys::slowDownCamera = { "ALT", VK_MENU };
KeyDef Keys::cameraForward = { "W", VK_UP };
KeyDef Keys::cameraBack = { "S", VK_DOWN };
KeyDef Keys::cameraLeft = { "A", VK_LEFT };
KeyDef Keys::cameraRight = { "D", VK_RIGHT };
KeyDef Keys::cameraUp = { "SPACE", VK_SPACE };
KeyDef Keys::cameraDown = { "CONTROL", VK_CONTROL };
KeyDef Keys::disableUi = { "F7", VK_F7 };
KeyDef Keys::freezeTime = { "F8", VK_F8 };
KeyDef Keys::fovIncrease = { "+", VK_OEM_PLUS };
KeyDef Keys::fovDecrease = { "-", VK_OEM_MINUS };
KeyDef Keys::resetSettingsMenus = { "" };

bool Settings::updateMouseState = false;
bool Settings::informationMenu = false;
bool Settings::enableFreeCam = false;
bool Settings::disableUi = true;
bool Settings::homeMenu = false;
bool Settings::cameraMenu = true;
bool Settings::dofMenu = true;
bool Settings::postMenu = true;
bool Settings::matchInfoMenu = false;
// Camera Settings
bool Settings::forceEv = false;
float Settings::evControl = 10.f;
float Settings::camSens = 1.f;
bool Settings::lockFreeCam = false;
float Settings::fov = 55;
float Settings::resScale = 1.f;
bool Settings::enableResScale = false;
float Settings::mainSpeed = 0.1f;
float Settings::slowSpeed = .01f;
float Settings::fastSpeed = 1.f;
float Settings::mouseSensitivity = 1.3f;
bool Settings::freezeTime = false;
float Settings::timeScale = 1.f;
bool Settings::freezePlayer = true;

bool Settings::ssrEnable = true;
bool Settings::ssrFullResEnable = true;
// DOF Settings
bool Settings::enableDof = false;
float Settings::focusDistance = 5.f;
bool Settings::spriteHalfResolution = false;
float Settings::dofBlurMax = 3.f;
float Settings::dofFarStart = 4.f;
float Settings::dofFarEnd = 16.f;
bool Settings::dofEnableForeground = false;
float Settings::dofNearStart = 2.f;
float Settings::dofNearEnd = 8.f;
// Post Proccess Settings
bool Settings::enablePost = false;
bool Settings::forceBloomEnable = true;
bool Settings::VignetteEnable = false;
bool Settings::enableGrading = true;
bool Settings::FilmGrainEnable = false;
bool Settings::ChromaticAberrationAllowed = false;
bool Settings::LensDistortionAllowed = false;
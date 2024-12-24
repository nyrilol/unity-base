#pragma once
#include <windows.h>

namespace core::globals
{
	// @note: for the love of god remember to change this if the game is mono
	bool is_il2cpp = false;

	// game module (changes between il2cpp and mono)
	HMODULE h_game = NULL;

	// ingame stuff
	float og_fov = 90.f;
}
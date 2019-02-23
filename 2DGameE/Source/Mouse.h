#pragma once
#include "Vector2D.h"


namespace Mouse {
	// Mouse movement
	void SetMouse(int mouseX, int mouseY);

	int GetScreenMouseX();
	int GetScreenMouseY();

	void SetWorldMouse(int mouseX, int mouseY);

	int GetWorldMouseX();
	int GetWorldMouseY();

	// Mouse buttons
	void SetLMB(bool isEnabled);
	void SetMMB(bool isEnabled);
	void SetRMB(bool isEnabled);

	bool GetLMB();
	bool GetMMB();
	bool GetRMB();

};
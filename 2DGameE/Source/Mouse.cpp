#include "Mouse.h"

namespace Mouse {
	namespace PV { // Private Variables - Don't change, don't acces dirrectly, use funtions
		int MouseX = 0; // Mouse X Coordinates
		int MouseY = 0; // Mouse Y Coordinates

		int WorldMouseX = 0;
		int WorldMouseY = 0;

		bool LMB = false; // Left Mouse Button
		bool MMB = false; // Middle Mouse Button
		bool RMB = false; // Right Mouse Button
	}

	// Mouse movement
	void SetMouse(int mouseX, int mouseY)
	{
		PV::MouseX = mouseX;
		PV::MouseY = mouseY;
	}

	int GetScreenMouseX()
	{
		return PV::MouseX;
	}
	int GetScreenMouseY()
	{
		return PV::MouseY;
	}

	void SetWorldMouse(int mouseX, int mouseY)
	{
		PV::WorldMouseX = mouseX;
		PV::WorldMouseY = mouseY;
	}

	int GetWorldMouseX()
	{
		return PV::WorldMouseX;
	}

	int GetWorldMouseY()
	{
		return PV::WorldMouseY;
	}

	// Mouse buttons
	void SetLMB(bool isEnabled)
	{
		PV::LMB = isEnabled;
	}
	void SetMMB(bool isEnabled)
	{
		PV::MMB = isEnabled;
	}
	void SetRMB(bool isEnabled)
	{
		PV::RMB = isEnabled;
	}

	bool GetLMB()
	{
		return PV::LMB;
	}
	bool GetMMB()
	{
		return PV::MMB;
	}
	bool GetRMB()
	{
		return PV::RMB;
	}

};
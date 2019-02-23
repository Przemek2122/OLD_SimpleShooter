#pragma once

namespace Keyboard {
	// Numbers 0 - 9
	// Set
	void SetKey_0(bool isEnabled);
	void SetKey_1(bool isEnabled);
	void SetKey_2(bool isEnabled);
	void SetKey_3(bool isEnabled);
	void SetKey_4(bool isEnabled);
	void SetKey_5(bool isEnabled);
	void SetKey_6(bool isEnabled);
	void SetKey_7(bool isEnabled);
	void SetKey_8(bool isEnabled);
	void SetKey_9(bool isEnabled);

	// Get
	bool GetKey_0();
	bool GetKey_1();
	bool GetKey_2();
	bool GetKey_3();
	bool GetKey_4();
	bool GetKey_5();
	bool GetKey_6();
	bool GetKey_7();
	bool GetKey_8();
	bool GetKey_9();

	// WASD
	// GET
	bool GetKeyW();
	bool GetKeyA();
	bool GetKeyS();
	bool GetKeyD();

	bool GetKeyR();
	bool GetKeyH();

	// Set
	void SetKeyW(bool isEnabled);
	void SetKeyA(bool isEnabled);
	void SetKeyS(bool isEnabled);
	void SetKeyD(bool isEnabled);

	void SetKeyR(bool isEnabled);
	void SetKeyH(bool isEnabled);

	// Arrows up, down, left, right
	// Get
	bool GetKeyArrowUP();
	bool GetKeyArrowDown();
	bool GetKeyArrowLeft();
	bool GetKeyArrowRight();

	// Set
	void SetArrowUP(bool isEnabled);
	void SetArrowDown(bool isEnabled);
	void SetArrowLeft(bool isEnabled);
	void SetArrowRight(bool isEnabled);
};



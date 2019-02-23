#include "Keyboard.h"

namespace Keyboard {
	namespace PV { // Private Variables - Don't change, don't acces dirrectly, use funtions
		bool key_w = false;
		bool key_a = false;
		bool key_s = false;
		bool key_d = false;

		bool key_r = false;
		bool key_h = false;

		bool arrow_up = false;
		bool arrow_down = false;
		bool arrow_left = false;
		bool arrow_right = false;

		bool key_0 = false;
		bool key_1 = false;
		bool key_2 = false;
		bool key_3 = false;
		bool key_4 = false;
		bool key_5 = false;
		bool key_6 = false;
		bool key_7 = false;
		bool key_8 = false;
		bool key_9 = false;
	}

	void SetKey_0(bool isEnabled)
	{
		PV::key_0 = isEnabled;
	}
	void SetKey_1(bool isEnabled)
	{
		PV::key_1 = isEnabled;
	}
	void SetKey_2(bool isEnabled)
	{
		PV::key_2 = isEnabled;
	}
	void SetKey_3(bool isEnabled)
	{
		PV::key_3 = isEnabled;
	}
	void SetKey_4(bool isEnabled)
	{
		PV::key_4 = isEnabled;
	}
	void SetKey_5(bool isEnabled)
	{
		PV::key_5 = isEnabled;
	}
	void SetKey_6(bool isEnabled)
	{
		PV::key_6 = isEnabled;
	}
	void SetKey_7(bool isEnabled)
	{
		PV::key_7 = isEnabled;
	}
	void SetKey_8(bool isEnabled)
	{
		PV::key_8 = isEnabled;
	}
	void SetKey_9(bool isEnabled)
	{
		PV::key_9 = isEnabled;
	}

	bool GetKey_0()
	{
		return PV::key_0;
	}
	bool GetKey_1()
	{
		return PV::key_1;
	}
	bool GetKey_2()
	{
		return PV::key_2;
	}
	bool GetKey_3()
	{
		return PV::key_3;
	}
	bool GetKey_4()
	{
		return PV::key_4;
	}
	bool GetKey_5()
	{
		return PV::key_5;
	}
	bool GetKey_6()
	{
		return PV::key_6;
	}
	bool GetKey_7()
	{
		return PV::key_7;
	}
	bool GetKey_8()
	{
		return PV::key_8;
	}
	bool GetKey_9()
	{
		return PV::key_9;
	}




	// Get
	bool GetKeyW()
	{
		return PV::key_w;
	}
	bool GetKeyA()
	{
		return PV::key_a;
	}
	bool GetKeyS()
	{
		return PV::key_s;
	}
	bool GetKeyD()
	{
		return PV::key_d;
	}

	bool GetKeyR()
	{
		return PV::key_r;
	}

	bool GetKeyH()
	{
		return PV::key_h;
	}

	bool GetKeyArrowUP()
	{
		return PV::arrow_up;
	}
	bool GetKeyArrowDown()
	{
		return PV::arrow_down;
	}
	bool GetKeyArrowLeft()
	{
		return PV::arrow_left;
	}
	bool GetKeyArrowRight()
	{
		return PV::arrow_right;
	}


	// Set
	void SetKeyW(bool isEnabled)
	{
		PV::key_w = isEnabled;
	}
	void SetKeyA(bool isEnabled)
	{
		PV::key_a = isEnabled;
	}
	void SetKeyS(bool isEnabled)
	{
		PV::key_s = isEnabled;
	}
	void SetKeyD(bool isEnabled)
	{
		PV::key_d = isEnabled;
	}

	void SetKeyR(bool isEnabled)
	{
		PV::key_r = isEnabled;
	}

	void SetKeyH(bool isEnabled)
	{
		PV::key_h = isEnabled;
	}

	void SetArrowUP(bool isEnabled)
	{
		PV::arrow_up = isEnabled;
	}
	void SetArrowDown(bool isEnabled)
	{
		PV::arrow_down = isEnabled;
	}
	void SetArrowLeft(bool isEnabled)
	{
		PV::arrow_left = isEnabled;
	}
	void SetArrowRight(bool isEnabled)
	{
		PV::arrow_right = isEnabled;
	}
}
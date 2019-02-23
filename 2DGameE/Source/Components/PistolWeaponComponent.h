#pragma once
#include "WeaponComponent.h"

class PistolWeaponComponent : public WeaponComponent
{
public:
	PistolWeaponComponent() 
	{
		automaticWeapon = false;
		magazineMaxCount = 10;
		totalAmmoCount = 50;
	}
	~PistolWeaponComponent() {}

};
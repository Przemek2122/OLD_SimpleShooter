#pragma once
#include "WeaponComponent.h"


class RifleWeaponComponent : public WeaponComponent 
{
public:
	RifleWeaponComponent()
	{
		automaticWeapon = true;
		fireRate = 10;
		magazineMaxCount = 31;
		totalAmmoCount = 155;
		recoilAngle = 8;
		reloadTimeMS = 900;
		bulletID = "bullet2";
		bulletPath = "assets/weapons/bullet2.png";
	}
	~RifleWeaponComponent() {}

};
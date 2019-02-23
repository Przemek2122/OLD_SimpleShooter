#pragma once
#include "ECS.h"
#include "../Vector2D.h"
#include "SDL.h"


class PlayerComponent;
class TransformComponent;
class TextWidget;
class Sound;

class WeaponComponent : public Component {
public:
	PlayerComponent * player;
	Manager BulletsManager;

	/* Activates weapon. Call when weapon is used.
	 * Enables update, ammo text, show cursor etc.. */
	virtual void activate();

	/* Dectivates weapon. Call when weapon isn't used anymore.
	 * Disables update ammo text, hide cursor etc.. */
	virtual void deActivate();

	/* Returns true when weapon is activated 
	 * or false when weapon is deactivated. */
	virtual bool isActive();

	virtual void init() override;
	virtual void postInit() override;
	virtual void update() override;
	virtual void render() override;

	/* Call to shoot projectile.
	 * This function will check if there is ammo, 
	 * last shoot was long enough and if it's not reloading */
	void shoot();

	/* Call to reload weapon.
	 * This function will check if	magazine isn't already full and if player have ammo. */
	void reload();

protected:
	/* Weapon update handler.  */
	virtual void handleUpdate();

	/* Creates projectile. Called by shoot(). */
	virtual void createProjectile();

	/* Adds bullet to magazine,
	 * remove from total count etc.. */
	virtual void finishReload();

	/* True if magazine isn't empty. */
	inline bool outOfAmmo();

	/* Check if last shoot was long enough. */
	inline bool canShoot();

	/* True if magazine is full. */
	inline bool isMagazineFull();

	/* Check if weapon have ammo. */
	inline bool haveAmmo();

	/* Updates text with ammunition */ 
	void updateAmmoText();



	bool weaponActive = false;

	bool automaticWeapon = false;
	bool aLastShootButtonReleased = true;

	Vector2D<> position;
	SDL_Color color = { 0, 0, 0, 0 };
	int length = 28;
	int weight = 3;
	const char * bulletPath = "assets/weapons/default_bullet.png";
	const char * bulletID = "bullet";

	int magazineAmmoCount;
	int magazineMaxCount = 12;
	int totalAmmoCount = 60;
	int fireRate = 6;
	long int fireDelay;
	long long int lastShoot;
	long int reloadTimeMS = 600;
	long long int reloadStartMS;
	bool reloading = false;
	int recoilAngle = 4;

	int bulletRange = 300;
	int bulletSpeed = 400;
	int bulletDamage = 33;
	SDL_Rect bulletRect = { 0, 0, 8, 8 };
	SDL_Color ammoInfoColor = { 0, 0, 0, 255 };

	TextWidget * textInfo;
	TransformComponent * transform;

	std::string weaponSoundID = "bareta";
	const char * weaponSoundPath = "assets/sounds/Beretta_92FS.wav";

	Sound * shootSound;

};
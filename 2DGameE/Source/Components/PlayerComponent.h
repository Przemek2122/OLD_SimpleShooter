#pragma once
#include "ECS.h"
#include <assert.h>
#include <array>
#include "../Keyboard.h"
#include "../UI/UI.h"
#include "../UI/TextWidget.h"
#include "../game.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "SimplePhysicsComponent.h"
#include "RectColliderComponent.h"
#include "WeaponComponent.h"
#include "PistolWeaponComponent.h"
#include "RifleWeaponComponent.h"
#include "ShotgunWeaponComponent.h"


class PlayerComponent : public Component {
public:
	float Speed = 7.0f;
	int currentWeaponID = 0;
	long long int lastSwitchWeapon;
	long int switchWeaponMS = 700;
	bool showRecoil = false;

	void init() override
	{
		lastSwitchWeapon = Util::GetMiliseconds();

		entity->EnsureComponent<TransformComponent>();

		entity->EnsureComponent<RenderComponent>().LoadTexture("assets/characters/head_player.png");

		physics = &entity->EnsureComponent<SimplePhysicsComponent>();

		entity->EnsureComponent<RectColliderComponent>("Player");

		// Add first weapon
		weapons[1] = &entity->addComponent<PistolWeaponComponent>();
		weapons[1]->player = this;
		// Add second weapon
		weapons[2] = &entity->addComponent<RifleWeaponComponent>();
		weapons[2]->player = this;
		// Add third weapon
		weapons[3] = &entity->addComponent<ShotgunWeaponComponent>();
		weapons[3]->player = this;
	}

	void postInit() override
	{
		SDL_Color color = { 0, 0, 0, 100 };

		// Create text with bullets info
		entity->getManager().game->UiManager->addWidget<TextWidget>
			("bullets", UIUtil::getScreenPercentW(2), UIUtil::getScreenPercentH(94), "0", "OpenSans_16", color).disable();
			
		physics->setMovementDamping(1.8);
	}

	void update() override
	{
		// Weapon switch
		if (Keyboard::GetKey_0()) {}
		if (Keyboard::GetKey_1() && Util::isDelayed(lastSwitchWeapon, switchWeaponMS)) 
		{ 
			deactivateWeapon();
			Util::startDelay(lastSwitchWeapon);

			if (currentWeaponID == 1)
			{
				currentWeaponID = 0;
				return;
			}

			currentWeaponID = 1;
			activateWeapon();
		}
		if (Keyboard::GetKey_2() && Util::isDelayed(lastSwitchWeapon, switchWeaponMS))
		{
			deactivateWeapon();
			Util::startDelay(lastSwitchWeapon);

			if (currentWeaponID == 2)
			{
				currentWeaponID = 0;
				return;
			}

			currentWeaponID = 2;
			activateWeapon();
		}
		if (Keyboard::GetKey_3() && Util::isDelayed(lastSwitchWeapon, switchWeaponMS))
		{
			deactivateWeapon();
			Util::startDelay(lastSwitchWeapon);

			if (currentWeaponID == 3)
			{
				currentWeaponID = 0;
				return;
			}

			currentWeaponID = 3;
			activateWeapon();
		}

		// Handle shooting
		if (currentWeaponID != 0)
		{
			if (Mouse::GetLMB())
			{
				weapons[currentWeaponID]->shoot();
			}
			else if (Keyboard::GetKeyR())
			{
				weapons[currentWeaponID]->reload();
			}
		}

		showRecoil = Keyboard::GetKeyH();

		// Just a variable
		Vector2D<> newAcceleration(0, 0);
		
		// Movement
		if (Keyboard::GetKeyArrowDown() || Keyboard::GetKeyS()) { newAcceleration.Y += Speed; }
		if (Keyboard::GetKeyArrowUP() || Keyboard::GetKeyW()) { newAcceleration.Y -= Speed; }
		if (Keyboard::GetKeyArrowRight() || Keyboard::GetKeyD()) { newAcceleration.X += Speed; }
		if (Keyboard::GetKeyArrowLeft() || Keyboard::GetKeyA()) { newAcceleration.X -= Speed; }

		// Add movement
		physics->addMovementAcceleration(newAcceleration);
	}

	inline void deactivateWeapon()
	{
		if (currentWeaponID > 0)
			weapons[currentWeaponID]->deActivate();
	}

	inline void activateWeapon()
	{
		weapons[currentWeaponID]->activate();
	}

protected:
	SimplePhysicsComponent * physics;
	std::array<WeaponComponent*, 10> weapons;


};
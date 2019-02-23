#pragma once
#include "../EngineMath.h"
#include "../Mouse.h"
#include "../AudioManager.h"
#include "../game.h"
#include "WeaponComponent.h"
#include "PlayerComponent.h"
#include "ProjectileComponent.h"
#include "RenderComponent.h"
#include "CameraManager.h"

class ShotgunWeaponComponent : public WeaponComponent
{
public:
	ShotgunWeaponComponent()
	{
		automaticWeapon = true;
		fireRate = 2;
		magazineMaxCount = 7;
		totalAmmoCount = 42;
		recoilAngle = 8;
		reloadTimeMS = 1000;
	}
	~ShotgunWeaponComponent() {}

	inline void createProjectile() override
	{
		// Player rotation
		Vector2D<> tempPos = transform->Location;
		Vector2D<> camPos = entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();
		double rad = EMath::Get2DAngleOfPointRadians(tempPos + camPos, Vector2D<>(Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY())) + M_PI;

		for (int i = 0; i < singleShootBulletsCount; i++)
		{
			double radm = rad + EMath::DegreesToRadians(EMath::RandomFloat(recoilAngle, -recoilAngle));

			// Create bullet
			auto& Bullet(BulletsManager.addEntity());
			TransformComponent * bulletTransform = &Bullet.addComponent<TransformComponent>
				(bulletRect.h, bulletRect.w, bulletRect.x, bulletRect.y, 
					Vector2D<>(transform->Location.X + (transform->Rect.w / 2), transform->Location.Y + (transform->Rect.h / 2)));
			bulletTransform->postInit();
			ProjectileComponent * bullet = &Bullet.addComponent<ProjectileComponent>();
			bullet->init();
			bullet->SetProjectile(radm, bulletRange, bulletSpeed);
			RenderComponent * bulletRenderComp = &Bullet.addComponent<RenderComponent>();
			bulletRenderComp->init();
			bulletRenderComp->UseTexture(bulletID);

			// Play sound
			shootSound->playSound(true);
		}

		// remove one bullet
		magazineAmmoCount--;

		// Update ammount of bullets info on screen
		updateAmmoText();
	}

private:
	int singleShootBulletsCount = 6;

};
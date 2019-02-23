#pragma once
#include "WeaponComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "ProjectileComponent.h"
#include "CameraManager.h"
#include "RenderComponent.h"
#include "../CustomShapes.h"
#include "../Mouse.h"
#include "../Keyboard.h"
#include "../EngineMath.h"
#include "../AssetsManager.h"
#include "../UI/UI.h"
#include "../UI/TextWidget.h"
#include "../AudioManager.h"
#include "../game.h"


void WeaponComponent::activate()
{
	weaponActive = true;
	entity->getManager().game->UiManager->getWidget<TextWidget>("bullets").enable();
	SDL_ShowCursor(false);
	updateAmmoText();
}
void WeaponComponent::deActivate()
{
	weaponActive = false;
	entity->getManager().game->UiManager->getWidget<TextWidget>("bullets").disable();
	SDL_ShowCursor(true);
}
bool WeaponComponent::isActive() { return weaponActive; }

void WeaponComponent::init()
{
	BulletsManager.init();

	BulletsManager.game = entity->getManager().game;

	transform = &entity->EnsureComponent<TransformComponent>();

	// Create bullet (texture)
	entity->getManager().game->assets->addTexture(bulletID, bulletPath);

	// Set default magazine
	magazineAmmoCount = magazineMaxCount;

	// Create sound
	shootSound = &entity->getManager().game->audioManager->addWidget<Sound>(weaponSoundID);
	shootSound->loadSound(weaponSoundPath);

	// Set delay for shooting
	Util::startDelay(lastShoot);
	fireDelay = 1000 / fireRate;
}

void WeaponComponent::postInit()
{
	// Create text with bullets info
	textInfo = &entity->getManager().game->UiManager->getWidget<TextWidget>("bullets");
}

void WeaponComponent::update()
{
	BulletsManager.update();
	BulletsManager.refresh(); // TBF

	if (weaponActive)
	{
		handleUpdate();
	}
}

void WeaponComponent::render()
{
	BulletsManager.render();

	if (weaponActive)
	{
		// Get player position
		position = transform->Location;
		Vector2D<> camPos = entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();

		// Draw line to crosshair
		SDL_SetRenderDrawColor(Game::renderer, 255, 50, 50, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Game::renderer, position.X + 16 + camPos.X, position.Y + 16 + camPos.Y, Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY());

		// Draw weapon
		SDL_SetRenderDrawColor(Game::renderer, color.r, color.g, color.g, color.a);
		Shapes::DrawLimitedLine(Game::renderer, position.X + 16 + camPos.X, position.Y + 16 + camPos.Y, Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY(), length);

		// Draw crosshair
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		Shapes::drawCircle(Game::renderer, Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY(), 10);
		Shapes::drawCircle(Game::renderer, Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY(), 9);

		if (player->showRecoil)
			Shapes::drawCircle(Game::renderer, Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY(), recoilAngle * 6);
	}
}

void WeaponComponent::handleUpdate()
{
	// Prevent automatic shooting when weapon is not auto
	if (!automaticWeapon && isActive())
		if (!aLastShootButtonReleased && !Mouse::GetLMB())
			aLastShootButtonReleased = true;

	if (reloading)
	{
		if (Util::isDelayed(reloadStartMS, reloadTimeMS))
		{
			if (haveAmmo())
			{
				finishReload();
			}

			reloading = false;
			updateAmmoText();
		}
	}
}

void WeaponComponent::shoot()
{
	if (!outOfAmmo() && canShoot() && !reloading)
	{
		// Prevent automatic shooting when weapon is not auto
		if (!automaticWeapon)
		{
			if (!aLastShootButtonReleased)
				return;

			aLastShootButtonReleased = false;
		}

		// Create bullet
		createProjectile();

		// Delay next shoot
		Util::startDelay(lastShoot);
	}
}

void WeaponComponent::reload()
{
	if (!isMagazineFull() && haveAmmo() && !reloading)
	{
		// Start reload delay
		Util::startDelay(reloadStartMS);

		reloading = true;
		updateAmmoText();
	}
}

void WeaponComponent::createProjectile()
{
	// Player rotation
	Vector2D<> tempPos = transform->Location;
	Vector2D<> camPos = entity->getManager().game->camera->getComponent<CameraManagerComponent>().getCameraPosition();
	double rad = EMath::Get2DAngleOfPointRadians(Vector2D<>(16, 16) + tempPos + camPos, Vector2D<>(Mouse::GetScreenMouseX(), Mouse::GetScreenMouseY()))
		+ M_PI + EMath::DegreesToRadians(EMath::RandomFloat(-recoilAngle, recoilAngle));

	// Create bullet
	auto& Bullet(BulletsManager.addEntity());
	Bullet.addComponent<TransformComponent>(bulletRect.h, bulletRect.w, bulletRect.x, bulletRect.y, 
		Vector2D<>(transform->Location.X + (transform->Rect.w / 2), transform->Location.Y + (transform->Rect.h / 2)));
	Bullet.addComponent<ProjectileComponent>().SetProjectile(rad, bulletRange, bulletSpeed);
	Bullet.addComponent<RenderComponent>().UseTexture(bulletID);

	// Play sound
	shootSound->playSound(true);

	// remove one bullet
	magazineAmmoCount--;

	// Update ammount of bullets info on screen
	updateAmmoText();
}

void WeaponComponent::finishReload()
{
	// Missing ammunition to full magazine
	int missingAmmo = magazineMaxCount - magazineAmmoCount;
	// if missing ammo count isn't bigger ammount then ammo left
	if (missingAmmo > totalAmmoCount)
		missingAmmo = totalAmmoCount;

	// then remove from ammo left and add to magazine
	totalAmmoCount -= missingAmmo;
	magazineAmmoCount += missingAmmo;
}


bool WeaponComponent::outOfAmmo()
{
	return magazineAmmoCount <= 0;
}

bool WeaponComponent::canShoot()
{
	return Util::isDelayed(lastShoot, fireDelay);
}

bool WeaponComponent::isMagazineFull()
{
	return magazineAmmoCount == magazineMaxCount;
}

bool WeaponComponent::haveAmmo()
{
	return totalAmmoCount > 0;
}

void WeaponComponent::updateAmmoText()
{
	std::string text = "";

	if (reloading)
		text = std::to_string(magazineAmmoCount) + "/" + std::to_string(totalAmmoCount) + " R";
	else
		text = std::to_string(magazineAmmoCount) + "/" + std::to_string(totalAmmoCount);

	textInfo->setText(text, "OpenSans_16");
}



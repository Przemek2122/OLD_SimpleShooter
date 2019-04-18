#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "../Util.h"


class Game;

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity * entity;

	unsigned int entityID;

	virtual void init() {}
	virtual void postInit() {}
	virtual void update() {}
	virtual void render() {}
	virtual ~Component() {}
};

class Entity
{
private:
	Manager & manager;
	bool pendingDelete = false;
	bool active = true;
	unsigned int entityID;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	/* Called after construct */
	void init()
	{
		for (auto& c : components) c->init();
	}
	//[[deprecated("Use init() instead")]]
	void postInit()
	{
		for (auto& c : components) c->postInit();
	}
	/* Called every frame. (Mostly for calculations.) */
	void update()
	{
		for (auto& c : components)
			if (active) c->update();
	}
	/* Called every fram.e (Drawing stuff.) */
	void render()
	{
		for (auto& c : components)
			if (active) c->render();
	}

	/* Call to mark entity as to be deleted. */
	void destroy()
	{
		pendingDelete = true;
		deactivate();
	}

	/* Check if entity is going to be destroyed. */
	bool isPendingDestroy() const { return pendingDelete; }
	void deactivate() { active = false; }
	void activate() { active = true; }

	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->entityID = components.size() - 1;

		c->init();
		return *c;
	}

	/* Returns component of chosen type. */
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	/* This will check if entity has component and add it if not. */
	template <typename T, typename... TArgs>
	T& EnsureComponent(TArgs&&... mArgs)
	{
		if (hasComponent<T>())
		{
			return getComponent<T>();
		}
		else
		{
			return addComponent<T>(mArgs...);
		}
	}

	void setEnitityID(unsigned int newID)
	{
		entityID = newID;
	}

	unsigned int getEntityID()
	{
		return entityID;
	}

	unsigned int getNumOfComponents()
	{
		return components.size();
	}

	Manager & getManager()
	{
		return manager;
	}
};

class Manager
{
private:
	bool firstRun = true;
	unsigned int numOfEntities = 0;

public:
	Game * game = nullptr;
	std::vector<std::unique_ptr<Entity>> entities;

	/* Called after creating */
	void init()
	{
		for (auto& e : entities)
			if (e != nullptr)
				e->init();
	}
	/* Called before first update() */
	[[deprecated("Use init() instead")]]
	void postInit()
	{
		for (auto& e : entities)
			if (e != nullptr)
				e->postInit();
	}	
	/* Called every frame */
	void update() 
	{
		if (firstRun) 
		{
			for (auto& e : entities)
				if (e != nullptr)
					e->postInit();
			firstRun = false;
		}

		for (auto& e : entities) 
			if (e != nullptr)
				e->update();
	}
	/* Called every frame */
	void render()
	{
		for (auto& e : entities) 
			if (e != nullptr)
				e->render();
	}

	void destroy(Entity & mEntity)
	{
		std::vector<std::unique_ptr<Entity>>::iterator ent =
			std::find_if(entities.begin(), entities.end(),
				[&](std::unique_ptr<Entity> & obj) { return obj->isPendingDestroy(); }
		);

		entities.erase(std::remove(entities.begin(), entities.end(), *ent));
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return mEntity->isPendingDestroy();
		}), std::end(entities));
	}

	Entity& addEntity()
	{
		Entity *e = new Entity(*this);

		numOfEntities++;
		e->setEnitityID(numOfEntities);

		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));

		return *e;
	}
};
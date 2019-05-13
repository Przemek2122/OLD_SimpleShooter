#pragma once
#include "../AssetsManager.h"
#include "../game.h"


class UIManager;

namespace UIUtil
{
	int getWindowWidth();
	int getWindowHeight();
	int getScreenPercentW(int p);
	int getScreenPercentH(int p);
};


class Widget {
public:
	UIManager * uiManager;

	virtual void init() {}/*
	virtual void postInit() {}*/
	virtual void update() {}
	virtual void render() {}

	virtual bool isUpdateEnabled() { return updateEnabled; }
	virtual bool isRenderEnabled() { return renderEnabled; }

	virtual void setUpdateEnabled(bool enabled) { updateEnabled = enabled; }
	virtual void setRenderEnabled(bool enabled) { renderEnabled = enabled; }

protected:
	bool updateEnabled = true;
	bool renderEnabled = true;

};


class UIManager{
public:
	Game * game = nullptr;

	UIManager(Game * mGame);
	~UIManager();

	void update();
	void render();

	bool isThereWidgetWithID(std::string id);

	template<typename T>
	T& getWidget(std::string id)
	{
		// Check if exists
		// @TODO

		return *static_cast<T*>(Widgets[id]);
	}

	template<typename T, typename ...TArgs>
	T& addWidget(std::string id, TArgs && ...mArgs)
	{
		// Check if not exists

		T* t(new T(std::forward<TArgs>(mArgs)...));

		Widgets.emplace(id, t);

		return *t;
	}

	//template<typename T, typename ...TArgs>
	//T& ensureWidget(std::string id, TArgs && ...mArgs)
	//{
	//	// Check if exists
	//	if (isThereWidgetWithID(id))
	//	{
	//		return *static_cast<T*>(Widgets[id]);
	//	}
	//	else
	//	{
	//		addWidget<T>(id, mArgs);
	//	}
	//}

	bool destroyWidget(std::string id)
	{
		// Check if exists (if needed)
		// TODO

		Widgets.erase(id);
	}

private:
	std::map<std::string, Widget*> Widgets;

};

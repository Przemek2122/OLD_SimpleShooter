#pragma once
#include "../AssetsManager.h"
#include "../game.h"


class UIManager;

namespace UIUtil {
	int getWindowWidth();
	int getWindowHeight();
	int getScreenPercentW(int p);
	int getScreenPercentH(int p);
};


class Widget {
public:
	UIManager * uiManager;

	virtual void init() {}
	virtual void postInit() {}
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

	template<typename Type>
	Type& getWidget(std::string id)
	{
		// Check if exists
		// TODO

		//if (Widgets[id] != nullptr)
		return *static_cast<Type*>(Widgets[id]);
	}

	template<typename Type, typename ...TArgs>
	Type& addWidget(std::string id, TArgs && ...mArgs)
	{
		// Check if not exists
		// TODO

		Type* t(new Type(std::forward<TArgs>(mArgs)...));

		Widgets.emplace(id, t);

		return *t;
	}

	bool destroyWidget(std::string id)
	{
		// Check if exists
		// TODO

		Widgets.erase(id);
	}

private:
	std::map<std::string, Widget*> Widgets;

};

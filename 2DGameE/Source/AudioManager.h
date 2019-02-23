#pragma once
#include <map>
#include "SDL_mixer.h"
#include "Util.h"

class Sound 
{
public:
	~Sound() { Mix_FreeMusic(sound); }

	virtual bool isPlaying() { return playing; }
	virtual bool loadSound(const char * file)
	{
		sound = Mix_LoadMUS(file);

		// Check if there isn't any error
		if (sound == NULL)
		{
			Util::Error("Can't play sound: " + (std::string)SDL_GetError());
			return false;
		}

		return true;
	}
	virtual bool playSound(bool force = false) 
	{
		// Check if there isn't any error
		if (sound == NULL)
		{
			Util::Error("Can't play sound: " + (std::string)SDL_GetError());
			Util::Error("Did you loaded sound?");
			return false;
		}

		// If there is no music playing 
		if (Mix_PlayingMusic() == 0 || force == true)
		{
			// Play the music 
			if (Mix_PlayMusic(sound, 1) == -1)
			{
				playing = true;
				return true;
			}

			playing = false;

			// False if other music is played
			return false;
		}

		return false;
	}
	virtual void pauseSound()
	{
		paused = true;
		Mix_PauseMusic();
	}

	virtual void resumeSound()
	{
		paused = false;
		Mix_ResumeMusic();
	}
	virtual void stopSound()
	{
		bool playing = false;
		Mix_HaltMusic();
	}

protected:
	bool playing = false;
	bool paused = false;

	Mix_Music *sound = NULL;

};

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void setVolme()
	{
		Mix_VolumeMusic(100);
	}

	template<typename Type>
	Type& getWidget(std::string id)
	{
		// Check if exists
		// TODO

		//if (Widgets[id] != nullptr)
		return *static_cast<Type*>(sounds[id]);
	}

	template<typename Type, typename ...TArgs>
	Type& addWidget(std::string id, TArgs && ...mArgs)
	{
		// Check if not exists
		// TODO

		Type* t(new Type(std::forward<TArgs>(mArgs)...));

		sounds.emplace(id, t);

		return *t;
	}

	bool destroyWidget(std::string id)
	{
		// Check if exists
		// TODO

		sounds.erase(id);
	}

private:
	std::map<std::string, Sound*> sounds;

};


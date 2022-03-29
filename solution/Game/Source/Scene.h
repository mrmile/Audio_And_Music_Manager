#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	int sceneTimer;

	SDL_Texture* img;
	SDL_Texture* img2;

	uint activationSound = 0;
	uint glassBreak = 0;
	uint steamValve = 0;

	uint ventWalk[21] = { 0 };
	int ventWalkSoundTimer = 0;
	int ventWalkSoundID = 0;

};

#endif // __SCENE_H__
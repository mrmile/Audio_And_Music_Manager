#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool start_enabled = false);

	// Destructor
	~ModulePlayer();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);
	

public:
	// Position of the player in the map
	iPoint position;

	Animation* currentAnimation = nullptr;

	Animation idleLeftAnim;
	Animation walkLeftAnim;
	Animation idleRightAnim;
	Animation walkRightAnim;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	int lookingPosition = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

};

#endif //!__MODULE_PLAYER_H__
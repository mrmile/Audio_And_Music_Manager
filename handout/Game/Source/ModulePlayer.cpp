#include "ModulePlayer.h"

#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "Render.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Window.h"
//#include "ModuleFonts.h"
#include "Log.h"


#include "Audio.h"
#include "Scene.h"

#include <stdio.h>
#include <time.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
using namespace std;

ModulePlayer::ModulePlayer(bool start_enabled) : Module()
{
	name.Create("player");

	idleLeftAnim.PushBack({ 90, 0, 70, 100 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.15f;

	idleRightAnim.PushBack({ 0, 0, 70, 100 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.15f;

	walkRightAnim.PushBack({ 0, 116, 70, 100 });
	walkRightAnim.PushBack({ 0, 415, 70, 100 });
	walkRightAnim.loop = true;
	walkRightAnim.speed = 0.15f;

	walkLeftAnim.PushBack({ 90, 116, 70, 100 });
	walkLeftAnim.PushBack({ 90, 415, 70, 100 });
	walkLeftAnim.loop = true;
	walkLeftAnim.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake()
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	texture = app->tex->Load("Assets/textures/player.png");

	currentAnimation = &idleLeftAnim;

	position.x = 475;
	position.y = 340;

	return ret;
}

bool ModulePlayer::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		position.y = position.y - 5;

		if (lookingPosition == 1)
		{
			if (currentAnimation != &walkLeftAnim)
			{
				walkLeftAnim.Reset();
				currentAnimation = &walkLeftAnim;
			}
		}
		if (lookingPosition == 2)
		{
			if (currentAnimation != &walkRightAnim)
			{
				walkRightAnim.Reset();
				currentAnimation = &walkRightAnim;
			}
		}
	}
		

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y = position.y + 5;

		if (lookingPosition == 1)
		{
			if (currentAnimation != &walkLeftAnim)
			{
				walkLeftAnim.Reset();
				currentAnimation = &walkLeftAnim;
			}
		}
		if (lookingPosition == 2)
		{
			if (currentAnimation != &walkRightAnim)
			{
				walkRightAnim.Reset();
				currentAnimation = &walkRightAnim;
			}
		}
	}
		

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		position.x = position.x - 5;
		lookingPosition = 1;

		if (currentAnimation != &walkLeftAnim)
		{
			walkLeftAnim.Reset();
			currentAnimation = &walkLeftAnim;
		}
	}
		

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		position.x = position.x + 5;
		lookingPosition = 2;

		if (currentAnimation != &walkRightAnim)
		{
			walkRightAnim.Reset();
			currentAnimation = &walkRightAnim;
		}
	}
	
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_IDLE
		&& app->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_IDLE)
	{
		if (lookingPosition == 1)
		{
			if (currentAnimation != &idleLeftAnim)
			{
				idleLeftAnim.Reset();
				currentAnimation = &idleLeftAnim;
			}
		}
		if (lookingPosition == 2)
		{
			if (currentAnimation != &idleRightAnim)
			{
				idleRightAnim.Reset();
				currentAnimation = &idleRightAnim;
			}
		}
	}
	
	currentAnimation->Update();

	return true;
}

bool ModulePlayer::PostUpdate()
{
	if (position.y <= 310)
	{
		app->render->DrawTexture(app->scene->img2, 540, 300);

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y, &rect);

		app->render->DrawTexture(app->scene->img, 540, 300);
	}
	else
	{
		app->render->DrawTexture(app->scene->img2, 540, 300);

		app->render->DrawTexture(app->scene->img, 540, 300);

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		app->render->DrawTexture(texture, position.x, position.y, &rect);
	}
	
	return true;
}

bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);
	
	return true;
}
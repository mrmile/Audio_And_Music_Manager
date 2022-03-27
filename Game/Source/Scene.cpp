#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "ModulePlayer.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	img = app->tex->Load("Assets/Textures/speakers.png");
	img2 = app->tex->Load("Assets/Textures/speakers_ground.png");

	glassBreak = app->audio->LoadFx("Assets/Audio/Fx/breaking_glass.wav");
	activationSound = app->audio->LoadFx("Assets/Audio/Fx/generator_activation.wav");
	steamValve = app->audio->LoadFx("Assets/Audio/Fx/steam_valve.wav");

	ventWalk[0] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_01.wav");
	ventWalk[1] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_02.wav");
	ventWalk[2] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_03.wav");
	ventWalk[3] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_04.wav");
	ventWalk[4] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_05.wav");
	ventWalk[5] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_06.wav");
	ventWalk[6] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_07.wav");
	ventWalk[7] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_08.wav");
	ventWalk[8] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_09.wav");
	ventWalk[9] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_10.wav");
	ventWalk[10] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_11.wav");
	ventWalk[11] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_12.wav");
	ventWalk[12] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_13.wav");
	ventWalk[13] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_14.wav");
	ventWalk[14] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_15.wav");
	ventWalk[15] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_16.wav");
	ventWalk[16] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_17.wav");
	ventWalk[17] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_18.wav");
	ventWalk[18] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_19.wav");
	ventWalk[19] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_20.wav");
	ventWalk[20] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_21.wav");
	ventWalk[21] = app->audio->LoadFx("Assets/Audio/Fx/MOV_HunterVentWalk_22.wav");

	sceneTimer = 0;
	ventWalkSoundID = 0;

	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	sceneTimer++;

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		//Todo 4.1: Use the new playFX function to play glassBreak sound effect spatially
		//(the speakers center coordinates are { 640, 360 })
		app->audio->PlayFx(glassBreak, { 640, 360 });
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		//Todo 4.2: Use the new playFX function to play steamValve sound effect spatially
		//(the speakers center coordinates are { 640, 360 })
		app->audio->PlayFx(steamValve, { 640, 360 });
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		//Todo 4.3: Use the new playFX function to play activationSound sound effect spatially
		//(the speakers center coordinates are { 640, 360 })
		app->audio->PlayFx(activationSound, { 640, 360 });
	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_REPEAT)
	{
		//Todo 4.4: Use the new playFX function to play the modular "ventWalk" sound effect
		//(the speakers center coordinates are { 640, 360 })
		//Note that modular sounds require extra logic in addition to the playFx function
		if (sceneTimer % 24 == 0)
		{
			app->audio->PlayFx(ventWalk[ventWalkSoundID], { 640, 360 });
			ventWalkSoundID++;

			if (ventWalkSoundID > 21) ventWalkSoundID = 0;
		}
	}


	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		// Todo 5.1: Use the ChangeMusic function to switch the music to OFF (feel free to experiment with fades)
		app->audio->ChangeMusic(OFF, 0.0f, 0.0f);
	}

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		// Todo 5.2: Use the ChangeMusic function to switch the music to EL_BOOM (feel free to experiment with fades)
		app->audio->ChangeMusic(EL_BOOM, 1.0f, 1.0f);
	}

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		// Todo 5.3: Use the ChangeMusic function to switch the music to PRENDE_UN_PORRO (feel free to experiment with fades)
		app->audio->ChangeMusic(PRENDE_UN_PORRO, 1.0f, 1.0f);
	}

	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		app->audio->playMusicSpatially = !app->audio->playMusicSpatially;
	}

	
	if (app->audio->playMusicSpatially == true)
	{
		// Todo 6: Use the PlayMusicSpatially function to play music spatially when switched on
		//(the speakers center coordinates are { 640, 360 })
		app->audio->PlayMusicSpatially({ 640, 360 });
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

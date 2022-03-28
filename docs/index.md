# Audio and music manager

An audio and music manager is a module in charge of loading, playing sounds effects and music tracks and switch between them. It should also be able to play them spatially.

The module should contain the playlist with all music tracks and methods (functions) to do all of the above. Even though you can play audio on a videogame by directly using the plain library or engine functions on the way, it is highly recomended to have an audio manager in order to have your code clean and ordered, avoid strange errors or unexpected bugs and behaviours, and simply make your life easier by having a set of functions that make all the management for you.

Note that all of the code below that you will see is written for this template. Your code may vary in order to accommodate your's.

## Music tracks switching

### Introduction
Switching between sound tracks is very common in videogames. Basically because you can see it, or in this case hear, in all of them.

To change to another music track, just introduce the music track you want to switch to and the fade out/in delays. The audio manager will do everything else.
```markdown
app->audio->ChangeMusic(MUSIC_TRACK_2, 1.0f, 2.0f);
```

### Code
In order to make the above function work you need 3 things:

- An enumerator with all the complete playlist
```markdown
enum Music
{
	OFF = 0,
	MUSIC_TRACK_1,
	MUSIC_TRACK_2,
};
```

- A function to play the actual music track
```markdown
bool Audio::PlayMusic(const char* path, float fadeInTime, float fadeOutTime)
{
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		if(fadeOutTime > 0.0f)
		{
			Mix_FadeOutMusic(int(fadeOutTime * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
			
		}
		
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fadeInTime > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fadeInTime * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}
```

- The actual function that switches between different the different music tracks
```markdown
bool Audio::ChangeMusic(int Id, float fadeInTime, float fadeOutTime)
{
	switch (Id)
	{
		case OFF:
		{
			Mix_HaltMusic();
			break;
		}
		case MUSIC_TRACK_1:
		{
			Mix_ResumeMusic();
			
			app->audio->PlayMusic("Assets/Audio/Music/MusicTrack1.ogg", fadeInTime, fadeOutTime);
			
			break;
		}
		case MUSIC_TRACK_2:
		{
			Mix_ResumeMusic();
			
			app->audio->PlayMusic("Assets/Audio/Music/MusicTrack2.ogg", fadeInTime, fadeOutTime);
			
			break;
		}
	}

	return true;
}
```

## Playing sound effects

### Introduction
In videogames we have 2 types of sound effects: The environment sound effects produced by enemies, player, scenario objects, etc... And the background sound effects produced by elements that are not on the actual scene. Sound effect when the pause menu pops up or when you select an option in the menu are examples of background sound effects.

Environment sound effects are played spatially and background sound effects are allways played at the same volume.

### Spatial sounds
Every sound can be played spatially. That means that it will be heared at a lower or higher volume depending on the distance between the sound listener and the sound source.

![example_image](https://user-images.githubusercontent.com/73582929/160496047-86251ad2-2cb6-4c98-a6d3-24a0971986f3.png)

Although this may sound tricky, it is actually very simple. The only thing you have to do is set the volume in function of the distance between the two points wich normally are the player (sound listener) and the sprite generating the sound (sound generator).

```markdown
setVolume = GAME_VOLUME - (sqrt(pow(app->player->position.x - soundGeneratorPosition.x, 2) + pow(app->player->position.y - soundGeneratorPosition.y, 2))
```

All of this can also be applied in the same way to play music tracks spatially.

### Playing simple sounds
To play them spatially the position from wich the sound is played is introduced on the soundGeneratorPosition variable and the volume will vary depending on where the player is.
```markdown
app->audio->PlayFx(sound1, { 640, 360 });
```
In order not to play the sound effect spatially introduce the position where the player is on the soundGeneratorPosition varialbe.
```markdown
app->audio->PlayFx(sound1, { app->player->position.x, app->player->position.y });
```
### Playing modular sounds (normally applied when you play them spatially)
When playing a sound, the volume is set once at the beggining, so it will not update later. However, you can divide the sound in different parts/files and play them separately so the volume changes at the beggining of each part.
```markdown
if (sceneTimer % 24 == 0)
{
	app->audio->PlayFx(modularSound2List[soundPartID], { 640, 360 });
	soundID++;
	
	if (soundID > arraySize) soundID = 0;
}
```

### Code
- In order to play sounds you just need the actual function to play them:
```markdown
bool Audio::PlayFx(unsigned int id, iPoint soundGeneratorPosition, int repeat)
{
	bool ret = false;

	if(!active)
		return false;

	int setChunkVolume = FX_VOLUME - (sqrt(pow(app->player->position.x - soundGeneratorPosition.x, 2) + pow(app->player->position.y - soundGeneratorPosition.y, 2)) / 6);

	if (setChunkVolume <= 0) setChunkVolume = 0;

	if(id > 0 && id <= fx.Count())
	{
		Mix_PlayChannel(-1, fx[id - 1], repeat);
		Mix_VolumeChunk(fx[id - 1], setChunkVolume);
	}

	return ret;
}
```

## Play music tracks spatially

### Introduction
There might be some cases where you may want to play a music track as part of the environment (spatially) and not as a backround ambience music in order to make it diegetic. In that case you need to set the coordinates from wich the music is generated.
```markdown
app->audio->PlayMusicSpatially({ 640, 360 });
```
### Code
To play the music spatially you just need the actual function:
```markdown
bool Audio::PlayMusicSpatially(iPoint musicGeneratorPosition)
{
	int setMusicVolume = MUSIC_VOLUME - (sqrt(pow(app->player->position.x - musicGeneratorPosition.x, 2) + pow(app->player->position.y - musicGeneratorPosition.y, 2)) / 6);
	
	if (setMusicVolume <= 0) setMusicVolume = 0;
	
	Mix_VolumeMusic(setMusicVolume);
	
	return true;
}
```

In case you want to combine spatial and background music you can play with logic to switch between the two states.

```markdown
if (app->audio->playMusicSpatially == true)
{
	app->audio->PlayMusicSpatially({ 640, 360 });
}

if(app->audio->playMusicSpatially == false) Mix_VolumeMusic(MUSIC_VOLUME);
```

## Citations
- [SDL_Mixer library](https://www.libsdl.org/projects/SDL_mixer/)
- [Code template used as a base for this Audio and music manager construction](https://github.com/raysan5/game_project_template)

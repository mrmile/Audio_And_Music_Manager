#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Module.h"
#include "Point.h"
#include "ModulePlayer.h"

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX_CHANNELS 56

#define FX_VOLUME 128 // 0-128
#define MUSIC_VOLUME 100 // 0-128

enum Music
{
	OFF = 0,
	EL_BOOM,
	PRENDE_UN_PORRO,
};

struct _Mix_Music;
struct Mix_Chunk;

class Audio : public Module
{
public:

	Audio();

	// Destructor
	virtual ~Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fadeInTime = DEFAULT_MUSIC_FADE_TIME, float fadeOutTime = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, iPoint soundGeneratorPosition, int repeat = 0);

	// Change Music track
	bool ChangeMusic(int Id, float fadeInTime = DEFAULT_MUSIC_FADE_TIME, float fadeOutTime= DEFAULT_MUSIC_FADE_TIME);

	// Play Music track spatially (diegetic)
	bool PlayMusicSpatially(iPoint musicGeneratorPosition);

private:

	_Mix_Music* music;
	List<Mix_Chunk *>	fx;

public:

	bool playMusicSpatially = false;
};

#endif // __AUDIO_H__
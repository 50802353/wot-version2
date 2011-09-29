#ifndef __SOUNDDRIVER_H__	//Begin __SOUNDDRIVER_H__
#define __SOUNDDRIVER_H__

#include "Header.h"

 //////////////////////////////////////
// Include Libraries
#if CONFIG_PLATFORM==PLATFORM_ANDROID	//Begin lib
	#include <stddef.h>
	#include <string.h>
	#include <al/al.h>
	#include <al/alc.h>
	#include <tremolo/ivorbisfile.h>
	#include <android/log.h>
	#include <jni.h>
	#include <assert.h>
	#include <string.h>
	#include <time.h>

#elif CONFIG_PLATFORM==PLATFORM_WIN32_VS
	#include <AL/al.h>
	#include <AL/alc.h>
	#include <AL/alut.h>
	#include <Windows.h>
	#include <Vorbis/vorbisfile.h>
	#pragma comment(lib, "alut.lib")
	#pragma comment(lib, "OpenAL32.lib")	
	#pragma comment(lib, "vorbisfile.lib")
#endif									//End lib

 ////////////////////////////////////////////
// Manage sound play in our game (WAV & OGG)
class GameSound{
private:
	ALfloat m_SourcePos[3];
	ALfloat m_SourceVel[3];
	ALfloat m_ListenerPos[3];
	ALfloat m_ListenerOri[6];
	ALboolean b_loop;
	ALboolean b_Relative;
	ALfloat volume;
	ALboolean b_SoundIsLoadedSuccessfull;

	//Handle Buffer data
	ALsizei numberBuff;
	ALuint *buffer;
	ALuint SourceID;		// Sources are points of emitting sound.

	 //////////////////////////////////////
	// Load WAV file to buffer
	void LoadSourceWav(const char* filePath);

	 //////////////////////////////////////
	// Load OGG file to buffer
	void LoadSourceOgg(const char* filePath);

public:	
	
	GameSound();

	         ////////////////////////////////////////////////////
	        // New sound with default info (Right-Hand Coord):
	       //	Pos = (0.0f, 0.0f, 0.0f)
	      //	Vel = (0.0f, 0.0f, 0.0f)
	     //		LisPos = (0.0f, 0.0f, 1.0f)
	    //		Lisori = (0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f)
	   //		isPlaying = 0
	  //		loop = false
	 //			Relative = true
	//			volume = 0.5
	GameSound(char *filePath);

	 //////////////////////////////////////////////////////////////
	// kill all data to free memory (not destroy sound device yet)
	~GameSound();

	 /////////////////////////////////////////////////////////////
	// Return Playing Status of this sound
	ALint GetPlayStatus();

	 //////////////////////////////////////
	// Update Position of sound
	void UpdateSourcePosition(ALfloat x, ALfloat y, ALfloat z);

	 //////////////////////////////////////
	// Get Position of sound
	ALfloat* GetSourcePosition();

	   ////////////////////////////////////////////
	  // Update Velocity of object make sound
	 //	(Cap nhat van toc cua vat phat ra am thanh)
	//	(Hieu ung Doppler)
	void UpdateSourceVelocity(ALfloat x, ALfloat y, ALfloat z);

	 ////////////////////////////////////////////
	// Get Velocity of object make sound	
	ALfloat* GetSourceVelocity();

	 //////////////////////////////////////
	// Update Listener Position
	void UpdateListenerPosition(ALfloat x, ALfloat y, ALfloat z);

	 //////////////////////////////////////
	// Get Listener Position
	ALfloat* GetListenerPosition();

	 //////////////////////////////////////
	//  Update Listener Orientation
	void UpdateListenerOrientation(	ALfloat x_target,	ALfloat y_target,	ALfloat z_target, 
									ALfloat x_up,		ALfloat y_up,		ALfloat z_up);

	//////////////////////////////////////
	//  Get Listener Orientation
	ALfloat* GetListenerOrientation();

	 //////////////////////////////////////
	// Make this sound loop or none
	void SetLoop(ALboolean alLoop);

	 //////////////////////////////////////
	// Get loop status of this sound
	ALboolean GetLoopStatus();

	  /////////////////////////////////////////////
	 // Relative SourcePos with ListenerPos 
	//  (I don't know clearly, advise to set true)
	void SetSourceRelative(ALboolean alRelative);

	 /////////////////////////////////////////////
	// Get Relative Status
	ALboolean GetRelativeStatus();

	 //////////////////////////////////////
	// Call play function
	void Play();

	 //////////////////////////////////////
	// Call play function with custom volume
	void Play(ALfloat _volume);

	 //////////////////////////////////////
	// Force a Sound play 
	void ForcePlay();

	 //////////////////////////////////////
	// Force a Sound play with custom volume
	void ForcePlay(ALfloat _volume);

	 //////////////////////////////////////
	// Call Pause function
	void Pause();

	 //////////////////////////////////////
	// Call Stop function
	void Stop();

	 ////////////////////////////////////////
	// Call volume function	from 0.0 -> 1.0
	void VolumeControl(ALfloat iVol);

	 //////////////////////////////////////
	// Get volume of this sound
	ALfloat GetVolume();
};

	typedef struct 
	{
		char  riff[4];//'RIFF'
		unsigned int riffSize;
		char  wave[4];//'WAVE'
		char  fmt[4];//'fmt '
		unsigned int fmtSize;
		unsigned short format;
		unsigned short channels;
		unsigned int samplesPerSec;
		unsigned int bytesPerSec;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char  data[4];//'data'
		unsigned int dataSize;
	} BasicWAVEHeader;

	char* ReadWAV(const char* filename, BasicWAVEHeader* header);

	ALuint CreateBufferFromWave(char* data,BasicWAVEHeader header);

static ALCcontext *Context;
static ALCdevice *Device;

 //////////////////////////////////////
// Use to check if Sound Device is opened
static bool b_DeviceIsOpened;

 //////////////////////////////////////
// Open Sound Device
bool OpenSoundDevice();

 //////////////////////////////////////
// Close Sound Device
void CloseSoundDevice();

 //////////////////////////////////////
// Decode OGGVorbis file to buffer
unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);

 //////////////////////////////////////
// Swap data
template <class T>
void Swap(T &s1, T &s2){
	short sTemp = s1;
	s1 = s2;
	s2 = sTemp;
}

 //////////////////////////////////////
// Read datasource to ptr buffer
size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource);

 //////////////////////////////////////
// Read datasource from offset
int ov_seek_func(void *datasource, ogg_int64_t offset, int whence);

 //////////////////////////////////////
// Close datasource file
int ov_close_func(void *datasource);

 //////////////////////////////////////
// Get current position in datasource
long ov_tell_func(void *datasource);

#endif									//End __SOUNDDRIVER_H__

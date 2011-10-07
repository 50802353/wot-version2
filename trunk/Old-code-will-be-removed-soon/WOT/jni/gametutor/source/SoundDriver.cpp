#include "SoundDriver.h"
#include <stdio.h>

GameSound::GameSound(){
}

GameSound::GameSound(char *filePath){
	if (!b_DeviceIsOpened)
		OpenSoundDevice();

	FILE *file = fopen(filePath, "rb");
	if(file==NULL) {
		b_SoundIsLoadedSuccessfull = false;
		LogError ("Sound: File %s not found", filePath);
		return;
	}

	//create 1 source
	alGenSources(1, &SourceID);

	char type[4];
	//struct TYPEFILE header;
	fread(type,sizeof(char)*4,1,file);

	if(!memcmp("RIFF",type,4))
	{
		numberBuff = 1;
		Log ("Sound: Load sound in WAV");
		LoadSourceWav(filePath);
	}
	else if(!memcmp("OggS",type,4))
	{
		numberBuff = 256;
		Log ("Sound: Load sound in OGG");
		LoadSourceOgg(filePath);
	}

	 /////////////////////////////////
	//	Default value for new sound
	b_loop = false;
	b_Relative = true;
	for (int i=0; i< 3; i++)
	{
		m_SourcePos[i] = 0.0f;
		m_SourceVel[i] = 0.0f;
		m_ListenerPos[i] = 0.0f;
		m_ListenerOri[i] = 0.0f;
		m_ListenerOri[i*2] = 0.0f;
	}
	volume = 0.5f;
	
	alSourcefv(SourceID, AL_POSITION,	m_SourcePos	);		//Source Pos
	alSourcefv(SourceID, AL_VELOCITY,	m_SourceVel	);		//Source Vel
	alSourcef (SourceID, AL_PITCH,		1.0			);
	alSourcef (SourceID, AL_GAIN,		volume		);		//Set Volume
	alSourcei (SourceID, AL_LOOPING,	b_loop		);		//Set loop
	alSourcei (SourceID, AL_SOURCE_RELATIVE, b_Relative);	//Set relative

	alListenerfv(AL_POSITION, m_ListenerPos);			//Listener Pos
	alListenerfv(AL_ORIENTATION, m_ListenerOri);		//Listener Ori

	b_SoundIsLoadedSuccessfull = true;

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Constructor");
	}
}

GameSound::~GameSound(){
	if (this == NULL) return;
	if (b_SoundIsLoadedSuccessfull){
		ALint state;
		alGetSourcei(this->SourceID, AL_SOURCE_STATE, &state);
		if (state!= AL_STOPPED)						//not playing
			alSourceStop(SourceID);
		
		alDeleteSources(1, &SourceID);
		alDeleteBuffers(numberBuff, buffer);
		Log("Sound: Delete Sound");
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at De-Constructor");
	}
}

ALint GameSound::GetPlayStatus(){
	if (this == NULL) return AL_STOPPED;

	if (b_SoundIsLoadedSuccessfull){
		ALint state;
		alGetSourcei(this->SourceID, AL_SOURCE_STATE, &state);
		return state;
	}
}

void GameSound::UpdateSourcePosition(ALfloat x, ALfloat y, ALfloat z){
	if (this == NULL) return;

	m_SourcePos[0] = x;
	m_SourcePos[1] = y;
	m_SourcePos[2] = z;

	alSourcefv(SourceID, AL_POSITION,	m_SourcePos);		//Source Pos

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at UpdateSourcePos");
	}
}

void GameSound::UpdateSourceVelocity(ALfloat x, ALfloat y, ALfloat z){
	if (this == NULL) return;

	m_SourceVel[0] = x;
	m_SourceVel[1] = y;
	m_SourceVel[2] = z;

	alSourcefv(SourceID, AL_VELOCITY,	m_SourceVel);		//Source Vel

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at UpdateSourceVel");
	}
}

void GameSound::UpdateListenerPosition(ALfloat x, ALfloat y, ALfloat z){
	if (this == NULL) return;

	m_ListenerPos[0] = x;
	m_ListenerPos[1] = y;
	m_ListenerPos[2] = z;

	alListenerfv(AL_POSITION, m_ListenerPos);			//Listener Pos
	
	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Update Listener Pos");
	}
}

void GameSound::UpdateListenerOrientation(	ALfloat x_target,	ALfloat y_target,	ALfloat z_target, 
											ALfloat x_up,		ALfloat y_up,		ALfloat z_up)
{
	if (this == NULL) return;

	m_ListenerOri[0] = x_target;
	m_ListenerOri[1] = y_target;
	m_ListenerOri[2] = z_target;
	m_ListenerOri[3] = x_up;
	m_ListenerOri[4] = y_up;
	m_ListenerOri[5] = z_up;

	alListenerfv(AL_ORIENTATION, m_ListenerOri);		//Listener Ori


	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Update Listener Ori");
	}
}

void GameSound::SetLoop(ALboolean alLoop){
	if (this == NULL) return;

	b_loop = alLoop;

	alSourcei (SourceID, AL_LOOPING,		b_loop);				//Set loop

	////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Setloop");
	}
}

void GameSound::SetSourceRelative(ALboolean alRelative){
	if (this == NULL) return;

	b_Relative = alRelative;

	alSourcei (SourceID, AL_SOURCE_RELATIVE, b_Relative);	//Set relative

	////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Set Relative");
	}
}

void GameSound::VolumeControl(ALfloat fVol){
	if (this == NULL) return;
	volume = fVol;
	alSourcef(SourceID, AL_GAIN, volume);
}

void GameSound::Play(ALfloat _volume){
	if (this == NULL) return;

	if (b_SoundIsLoadedSuccessfull){
		this->VolumeControl(_volume);
		alSourcef(SourceID, AL_GAIN, _volume);
		if (GetPlayStatus() != AL_PLAYING)	{					//not playing
			alSourcePlay(this->SourceID);
			Log ("Sound: Play");
		}
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Play Func");
	}
}

void GameSound::Play(){
	if (this == NULL) return;

	if (b_SoundIsLoadedSuccessfull){
		alSourcef(SourceID, AL_GAIN, volume);
		if (GetPlayStatus() != AL_PLAYING)	{					//not playing
			alSourcePlay(this->SourceID);
			Log ("Sound: Play");
		}
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Play Func");
	}
}

void GameSound::ForcePlay(){
	if (this == NULL) return;	

	if (b_SoundIsLoadedSuccessfull){
		alSourcePlay(this->SourceID);
		Log ("Sound: Force Play");
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Force Play Func");
	}
}

void GameSound::ForcePlay(ALfloat _volume){
	if (this == NULL) return;	

	if (b_SoundIsLoadedSuccessfull){
		this->VolumeControl(_volume);
		alSourcePlay(this->SourceID);
		Log ("Sound: Force Play");
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Force Play Func");
	}
}

void GameSound::Pause(){
	if (this == NULL) return;	

	if (b_SoundIsLoadedSuccessfull){
		if (GetPlayStatus() != AL_PAUSED){					//is not pause
			alSourcePause(this->SourceID);
			Log ("Sound: Pause");
		}
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Pause Func");
	}
}

void GameSound::Stop(){
	if (this == NULL) return;

	if (b_SoundIsLoadedSuccessfull){
		if (GetPlayStatus() != AL_STOPPED)	{				//is not stop
			alSourceStop(this->SourceID);
			Log("Sound: Stop");
		}
	}

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Stop Func");
	}
}

ALfloat * GameSound::GetSourcePosition(){
	if (this == NULL) return false;

	return this->m_SourcePos;
}

ALfloat* GameSound::GetSourceVelocity(){
	if (this == NULL) return false;

	return this->m_SourceVel;
}

ALfloat* GameSound::GetListenerPosition(){
	if (this == NULL) return false;

	return this->m_ListenerPos;
}

ALfloat* GameSound::GetListenerOrientation(){
	if (this == NULL) return false;

	return this->m_ListenerOri;
}

ALboolean GameSound::GetLoopStatus(){
	if (this == NULL) return false;

	return this->b_loop;
}

ALboolean GameSound::GetRelativeStatus(){
	if (this == NULL) return false;

	return this->b_Relative;
}

ALfloat GameSound::GetVolume(){
	if (this == NULL) return 0;

	return this->volume;
}

char* ReadWAV(const char* filename, BasicWAVEHeader* header)
{
	char* buffer = 0;
	FILE* file = fopen(filename,"rb");

	if (!file) 
	{
		LogError ("Sound: Fail to open: %s", filename);
		return 0;
	}

	if (fread(header,sizeof(BasicWAVEHeader),1,file))
	{
		if (!(	//these things *must* be valid with this basic header
			memcmp("RIFF",header->riff,4) ||		//memcmp return 0 if their values is equal
			memcmp("WAVE",header->wave,4) ||
			memcmp("fmt ",header->fmt,4)  ||
			memcmp("data",header->data,4)
			))
		{
			buffer = (char*)malloc(header->dataSize) ;
			if (buffer)
			{
				if (fread(buffer,header->dataSize,1,file))
				{
					fclose(file);
					return buffer;
				}
				free(buffer);
			}
		}
	}
	fclose(file);
	Log ("Sound: End read WAV");
	return 0;
}

ALuint CreateBufferFromWave(char* data,BasicWAVEHeader header)
{
	ALuint buffer = 0;
	ALuint format = 0;
	switch (header.bitsPerSample)
	{
	case 8:
		format = (header.channels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
		break;
	case 16:
		format = (header.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		break;
	default:
		return 0;
	}
	alGenBuffers(1,&buffer);
	alBufferData(buffer,format,data,header.dataSize,header.samplesPerSec);
	return buffer;
}

bool OpenSoundDevice()
{
	if (b_DeviceIsOpened) return true;

	#if CONFIG_PLATFORM==PLATFORM_ANDROID
		const ALint context_attribs[] = { ALC_FREQUENCY, 22050, 0 };
	#endif

	// Initialization
	Device = alcOpenDevice(0);
	if (Device == NULL){
		LogError("Sound: Sound Device not found");
		return false;
	}

	//Create context(s)
	#if CONFIG_PLATFORM==PLATFORM_ANDROID
			Context = alcCreateContext(Device, context_attribs);
	#elif CONFIG_PLATFORM==PLATFORM_WIN32_VS	
			Context=alcCreateContext(Device, NULL);
	#endif

	//Set active context
	alcMakeContextCurrent(Context);
	// Clear Error Code
	alGetError();

	b_DeviceIsOpened = true;

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Open Device");
	}
	else {
		Log ("Sound: Finished Open Sound device");
	}
	return true;
}

void CloseSoundDevice(){
	if (!b_DeviceIsOpened) return;

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Close Device");
	}
	else {
		Log ("Sound: Close Sound device");
	}

	Context=alcGetCurrentContext();
	//Get device for active context
	Device=alcGetContextsDevice(Context);
	//Disable context
	alcMakeContextCurrent(NULL);
	//Release context(s)
	alcDestroyContext(Context);
	//Close device
	alcCloseDevice(Device);
	b_DeviceIsOpened = false;

	return;
}

unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels)
{
	int current_section;
	long lDecodeSize;
	unsigned long ulSamples;
	short *pSamples;

	unsigned long ulBytesDone = 0;
	while (1)
	{
	#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)
			lDecodeSize = ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
	#elif (CONFIG_PLATFORM==PLATFORM_ANDROID)
			lDecodeSize = ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0);//, 2, 1, &current_section);
	#endif
		if (lDecodeSize > 0)
		{
			ulBytesDone += lDecodeSize;
			if (ulBytesDone >= ulBufferSize)
				break;
		}
		else
		{
			break;
		}
	}

	// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
	// however 6-Channels files need to be re-ordered
	if (ulChannels == 6)
	{		
		pSamples = (short*)pDecodeBuffer;
		for (ulSamples = 0; ulSamples < (ulBufferSize>>1); ulSamples+=6)
		{
			// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
			// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
			Swap(pSamples[ulSamples+1], pSamples[ulSamples+2]);
			Swap(pSamples[ulSamples+3], pSamples[ulSamples+5]);
			Swap(pSamples[ulSamples+4], pSamples[ulSamples+5]);
		}
	}
	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at DecodeOGG");
	}

	return ulBytesDone;
}

size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	return fread(ptr, size, nmemb, (FILE*)datasource);
}

int ov_seek_func(void *datasource, ogg_int64_t offset, int whence)
{
	return fseek((FILE*)datasource, (long)offset, whence);
}

int ov_close_func(void *datasource)
{
	return fclose((FILE*)datasource);
}

long ov_tell_func(void *datasource)
{
	return ftell((FILE*)datasource);
}

void GameSound::LoadSourceWav(const char* filePath){
	if (this == NULL) return;

	buffer = new ALuint;
	//alGetError();		//Clear error		//Why error here?!!!

	BasicWAVEHeader header;
	char* data = ReadWAV(filePath,&header);
	
	if (data)
	{
		//Now We've Got A Wave In Memory, Time To Turn It Into A Usable Buffer
		*(buffer) = CreateBufferFromWave(data,header);
		delete data;
	} 
	else 
	{	
		LogError ("Sound: Can not read file %s", filePath);
		alDeleteBuffers(numberBuff,buffer);
		*(buffer) = 0;
		SourceID = 0;
		return;
	}

	if(!*buffer)
	{
		LogError ("Sound: Can not create Buffer");
		alDeleteBuffers(numberBuff, buffer);
		*buffer = 0;
		SourceID = 0;
		return;
	}

	//assign the buffer to this source
	alSourcei(SourceID, AL_BUFFER, *buffer);

	 ////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at Load WAV");
	}
	else {
		Log ("Finished load WAV");
	}
}

void GameSound::LoadSourceOgg(const char* filePath){	
	if (this == NULL) return;

	buffer			= new ALuint[numberBuff];
	unsigned long	ulFrequency = 0;
	unsigned long	ulFormat = 0;
	unsigned long	ulChannels = 0;
	unsigned long	ulBufferSize;
	unsigned long	ulBytesWritten;
	char			*pDecodeBuffer;

	// Open Ogg Stream
	ov_callbacks	sCallbacks;
	OggVorbis_File	*sOggVorbisFile = new OggVorbis_File;
	vorbis_info		*psVorbisInfo;

	sCallbacks.read_func = ov_read_func;
	sCallbacks.seek_func = ov_seek_func;
	sCallbacks.close_func = ov_close_func;
	sCallbacks.tell_func = ov_tell_func;

	// Open the OggVorbis file
	FILE *pOggVorbisFile = fopen(filePath, "rb");
	if (!pOggVorbisFile)
	{
		LogError ("Sound: Wrong format");
		return;
	}

	// Create an OggVorbis file stream
	if (ov_open_callbacks(pOggVorbisFile, sOggVorbisFile, NULL, 0, sCallbacks) == 0)
	{
		// Get some information about the file (Channels, Format, and Frequency)
		psVorbisInfo = ov_info(sOggVorbisFile, -1);

		if (psVorbisInfo)
		{
			ulFrequency = psVorbisInfo->rate;
			ulChannels = psVorbisInfo->channels;
			if (psVorbisInfo->channels == 1)
			{
				ulFormat = AL_FORMAT_MONO16;
				// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
				ulBufferSize = ulFrequency >> 1;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				ulBufferSize -= (ulBufferSize % 2);
			}
			else if (psVorbisInfo->channels == 2)
			{
				ulFormat = AL_FORMAT_STEREO16;
				// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
				ulBufferSize = ulFrequency;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				ulBufferSize -= (ulBufferSize % 4);
			}
			else if (psVorbisInfo->channels == 4)
			{
				ulFormat = alGetEnumValue("AL_FORMAT_QUAD16");
				// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
				ulBufferSize = ulFrequency * 2;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				ulBufferSize -= (ulBufferSize % 8);
			}
			else if (psVorbisInfo->channels == 6)
			{
				ulFormat = alGetEnumValue("AL_FORMAT_51CHN16");
				// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
				ulBufferSize = ulFrequency * 3;
				// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
				ulBufferSize -= (ulBufferSize % 12);
			}
		}

		if (ulFormat != 0)
		{
			// Allocate a buffer to be used to store decoded data for all Buffers
			pDecodeBuffer = (char*)malloc(ulBufferSize);
			if (!pDecodeBuffer)
			{
				LogError("Can't create buffer");
				ov_clear(sOggVorbisFile);
				return;
			}

			// Generate some AL Buffers for streaming
			alGenBuffers(numberBuff, buffer);

			// Fill all the Buffers with decoded audio data from the OggVorbis file
			for (ALint iLoop = 0; iLoop <numberBuff; iLoop++)
			{
				ulBytesWritten = DecodeOggVorbis(sOggVorbisFile, pDecodeBuffer, ulBufferSize, ulChannels);
				if (ulBytesWritten)
				{
					alBufferData(buffer[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
					alSourceQueueBuffers(SourceID, 1, &buffer[iLoop]);
				}
			}			
		}
		else
		{
			LogError("Sound: Can't read file %s", filePath);
			ov_clear(sOggVorbisFile);
			free(pDecodeBuffer);
			return;
		}

		// Close OggVorbis stream
		ov_clear(sOggVorbisFile);
		free(pDecodeBuffer);
	}

	////////////////////////////////////
	//	Just for DEBUG
	if (alGetError() != AL_NO_ERROR) {
		LogError ("Sound: Runtime Error at load OGG");
	}
	else {
		Log("Sound: Finished load OGG");
	}
}
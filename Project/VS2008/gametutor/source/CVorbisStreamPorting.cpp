#include "CVorbisStreamPorting.h"
namespace GameTutor
{
	size_t CVorbisStreamPorting::VorbisRead(void *ptr,	size_t byteSize, size_t sizeToRead,	void *datasource)
	{
		size_t				spaceToEOF;			// How much more we can read till we hit the EOF marker
		size_t				actualSizeToRead;	// How much data we are actually going to read from memory
		SOggFile*			vorbisData;			// Our vorbis data, for the typecast

		// Get the data in the right format
		vorbisData = (SOggFile*)datasource;

		// Calculate how much we need to read.  This can be sizeToRead*byteSize or less depending on how near the EOF marker we are
		spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
		if ((sizeToRead*byteSize) < spaceToEOF)
			actualSizeToRead = (sizeToRead*byteSize);
		else
			actualSizeToRead = spaceToEOF;	

		// A simple copy of the data from memory to the datastruct that the vorbis libs will use
		if (actualSizeToRead)
		{
			// Copy the data from the start of the file PLUS how much we have already read in
			memcpy(ptr, (char*)vorbisData->dataPtr + vorbisData->dataRead, actualSizeToRead);
			// Increase by how much we have read by
			vorbisData->dataRead += (actualSizeToRead);
		}

		// Return how much we read (in the same way fread would)
		return actualSizeToRead;
	}

	int CVorbisStreamPorting::VorbisSeek(void *datasource, ogg_int64_t offset, int whence)	
	{
		size_t				spaceToEOF;		// How much more we can read till we hit the EOF marker
		ogg_int64_t			actualOffset;	// How much we can actually offset it by
		SOggFile*			vorbisData;		// The data we passed in (for the typecast)

		// Get the data in the right format
		vorbisData = (SOggFile*)datasource;

		// Goto where we wish to seek to
		switch (whence)
		{
		case SEEK_SET: // Seek to the start of the data file
			// Make sure we are not going to the end of the file
			if (vorbisData->dataSize >= offset)
				actualOffset = offset;
			else
				actualOffset = vorbisData->dataSize;
			// Set where we now are
			vorbisData->dataRead = (int)actualOffset;
			break;
		case SEEK_CUR: // Seek from where we are
			// Make sure we dont go past the end
			spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
			if (offset < spaceToEOF)
				actualOffset = (offset);
			else
				actualOffset = spaceToEOF;	
			// Seek from our currrent location
			vorbisData->dataRead += actualOffset;
			break;
		case SEEK_END: // Seek from the end of the file
			vorbisData->dataRead = vorbisData->dataSize+1;
			break;
		default:
			printf("*** ERROR *** Unknown seek command in VorbisSeek\n");
			break;
		};

		return 0;
	}

	int CVorbisStreamPorting::VorbisClose(void *datasource)
	{
		// This file is called when we call ov_close.  If we wanted, we could free our memory here, but
		// in this case, we will free the memory in the main body of the program, so dont do anything
		return 1;
	}


	long CVorbisStreamPorting::VorbisTell(void *datasource)
	{
		SOggFile*	vorbisData;

		// Get the data in the right format
		vorbisData = (SOggFile*)datasource;

		// We just want to tell the vorbis libs how much we have read so far
		return vorbisData->dataRead;
	}


	void CVorbisStreamPorting::VorbisError(int code)
	{
		switch(code)
		{
		case OV_EREAD:
			LogError("[CVorbisStreamPorting::VorbisError] Read from media.");
			break;
		case OV_ENOTVORBIS:
			Log("[CVorbisStreamPorting::VorbisError] Not Vorbis data.");
			break;
		case OV_EVERSION:
			Log("[CVorbisStreamPorting::VorbisError] Vorbis version mismatch.");
			break;
		case OV_EBADHEADER:
			Log("[CVorbisStreamPorting::VorbisError]Invalid Vorbis header.");
			break;
		case OV_EFAULT:
			Log("[CVorbisStreamPorting::VorbisError]Internal logic fault (bug or heap/stack corruption).");
			break;
		default:
			Log("[CVorbisStreamPorting::VorbisError] Unknown Ogg error.");
		}
	}
}
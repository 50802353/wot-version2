#include "Header.h"
namespace GameTutor
{
	// vorbis porting
	struct SOggFile
	{
		char*		dataPtr;			// Pointer to the data in memoru
		int			dataSize;			// Sizeo fo the data
		int			dataRead;			// How much data we have read so far
	};

	class CVorbisStreamPorting
	{
	public:
		static size_t VorbisRead(
			void *ptr,			// ptr to the data that the vorbis files need, 
			size_t byteSize,	// how big a byte is, 
			size_t sizeToRead,	// How much we can read, 
			void *datasource);	// this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct);
		
		static int VorbisSeek(
			void *datasource,		//this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct)
			ogg_int64_t offset,		//offset from the point we wish to seek to
			int whence);		//where we want to seek to
				
		static int VorbisClose(void *datasource); //this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct)
			
		static long VorbisTell(void *datasource); //this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct)
		
		static void VorbisError(int code);
	};
}
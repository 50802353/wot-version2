#include "ReadBinaryToolkit.h"


//Check Little Endian
bool isLittleEndian()
{
	short s = 1;
	return (((char*)&s)[0]) == 1;
}


//TO SHORT
//--Converts a two-character array to a short
short BKToShort(const char* bytes)
{
	if(isLittleEndian())
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	else return (short)(((unsigned char)bytes[0] << 8) |
					   (unsigned char)bytes[1]);
}
//--Converts a two-character array to an unsigned short
unsigned short BKToUShort(const char* bytes)
{
	if(isLittleEndian())
		return (unsigned short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	else return (unsigned short)(((unsigned char)bytes[0] << 8) |
					   (unsigned char)bytes[1]);
}
//--Reads the next two bytes as a short
short BKReadShort(FILE* fp)
{
	char buffer[2];
	fread(buffer,2,1,fp);
	return BKToShort(buffer);
}
//--Reads the next two bytes as an unsigned short
unsigned short BKReadUShort(FILE* fp)
{
	char buffer[2];
	fread(buffer,2,1,fp);
	return BKToUShort(buffer);
}


//TO INT
//--Converts a four-character array to an integer
int BKToInt(const char* bytes)
{
	if(isLittleEndian())
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	else return (int)(((unsigned char)bytes[0] << 24) |
					 ((unsigned char)bytes[1] << 16) |
					 ((unsigned char)bytes[2] << 8) |
					 (unsigned char)bytes[3]);
}
//--Reads the next four bytes as an integer
int BKReadInt(FILE* fp)
{
	char buffer[4];
	fread(buffer,4,1,fp);
	return BKToInt(buffer);
}

//TO FLOAT
//--Converts a four-character array to a float
float BKToFloat(const char* bytes) {
		float f;
		if (isLittleEndian()) {
			((char*)&f)[0] = bytes[0];
			((char*)&f)[1] = bytes[1];
			((char*)&f)[2] = bytes[2];
			((char*)&f)[3] = bytes[3];
		}
		else {
			((char*)&f)[0] = bytes[3];
			((char*)&f)[1] = bytes[2];
			((char*)&f)[2] = bytes[1];
			((char*)&f)[3] = bytes[0];
		}
		return f;
}
//--Reads the next four bytes as a float
float BKReadFloat(FILE* fp)
{
	char buffer[4];
	fread(buffer,4,1,fp);
	return BKToFloat(buffer);
}


//TO 3F VECTOR
//--Calls BKReadFloat three times and returns the results as a Vec3f object
Vec3f BKReadVec3f(FILE* fp)
{
	float x = BKReadFloat(fp);
	float y = BKReadFloat(fp);
	float z = BKReadFloat(fp);
	return Vec3f(x, y, z);
}
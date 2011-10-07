#include <stdio.h>
#include "vec3f.h"

//Check Little Endian
bool isLittleEndian();

//TO SHORT
//--Converts a two-character array to a short
short BKToShort(const char* bytes);
//--Converts a two-character array to an unsigned short
unsigned short BKToUShort(const char* bytes);
//--Reads the next two bytes as a short
short BKReadShort(FILE* fp);
//--Reads the next two bytes as an unsigned short
unsigned short BKReadUShort(FILE* input);

//TO INT
//--Converts a four-character array to an integer
int BKToInt(const char* bytes);
//--Reads the next four bytes as an integer
int BKReadInt(FILE* fp);

//TO FLOAT
//--Converts a four-character array to a float
float BKToFloat(const char* bytes);
//--Reads the next four bytes as a float
float BKReadFloat(FILE* fp);

//TO 3F VECTOR
//--Calls BKReadFloat three times and returns the results as a Vec3f object
Vec3f BKReadVec3f(FILE* fp);
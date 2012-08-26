#include "StringMap.h"


StringMap::StringMap(int string_ID)
{
	left = right = -1;
	left_end = right_end = string_ID;
}

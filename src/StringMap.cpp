#include "StringMap.h"


StringMap::StringMap(int string_ID)
{
	left = right = suffix_overlap = -1;
	left_end = right_end = string_ID;
	deleted = false;
}

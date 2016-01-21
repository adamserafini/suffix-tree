#pragma once
class StringMap
{
public:
	StringMap() {}
	StringMap(int);

	int left;
	int right;
	int left_end;
	int right_end;
	int suffix_overlap;
	bool deleted;
};


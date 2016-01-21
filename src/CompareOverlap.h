#pragma once

#include "Overlap.h"
class CompareOverlap
{
public:
	bool operator ()(const Overlap& left, const Overlap& right) const {
		return left.overlap < right.overlap;
	}
};


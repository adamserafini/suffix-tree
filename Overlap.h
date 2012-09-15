#pragma once

class Node;
class Overlap
{
public:
	Overlap(Node*, int, int, int);

	Node* node;
	int string_left;
	int string_right;
	int overlap;
};


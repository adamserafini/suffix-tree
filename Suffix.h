#pragma once

class Node;
class Suffix {
public:
    Suffix(Node*, int);
    Node* node;
    int char_index;
    bool ends_at_node();
    bool ends_at_leaf();
    bool continues_with_char(char);
};


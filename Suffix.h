#pragma once

class SuffixTree;
class Node;
class Suffix {
public:
    Suffix(Node*, int);
    Node* node;
    int char_index;
    bool ends_at_node() const;
    bool ends_at_leaf() const;
    bool continues_with_char(const SuffixTree&, char) const;
};


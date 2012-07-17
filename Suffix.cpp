#include "Suffix.h"
#include "Node.h"

Suffix::Suffix(Node* n, int c) : node(n), char_index(c) {
}

bool Suffix::ends_at_node() { 
    return char_index == static_cast<int>(node->edge_label.length()) - 1;
}

bool Suffix::ends_at_leaf() {
    return node->is_leaf() && ends_at_node();
}

bool Suffix::continues_with_char(char ch) {
    return (ends_at_node() && node->get_child(ch) != NULL)
            || (!ends_at_node() && node->edge_label[char_index + 1] == ch);
}

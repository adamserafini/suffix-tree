# suffix-tree #

A C++ implementation of [Ukkonen's algorithm for linear-time suffix tree
construction](https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf).

![Suffix Tree for xabxa$](xabxa$.jpg?raw=true "Suffix Tree for xabxa$")

## Build ##

To build everything simply run `make`.

## Test ##

Tests are written with [bats](https://github.com/sstephenson/bats):

    bats test/tests/bats

## Using ##

The compiled program `suffixtree` takes a single string parameter and outputs
a DOT language (Graphviz) representation of the tree to STDOUT. With
ImageMagick and Graphviz installed you should see a `.jpg` like the above:

    ./suffixtree xabxa$ | dot -Tjpg | display

## License ##

MIT

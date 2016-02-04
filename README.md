# suffix-tree #

A C++ implementation of [Ukkonen's algorithm for linear-time suffix tree
construction](https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf) compiled for JavaScript using Emscripten.

## Prerequisites ##

Compiling for JavaScript requires Emscripten. Compilation has only been tested
with version 1.35.0.

## Build ##

To build everything simply run `make`.

## Demo ##

The file `demo.html` opens the compiled `suffix_tree.js` file from the build
step and outputs a suffix tree for `hello_world$` to the console.

## License ##

MIT

# suffix-tree #

A C++ implementation of Ukkonen's algorithm for linear-time suffix tree
construction compiled for JavaScript using Emscripten.

## Prerequisites ##

Compiling for JavaScript requires Emscripten.

## Build ##

To build everything simply run `make`.

## Demo ##

The file `demo.html` opens the compiled `suffix_tree.js` file from the build
step and outputs a suffix tree for `hello_world$` to the console.

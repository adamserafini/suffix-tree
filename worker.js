// Worker script to generate SVG Suffix Trees

importScripts("lib/viz.min.js", "suffix_tree.js");
// If you're thinking about inspecting either of the imported scripts, be aware
// they are both 'compiled' from C/C++ to JavaScript using Emscripten and will
// not be interesting to read.

// "viz.min.js" is Graphviz for the web: https://github.com/mdaines/viz.js/.
// This particular version is the same one used by http://www.webgraphviz.com/
// which I found to be slightly smaller/faster than the 'official' Viz.js
// release.

// "suffix_tree.js" is compiled from my C++ suffix tree
// implementation: https://github.com/adamserafini/ukkonens-algorithm

// Initialise SuffixTree once
var suffix_tree = SuffixTree({noInitialRun: true});

onmessage = function(e) {
  postMessage({
    'slice': e.data,
    'tree': Viz(suffix_tree.print_tree(e.data), "svg")
  });
}

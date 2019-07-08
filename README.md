# dfs-rule-search
A generalised exhaustive CA rule searcher

A collection of programs to find all the rules in which a pattern is an oscillator. Finds all isotropic two-state CA rules on the Moore neighbourhood in which the pattern of interest is an oscillator (within a fixed bounding box and maximum period). Uses a depth first search approach to exhaustively search the allowed rulespace.

Original [two cell oscillator](http://conwaylife.com/forums/viewtopic.php?p=67136#p67136) search by Oscar Cunningham.

## Adaptations:

pop2osc.cpp - Adaptation to allow searching larger grids by restricting the rulespace. Pattern: obo$

pop3osc.cpp - Adaptation to search a 3-cell pattern in a larger grid with a restricted rulespace. Output results filtered by minimum population (set the `minP` variable). Pattern: obobo$

## Helper scripts

pop2osc-setrule.py - Python script to convert isotropic rule range to C function which sets the rule restriction in pop2osc.cpp
Usage: $ python pop2osc-setrule.py "<minrule> - <maxrule>"
The ouput will be a setrule() function which can be used in on of the rule search programs.


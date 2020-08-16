# Laby-Jupyter: Learn programming, playing with ants and spider webs ;-) In Jupyter :-)

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/nthiery/laby-jupyter/master?filepath=notebooks).

[Laby](https://github.com/sgimenez/laby/issues/52) is an introductory
coding game, where the learner (from six years old on) solves puzzles
by guiding -- with code -- a lost ant out labyrinths riddled with
deadly obstacles. This is nothing but the good old pedagogical concept
of turtle; but gamified with a well conceived sequence of puzzles
guiding the learner through the basic concepts of imperative
programming.

Laby-Jupyter is a (partial) reimplementation of Laby, as a Jupyter-based web application.
Here is some [context and motivation](https://github.com/sgimenez/laby/issues/52).

Credits for all the artwork and puzzles goes to the original Laby
authors! Thank you for making this possible by sharing your work !!!

This an alpha version:
- supports only the C++ programming language
- supports only the French language
- is likely to have bugs or missing features

Please [try it out online](https://mybinder.org/v2/gh/nthiery/laby-jupyter/master?filepath=notebooks) and report bugs!

## Installation

Install the [dependencies](environment.yml), typically with conda.
Then:

    git clone git@github.com:nthiery/laby-jupyter.git
    pip install .

After this step, you should be able to enjoy all the [notebooks](notebooks/).

The installation procedure is primitive and assumes a standard
environment with <PREFIX>/include, <PREFIX>/share.

## Tests

Run:

    make tests

Again, this is primitive, assuming g++ and xwidgets and stuff directly
in the standard include path, or $(CONDA_PREFIX)/include.
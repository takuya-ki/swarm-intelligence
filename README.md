# swarm-intelligence

Examples of easy swarm intelligence algorithm.

## Description

Examples of various swarm intelligence algorithms.

- [pso](https://en.wikipedia.org/wiki/Particle_swarm_optimization): particle swarm optimization  
For adaptive pso with opso and epso, see this [reference](http://lab.cntl.kyutech.ac.jp/~nishida/paper/2011/131_1642.pdf).

## Features

- Easy to use for optimization
- pso(simple-pso): offline use
- opso/epso: online use

## Installation/Requirement

### c++
	$ git clone git@github.com:takuya-ki/swarm-intelligence.git
	$ cd swarm-intelligence/eigen (or boost)

- eigen 3.3.3
- boost 1.61.0
- g++ 4.9.4 (g++ -dumpversion)
- c++11

### python
	$ git clone git@github.com:takuya-ki/swarm-intelligence.git
	$ cd swarm-intelligence/python

- python 3.0.0 or above

## Usage

- pso (c++):  
1. design fitness function according to your purpose
2. `$ make pso`
3. `$ ./pso`

- pso (python)
1. design fitness function according to your purpose
2. `$ python pso.py`

## Author/Contributors

[Takuya Kiyokawa](https://takuya-ki.github.io/)

## License

This software is released under the MIT License, see LICENSE.

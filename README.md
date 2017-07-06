# swarm-intelligence-examples

This is easy swarm intelligence algorithm's examples.

## Description

This is a examples of various Particle swarm intelligence algorithm.

- pso
(https://en.wikipedia.org/wiki/Particle_swarm_optimization)  
For Adaptive PSO with opso and epso, see [here](http://lab.cntl.kyutech.ac.jp/~nishida/paper/2011/131_1642.pdf).

## Features

- Easy to use for optimization
- pso(simple-pso): offline use
- opso/epso: online use

## Installation/Requirement

### c++
	$ git clone git@github.com:takuya-ki/swarm-intelligence-examples.git
	$ cd swarm-intelligence-examples/eigen (or boost)

- eigen3.3.3
- boost1.61.0
- g++4.9.4 (g++ -dumpversion)
- c++11

### python
	$ git clone git@github.com:takuya-ki/swarm-intelligence-examples.git
	$ cd swarm-intelligence-examples/Python

- python3.0 or above
- numpy

## Usage

- pso(c++):  
1. design fitness function according to your purpose
2. `$ make pso`
3. `$ ./pso`

- pso(python)
1. design fitness function according to your purpose
2. `$ python pso.py`

## Author/Contributors

qiita: [@takuya-ki](http://qiita.com/takuya-ki)

## License

This software is released under the MIT License, see LICENSE.txt.

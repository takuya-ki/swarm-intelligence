# various-pso-examples

easy PSO examples.

## Description

This is a examples of various Particle Swarm Optimization algorithms.
(https://en.wikipedia.org/wiki/Particle_swarm_optimization)  
For Adaptive PSO with opso and epso, see [here](http://lab.cntl.kyutech.ac.jp/~nishida/paper/2011/131_1642.pdf).


## Features

- Easy Optimization algorithms
- Offline use: pso(simple-pso)
- Online use: opso/epso

## Installation/Requirement

	$ git clone git@github.com:takuya-ki/various-pso-examples.git
	$ cd various-pso-examples
	$ cd eigen (or boost)

- eigen 3.3.3
- boost 1.61.0
- g++ 4.9.4 (g++ -dumpversion)
- C++11

## Usage

In case of pso:  
1. design fitness function according to your purpose．  
2. `$ make pso`  
3. `$ ./pso`  

## Author/Contributors

qiita: [@takuya-ki](http://qiita.com/takuya-ki)

## License

This software is released under the MIT License, see LICENSE.txt.

Physics2D
=========

Some 2D collision detection and physics stuff written in C++.  
Utilizes and remains consistent with the [C++ General Utility Library (CGUL)](https://github.com/Zethes/CGUL).

Goals
=====
* [Collision detection](#collision-detection) between various trivial 2D primitives (AABB, OBB, Circle, Triangle, Line Segment/Ray, etc)
* [Closest point](#closest-point) algorithms
* "Complex" objects built from trivial primitives
* Triangulization from convex and concave primitives
* Collision prediction algorithms
* Collision response (impulse based?)
* Force generators (gravity/springs/explosions)
* Consistent results between identical iterations
* Hierarchy collision detection optimizations
* Binary space partitioning optimizations

Collision Detection
=====
Below is a matrix of supported collision algorithms between trivial 2D primitives.

| X          | Circle | AABB  | OBB   |
|:----------:|:------:|:-----:|:-----:|
| __Circle__ | CHECK  |       |       |
| __AABB__   |        | CHECK |       |
| __OBB__    |        |       | CHECK |

__Planned types:__
* Triangles
* Line Segments
* Ovals ?

Closest Point
=====
Closest point algorithms are implemented for the following types:  
__NONE__ :grinning:

Requirements
=====
Requires [CGUL](https://github.com/Zethes/CGUL) built with [GLEW](http://glew.sourceforge.net/).  
Uses [CMake](http://www.cmake.org/) build system.  
Graphics via OpenGL 2.1(ish?)  
Tested with GCC 4.2 (Mac), Clang 3.2 (Mac), GCC 4.7 (Linux & MinGW), and Visual Studio 2010 (Windows).

License
=====
The code is under the [BSD 2-clause License](https://github.com/JoshuaBrookover/Physics2D/blob/master/LICENSE).  You must include a copyright notice in your product's documentation if you use this code in full.  Feel free to use snippets of the code, or re-implement the code, without this restriction.

# Maze Generator using OpenGL

First project in OpenGL to get familiar with Vertex Buffer, Vertex Array, Vertex Element Array and the basic API of OpenGL.

I am using two vertex buffer. One for the color of the cells (white -> visited, black -> not visited). Each cell is composed of two triangle. I use a Vertex Element Array to reduce the number of vertex in the cell Vertex Buffer.
For the wall is use another vertex buffer without a Vertex Element Buffer.

The generation is animated, where each step of the algorithm (Depth First Search) is showed.
Press R to restart a random maze generation.

![Maze OpenLG](images/maze.png)

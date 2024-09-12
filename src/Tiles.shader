#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 mazePosition;
layout(location = 2) in vec4 colorOn;
layout(location = 3) in vec4 colorOff;
out vec4 vertexColorOn;
out vec4 vertexColorOff;
out vec2 vertexMazePosition;

void main()
{
    gl_Position = position;
    vertexColorOn = colorOn;
    vertexColorOff = colorOff;
    vertexMazePosition = mazePosition;
};

#shader fragment
#version 330
#define WIDTH 44
#define HEIGHT 44

in vec4 vertexColorOn;
in vec4 vertexColorOff;
in vec2 vertexMazePosition;
layout(location = 0) out vec4 color;
uniform int u_MazeTileState[WIDTH * HEIGHT];

void main()
{
    int index = int(vertexMazePosition.y * WIDTH + vertexMazePosition.x);
    if(u_MazeTileState[index] == 1)
        color = vertexColorOn;
    else
        color = vertexColorOff;
};

#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in float index;
layout(location = 2) in vec3 colorOn;
layout(location = 3) in vec3 colorOff;
out vec3 vertexColorOn;
out vec3 vertexColorOff;
out float wallIndex;

void main()
{
    gl_Position = vec4(position.xy, 1.0, 1.0);
    vertexColorOn = colorOn;
    vertexColorOff = colorOff;
    wallIndex = index;
};

#shader fragment
#version 330
#define WIDTH 44
#define HEIGHT 44
#define NB_WALL 2*WIDTH*HEIGHT+WIDTH+HEIGHT

in vec3 vertexColorOn;
in vec3 vertexColorOff;
in float wallIndex;
layout(location = 0) out vec4 color;
uniform int u_MazeWallState[NB_WALL];

void main()
{
    int index = int(wallIndex);
    if(u_MazeWallState[index] == 1)
        color = vec4(vertexColorOn.xyz, 1.0);
    else
        color = vec4(vertexColorOff.xyz, 1.0);
};

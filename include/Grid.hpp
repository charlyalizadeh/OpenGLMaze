#ifndef GRID_H
#define GRID_H

#include "Dimension.hpp"
#include "Maze.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexIndexBuffer.hpp"

#include <vector>
#include <map>



class Grid {
public:
    Grid(int width, int height, float tileWidth, float tileHeight);
    void draw();
    void setWallState(int x1, int y1, int x2, int y2, int value);
    void setTileState(int x, int y, int value);
    void setAllWallState(int value);
    void setAllTileState(int value);

    int getWallState(int x1, int y1, int x2, int y2) const;
    int getTileState(int x, int y) const;

private:
    void fillIndicesWalls();
    void fillVerticesWalls();
    void fillIndicesTiles();
    void fillVerticesTiles();

private:
    int width, height;
    float tileWidth, tileHeight;

    std::vector<float> verticesWalls;
    std::vector<float> verticesTiles;
    std::vector<unsigned int> indicesWalls;
    std::vector<unsigned int> indicesTiles;
    std::map<Vec2D,int> wall2index;


    VertexBuffer vboWalls;
    VertexBuffer vboTiles;

    VertexArray vaoWalls;
    VertexArray vaoTiles;

    VertexIndexBuffer iboTiles;

    Shader shaderTiles;
    Shader shaderWalls;

    std::array<int, NB_TILE> tileState;
    std::array<int, NB_WALL> wallState;
};

#endif

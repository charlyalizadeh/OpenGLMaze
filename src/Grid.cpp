#include "../include/Grid.hpp"


static void pushColors(std::vector<float>& vertices) {
        vertices.insert(vertices.end(), 3, 1);
        vertices.insert(vertices.end(), 3, 0);
}

static void pushPositionAndColors(int x, int y, std::vector<float>& vertices) {
        vertices.push_back((float)x);
        vertices.push_back((float)y);
        pushColors(vertices);
}

static void pushIndexAndColors(int index, std::vector<float>& vertices) {
    vertices.push_back((float)index);
    pushColors(vertices);
}

static void pushLine(int index, float x1, float y1, float x2, float y2, std::vector<float>& vertices) {
    vertices.push_back(x1); vertices.push_back(y1);
    pushIndexAndColors(index, vertices);
    vertices.push_back(x2); vertices.push_back(y2);
    pushIndexAndColors(index, vertices);
}

/*
 Order of vertices for each tile
 0--1
 |  |
 2--3
 0 = (x1, y1)
 1 = (x2, y1)
 2 = (x1, y2)
 3 = (x2, y2)
 Always (0 -> 1) and (0 -> 2)
 Do (1 -> 3) if x == width - 1
 Do (2 -> 3) if y == height - 1
*/
void Grid::fillVerticesWalls() {
    float index;

    index = 0;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float x1 = (-(float)width / 2.f + x) * tileWidth;
            float x2 = (-(float)width / 2.f + x + 1) * tileWidth;
            float y1 = (-(float)height / 2.f + y) * tileHeight;
            float y2 = (-(float)height / 2.f + y + 1) * tileHeight;
            int gridIndex = y * width + x;

            // Line 0 -> 1
            pushLine(index, x1, y1, x2, y1, verticesWalls);
            wall2index[Vec2D(gridIndex, gridIndex - width)] = index;
            wall2index[Vec2D(gridIndex - width, gridIndex)] = index;
            index++;

            // Line 0 -> 2
            pushLine(index, x1, y1, x1, y2, verticesWalls);
            wall2index[Vec2D(gridIndex, gridIndex - 1)] = index;
            wall2index[Vec2D(gridIndex - 1, gridIndex)] = index;
            index++;

            // Line 1 -> 3
            if(x == width - 1) {
                pushLine(index, x2, y1, x2, y2, verticesWalls);
                wall2index[Vec2D(gridIndex, gridIndex + 1)] = index;
                wall2index[Vec2D(gridIndex + 1, gridIndex)] = index;
                index++;
            }

            // Line 2 -> 3
            if(y == height - 1) {
                pushLine(index, x1, y2, x2, y2, verticesWalls);
                wall2index[Vec2D(gridIndex, gridIndex + width)] = index;
                wall2index[Vec2D(gridIndex + width, gridIndex)] = index;
                index++;
            }
        }
    }
}

void Grid::fillVerticesTiles() {
    // Order of vertices for each tile
    // 0 1
    // 2 3
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            verticesTiles.push_back((-(float)width / 2.f + x) * tileWidth);
            verticesTiles.push_back((-(float)height / 2.f + y) * tileHeight);
            pushPositionAndColors(x, y, verticesTiles);

            verticesTiles.push_back((-(float)width / 2.f + x + 1) * tileWidth);
            verticesTiles.push_back((-(float)height / 2.f + y) * tileHeight);
            pushPositionAndColors(x, y, verticesTiles);

            verticesTiles.push_back((-(float)width / 2.f + x) * tileWidth);
            verticesTiles.push_back((-(float)height / 2.f + y + 1) * tileHeight);
            pushPositionAndColors(x, y, verticesTiles);

            verticesTiles.push_back((-(float)width / 2.f + x + 1) * tileWidth);
            verticesTiles.push_back((-(float)height / 2.f + y + 1) * tileHeight);
            pushPositionAndColors(x, y, verticesTiles);
        }
    }
}

void Grid::fillIndicesWalls() {
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            int topLeftCorner = (y * 2) * width * 2 + x * 4;
            // Line 0 -> 1
            indicesWalls.push_back(topLeftCorner);indicesWalls.push_back(topLeftCorner + 1);
            // Line 0 -> 2
            indicesWalls.push_back(topLeftCorner);indicesWalls.push_back(topLeftCorner + 2);
            // Line 1 -> 3
            indicesWalls.push_back(topLeftCorner + 1);indicesWalls.push_back(topLeftCorner + 3);
            // Line 2 -> 3
            indicesWalls.push_back(topLeftCorner + 2);indicesWalls.push_back(topLeftCorner + 3);
        }
    }
}

void Grid::fillIndicesTiles() {
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            // First triangle
            int topLeftCorner = (y * 2) * width * 2 + x * 4;
            indicesTiles.push_back(topLeftCorner);
            indicesTiles.push_back(topLeftCorner + 2);
            indicesTiles.push_back(topLeftCorner + 1);

            // Second triangle
            indicesTiles.push_back(topLeftCorner + 1);
            indicesTiles.push_back(topLeftCorner + 2);
            indicesTiles.push_back(topLeftCorner + 3);
        }
    }
}

Grid::Grid(int width, int height, float tileWidth, float tileHeight): width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight) {
    fillVerticesWalls();
    fillVerticesTiles();
    fillIndicesWalls();
    fillIndicesTiles();

    vboWalls.init(&verticesWalls[0], verticesWalls.size() * sizeof(float));
    vboTiles.init(&verticesTiles[0], verticesTiles.size() * sizeof(float));

    vboWalls.bind();
    vaoWalls.init();
    vaoWalls.setAttribute(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
    vaoWalls.setAttribute(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 2));
    vaoWalls.setAttribute(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
    vaoWalls.setAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 6));

    vboTiles.bind();
    vaoTiles.init();
    vaoTiles.setAttribute(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)0);
    vaoTiles.setAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 2));
    vaoTiles.setAttribute(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 4));
    vaoTiles.setAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (void*)(sizeof(float) * 7));

    iboTiles.init(&indicesTiles[0], indicesTiles.size());

    shaderWalls.init("./src/Walls.shader");
    shaderTiles.init("./src/Tiles.shader");

    glClearColor(0.5f, 0.3f, 0.3f, 1.0f);

    for(size_t i = 0; i < wallState.size(); i++)
        wallState[i] = 0;
    for(size_t i = 0; i < tileState.size(); i++)
        tileState[i] = 0;
}

void Grid::draw() {
    vboTiles.bind();
    iboTiles.bind();
    vaoTiles.bind();
    shaderTiles.bind();
    glDrawElements(GL_TRIANGLES, indicesTiles.size(), GL_UNSIGNED_INT, NULL);

    vboWalls.bind();
    vaoWalls.bind();
    shaderWalls.bind();
    glDrawArrays(GL_LINES, 0, (int)(verticesWalls.size() / 9));
}

void Grid::setWallState(int x1, int y1, int x2, int y2, int value) {
    int index1, index2, wallIndex;

    shaderWalls.bind();
    index1 = y1 * WIDTH + x1;
    index2 = y2 * WIDTH + x2;
    wallIndex = wall2index[Vec2D(index1, index2)];
    wallState[wallIndex] = value;
    shaderWalls.setUniformIntArray("u_MazeWallState", &wallState[0], wallState.size());
}

void Grid::setTileState(int x, int y, int value) {
    shaderTiles.bind();
    tileState[y * WIDTH + x] = value;
    shaderTiles.setUniformIntArray("u_MazeTileState", &tileState[0], tileState.size());
}

void Grid::setAllWallState(int value) {
    shaderWalls.bind();
    for(size_t i = 0; i < wallState.size(); i++)
        wallState[i] = value;
    shaderWalls.setUniformIntArray("u_MazeWallState", &wallState[0], wallState.size());
}

void Grid::setAllTileState(int value) {
    shaderTiles.bind();
    for(size_t i = 0; i < tileState.size(); i++)
        tileState[i] = value;
    shaderTiles.setUniformIntArray("u_MazeTileState", &tileState[0], tileState.size());
}

int Grid::getWallState(int x1, int y1, int x2, int y2) const {
    int index1, index2, wallIndex;

    index1 = y1 * WIDTH + x1;
    index2 = y2 * WIDTH + x2;
    wallIndex = wall2index.at(Vec2D(index1, index2));
    return wallState.at(wallIndex);
}

int Grid::getTileState(int x, int y) const {
    return tileState.at(y * WIDTH + x);
}

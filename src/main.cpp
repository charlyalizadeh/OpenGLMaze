#include "../include/Dimension.hpp"
#include "../include/Grid.hpp"
#include "../include/Maze.hpp"
#include "../include/MazeGenerator.hpp"
#include <chrono>

static Vec2D index2xy(int index) {
    int x, y;

    y = int(index / WIDTH);
    x = index - y * WIDTH;
    return Vec2D(x, y);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    {
        // Init OpenGL and create a window
        GLFWwindow* window = initOpenGL(800, 800, 3, 3);
        if(window == nullptr)
            return -1;

        glLineWidth(2);

        std::vector<int> path;
        int pathIteration;
        Vec2D oldIndexCoord;
        Vec2D indexCoord;

        path = dfs(WIDTH, HEIGHT);
        pathIteration = 0;

        Grid grid = Grid(WIDTH, HEIGHT, 0.040, 0.040);
        grid.setAllWallState(0);
        grid.setAllTileState(0);

        // Main loop
        while(!glfwWindowShouldClose(window)) {
            processInput(window);

            // Render
            glClear(GL_COLOR_BUFFER_BIT);
            grid.draw();

            if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                path = dfs(WIDTH, HEIGHT);
                pathIteration = 0;

                grid.setAllWallState(0);
                grid.setAllTileState(0);
            }


            if(pathIteration < path.size()) {
                indexCoord = index2xy(path[pathIteration]);
                if(pathIteration > 0 && grid.getTileState(indexCoord.x, indexCoord.y) == 0)
                    grid.setWallState(oldIndexCoord.x, oldIndexCoord.y, indexCoord.x, indexCoord.y, 1);
                grid.setTileState(indexCoord.x, indexCoord.y, 1);
                oldIndexCoord = indexCoord;
                pathIteration++;
            }


            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

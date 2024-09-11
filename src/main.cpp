#include "../include/Maze.hpp"
#include "../include/Grid.hpp"
#include "../include/Dimension.hpp"
#include <chrono>


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
        std::cout << NB_WALL << "\n";

        // Buffer, Array Buffer and Index Buffer
        Grid grid = Grid(WIDTH, HEIGHT, 0.035, 0.035);
        grid.setAllWallState(0);
        grid.setAllTileState(1);

        grid.setWallState(0, 1, 0, 2, 1);
        grid.setWallState(8, 8, 8, 9, 1);

        // Main loop
        while(!glfwWindowShouldClose(window)) {
            processInput(window);

            // Render
            glClear(GL_COLOR_BUFFER_BIT);
            grid.draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

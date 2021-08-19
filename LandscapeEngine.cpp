#include <vector>
#include <random>
#include "LandscapeEngine.hpp"

// The function returns a Mesh consisting of triangles makeing up a landscape
// Note that "triangles" is a bit of a mis-nomer as the grid is based on two and two line segments

LandscapeEngine::LandscapeEngine(int gs){
    gridSize = gs;
}

Mesh LandscapeEngine::makeLandscape() {
    std::random_device rd;
    std::mt19937 gen(rd());
        //std::uniform_real_distribution<float> unifDis(-0.5f, 0.5f);
        
    const float gridDelta = 1 / (float)gridSize;
    const int numTriangles = gridSize * gridSize * 2;
    std::normal_distribution<float> unifDis(0.0f, 1.0f);

    Vert vert;
    Triangle tri;
    Mesh triangleCollection;
    triangleCollection.tri.reserve(numTriangles);

    float myFloat[gridSize][gridSize];
    myFloat[0][0] = unifDis(gen);
    for (int i = 1; i < gridSize; ++i) {
        myFloat[0][i] = myFloat[0][i - 1] + unifDis(gen)*sqrt(gridSize)/(2.0f*gridSize);
        myFloat[i][0] = myFloat[i - 1][0] + unifDis(gen)*sqrt(gridSize)/(2.0f*gridSize);
    }

    for (int i = 1; i < gridSize; ++i)
        for (int j = 1; j < gridSize; ++j)
            myFloat[i][j] = 0.5f*(myFloat[i][j - 1] + myFloat[i - 1][j]) + unifDis(gen) * gridDelta * 2.0f;

    for (int i = 0; i + 1 < gridSize; ++i)
        for (int j = 0; j + 1 < gridSize; ++j) {
            tri.v[0].x = gridDelta * j;
            tri.v[0].z = gridDelta * i;
            tri.v[0].y = myFloat[i][j];
            tri.v[1].x = gridDelta * j;
            tri.v[1].z = gridDelta * (i + 1);
            tri.v[1].y = myFloat[i + 1][j];
            tri.v[2].x = gridDelta * (j + 1);
            tri.v[2].z = gridDelta * (i + 1);
            tri.v[2].y = myFloat[i + 1][j + 1];
            triangleCollection.tri.push_back(tri);

            tri.v[0].x = gridDelta * (j + 1);
            tri.v[0].z = gridDelta * (i + 1);
            tri.v[0].y = myFloat[i + 1][j + 1];
            tri.v[1].x = gridDelta * (j + 1);
            tri.v[1].z = gridDelta * i;
            tri.v[1].y = myFloat[i][j + 1];
            tri.v[2].x = gridDelta * j;
            tri.v[2].z = gridDelta * i;
            tri.v[2].y = myFloat[i][j];
            triangleCollection.tri.push_back(tri);
        }
    return triangleCollection;
}

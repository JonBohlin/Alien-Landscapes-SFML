#include <vector>
#pragma once

struct Vert {
    float x, y, z;
};

// Triangles consist of three vertices
struct Triangle {
    Vert v[3];
};

// Vector contains a list of triangles
struct Mesh {
    std::vector<Triangle> tri;
};

#include<vector>
#include<random>
#include "Datastructures.hpp"

// The landscape class -this class makes landscapes

class LandscapeEngine {
private:
    int gridSize;
    
public:
    LandscapeEngine(int gs);

    ~LandscapeEngine(){}
// The function returns a Mesh consisting of triangles makeing up a landscape
// Note that "triangles" is a bit of a mis-nomer as the grid is based on two and two line segments
    Mesh makeLandscape();
     
};

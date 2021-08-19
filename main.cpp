#include "ThreeDEngine.hpp"
#include "Lightning.hpp"
#include "LandscapeEngine.hpp"
#include <SFML/Graphics.hpp>
#include <thread>

// g++ -c main.cpp ThreeDEngine.cpp Lightning.cpp LandscapeEngine.cpp -O3
// g++ main.o ThreeDEngine.o Lightning.o LandscapeEngine.o -o sfml-app -O3 -lsfml-graphics -lsfml-window -lsfml-system -lpthread


    const int screenWidth = 1280;
    const int screenHeight = 768;
    const int gridSize = 400;
    
    void calculateLandscape(const std::vector<Triangle> *meshTriangles, std::vector<sf::VertexArray> *triangleArray, float frTheta, float viewAngRad){
        float dp;
        ThreeDEngine MyEngine;
        Lightning light;
        std::vector<int> tempLight;
        Vert normVec, planeVec, normalisedVector;
        Vert lightVec = {0.0f, 0.0f, 1.0f};
        MyEngine.init(screenWidth, screenHeight);
        MyEngine.viewAngRad = viewAngRad;
        tempLight.reserve( 3 );
        sf::VertexArray triangle(sf::Triangles, 3);
        Triangle transRot, rotTriY, rotTriX, transVertZ, tempTri, scaledTriangle, translatedTriangle;
        
        for(auto tri: *meshTriangles){
            transRot = MyEngine.translateAllVertices(tri, -0.5f);
            rotTriY = MyEngine.rotateTriangleY(transRot, frTheta);
            rotTriX=MyEngine.rotateTriangleX( rotTriY, 1.8f);
            transVertZ=MyEngine.translateTriangle(rotTriX, 0.0f, 0.0f, 5.0f);
            normVec = MyEngine.crossProduct( transVertZ );
            planeVec = transVertZ.v[0];

            if( MyEngine.dotProduct( normVec, planeVec) > 0.0f){
                tempTri = MyEngine.transformTrianleTo2D(transVertZ);
                translatedTriangle=MyEngine.translateTriangle(tempTri, 1.0f, 1.0f, 0.0f);
                scaledTriangle = MyEngine.scaleTriangle( translatedTriangle, (float)screenWidth/2.0f, (float)screenHeight/2.0f, 1.0f);
                normalisedVector = MyEngine.normaliseVector( tri.v[0] );
                lightVec = MyEngine.normaliseVector(lightVec);
                dp = std::max(0.01f, normalisedVector.z * MyEngine.dotProduct(lightVec, normVec));
                tempLight = light.getLightColour( dp );
                for(int ind = 0; ind < 3; ind++){
                    triangle[ ind ].position = sf::Vector2f(scaledTriangle.v[ ind ].x, scaledTriangle.v[ ind ].y);
                    triangle[ ind ].color = sf::Color(tempLight[0], tempLight[1], tempLight[2]);
                }
                triangleArray->push_back( triangle );
            }
        }
    }

int main()
{
    float stepSize = 0.05;
    float frTheta=1.0f;
    float viewAngRad=3.0f / tanf(90.0f * 0.5f / 180.0f * 3.14159f);
    int meshSize;
    const unsigned int numThreads = std::thread::hardware_concurrency();
    LandscapeEngine l = LandscapeEngine( gridSize );
    Mesh meshLandscape = l.makeLandscape();
    meshSize = meshLandscape.tri.size() / numThreads;
    std::thread tr[ numThreads ];
    std::vector<std::vector<Triangle>> vectorOfMeshLandscape;
    vectorOfMeshLandscape.resize( numThreads );
    std::vector<std::vector<sf::VertexArray>> vectorOfTriangleArrays;
    vectorOfTriangleArrays.resize( numThreads );
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Alien landscapes");

    for(int id = 0; id < numThreads; id++ ){
        vectorOfMeshLandscape[id].resize( meshSize );
        vectorOfTriangleArrays[id].resize( meshSize );
    }

    while (window.isOpen()){
        window.clear();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelMoved)
                if( event.mouseWheel.delta>0 ){
                    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                        viewAngRad += 0.1f;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                        stepSize +=0.001;
                    }
                }
                else{
                    if(event.mouseWheel.delta<0) {
                        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            viewAngRad -= 0.1f;
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                            stepSize -=0.001;
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            meshLandscape = l.makeLandscape();

        frTheta += stepSize;

        for(int k=0; k < numThreads; k++){
            for(int i = k*meshSize; i<(k+1)*meshSize; i++){
                vectorOfMeshLandscape[k].push_back(meshLandscape.tri[i]);
            }
            tr[ k ] = std::thread( calculateLandscape, &vectorOfMeshLandscape[k], &vectorOfTriangleArrays[k], frTheta, viewAngRad);
        }

        for(int k = 0; k < numThreads; k++ ){
            tr[ k ].join();
            for( const auto &tri: vectorOfTriangleArrays[k] )
                window.draw( tri );
                vectorOfTriangleArrays[k].clear();
                vectorOfMeshLandscape[k].clear();
        }

        window.display();
    }
    return 0;
}
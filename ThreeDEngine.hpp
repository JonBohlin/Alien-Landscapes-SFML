#include <cmath>
#include "Datastructures.hpp"
class ThreeDEngine{

public:
// Global declarations. This have to be set in accordance with screen/window parameters
    float aspect;
    float zend=1000.0, zstart=0.1f, totViewAngle=90.0f;
    float viewAngRad=3.0f / tanf(totViewAngle * 0.5f / 180.0f * 3.14159f);

// Vertices describing a polygon
    
    ThreeDEngine(){}

// Destructor*/
    ~ThreeDEngine(){}

    void init(int screenheight, int screenwidth);
    Vert transform3Dto2D( Vert points );
    Triangle transformTrianleTo2D( Triangle transTri );
    Vert rotateX( Vert points, float angle );
    Vert rotateY( Vert points, float angle );
    Vert rotateZ( Vert points, float angle );
    Triangle rotateTriangleX( Triangle tri, float fTheta );
    Triangle rotateTriangleY( Triangle tri, float fTheta );
    Triangle rotateTriangleZ( Triangle tri, float fTheta );
    Triangle scaleAllVertices( Triangle tri, float trans );
    Triangle scaleTriangle( Triangle tri, float transX, float transY, float transZ );
    Triangle scaleXVertice( Triangle tri, float trans );
    Triangle scaleYVertice( Triangle tri, float trans );
    Triangle scaleZVertice( Triangle tri, float trans );
    Triangle translateAllVertices( Triangle tri, float trans );
    Triangle translateTriangle( Triangle tri, float transX, float transY, float transZ );
    Triangle translateVerticeX( Triangle tri, float trans );
    Triangle translateVerticeY( Triangle tri, float trans );
    Triangle translateVerticeZ( Triangle tri, float trans );
    Vert crossProduct(Triangle tri);
    float dotProduct(Vert v1, Vert v2);
    Vert normaliseVector(Vert& v1);
};


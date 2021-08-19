#include "ThreeDEngine.hpp"

void ThreeDEngine::init(int screenwidth, int screenheight) {
    aspect = (float)screenwidth / (float)screenheight;
}

Vert ThreeDEngine::transform3Dto2D( Vert points ){
    Vert transPoints;
    transPoints.x=points.x*aspect*viewAngRad;
    transPoints.y=points.y*viewAngRad;
    transPoints.z=(points.z*zend/(zend-zstart))-zend*zstart/(zend-zstart);

    if(points.z!=0.0f){
        transPoints.x/=points.z;
        transPoints.y/=points.z;
        transPoints.z/=points.z;
    }

    return transPoints;
}

Triangle ThreeDEngine::transformTrianleTo2D( Triangle transTri ){
    Triangle tempTri;
    tempTri.v[0]=transform3Dto2D( transTri.v[0] );
    tempTri.v[1]=transform3Dto2D( transTri.v[1] );
    tempTri.v[2]=transform3Dto2D( transTri.v[2] );
    return tempTri; 
}

Vert ThreeDEngine::rotateX( Vert points, float angle ){
    Vert rot;
    rot.x=points.x;
    rot.y=(points.y)*cosf(angle/2)-points.z*sinf(angle/2);
    rot.z=(points.y)*sinf(angle/2)+points.z*cosf(angle/2);
    return rot;
}

Vert ThreeDEngine::rotateY( Vert points, float angle ){
    Vert rot;
    rot.x=(points.x)*cosf(angle/2)-points.z*sinf(angle/2);
    rot.y=points.y;
    rot.z=(points.x)*sinf(angle/2)+points.z*cosf(angle/2);
    return rot;
}

Vert ThreeDEngine::rotateZ( Vert points, float angle ){
    Vert rot;
    rot.x=(points.x)*cosf(angle)-points.y*sinf(angle);
    rot.y=(points.x)*sinf(angle)+points.y*cosf(angle);
    rot.z=points.z;
    return rot;
}

Triangle ThreeDEngine::rotateTriangleX( Triangle tri, float fTheta ){
    Triangle tempTri;
    tempTri.v[0]=rotateX( tri.v[0], fTheta);
    tempTri.v[1]=rotateX( tri.v[1], fTheta);
    tempTri.v[2]=rotateX( tri.v[2], fTheta);
    return tempTri;
}

Triangle ThreeDEngine::rotateTriangleY( Triangle tri, float fTheta ){
    Triangle tempTri;
    tempTri.v[0]=rotateY( tri.v[0], fTheta);
    tempTri.v[1]=rotateY( tri.v[1], fTheta);
    tempTri.v[2]=rotateY( tri.v[2], fTheta);
    return tempTri;
}

Triangle ThreeDEngine::rotateTriangleZ( Triangle tri, float fTheta ){
    Triangle tempTri;
    tempTri.v[0]=rotateZ( tri.v[0], fTheta);
    tempTri.v[1]=rotateZ( tri.v[1], fTheta);
    tempTri.v[2]=rotateZ( tri.v[2], fTheta);
    return tempTri;
}

Triangle ThreeDEngine::scaleAllVertices( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i){
        tempTri.v[i].x=tri.v[i].x*trans;
        tempTri.v[i].y=tri.v[i].y*trans;
        tempTri.v[i].z=tri.v[i].z*trans;
    }
    return tempTri;
}

Triangle ThreeDEngine::scaleTriangle( Triangle tri, float transX, float transY, float transZ ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i){
        tempTri.v[i].x=tri.v[i].x*transX;
        tempTri.v[i].y=tri.v[i].y*transY;
        tempTri.v[i].z=tri.v[i].z*transZ;
    }
    return tempTri;
}

Triangle ThreeDEngine::scaleXVertice( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].x=tri.v[i].x*trans;
    
    return tempTri;
}

Triangle ThreeDEngine::scaleYVertice( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].y=tri.v[i].y*trans;
    return tempTri;
}

Triangle ThreeDEngine::scaleZVertice( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].z=tri.v[i].z*trans;
    
    return tempTri;
}

Triangle ThreeDEngine::translateAllVertices( Triangle tri, float trans ){
    int i;
    Triangle tempTri;
    for(i=0; i<3; ++i){
        tempTri.v[i].x=tri.v[i].x+trans;
        tempTri.v[i].y=tri.v[i].y+trans;
        tempTri.v[i].z=tri.v[i].z+trans;
    }
    return tempTri;
}

Triangle ThreeDEngine::translateTriangle( Triangle tri, float transX, float transY, float transZ ){
    int i;
    Triangle tempTri;
    for(i=0; i<3; ++i){
        tempTri.v[i].x=tri.v[i].x+transX;
        tempTri.v[i].y=tri.v[i].y+transY;
        tempTri.v[i].z=tri.v[i].z+transZ;
    }
    return tempTri;
}

Triangle ThreeDEngine::translateVerticeX( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].x=tri.v[i].x+trans;
    
    return tempTri;
}

Triangle ThreeDEngine::translateVerticeY( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].y=tri.v[i].y+trans;
    
    return tempTri;
}

Triangle ThreeDEngine::translateVerticeZ( Triangle tri, float trans ){
    int i;
    Triangle tempTri=tri;
    for(i=0; i<3; ++i)
        tempTri.v[i].z=tri.v[i].z+trans;
    
    return tempTri;
}

Vert ThreeDEngine::crossProduct(Triangle tri) {
    Vert v1, v2, crossVec;
    float vecSize;
    v1.x = tri.v[1].x - tri.v[0].x;
    v1.y = tri.v[1].y - tri.v[0].y;
    v1.z = tri.v[1].z - tri.v[0].z;

    v2.x = tri.v[2].x - tri.v[0].x;
    v2.y = tri.v[2].y - tri.v[0].y;
    v2.z = tri.v[2].z - tri.v[0].z;

// Calculate cross product

    crossVec.x = v1.y * v2.z - v2.y * v1.z;
    crossVec.y = -1.0f*(v1.x * v2.z - v2.x * v1.z);
    crossVec.z = v1.x * v2.y - v2.x * v1.y;

    crossVec = normaliseVector( crossVec );

    return crossVec;
}

float ThreeDEngine::dotProduct(Vert v1, Vert v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

Vert ThreeDEngine::normaliseVector(Vert& v1) {
    float vecSize;
    Vert retVec = v1;
    vecSize = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    retVec.x /= vecSize;
    retVec.y /= vecSize;
    retVec.z /= vecSize;
    return retVec;
}

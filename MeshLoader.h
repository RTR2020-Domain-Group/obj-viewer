//#pragma once
#ifndef MESHLOADING_H
#define MESHLOADING_H
#include <windows.h>
#include <gl/GL.h>
#include<iostream>
#pragma warning(disable : 4996)

#define POINT_COORDS 3
#define TEXTURE_COORDS 2
#define NORMAL_COORDS 3
#define FACE_TOKENS 4
#define TRIANGE_VERTICES 3
#define QUAD_VERTICES 4
#define BUFFER_SIZE 256

typedef struct Vec2DInt
{
	GLint** pp_arr;
	size_t size;
} vec2dInt_t;

typedef struct Vec2DFloat
{
	GLfloat** pp_arr;
	size_t size;
} vec2dFloat_t;

struct BBox {
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;
};

vec2dInt_t* CreateVec2dInt(void);
vec2dFloat_t* CreateVec2dFloat(void);
void PushBackVec2DInt(vec2dInt_t*, int*);
void PushBackVec2DFloat(vec2dFloat_t* , float*);
void CleanVec2DInt(vec2dInt_t** );
void CleanVec2DFloat(vec2dFloat_t** );
void* CallocWrapper(int , size_t );
void* ReallocWrapper(void* , size_t );


#endif

class MeshLoader {
	public:
		MeshLoader();
		~MeshLoader();
		vec2dFloat_t* m_pVertices;
		vec2dFloat_t* m_pTexture;
		vec2dFloat_t* m_pNormals;
		vec2dInt_t* m_pFaceTriangles;
		vec2dInt_t* m_pFaceTextures;
		vec2dInt_t* m_pFaceNormals;
		vec2dInt_t* m_pFaceQuads;

		void loadMeshData(char*);
		BBox computeBBox(void);

};

#include <windows.h>
#include <gl/GL.h>
#include<stdio.h>
#include<iostream>
#include <string.h>
#include"MeshLoader.h"
char gpLine[BUFFER_SIZE];
FILE* gpMeshFile;
#define MAX_FLOAT_VALUE 3.402823E+38
#define MIN_FLOAT_VALUE 1.175494351E-38
//using namespace MeshLoader;
//Line in a file

vec2dInt_t* CreateVec2dInt(void)
{
	//Function declaration
	void* CallocWrapper(int no, size_t size);

	//code
	return (vec2dInt_t*)CallocWrapper(1, sizeof(vec2dInt_t));
}

vec2dFloat_t* CreateVec2dFloat(void)
{
	//Function declaration
	void* CallocWrapper(int, size_t);

	//code
	return (vec2dFloat_t*)CallocWrapper(1, sizeof(vec2dFloat_t));
}

void PushBackVec2DInt(vec2dInt_t* pVec, int* pArr)
{
	//Function declaration
	void* ReallocWrapper(void* p, size_t newSize);

	pVec->pp_arr = (GLint**)ReallocWrapper(pVec->pp_arr, (pVec->size + 1) * sizeof(int**));
	pVec->size++;
	pVec->pp_arr[pVec->size - 1] = pArr;
}
void PushBackVec2DFloat(vec2dFloat_t* pVec, float* pArr)
{
	//Function declaration
	void* ReallocWrapper(void* p, size_t newSize);

	pVec->pp_arr = (GLfloat**)ReallocWrapper(pVec->pp_arr, (pVec->size + 1) * sizeof(GLfloat**));
	pVec->size++;
	pVec->pp_arr[pVec->size - 1] = pArr;
}

void CleanVec2DInt(vec2dInt_t** ppVec)
{
	vec2dInt_t* pVec = *ppVec;
	for (size_t i = 0; i != pVec->size; i++)
		free(pVec->pp_arr[i]);
	free(pVec);
	*ppVec = NULL;
}

void CleanVec2DFloat(vec2dFloat_t** ppVec)
{
	vec2dFloat_t* pVec = *ppVec;
	for (size_t i = 0; i != pVec->size; i++)
		free(pVec->pp_arr[i]);
	free(pVec);
	*ppVec = NULL;
}

//Calloc Wrapper
void* CallocWrapper(int noOfelements, size_t sizeOfElement)
{
	//function declarations
	void uninitialize();

	void* ptr = calloc(noOfelements, sizeOfElement);
	if (!ptr)
	{
		//fprintf(gpLogFile, "Calloc Error: Unable to allocate memory \n");
		uninitialize();
	}

	return ptr;
}

//Realloc wrapper
void* ReallocWrapper(void* p, size_t newSize)
{
	//function declarations
	void uninitialize();

	void* ptr = realloc(p, newSize);
	if (!ptr)
	{
		//fprintf(gpLogFile, "Unable to allocate memory \n");
		uninitialize();
	}

	return ptr;
}


void MeshLoader::loadMeshData(char* fileName) {
	//Function declarations
	void uninitialize();

	//Create vectors to load data
	vec2dInt_t* CreateVec2dInt(void);
	vec2dFloat_t* CreateVec2dFloat(void);

	//Functions for Pushing data to vecotrs
	void PushBackVec2DInt(vec2dInt_t * pVec, int* pArr);
	void PushBackVec2DFloat(vec2dFloat_t * pVec, float* pArr);

	//Wrapper around calloc
	void* CallocWrapper(int, size_t);
	/*	gpLogFile = NULL;
		if (fopen_s(&gpLogFile, "obj-viewer.log", "w") != 0)
		{
			MessageBox(NULL, TEXT("Cannot open obj-viewer.log file.."), TEXT("Error"), MB_OK | MB_ICONERROR);
			exit(0);
		}
		else
		{
			fprintf(gpLogFile, "==== Application Started ====\n");
		}*/
		//code
	fopen_s(&gpMeshFile, fileName, "r");
	if (!gpMeshFile)
	{
		//fprintf(gpLogFile, "Unable to open Object file: %s \n", fileName);
		uninitialize();
	}

	//Create vectors to load vertex, texrture and normal data
	m_pVertices = CreateVec2dFloat();
	m_pTexture = CreateVec2dFloat();
	m_pNormals = CreateVec2dFloat();

	//Create vectors to hold interger face data
	m_pFaceTriangles = CreateVec2dInt();
	m_pFaceQuads = CreateVec2dInt();
	m_pFaceTextures = CreateVec2dInt();
	m_pFaceNormals = CreateVec2dInt();

	//File seperator strings
	char seperatorSpace[] = " ";
	char sepSlash[] = "/";

	//Token Pointers
	//Character pointer for holding first word in blue
	char* firstToken = NULL;
	char* token = NULL;

	//Array of character
	char* faceTokens[FACE_TOKENS];

	int nrTokens;

	//vertex index
	char* tokenVertexIndex = NULL;

	//texture index
	char* tokenTextureIndex = NULL;

	//Normal index
	char* tokenNormalIndex = NULL;

	//Loading starts
	while (fgets(gpLine, BUFFER_SIZE, gpMeshFile) != NULL)
	{
		firstToken = strtok(gpLine, seperatorSpace);

		//If first token indicates vertex data
		if (strcmp(firstToken, "v") == 0)
		{
			GLfloat* pvecPointCoordinate = (GLfloat*)CallocWrapper(POINT_COORDS, sizeof(GLfloat));

			for (int i = 0; i != POINT_COORDS; i++)
				pvecPointCoordinate[i] = (GLfloat)atof(strtok(NULL, seperatorSpace));

			PushBackVec2DFloat(m_pVertices, pvecPointCoordinate);
		}

		else if (strcmp(firstToken, "vt") == 0)
		{
			GLfloat* pvecTextureCoordinates = (GLfloat*)CallocWrapper(POINT_COORDS, sizeof(GLfloat));

			for (int i = 0; i != TEXTURE_COORDS; i++)
				pvecTextureCoordinates[i] = (GLfloat)atof(strtok(NULL, seperatorSpace));

			PushBackVec2DFloat(m_pTexture, pvecTextureCoordinates);
		}

		else if (strcmp(firstToken, "vn") == 0)
		{
			GLfloat* pvecNormalCoordinates = (GLfloat*)CallocWrapper(NORMAL_COORDS, sizeof(GLfloat));

			for (int i = 0; i != NORMAL_COORDS; i++)
				pvecNormalCoordinates[i] = (GLfloat)atof(strtok(NULL, seperatorSpace));

			PushBackVec2DFloat(m_pNormals, pvecNormalCoordinates);
		}

		else if (strcmp(firstToken, "f") == 0)
		{
			GLint* pvecVertexIndices = (GLint*)CallocWrapper(4, sizeof(GLint));
			GLint* pvecTextureIndices = (GLint*)CallocWrapper(4, sizeof(GLint));
			GLint* pvecNormalIndices = (GLint*)CallocWrapper(4, sizeof(GLint));

			//Initialize all above with
			memset((char*)faceTokens, 0, FACE_TOKENS);

			//Extract the information
			nrTokens = 0;
			while (token = strtok(NULL, seperatorSpace))
			{
				if (strlen(token) < 3)
					break;

				faceTokens[nrTokens] = token;
				nrTokens++;
			}

			//TCHAR wtext[255];
			for (int i = 0; i != nrTokens; i++)
			{
				tokenVertexIndex = strtok(faceTokens[i], sepSlash);
				tokenTextureIndex = strtok(NULL, sepSlash);
				tokenNormalIndex = strtok(NULL, sepSlash);

				//convert to int
				pvecVertexIndices[i] = atoi(tokenVertexIndex);
				pvecTextureIndices[i] = atoi(tokenTextureIndex);
				pvecNormalIndices[i] = atoi(tokenNormalIndex);
			}

			if (nrTokens == 3)
				PushBackVec2DInt(m_pFaceTriangles, pvecVertexIndices);

			//For handling quad based models
			if (nrTokens == 4)
				PushBackVec2DInt(m_pFaceQuads, pvecVertexIndices);

			PushBackVec2DInt(m_pFaceTextures, pvecTextureIndices);
			PushBackVec2DInt(m_pFaceNormals, pvecNormalIndices);
		}

		memset((void*)gpLine, (int)'\0', BUFFER_SIZE);
	}

	//Close meshfile
	//fclose(gpMeshFile);
	gpMeshFile = NULL;
}

BBox MeshLoader::computeBBox(void) {
	BBox meshBBox;
	GLfloat prevMinX = m_pVertices->pp_arr[0][0];
	GLfloat prevMaxX = m_pVertices->pp_arr[0][0];

	GLfloat prevMinY = m_pVertices->pp_arr[0][1];
	GLfloat prevMaxY = m_pVertices->pp_arr[0][1];

	GLfloat prevMinZ = m_pVertices->pp_arr[0][2];
	GLfloat prevMaxZ = m_pVertices->pp_arr[0][2];

	for (int i = 0; i < m_pVertices->size; i++) {
		GLfloat currentVertexX = m_pVertices->pp_arr[i][0];
		GLfloat currentVertexY = m_pVertices->pp_arr[i][1];
		GLfloat currentVertexZ = m_pVertices->pp_arr[i][2];
		if (currentVertexX < prevMinX) {
			prevMinX = currentVertexX;
		}
		if (currentVertexX > prevMaxX) {
			prevMaxX = currentVertexX;
		}

		if (currentVertexY < prevMinY) {
			prevMinY = currentVertexY;
		}
		if (currentVertexY > prevMaxY) {
			prevMaxY = currentVertexY;
		}

		if (currentVertexZ < prevMinZ) {
			prevMinZ = currentVertexZ;
		}
		if (currentVertexZ > prevMaxZ) {
			prevMaxZ = currentVertexZ;
		}

	}
	meshBBox.maxX = prevMaxX;
	meshBBox.minX = prevMinX;
	meshBBox.maxY = prevMaxY;
	meshBBox.minY = prevMinY;
	meshBBox.maxZ = prevMaxZ;
	meshBBox.minZ = prevMinZ;
	return meshBBox;
}
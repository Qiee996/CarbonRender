#ifndef CR_GLOBLE
#define CR_GLOBLE

#define FBXSDK_SHARED
#define BUFFER_OFFSET(offset) ((void *)(offset))
#define CR_VERTATTRIPOS_POS 0
#define CR_VERTATTRIPOS_NOR 1
#define CR_VERTATTRIPOS_TAG 2
#define CR_VERTATTRIPOS_UVS 3
#define CR_VERTATTRIPOS_COL 4
#define FIXEDUPDATE_TIME 0.02f

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <unordered_map>

#include "..\Third\GL\include\glew.h"
#pragma comment(lib, "glew32.lib")
#include "..\Third\GL\include\glut.h"
#pragma comment(lib, "glut32.lib")
#include "..\Third\FBX\include\fbxsdk.h"
#pragma comment(lib, "libfbxsdk.lib")
#include "..\Third\Simple OpenGL Image Library\src\SOIL.h"
#pragma comment(lib, "SOIL.lib")

using namespace std;

inline void SetGLArrayBuffer(GLuint bIndex, GLsizeiptr bSize, const GLvoid* bData, GLuint eSize, GLenum eType, GLuint aPos)
{
	glBindBuffer(GL_ARRAY_BUFFER, bIndex);
	glBufferData(GL_ARRAY_BUFFER, bSize, bData, GL_STATIC_DRAW);
	glVertexAttribPointer(aPos, eSize, eType, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(aPos);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

#endif
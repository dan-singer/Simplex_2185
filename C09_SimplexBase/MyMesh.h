#ifndef MYMESH_H
#define MYMESH_H

#include "Definitions.h"

class MyMesh
{
public:
	GLuint m_shaderProgramId;
	GLuint m_uVAO;
	GLuint m_uVBO;

	std::vector<vector3> m_lVertex;
	std::vector<vector3> m_lVertexPos;
	std::vector<vector3> m_lVertexColor;



	void AddVertexPos(vector3 a_v3Pos);
	void AddVertexColor(vector3 a_v3Color);
	void CompleteMesh();

	void Init();
	void CompileOpenGL3X();
	void Render(matrix4 a_m4Model, matrix4 a_m4View, matrix4 a_m4Projection);

	MyMesh();

	void Release();
	~MyMesh();
};

#endif // !MYMESH_H

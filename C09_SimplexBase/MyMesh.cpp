#include "MyMesh.h"



MyMesh::MyMesh()
{
	Init();
}



void MyMesh::Init()
{
	m_shaderProgramId = LoadShaders("Shaders//Basic.vs", "Shaders//Basic.fs");
	m_uVAO = 0;
	m_uVBO = 0;
}

void MyMesh::AddVertexPos(vector3 a_v3Pos)
{
	m_lVertexPos.push_back(a_v3Pos);
}
void MyMesh::AddVertexColor(vector3 a_v3Color)
{
	m_lVertexColor.push_back(a_v3Color);
}
void MyMesh::CompleteMesh()
{
	for (uint i = 0; i < m_lVertexPos.size(); i++)
	{
		m_lVertex.push_back(m_lVertexPos[i]);
		m_lVertex.push_back(m_lVertexColor[i]);
	}
}

void MyMesh::CompileOpenGL3X()
{
	CompleteMesh();
	glGenVertexArrays(1, &m_uVAO);//Generate vertex array object
	glGenBuffers(1, &m_uVBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_uVAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);//Bind the VBO

	//Generate space for the VBO (vertex count times size of vec3)
	glBufferData(GL_ARRAY_BUFFER, m_lVertex.size() * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);

	//count the attributes
	int attributeCount = 2;

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	glBindVertexArray(0);

}

void MyMesh::Render(matrix4 a_m4Model, matrix4 a_m4View, matrix4 a_m4Projection)
{
	glUseProgram(m_shaderProgramId);
	glBindVertexArray(m_uVAO);
	//read uniforms and send values
	GLuint MVP = glGetUniformLocation(m_shaderProgramId, "MVP");//Model View Projection
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(a_m4Projection * a_m4View * a_m4Model));

	glDrawArrays(GL_TRIANGLES, 0, m_lVertexPos.size());
}


void MyMesh::Release()
{
	if (m_uVBO > 0)
		glDeleteBuffers(1, &m_uVBO);
	if (m_uVAO > 0)
		glDeleteBuffers(1, &m_uVAO);
}

MyMesh::~MyMesh()
{
	Release();
}

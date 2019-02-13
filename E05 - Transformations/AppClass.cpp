#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the map: 0 = no cube, 1 = cube
	m_invaderMap = new unsigned char*[ROWS];
	m_invaderMap[0] = new unsigned char[COLS]{ 0,0,1,0,0,0,0,0,1,0,0 };
	m_invaderMap[1] = new unsigned char[COLS]{ 0,0,0,1,0,0,0,1,0,0,0 };
	m_invaderMap[2] = new unsigned char[COLS]{ 0,0,1,1,1,1,1,1,1,0,0 };
	m_invaderMap[3] = new unsigned char[COLS]{ 0,1,1,0,1,1,1,0,1,1,0 };
	m_invaderMap[4] = new unsigned char[COLS]{ 1,1,1,1,1,1,1,1,1,1,1 };
	m_invaderMap[5] = new unsigned char[COLS]{ 1,0,1,1,1,1,1,1,1,0,1 };
	m_invaderMap[6] = new unsigned char[COLS]{ 1,0,1,0,0,0,0,0,1,0,1 };
	m_invaderMap[7] = new unsigned char[COLS]{ 0,0,0,1,1,0,1,1,0,0,0 };

	// Create a mesh for each 1 in the array
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (m_invaderMap[r][c] == 1) {
				MyMesh* mesh = new MyMesh();
				mesh->GenerateCube(1, vector3(0, 0, 0));
				m_invaderMeshes.push_back(mesh);
			}
		}
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4Model = glm::translate(vector3(-COLS/2, -ROWS/2, 0));

	static vector3 sinOffset(0);
	sinOffset.x += .01;
	sinOffset.y = 5 * sin(sinOffset.x);
	m4Model = glm::translate(m4Model, sinOffset);
	// Render each space invader mesh
	int curMeshIndex = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (m_invaderMap[r][c] == 1) {
				m_invaderMeshes[curMeshIndex]->Render(m4Projection, m4View, glm::translate(m4Model, vector3(c, ROWS - r, 0)));
				curMeshIndex++;
			}
		}
	}
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddGridToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{

	for (int r = 0; r < ROWS; ++r) {
		delete[] m_invaderMap[r];
	}
	delete[] m_invaderMap;

	for (MyMesh* mesh : m_invaderMeshes) {
		SafeDelete(mesh);
	}

	//release GUI
	ShutdownGUI();
}
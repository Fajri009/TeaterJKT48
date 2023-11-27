#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	Cube* cube; 
	Cube* lantai;
	Cube* panggung;
	Cube* layarLedDepan;
	Cube* layarLedBelakang;
	float angle;
	glm::vec3 viewPos;
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void Lantai();
	void Panggung();
	void LayarLED();
	void Kursi(float posX, float posZ);
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};


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
	Cube* tembok;
	Cube* panggung;
	Cube* mic;
	Cube* layarLedDepan;
	Cube* layarLedBelakang;
	Cube* tangkaiKursi;
	Cube* bantalKursi;
	float angle;
	glm::vec3 viewPos;
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	void setupPerspective();
	void setupCamera();
	void setupLighting();
	void Lantai();
	void Tembok();
	void Panggung();
	void Mic();
	void LayarLED();
	void Kursi();
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


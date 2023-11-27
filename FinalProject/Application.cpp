#include "Application.h"

Application::Application()
{
	// angle = 0;
}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
}


void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	//viewPos = glm::vec3(0, 0, 3);
	// glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3(4, 4, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("cube.vert", "cube.frag");
	shader->Init();
	// Create instance of cube
	cube = new Cube(shader);
	cube->Init();
	cube->SetRotation(0, 0, 1, 0);

	lantai = new Cube(shader);
	lantai->Init();
	lantai->SetRotation(0, 0, 1, 0);
	lantai->SetScale(100.0f, 0.01f, 100.0f);

	panggung = new Cube(shader);
	panggung->Init();
	panggung->SetRotation(0, 0, 1, 0);
	panggung->SetScale(13.0f, 1.0f, 6.0f);

	layarLedDepan = new Cube(shader);
	layarLedDepan->Init();
	layarLedDepan->SetRotation(0, 0, 1, 0);
	layarLedDepan->SetScale(4.2f, 2.5f, 0.05f);
	layarLedDepan->SetColor(94, 232, 247);

	layarLedBelakang = new Cube(shader);
	layarLedBelakang->Init();
	layarLedBelakang->SetRotation(0, 0, 1, 0);
	layarLedBelakang->SetScale(4.2f, 2.5f, 1.0f);
	layarLedBelakang->SetColor(0, 0, 0);

	// setup perspective 
	//setupPerspective();
	// setup camera
	//setupCamera();
	InitCamera();
	//setup lighting
	//setupLighting();
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 0.5f) / 1000);
	//cube->SetRotation(angle, 0, 1, 0);

	//angle += (float)((deltaTime * 1.5f) / 1000);
}

void Application::Lantai() {
	lantai->SetColor(139, 69, 19);
	lantai->SetPosition(0, 0, 0);
	lantai->Draw();
}

void Application::Panggung() {
	panggung->SetColor(128, 128, 128);
	panggung->SetPosition(0, 0, 1.7f);
	panggung->Draw();
}

void Application::LayarLED() {
	// Layar LED Tengah
	layarLedDepan->SetPosition(0.0f, 1.75f, 0.13f);
	layarLedDepan->Draw();

	layarLedBelakang->SetPosition(0.0f, 1.75f, -0.4f);
	layarLedBelakang->Draw();

	// Layar LED Kiri
	layarLedDepan->SetPosition(-4.0f, 1.75f, 2.03f);
	layarLedDepan->Draw();

	layarLedBelakang->SetPosition(-4.0f, 1.75f, 1.5f);
	layarLedBelakang->Draw();
	
	// Layar LED Kanan
	layarLedDepan->SetPosition(4.0f, 1.75f, 2.03f);
	layarLedDepan->Draw();

	layarLedBelakang->SetPosition(4.0f, 1.75f, 1.5f);
	layarLedBelakang->Draw();
}

void Application::Kursi(float posX, float posY) {
	// Kaki Kiri Depan
	cube->SetColor(128, 128, 128);
	cube->SetPosition(0.0f, 0.0f, 7.0f);
	cube->SetScale(0.07f, 0.8f, 0.07f);
	cube->Draw();

	// Kaki Kanan Depan
	cube->SetColor(128, 128, 128);
	cube->SetPosition(0.0f, 0.0f, 7.0f);
	cube->SetScale(0.07f, 0.8f, 0.07f);
	cube->Draw();
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(219, 112, 147);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();

	Lantai();

	Panggung();

	LayarLED();

	Kursi(10.f, 10.f);

	glDisable(GL_DEPTH_TEST);
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Application::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Teater JKT48",
		1366, 768,
		false,
		false);
}
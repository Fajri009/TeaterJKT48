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
	glm::vec3 lightPos = glm::vec3(0, 6, 12.5);
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
	lantai->SetScale(200.0f, 0.01f, 200.0f);

	tembok = new Cube(shader);
	tembok->Init();
	tembok->SetRotation(0, 0, 1, 0);
	tembok->SetColor(139, 69, 19);

	panggung = new Cube(shader);
	panggung->Init();
	panggung->SetRotation(0, 0, 1, 0);
	panggung->SetScale(13.0f, 1.0f, 6.0f);
	
	mic = new Cube(shader);
	mic->Init();
	mic->SetRotation(0, 0, 1, 0);

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

	tangkaiKursi = new Cube(shader);
	tangkaiKursi->Init();
	tangkaiKursi->SetRotation(0, 0, 1, 0);
	tangkaiKursi->SetColor(128, 128, 128);

	bantalKursi = new Cube(shader);
	bantalKursi->Init();
	bantalKursi->SetRotation(0, 0, 1, 0);
	bantalKursi->SetColor(178, 34, 34);

	lampuBelakang = new Cube(shader);
	lampuBelakang->Init();
	lampuBelakang->SetRotation(0, 0, 1, 0);
	lampuBelakang->SetColor(0, 0, 0);

	lampuDepan = new Cube(shader);
	lampuDepan->Init();
	lampuDepan->SetRotation(0, 0, 1, 0);

	speaker = new Cube(shader);
	speaker->Init();
	speaker->SetRotation(0, 0, 1, 0);

	InitCamera();
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

void Application::Tembok() {
	// Tembok Kiri
	tembok->SetScale(1.0f, 10.0f, 25.0f);
	tembok->SetPosition(-10, 2.5, 8);
	tembok->Draw();

	// Tembok Kanan
	tembok->SetScale(1.0f, 10.0f, 25.0f);
	tembok->SetPosition(10, 2.5, 8);
	tembok->Draw();
	
	// Tembok Belakang
	tembok->SetScale(20.0f, 10.0f, 1.0f); 
	tembok->SetPosition(0, 2.5, -5); 
	tembok->Draw();

	// Tembok Depan (Kanan)
	tembok->SetScale(8.0f, 10.0f, 1.0f);
	tembok->SetPosition(6.0f, 2.5f, 20.0f);
	tembok->Draw();
	
	// Tembok Depan (Kiri)
	tembok->SetScale(8.0f, 10.0f, 1.0f);
	tembok->SetPosition(-6.0f, 2.5f, 20.0f);
	tembok->Draw();

	// Tembok Depan (Atas)
	tembok->SetScale(4.0f, 4.0f, 1.0f);
	tembok->SetPosition(0.0f, 5.5f, 20.0f);
	tembok->Draw();

	// Atap
	tembok->SetScale(20.0f, 1.0f, 25.0f);
	tembok->SetPosition(0.0f, 7.5f, 8.0f);
	tembok->Draw();
}

void Application::Panggung() {
	panggung->SetColor(128, 128, 128);
	panggung->SetPosition(0, 0, 1.7f);
	panggung->Draw();
}

void Application::Mic() {
	for (int x = -4; x <= 4; x += 4) {
		// Alas
		mic->SetPosition(0 + x, 0.5f, 4);
		mic->SetScale(0.5f, 0.2f, 0.5f);
		mic->SetColor(0, 0, 0);
		mic->Draw();

		// Tangkai
		mic->SetPosition(0 + x, 1.1f, 4);
		mic->SetScale(0.1f, 1, 0.1f);
		mic->SetColor(0, 0, 0);
		mic->Draw();

		// Pegangan Mic
		mic->SetPosition(0 + x, 1.65f, 4);
		mic->SetColor(0, 0, 0);
		mic->SetScale(0.1f, 0.1f, 0.5f);
		mic->Draw();

		// Output Mic
		mic->SetPosition(0 + x, 1.65f, 3.7f);
		mic->SetColor(192, 192, 192);
		mic->SetScale(0.15f, 0.15f, 0.15f);
		mic->Draw();
	}
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

void Application::Lampu() {
	setupLighting();
	for (int a = -5; a <= 5; a += 5) {
		// Tangkai Lampu
		lampuBelakang->SetScale(0.1f, 1.5f, 0.1f);
		lampuBelakang->SetPosition(0.0f + a, 7.0f, 12.5f);
		lampuBelakang->Draw();

		// Lampu Belakang
		lampuBelakang->SetScale(0.8f, 0.8f, 0.5f);
		lampuBelakang->SetPosition(0.0f + a, 5.9f, 12.5f);
		lampuBelakang->Draw();

		for (float y = 0.0f; y <= 0.4f; y += 0.4f) {
			for (float x = 0.0f; x <= 0.4f; x += 0.4f) {
				// Lampu Depan
				lampuDepan->SetScale(0.2f, 0.2f, 0.15f);
				if (a == -5) {
					lampuDepan->SetColor(34, 139, 34);
				}
				else if (a == 0) {
					lampuDepan->SetColor(220, 20, 60);
				}
				else {
					lampuDepan->SetColor(0, 128, 128);
				}
				lampuDepan->SetPosition(0.2f - x + a, 6.1f - y, 12.2f);
				lampuDepan->Draw();
			}
		}
	}
}

void Application::Kursi() {
	for (int x = -6; x <= 6; x+=2) {
		int a = 0;
		int diffRow = 2;

		for (int z = 0; z <= 8; z +=2) {
			if (diffRow == z) {
				a = 1;
				diffRow += 4;
			}
			else {
				a = 0;
			}

			// Kaki Kiri Depan
			tangkaiKursi->SetPosition(-0.25 + x + a, 0, 8 + z);
			tangkaiKursi->SetScale(0.07f, 0.8f, 0.07f);
			tangkaiKursi->Draw();

			// Kaki Kanan Depan
			tangkaiKursi->SetPosition(0.25 + x + a, 0, 8 + z);
			tangkaiKursi->SetScale(0.07f, 0.8f, 0.07f);
			tangkaiKursi->Draw();

			// Kaki Kiri Belakang
			tangkaiKursi->SetPosition(-0.25 + x + a, 0, 8.5 + z);
			tangkaiKursi->SetScale(0.07f, 0.8f, 0.07f);
			tangkaiKursi->Draw();

			// Kaki Kanan Belakang
			tangkaiKursi->SetPosition(0.25 + x + a, 0, 8.5 + z);
			tangkaiKursi->SetScale(0.07f, 0.8f, 0.07f);
			tangkaiKursi->Draw();

			// Bantal Bawah
			bantalKursi->SetPosition(0 + x + a, 0.45f, 8.25f + z);
			bantalKursi->SetScale(0.57, 0.1, 0.57);
			bantalKursi->Draw();

			// Tangkai Kiri 
			tangkaiKursi->SetPosition(-0.25f + x + a, 0.75f, 8.5f + z);
			tangkaiKursi->SetScale(0.07f, 0.5f, 0.07f);
			tangkaiKursi->Draw();

			// Tangkai Kanan
			tangkaiKursi->SetPosition(0.25f + x + a, 0.75f, 8.5f + z);
			tangkaiKursi->SetScale(0.07f, 0.5f, 0.07f);
			tangkaiKursi->Draw();

			// Tangkai Atas
			tangkaiKursi->SetPosition(0 + x + a, 1.03f, 8.5f + z);
			tangkaiKursi->SetScale(0.57f, 0.07f, 0.07f);
			tangkaiKursi->Draw();

			// Bantal Belakang
			bantalKursi->SetPosition(0 + x + a, 0.77f, 8.5f + z);
			bantalKursi->SetScale(0.43f, 0.45f, 0.07f);
			bantalKursi->Draw();
		}
	}
}

void Application::Speaker() {
	for (int a = -5; a <= 3; a += 8) {
		int kiri = 0;
		int kanan = 0;
		for (int x = 0; x <= 2; x += 2) {
			// Tangkai Speaker
			speaker->SetScale(0.1f, 1.5f, 0.1f);
			speaker->SetPosition(a + x, 7.0f, 1.0f);
			speaker->SetColor(0, 0, 0);
			speaker->Draw();

			if (x == 0) {
				kiri = a + x;
			}
			else {
				kanan = a + x;
			}
		}
		// Speaker 
		speaker->SetScale(3.0f, 1.0f, 0.7f);
		speaker->SetPosition((kiri + kanan) / 2, 6.0f, 1.0f);
		speaker->SetColor(128, 128, 128);
		speaker->Draw();

		for (float b = a + 0.2; b <= -3.3f; b += 1.5f) {
			// Output Speaker
			speaker->SetScale(0.7f, 0.5f, 0.1f);
			speaker->SetPosition(b, 6.0f, 1.4f);
			speaker->SetColor(0, 0, 0);
			speaker->Draw();
		}


		// Output Speaker
		speaker->SetScale(0.7f, 0.5f, 0.1f);
		speaker->SetPosition(4.8, 6.0f, 1.4f);
		speaker->SetColor(0, 0, 0);
		speaker->Draw();

		// Output Speaker
		speaker->SetScale(0.7f, 0.5f, 0.1f);
		speaker->SetPosition(3.3, 6.0f, 1.4f);
		speaker->SetColor(0, 0, 0);
		speaker->Draw();
	}
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(94, 232, 247);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting

	Lantai();

	Tembok();

	Panggung();

	Mic();

	LayarLED();

	Kursi();

	Lampu();

	Speaker();

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
	posCamY = 2.0f;
	posCamZ = 25.0f;
	viewCamX = 0.0f;
	viewCamY = 0.0f;
	viewCamZ = 2.0f;
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
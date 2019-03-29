#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Core/GameObject.h"
#include "Rendering/Camera.h"
#include "Rendering/Light.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/SimpleShader.h"
#include "Rendering/Vertex.h"

#include "DXCore.h"

//using namespace Colliders;
using namespace ScratchEngine::Rendering;

class Game : public DXCore
{
public:
	Game(HINSTANCE hInstance, char* name);
	~Game();

	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	void OnMouseDown(WPARAM buttonState, int x, int y);
	void OnMouseUp(WPARAM buttonState, int x, int y);
	void OnMouseMove(WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta, int x, int y);

private:
	void LoadShaders();
	void CreateMatrces();
	void CreateBasicGeometry();

	POINT prevMousePos;

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	//XMFLOAT4X4 worldMatrix;
	//XMFLOAT4X4 viewMatrix;
	//XMFLOAT4X4 projectionMatrix;

	Mesh* mesh;
	Mesh* mesh1;

	//CollisionManager* physics;

	//std::vector<Entity*> entityVector;

	Material* simpleMaterial;

	DirectionalLight* directionalLight;
	GameObject* camera;
	GameObject* go1;
	GameObject* go2;

	//PointLight pointLight;
};
#include "../Animation/Animator.h"
#include "../Rendering/Model.h"
#include "../Rendering/RenderingEngine.h"

#include "Game.h"
#include "Renderer.h"
#include "Scene.h"
#include "Transform.h"

using namespace ScratchEngine::Rendering;


ScratchEngine::Renderer::Renderer()
{
	this->mesh = nullptr;
	this->material = nullptr;
	this->anim = nullptr;
	this->model = nullptr;
	this->renderable = null_index;
}

ScratchEngine::Renderer::Renderer(Material* material, Mesh* mesh)
{
	this->mesh = mesh;
	this->material = material;
	this->renderable = null_index;
	this->anim = nullptr;
	this->model = nullptr; 

	//this->slotIndex = null_index;
	//this->slot = nullptr;

	Scene::GetCurrentScene()->AddRenderer(this);
}

ScratchEngine::Renderer::Renderer(Material* material, Rendering::Model* model)
{
	this->model = model;
	this->mesh = model->mesh;
	this->material = material;
	this->renderable = null_index;
	this->anim = model->anim;

	//this->slotIndex = null_index;
	//this->slot = nullptr;

	Scene::GetCurrentScene()->AddRenderer(this);
}

ScratchEngine::Renderer::~Renderer()
{
	Scene::GetCurrentScene()->RemoveRenderer(this);
}

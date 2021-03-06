#include "../Rendering/RenderingEngine.h"

#include "GameObject.h"
#include "Light.h"
#include "Scene.h"


ScratchEngine::Light::Light(LightType type) : Light(type, XMVectorSet(0.1f, 0.1f, 0.1f, 1.0f), XMVectorSet(0.6f, 0.6f, 0.6f, 1.0f))
{
}

ScratchEngine::Light::Light(LightType type, XMVECTOR ambientColor, XMVECTOR diffuseColor)
{
	this->type = type;
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;

	this->next = nullptr;
	this->previous = nullptr;

	Scene::GetCurrentScene()->AddLight(this);
}

ScratchEngine::Light::~Light()
{
	Scene::GetCurrentScene()->RemoveLight(this);
}


ScratchEngine::DirectionalLight::DirectionalLight() : Light(LightType::DIRECTIONAL)
{
}

ScratchEngine::DirectionalLight::DirectionalLight(XMVECTOR ambientColor, XMVECTOR diffuseColor) : Light(LightType::DIRECTIONAL, ambientColor, diffuseColor)
{
}


ScratchEngine::PointLight::PointLight() : Light(LightType::POINT)
{
}

ScratchEngine::PointLight::PointLight(XMVECTOR ambientColor, XMVECTOR diffuseColor) : Light(LightType::POINT, ambientColor, diffuseColor)
{
}


ScratchEngine::SpotLight::SpotLight() : Light(LightType::SPOT)
{
	this->angle = 30.0f;
}

ScratchEngine::SpotLight::SpotLight(XMVECTOR ambientColor, XMVECTOR diffuseColor, f32 angle) : Light(LightType::SPOT, ambientColor, diffuseColor)
{
	this->angle = angle;
}

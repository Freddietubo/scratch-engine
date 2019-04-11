#include <cstdlib>

#include "../Core/GameObject.h"

#include "Collider.h"
#include "PhysicsEngine.h"

using namespace DirectX;
using namespace ScratchEngine::Physics;


f32 collisionCheckBack = 0.00f;

bool ScratchEngine::Collider::IsOverlappingWith(Collider* other)
{
	switch (type)
	{
	case ScratchEngine::Physics::AABB:
		break;


	case ScratchEngine::Physics::OBB:
		switch (other->GetType())
		{
		case ScratchEngine::Physics::AABB:
			break;


		case ScratchEngine::Physics::OBB:
			return ScratchEngine::Physics::TestOverlap(reinterpret_cast<OrientedBoundingBox*>(GetBoundingVolume()), reinterpret_cast<OrientedBoundingBox*>(other->GetBoundingVolume()));
			break;


		case ScratchEngine::Physics::Sphere:
			return ScratchEngine::Physics::TestOverlap(reinterpret_cast<OrientedBoundingBox*>(GetBoundingVolume()), reinterpret_cast<BoundingSphere*>(other->GetBoundingVolume()));
			break;
		}
		break;


	case ScratchEngine::Physics::Sphere:
		switch (other->GetType())
		{
		case ScratchEngine::Physics::AABB:
			break;


		case ScratchEngine::Physics::OBB:
			return ScratchEngine::Physics::TestOverlap(reinterpret_cast<OrientedBoundingBox*>(GetBoundingVolume()), reinterpret_cast<BoundingSphere*>(other->GetBoundingVolume()));
			break;


		case ScratchEngine::Physics::Sphere:
			return ScratchEngine::Physics::TestOverlap(reinterpret_cast<BoundingSphere*>(GetBoundingVolume()), reinterpret_cast<BoundingSphere*>(other->GetBoundingVolume()));
			break;
		}
		break;
	}

	throw "NOT IMPLEMENTED";
}

ScratchEngine::Collider::Collider()
{
	this->next = nullptr;
	this->previous = nullptr;

	this->boundingVolume = nullptr;

	PhysicsEngine::GetSingleton()->AddCollider(this);
}

ScratchEngine::Collider::Collider(BoundingVolumeType type)
{
	this->next = nullptr;
	this->previous = nullptr;

	this->type = type;
	this->boundingVolume = nullptr;

	PhysicsEngine::GetSingleton()->AddCollider(this);
}

ScratchEngine::Collider::~Collider()
{
	PhysicsEngine::GetSingleton()->RemoveCollider(this);
}

BoundingVolumeType ScratchEngine::Collider::GetType()
{
	return type;
}

BoundingVolume* ScratchEngine::Collider::GetBoundingVolume()
{
	return boundingVolume;
}


ScratchEngine::BoxCollider::BoxCollider() : BoxCollider({1, 1, 1})
{
}

ScratchEngine::BoxCollider::BoxCollider(XMVECTOR size) : Collider(OBB)
{
	this->size = size;
}

ScratchEngine::BoxCollider::~BoxCollider()
{
}


ScratchEngine::SphereCollider::SphereCollider(f32 radius)
{
	this->radius = radius;
}

ScratchEngine::SphereCollider::~SphereCollider()
{
}

//
//bool isUnique(std::vector<XMVECTOR> points, XMVECTOR test)
//{
//	bool add = true;
//	for (int i = 0; i < points.size(); i++) {
//		XMVECTOR diff = points[i] - test;
//		if (abs(diff.m128_f32[0]) + abs(diff.m128_f32[1]) + abs(diff.m128_f32[2]) < 0.1f) {
//			add = false;
//		}
//	}
//	return add;
//}
//XMVECTOR getPlaneNormal(BoxCollider * Entity, XMVECTOR point)
//{
//	float x = point.m128_f32[0];
//	float y = point.m128_f32[1];
//	float z = point.m128_f32[2];
//	XMVECTOR ret = { 0,0,0 };
//
//	for (int i = 0; i < Entity->planes.size(); i++) {
//		XMVECTOR plane = Entity->planes[i];
//		float A = plane.m128_f32[0];
//		float B = plane.m128_f32[1];
//		float C = plane.m128_f32[2];
//		float D = plane.m128_f32[3];
//		if (abs(A * x + B * y + C * z + D) <= 0.1f) {
//				ret = plane;
//		}
//	}
//
//	/*if (XMVector3Equal(ret, { 0,0,0 })) {
//		printf("6 plane! \n");
//		for (int i = 0; i < Entity->planes.size(); i++) {
//			XMVECTOR plane = Entity->planes[i];
//			float A = plane.m128_f32[0];
//			float B = plane.m128_f32[1];
//			float C = plane.m128_f32[2];
//			float D = plane.m128_f32[3];
//			printf("point:  %f,  %f,  %f \n", point.m128_f32[0], point.m128_f32[1], point.m128_f32[2]);
//			printf("plane:  %f,  %f,  %f \n", plane.m128_f32[0], plane.m128_f32[1], plane.m128_f32[2]);
//			printf("%f \n", abs(A * x + B * y + C * z + D));
//		}
//	}*/
//	return ret;
//}
//XMVECTOR getLineIntersection(XMVECTOR start, XMVECTOR end, std::tuple<XMVECTOR, XMVECTOR, XMVECTOR, XMVECTOR> planeVertetices, 
//	XMFLOAT3 Max, XMFLOAT3 Min)
//{
//	std::vector<XMVECTOR> planeVerteticesVec;
//	planeVerteticesVec.push_back(std::get<0>(planeVertetices));
//	planeVerteticesVec.push_back(std::get<1>(planeVertetices));
//	planeVerteticesVec.push_back(std::get<2>(planeVertetices));
//	planeVerteticesVec.push_back(std::get<3>(planeVertetices));
//	XMVECTOR v1 = end - start;
//	XMVECTOR ip = { 0,0,0 };
//	int counter = 0;
//	for (int i = 0; i < planeVerteticesVec.size()-1; i++)
//	{
//		XMVECTOR A = planeVerteticesVec[i];
//		for (int j = i + 1; j < planeVerteticesVec.size(); j++)
//		{
//			XMVECTOR B = planeVerteticesVec[j];
//			XMVECTOR v2 = XMVector3Normalize(B - A);
//			//printf("v1:  %f,  %f,  %f \n", v1.m128_f32[0], v1.m128_f32[1], v1.m128_f32[2]);
//			//printf("v2:  %f,  %f,  %f \n", v2.m128_f32[0], v2.m128_f32[1], v2.m128_f32[2]);
//			if (abs(XMVector3Dot(v1, v2).m128_f32[0]) == 1)
//			{
//				// ����ƽ��
//				//printf("line parallel \n ");
//				continue;
//			}
//
//			XMVECTOR diag = XMVector3Normalize(A - start);
//			XMVECTOR vecS1 = XMVector3Cross(v1, v2);            // �������1
//			XMVECTOR vecS2 = XMVector3Cross(diag, v2); // �������2
//			float num = XMVector3Dot(diag, vecS1).m128_f32[0];
//
//			// �ж�����ֱ���Ƿ���
//			//if (num >= 1E-05f || num <= -1E-05f)
//			//{
//			//	continue;
//			//}
//
//			// ���������ֵ�����õ������Ϊ����������������߸���
//			float num2 = (XMVector3Dot(vecS2, vecS1) / XMVector3LengthSq(vecS1)).m128_f32[0];
//			XMVECTOR point = start + v1 * num2;
//				
//			point = XMVectorClamp(point, { Min.x,Min.y,Min.z }, { Max.x,Max.y,Max.z });
//			ip += point;
//			counter++;
//			//if (point.m128_f32[0] <= Max.x && point.m128_f32[0] >= Min.x &&
//			//	point.m128_f32[1] <= Max.y && point.m128_f32[1] >= Min.y &&
//			//	point.m128_f32[2] <= Max.z && point.m128_f32[2] >= Min.z) {
//			
//			//	printf("add!\n");
//			//}
//			//else {
//			//	printf("out of bound!\n");
//			//}
//			
//		}
//	}
//	if (counter == 0) {
//		return { NAN,NAN,NAN };
//	}
//	XMVECTOR ret = ip / (float)counter;
//	return ret;
//}

#include "Scene.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	//CollisionDetection()

	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->LateUpdate(deltaTime);
	}

	//Delete gameobjects that are marked to be deleted
	for (auto& object : m_objects)
	{
		if (object == nullptr) continue;
		if (object.get()->IsRemoveGameObjectTrue())
		{
			//object.get()->RemoveAllComponent();
			m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
		}
	}
}


void Scene::FixedUpdate(float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}


void Scene::CollisionDetection()
{
	// Iterate over all pairs of objects that could potentially collide
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		auto* collisionComponent1 = m_objects[i]->GetComponent<CollisionComponent>();
		if (!collisionComponent1)
			continue;

		for (size_t j = i + 1; j < m_objects.size(); ++j)
		{
			auto* collisionComponent2 = m_objects[j]->GetComponent<CollisionComponent>();
			if (!collisionComponent2)
				continue;

			//ToDo
			//add check if object 1 is close to object 2 otherwise don't test intersects

			// Check for collision between the two collision components
			if (collisionComponent1->Intersects(*collisionComponent2))
			{
				//std::cout << "Collisonnnn";
				// Handle the collision;
				//HandleCollision(collisionComponent1, collisionComponent2);
			}
			if (collisionComponent2->Intersects(*collisionComponent1))
			{
				//std::cout << "Collisonnnn";
				// Handle the collision;
				//HandleCollision(collisionComponent1, collisionComponent2);
			}
		}
	}
}

std::vector<GameObject*> dae::Scene::GetGameObjectsWithTag(std::string tag)
{
	std::vector<GameObject*> gameobjectsWithTag;

	for (const auto& object : m_objects)
	{
		if (object->GetTag() == tag)
			gameobjectsWithTag.emplace_back(object.get());
	}

	return gameobjectsWithTag;
}

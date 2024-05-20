#include "SceneManager.h"
#include <iostream>

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::LateUpdate(float fixedTimeStep)
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::CollisionDetection()
{
	for (const auto& scene : m_scenes)
	{
		scene->CollisionDetection();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(std::move(scene));
	return *m_scenes[m_scenes.size() - 1];
}

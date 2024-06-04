#include "SceneManager.h"
#include <algorithm>
#include <iostream>

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_ActiveScenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float fixedTimeStep)
{
	for (auto& scene : m_ActiveScenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::LateUpdate(float fixedTimeStep)
{
	for (auto& scene : m_ActiveScenes)
	{
		scene->LateUpdate(fixedTimeStep);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_ActiveScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::CollisionDetection()
{
	for (const auto& scene : m_ActiveScenes)
	{
		scene->CollisionDetection();
	}
}

dae::Scene* dae::SceneManager::GetSceneByName(std::string name)
{
	for (const auto& scene : m_ActiveScenes)
	{
		if (scene->m_name == name)
			return scene.get();
	}

	return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene(name));
	m_scenes.emplace_back(std::move(scene));
	return *m_scenes[m_scenes.size() - 1];
}

dae::Scene& dae::SceneManager::LoadScene(const std::string& name)
{
	for (const auto& scene : m_scenes)
	{
		if (scene->m_name == name)
		{
			m_ActiveScenes.push_back(scene.get());
			return *scene;
		}
	}
	throw std::runtime_error("Scene not found");
}
void dae::SceneManager::UnloadScene(const std::string& name)
{
	auto it = std::remove_if(m_ActiveScenes.begin(), m_ActiveScenes.end(),
		[&name](Scene* scene) {
			return scene->m_name == name;
		});

	if (it != m_ActiveScenes.end())
	{
		m_ActiveScenes.erase(it, m_ActiveScenes.end());
	}
}

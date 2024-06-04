#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"
#include "GameObject.h"
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		Scene& LoadScene(const std::string& name);
		void UnloadScene(const std::string& name);

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render();

		void CollisionDetection();

		Scene* GetSceneByName(std::string name);
		std::vector<Scene*> GetActiveScenes();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes;
		std::vector<Scene*> m_ActiveScenes;
	};
}

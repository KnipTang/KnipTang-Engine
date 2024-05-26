#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend class SceneManager;
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		void CollisionDetection();

		std::vector<GameObject*> GetGameObjectsWithTag(std::string tag);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 


		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}

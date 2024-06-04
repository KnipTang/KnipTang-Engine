#include "Wall.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

Wall::Wall(int posX, int posY)
{
	m_Actor = std::make_unique<dae::GameObject>();

	m_Actor.get()->AddComponent(new dae::RenderComponent(m_Actor.get()));
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(708, 0, 16, 16);
	m_Actor.get()->SetGameObjectPosition(static_cast<float>(posX), static_cast<float>(posY));
	m_Actor.get()->AddComponent(new dae::CollisionComponent(m_Actor.get(), 16, 16));

	m_Actor.get()->SetLayer("Wall");
}

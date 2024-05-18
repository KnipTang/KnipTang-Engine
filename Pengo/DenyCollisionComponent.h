#pragma once
#include <Component.h>
#include "glm/glm.hpp"
class BlockCollisionCheckComponent : public dae::Component
{
public:
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	bool CheckBlockCollision();
	void SetDirection(glm::vec3 direction) { m_Direction = direction; };
	void SetHitBlock(bool value) 
	{ m_HitBlock = value; };

	BlockCollisionCheckComponent(dae::GameObject* gameObject) : dae::Component(gameObject) { m_HitBlock = false; };
	virtual ~BlockCollisionCheckComponent() { }
	BlockCollisionCheckComponent(const BlockCollisionCheckComponent& other) = delete;
	BlockCollisionCheckComponent(BlockCollisionCheckComponent&& other) = delete;
	BlockCollisionCheckComponent& operator=(const BlockCollisionCheckComponent& other) = delete;
	BlockCollisionCheckComponent& operator=(BlockCollisionCheckComponent&& other) = delete;
private:
	bool m_HitBlock;
	glm::vec3 m_Direction;

	bool m_Testing;

	glm::vec3 m_StartPos;
};


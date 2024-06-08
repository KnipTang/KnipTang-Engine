#pragma once
#include <string>
#include <vector>
#include <memory>
#include <glm/fwd.hpp>
#include "GameObject.h"
class Level
{
public:
	Level(std::string filePath);
	~Level(){}

	std::vector<std::unique_ptr<dae::GameObject>> LoadLevel();


	Level(const Level& other) = delete;
	Level(Level&& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) = delete;
private:
	void HandleLine(std::string line);
	void HandleElement(std::string element);
	void PlaceWall();
	void PlacePlayer();
	void PlacePlayer2();
	void PlaceHardWall();
	void PlaceEnemyWall();

	void Player1Bindings(dae::GameObject* player);
	void Player2Bindings(dae::GameObject* player);

	int m_Element = 16;
	int m_MapBorder = 8;

	int m_CurrentRow = 0;
	int m_CurrentColum = 0;

	float m_PosX;
	float m_PosY;

	std::vector<std::unique_ptr<dae::GameObject>> m_GameObjects;

	std::string m_FilePath;
};


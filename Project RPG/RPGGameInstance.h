#pragma once
#include <memory>
#include <vector>
#include "PathPoint.h"
class RPGGameInstance {
private:
	static std::shared_ptr<RPGGameInstance> Instance;

public:
	static void Initalize();
	static std::shared_ptr<RPGGameInstance>Get();
	static void ShutDown();

public:
	void GameStart();

private:
	void LoadMap();
	void Refresh();
	void Move();
	void Shop();

	std::shared_ptr<PathPoint> MakePathPoint(EPathPointType type);
	PlayerState Player;
	std::vector<std::shared_ptr<PathPoint>> Map;
};

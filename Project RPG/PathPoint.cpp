#include "PathPoint.h"
#include <iostream>

SlimeProperty::SlimeProperty(int _Health, int _Attack, int _Defence, int _Experience) :
	Health(_Health),
	Attack(_Attack),
	Defence(_Defence),
	Experience(_Experience)
{
}

PlayerState::PlayerState() :
	Health(200),
	Attack(10),
	Defence(10),
	FreeExperience(0),
	Position(-1)
{
}

void PathPoint::Draw()
{
	switch (Type)
	{
	case EPathPointType::HealthBottle:
		std::cout << "\tH";
		break;
	case EPathPointType::StrengthGem:
		std::cout << "\t��";
		break;
	case EPathPointType::DefenceGem:
		std::cout << "\t��";
		break;
	case EPathPointType::ExperienceBottle:
		std::cout << "\t��";
		break;
	case EPathPointType::Slime:
		std::cout << "\t��";
		break;
	case EPathPointType::BigSlime:
		std::cout << "\t��";
		break;
	case EPathPointType::GiantSlime:
		std::cout << "\t��";
		break;
	case EPathPointType::SlimeImp:
		std::cout << "\tI";
		break;
	case EPathPointType::SlimeDevil:
		std::cout << "\t��";
		break;
	case EPathPointType::EliteSlime:
		std::cout << "\t��";
		break;
	case EPathPointType::SlimeKing:
		std::cout << "\t�ޡ�";
		break;
	default:
		break;
	}
}

PathPoint::PathPoint(EPathPointType _Type) :
	Type(_Type)
{
}

std::unordered_map<int, SlimeProperty> MonsterPoint::SlimeProperties;
MonsterPoint::MonsterPoint(EPathPointType _Type) :
	PathPoint(_Type)
{
}

void MonsterPoint::StepOn(PlayerState & Player)
{
	if (SlimeProperties.empty()) {
		using SlimeType = std::unordered_map<int, SlimeProperty>::value_type;
		SlimeProperties.insert(SlimeType(int(EPathPointType::Slime),SlimeProperty(20,15,3, 10)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::BigSlime), SlimeProperty(40, 20, 8, 20)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::GiantSlime), SlimeProperty(70, 30, 17, 30)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::SlimeImp), SlimeProperty(100, 35, 25, 40)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::SlimeDevil), SlimeProperty(200, 50, 38, 50)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::EliteSlime), SlimeProperty(350, 70, 56, 100)));
		SlimeProperties.insert(SlimeType(int(EPathPointType::SlimeKing), SlimeProperty(1000, 100, 100, 10000)));
	}
	SlimeProperty TempSlime = SlimeProperties.at(int(Type));
	if (!(Player.Attack > TempSlime.Defence))
		throw std::string("��δ�ܻ���ʷ��ķ�ķ���");
	if (!(Player.Defence < TempSlime.Attack)) {
		std::cout << "ʷ��ķ�޷���������˺�" <<std::endl;
		Player.FreeExperience += TempSlime.Experience;
		if (TempSlime.Experience == 10000)
			throw std::string("������ʷ��ķ������Ӯ��");
		std::cout << "�����" << TempSlime.Experience << "�㾭��" << std::endl;
		return;
	}
	while (1)
	{
		TempSlime.Health -= (Player.Attack - TempSlime.Defence);
		std::cout << "��ʷ��ķ�����" << (Player.Attack - TempSlime.Defence) << "���˺���ʷ��ķ��ʣ��" << TempSlime.Health << "������" << std::endl;
		if (!(TempSlime.Health > 0)) {
			Player.FreeExperience += TempSlime.Experience;
			if (TempSlime.Experience == 10000)
				throw std::string("������ʷ��ķ������Ӯ��");
			std::cout << "������ʷ��ķ�������" << TempSlime.Experience << "�㾭��" << std::endl;
			return;
		}
		Player.Health -= (TempSlime.Attack - Player.Defence);
		std::cout << "�ܵ���" << (TempSlime.Attack - Player.Defence) << "���˺����㻹ʣ��" << Player.Health << "������" << std::endl;
		if (!(Player.Health > 0)) {
			throw("������");
		}
		system("timeout 1 >nul");
	}
}

TreasurePoint::TreasurePoint(EPathPointType _Type) :
	PathPoint(_Type)
{
}

void TreasurePoint::StepOn(PlayerState & Player)
{
	switch (Type)
	{
	case EPathPointType::HealthBottle:
		Player.Health += 50;
		std::cout << "��������ҩˮ������+50" << std::endl;
		break;
	case EPathPointType::StrengthGem:
		Player.Attack += 10;
		std::cout << "����������ʯ������+10" << std::endl;
		break;
	case EPathPointType::DefenceGem:
		Player.Defence += 10;
		std::cout << "���˷�����ʯ������+10" << std::endl;
		break;
	case EPathPointType::ExperienceBottle:
		Player.FreeExperience += 50;
		std::cout << "���˾���ҩˮ������+50" << std::endl;
		break;
	default:
		break;
	}
}

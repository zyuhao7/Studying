#include <iostream>
#include <map>
#include <vector>
using namespace std;
// 2025-7-5
// ������ģʽ
/*
����		��һ�����Ӷ���Ĺ��������ı�ʾ���룬ʹͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
�������	Builder�������ߣ���ConcreteBuilder�����幹���ߣ���Director��ָ���ߣ���Product����Ʒ��
���ó���	���󹹽����̸��ӡ��в��裬�����߼��ɸ��õ�����ɱ�

	����:
	���ý������̣�CreateMaze��
	��ͬ�� Builder ���Դ�����ͬ���� Maze��ħ����ը���ȣ�
	�ͻ��˴�������֪�����幹��ϸ��

	
	��������	һ�������ʵ�������ֲ�Ʒ	MazeGame �����õ�	����ֻ���� һ�� ��Ʒ��Builder ����װ�������
	���󹤳�	������صĶ�����	MazeFactory �汾�г���	    ���󹤳�һ���������������ǽ���š����䣩��Builder ���𲽹���һ������
	ԭ��ģʽ	��¡���ж���	�����ڸ��� Maze ģ��	        ԭ�͹�ע���ƣ�Builder ��ע��װ˳���ϸ��
	���ģʽ	��������ϳ���״�ṹ	Maze Ҳ�������ʵ�֣�����+��+ǽ��	������Ͻṹ�������𹹽����̣�Builder �ǹ�����
	ָ���ߣ�Director��	���ƽ���˳��	MazeGame ����ָ����	Builder �ṩ�ӿڣ�ָ���߿��ƹ���

*/

enum Direction { North, South, East, West };

class MapSite {
public:
	virtual void Enter() = 0;
	virtual ~MapSite() = default;
};

class Room : public MapSite {
public:
	Room(int roomNo) : roomNumber(roomNo) {}

	void SetSide(Direction dir, MapSite* site) {
		sides[dir] = site;
	}

	void Enter() override {
		std::cout << "You entered Room " << roomNumber << std::endl;
	}

	int GetRoomNumber() const { return roomNumber; }

private:
	int roomNumber;
	std::map<Direction, MapSite*> sides;
};

class Wall : public MapSite {
public:
	void Enter() override {
		std::cout << "You ran into a wall." << std::endl;
	}
};

class Door : public MapSite {
public:
	Door(Room* r1, Room* r2) : room1(r1), room2(r2), isOpen(false) {}

	void Enter() override {
		if (isOpen)
			std::cout << "You passed through the door." << std::endl;
		else
			std::cout << "The door is closed." << std::endl;
	}

	void SetOpen(bool open) { isOpen = open; }

private:
	Room* room1;
	Room* room2;
	bool isOpen;
};

//  Maze ��: ���伯��
class Maze
{
public:
	void AddRoom(Room* room)
	{
		rooms.push_back(room);
	}
	Room* GetRoom(int i)
	{
		return rooms[i];
	}
private:
	std::vector<Room*> rooms;
};

// MazeBuilder ������
class MazeBuilder
{
public:
	virtual void BuildMaze() = 0;
	virtual void BuildRoom(int room) = 0;
	virtual void BuildDoor(int room1, int room2) = 0;
	virtual Maze* GetMaze() = 0;
	virtual ~MazeBuilder() = default;
};

// ���幹����: StandardMazeBuilder
class StandardMazeBuilder : public MazeBuilder
{
private:
	Maze* maze;
	std::map<int, Room*> rooms;

public:
	StandardMazeBuilder()
		:maze(new Maze())
	{
	}

	void BuildMaze() override {/* ����һ�� ���Թ� */ }
	void BuildRoom(int roomNo) override
	{
		Room* room = new Room(roomNo);
		room->SetSide(North, new Wall());
		room->SetSide(South, new Wall());
		room->SetSide(East, new Wall());
		room->SetSide(West, new Wall());
		rooms[roomNo] = room;
		maze->AddRoom(room);
	}

	void BuildDoor(int r1, int r2) override
	{
		Room* room1 = rooms[r1];
		Room* room2 = rooms[r2];
		Door* door = new Door(room1, room2);

		room1->SetSide(East, door);
		room2->SetSide(West, door);
	}

	Maze* GetMaze() override {
		return maze;
	}
};

class MazeGame {
public:
	Maze* CreateMaze(MazeBuilder& builder) {
		builder.BuildMaze();
		builder.BuildRoom(0);
		builder.BuildRoom(1);
		builder.BuildDoor(0, 1);
		return builder.GetMaze();
	}
};


//int main() {
//	StandardMazeBuilder builder;
//	MazeGame game;
//	Maze* maze = game.CreateMaze(builder);
//
//	Room* room0 = maze->GetRoom(0);
//	Room* room1 = maze->GetRoom(1);
//
//	room0->Enter();
//	room1->Enter();
//
//	return 0;
//}
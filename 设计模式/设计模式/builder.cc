#include <iostream>
#include <map>
#include <vector>
using namespace std;
// 2025-7-5
// 建造者模式
/*
定义		将一个复杂对象的构建与它的表示分离，使同样的构建过程可以创建不同的表示。
核心组成	Builder（构建者）、ConcreteBuilder（具体构建者）、Director（指挥者）、Product（产品）
适用场景	对象构建过程复杂、有步骤，构造逻辑可复用但结果可变

	优势:
	复用建造流程（CreateMaze）
	不同的 Builder 可以创建不同风格的 Maze（魔法、炸弹等）
	客户端代码无需知道具体构造细节

	
	工厂方法	一个类决定实例化哪种产品	MazeGame 可能用到	工厂只生产 一个 产品，Builder 逐步组装多个部件
	抽象工厂	创建相关的对象族	MazeFactory 版本中出现	    抽象工厂一次性生产多个对象（墙、门、房间），Builder 是逐步构建一个对象
	原型模式	克隆已有对象	可用于复制 Maze 模板	        原型关注复制，Builder 关注组装顺序和细节
	组合模式	将对象组合成树状结构	Maze 也可用组合实现（房间+门+墙）	可以组合结构但不负责构建过程，Builder 是构建器
	指挥者（Director）	控制建造顺序	MazeGame 就是指挥者	Builder 提供接口，指挥者控制过程

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

//  Maze 类: 房间集合
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

// MazeBuilder 抽象类
class MazeBuilder
{
public:
	virtual void BuildMaze() = 0;
	virtual void BuildRoom(int room) = 0;
	virtual void BuildDoor(int room1, int room2) = 0;
	virtual Maze* GetMaze() = 0;
	virtual ~MazeBuilder() = default;
};

// 具体构建者: StandardMazeBuilder
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

	void BuildMaze() override {/* 创建一个 空迷宫 */ }
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
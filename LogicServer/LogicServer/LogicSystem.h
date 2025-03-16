#pragma once
#include "LogicSystem.h"
#include "Singleton.h"
#include "const.h"
#include "CSession.h"
#include <queue>
#include <thread>
#include <map>
#include <functional>
#include <json/reader.h>
#include <json/value.h>
#include <json/json.h>

typedef function<void(shared_ptr<CSession>, short msg_id, std::string msg_data) > FunCallBack;
class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	void PostMsgToQue(shared_ptr<LogicNode> msg);
private:
	LogicSystem();
	void DealMsg();
	void RegisterCallBacks();
	void HelloWordCallBack(shared_ptr<CSession>, short msg_id, string msg_data);
	std::thread _worker_thread;
	std::queue<shared_ptr<LogicNode>> _msg_que;
	std::mutex _mutex;
	std::condition_variable _consume;
	bool _b_stop;
	std::map<short, FunCallBack> _fun_callbacks;
};


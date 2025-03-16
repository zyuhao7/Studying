#include "LogicSystem.h"
using namespace std;

LogicSystem::LogicSystem()
	:_b_stop(false)
{
	RegisterCallBacks();
	_worker_thread = std::thread(&LogicSystem::DealMsg, this);
}

LogicSystem::~LogicSystem()
{
	_b_stop = true;
	_consume.notify_all();
	_worker_thread.join();
}

void LogicSystem::PostMsgToQue(shared_ptr<LogicNode> msg)
{
	std::unique_lock<std::mutex> unique_lk(_mutex);
	_msg_que.push(msg);
	if (_msg_que.size() == 1)
	{
		unique_lk.unlock();
		_consume.notify_one();
	}
}

void LogicSystem::DealMsg()
{
	for (;;)
	{
		std::unique_lock<std::mutex> unique_lk(_mutex);
		// �ж϶���Ϊ���������ȴ�.
		while (_msg_que.empty() && !_b_stop)
		{
			_consume.wait(unique_lk);
		}
		// �������ж��Ƿ�ر�, ���߼�ִ�����˳�ѭ��
		if (_b_stop)
		{
			while (!_msg_que.empty())
			{
				auto msg_node = _msg_que.front();
				cout << "recv_msg id is" << msg_node->_recvnode->_msg_id;
				auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
				if (call_back_iter == _fun_callbacks.end())
				{
					_msg_que.pop();
					continue;
				}
				call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
					std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
				_msg_que.pop();
			}
			break;
		}
		// ���û��ͣ��, ��˵��������������
		auto msg_node = _msg_que.front();
		cout << "recv_msg id is " << msg_node->_recvnode->_msg_id << endl;
		auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
		if (call_back_iter == _fun_callbacks.end())
		{
			_msg_que.pop();
			continue;
		}
		call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
			std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
		_msg_que.pop();
	}
}

void LogicSystem::RegisterCallBacks()
{
	_fun_callbacks[MSG_HELLO_WORD] = std::bind(&LogicSystem::HelloWordCallBack, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
}

void LogicSystem::HelloWordCallBack(shared_ptr<CSession> session, short msg_id, string msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	//std::cout << "receive msg id is " << root["id"].asInt() << " msg data is " << root["data"].asString() << endl;

	root["data"] = "server has reveived msg, msg data is " + root["data"].asString();
	std::string return_str = root.toStyledString();
	session->Send(return_str, root["id"].asInt());
}
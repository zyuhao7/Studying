#pragma once
#include <string>
#include <boost/asio.hpp>
#include <iostream>
#include "const.h"
using namespace std;
using boost::asio::ip::tcp;

class LogicSystem;

class MsgNode
{
public:
	MsgNode(short max_len)
		: _cur_len(0),
		_total_len(max_len)
	{
		_data = new char[_total_len + 1]();
		_data[_total_len] = '\0';
	}

	~MsgNode()
	{
		delete[] _data;
	}
	void Clear()
	{
		::memset(_data, 0, _total_len);
		_cur_len = 0;
	}

	short _cur_len;
	short _total_len;
	char* _data;
};

class RecvNode : public MsgNode
{
	friend class LogicSystem;
public:
	RecvNode(short max_len, short msg_id);

private:
	short _msg_id;
};

class SendNode : public MsgNode
{
	friend class LogicSystem;
public:
	SendNode(const char* msg, short max_len, short msg_id);

private:
	short _msg_id;
};


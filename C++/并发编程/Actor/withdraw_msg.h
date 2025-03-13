#pragma once
#include "dispatcher.h"
//柜员消息列举

//取钱
struct withdraw
{
	std::string account;
	unsigned amount;
	//atm 消息队列
	mutable messaging::sender atm_queue;
	withdraw(std::string const& account_,
		unsigned amount_,
		messaging::sender atm_queue_) :
		account(account_), amount(amount_),
		atm_queue(atm_queue_)
	{
	}
};

//取钱成功
struct withdraw_ok
{
};

//取钱被拒绝
struct withdraw_denied
{
};

//取消取钱
struct cancel_withdrawal
{
	std::string account;
	unsigned amount;
	cancel_withdrawal(std::string const& account_,
		unsigned amount_) :
		account(account_), amount(amount_)
	{
	}
};

//取款已处理
struct withdrawal_processed
{
	std::string account;
	unsigned amount;
	withdrawal_processed(std::string const& account_,
		unsigned amount_) :
		account(account_), amount(amount_)
	{
	}
};

//插卡
struct card_inserted
{
	std::string account;
	explicit card_inserted(std::string const& account_) :
		account(account_)
	{
	}

};

//按下数字键
struct digit_pressed
{
	char digit;
	explicit digit_pressed(char digit_) :
		digit(digit_)
	{
	}

};

//清除上一次点击
struct clear_last_pressed
{
};

//弹出卡片
struct eject_card
{
};

//点击取款
struct withdraw_pressed
{
	unsigned amount;
	explicit withdraw_pressed(unsigned amount_) :
		amount(amount_)
	{
	}

};

//点击取消
struct cancel_pressed
{
};

//发钱
struct issue_money
{
	unsigned amount;
	issue_money(unsigned amount_) :
		amount(amount_)
	{
	}
};

//核验密码
struct verify_pin
{
	std::string account;
	std::string pin;
	mutable messaging::sender atm_queue;
	verify_pin(std::string const& account_, std::string const& pin_,
		messaging::sender atm_queue_) :
		account(account_), pin(pin_), atm_queue(atm_queue_)
	{
	}
};

//密码核验完成
struct pin_verified
{
};

//密码正确
struct pin_incorrect
{
};

//展示输入密码，提示用户输入
struct display_enter_pin
{
};

//显示卡进入
struct display_enter_card
{
};

//显示资金不足
struct display_insufficient_funds
{
};

//显示取钱被取消
struct display_withdrawal_cancelled
{
};

//显示错误消息
struct display_pin_incorrect_message
{
};

//显示取钱选项
struct display_withdrawal_options
{
};

//获取余额
struct get_balance
{
	std::string account;
	mutable messaging::sender atm_queue;
	get_balance(std::string const& account_, messaging::sender atm_queue_) :
		account(account_), atm_queue(atm_queue_)
	{
	}
};

//余额
struct balance
{
	unsigned amount;

	explicit balance(unsigned amount_) :
		amount(amount_)
	{
	}
};

//显示余额
struct display_balance
{
	unsigned amount;
	explicit display_balance(unsigned amount_) :
		amount(amount_)
	{
	}
};

//余额已按下
struct balance_pressed
{
};
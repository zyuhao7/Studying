#pragma once
#include "dispatcher.h"
//��Ա��Ϣ�о�

//ȡǮ
struct withdraw
{
	std::string account;
	unsigned amount;
	//atm ��Ϣ����
	mutable messaging::sender atm_queue;
	withdraw(std::string const& account_,
		unsigned amount_,
		messaging::sender atm_queue_) :
		account(account_), amount(amount_),
		atm_queue(atm_queue_)
	{
	}
};

//ȡǮ�ɹ�
struct withdraw_ok
{
};

//ȡǮ���ܾ�
struct withdraw_denied
{
};

//ȡ��ȡǮ
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

//ȡ���Ѵ���
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

//�忨
struct card_inserted
{
	std::string account;
	explicit card_inserted(std::string const& account_) :
		account(account_)
	{
	}

};

//�������ּ�
struct digit_pressed
{
	char digit;
	explicit digit_pressed(char digit_) :
		digit(digit_)
	{
	}

};

//�����һ�ε��
struct clear_last_pressed
{
};

//������Ƭ
struct eject_card
{
};

//���ȡ��
struct withdraw_pressed
{
	unsigned amount;
	explicit withdraw_pressed(unsigned amount_) :
		amount(amount_)
	{
	}

};

//���ȡ��
struct cancel_pressed
{
};

//��Ǯ
struct issue_money
{
	unsigned amount;
	issue_money(unsigned amount_) :
		amount(amount_)
	{
	}
};

//��������
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

//����������
struct pin_verified
{
};

//������ȷ
struct pin_incorrect
{
};

//չʾ�������룬��ʾ�û�����
struct display_enter_pin
{
};

//��ʾ������
struct display_enter_card
{
};

//��ʾ�ʽ���
struct display_insufficient_funds
{
};

//��ʾȡǮ��ȡ��
struct display_withdrawal_cancelled
{
};

//��ʾ������Ϣ
struct display_pin_incorrect_message
{
};

//��ʾȡǮѡ��
struct display_withdrawal_options
{
};

//��ȡ���
struct get_balance
{
	std::string account;
	mutable messaging::sender atm_queue;
	get_balance(std::string const& account_, messaging::sender atm_queue_) :
		account(account_), atm_queue(atm_queue_)
	{
	}
};

//���
struct balance
{
	unsigned amount;

	explicit balance(unsigned amount_) :
		amount(amount_)
	{
	}
};

//��ʾ���
struct display_balance
{
	unsigned amount;
	explicit display_balance(unsigned amount_) :
		amount(amount_)
	{
	}
};

//����Ѱ���
struct balance_pressed
{
};
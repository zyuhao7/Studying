#pragma once
#include "dispatcher.h"
#include <functional>
#include <iostream>
class atm
{
	messaging::receiver incoming;
	messaging::sender bank;
	messaging::sender interface_hardware;
	void (atm::* state)();
	std::string account;
	unsigned withdrawal_amount;
	std::string pin;

	void process_withdrawal()
	{
		incoming.wait().handle<withdraw_ok, std::function<void(withdraw_ok const& msg)>,
			messaging::dispatcher >(
				[&](withdraw_ok const& msg)
				{
					interface_hardware.send(
						issue_money(withdrawal_amount));
					bank.send(
						withdrawal_processed(account, withdrawal_amount));
					state = &atm::done_processing;
				}, "withdraw_ok").handle<withdraw_denied, std::function<void(withdraw_denied const& msg)>>(
					[&](withdraw_denied const& msg)
					{
						interface_hardware.send(display_insufficient_funds());
						state = &atm::done_processing;
					}, "withdraw_denied").handle<cancel_pressed, std::function<void(cancel_pressed const& msg)>>(
						[&](cancel_pressed const& msg)
						{
							bank.send(
								cancel_withdrawal(account, withdrawal_amount));
							interface_hardware.send(
								display_withdrawal_cancelled());
							state = &atm::done_processing;
						}, "cancel_pressed"
					);
	}
	void process_balance()
	{
		incoming.wait()
			.handle<balance, std::function<void(balance const& msg)>,
			messaging::dispatcher>(
				[&](balance const& msg)
				{
					interface_hardware.send(display_balance(msg.amount));
					state = &atm::wait_for_action;
				}, "balance"
			).handle < cancel_pressed, std::function<void(cancel_pressed const& msg) >>(
				[&](cancel_pressed const& msg)
				{
					state = &atm::done_processing;
				}, "cancel_pressed"
			);
	}
	void wait_for_action()
	{
		interface_hardware.send(display_withdrawal_options());
		incoming.wait()
			.handle<withdraw_pressed, std::function<void(withdraw_pressed const& msg)>,
			messaging::dispatcher>(
				[&](withdraw_pressed const& msg)
				{
					withdrawal_amount = msg.amount;
					bank.send(withdraw(account, msg.amount, incoming));
					state = &atm::process_withdrawal;
				}, "withdraw_pressed"
			).handle < balance_pressed, std::function<void(balance_pressed const& msg) >>(
				[&](balance_pressed const& msg)
				{
					bank.send(get_balance(account, incoming));
					state = &atm::process_balance;
				}, "balance_pressed"
			).handle<cancel_pressed, std::function<void(cancel_pressed const& msg) >>(
				[&](cancel_pressed const& msg)
				{
					state = &atm::done_processing;
				}, "cancel_pressed"
			);
	}
	void verifying_pin()
	{
		incoming.wait()
			.handle<pin_verified, std::function<void(pin_verified const& msg)>,
			messaging::dispatcher>(
				[&](pin_verified const& msg)
				{
					state = &atm::wait_for_action;
				}, "pin_verified"
			).handle<pin_incorrect, std::function<void(pin_incorrect const& msg)>>(
				[&](pin_incorrect const& msg)
				{
					interface_hardware.send(
						display_pin_incorrect_message());
					state = &atm::done_processing;
				}, "pin_incorrect"
			).handle<cancel_pressed, std::function<void(cancel_pressed const& msg)>>(
				[&](cancel_pressed const& msg)
				{
					state = &atm::done_processing;
				}, "cancel_pressed"
			);
	}
	void getting_pin()
	{
		incoming.wait().handle<digit_pressed, std::function<void(digit_pressed const& msg)>,
			messaging::dispatcher>(
				[&](digit_pressed const& msg)
				{
					unsigned const pin_length = 6;
					pin += msg.digit;
					if (pin.length() == pin_length)
					{
						bank.send(verify_pin(account, pin, incoming));
						state = &atm::verifying_pin;
					}
				}, "digit_pressed"
			).handle<clear_last_pressed, std::function<void(clear_last_pressed const& msg)>>(
				[&](clear_last_pressed const& msg)
				{
					if (!pin.empty())
					{
						pin.pop_back();
					}
				}, "clear_last_pressed"
			).handle<cancel_pressed, std::function<void(cancel_pressed const& msg)>>(
				[&](cancel_pressed const& msg)
				{
					state = &atm::done_processing;
				}, "cancel_pressed"
			);
	}

	void waiting_for_card()
	{
		interface_hardware.send(display_enter_card());
		incoming.wait().handle<card_inserted, std::function<void(card_inserted const& msg)>,
			messaging::dispatcher>(
				[&](card_inserted const& msg)
				{
					account = msg.account;
					pin = "";
					interface_hardware.send(display_enter_pin());
					state = &atm::getting_pin;
				}, "card_inserted"
			);
	}
	void done_processing()
	{
		interface_hardware.send(eject_card());
		state = &atm::waiting_for_card;
	}
	atm(atm const&) = delete;
	atm& operator=(atm const&) = delete;
public:
	atm(messaging::sender bank_,
		messaging::sender interface_hardware_) :
		bank(bank_), interface_hardware(interface_hardware_)
	{
	}
	void done()
	{
		get_sender().send(messaging::close_queue());
	}
	void run()
	{
		state = &atm::waiting_for_card;
		try
		{
			for (;;)
			{
				(this->*state)();
			}
		}
		catch (messaging::close_queue const&)
		{
		}
	}
	messaging::sender get_sender()
	{
		return incoming;
	}
};
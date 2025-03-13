#pragma once
#include "message.h"
#include <mutex>
class interface_machine
{
	std::mutex   iom;
	messaging::receiver incoming;
public:
	void done()
	{
		get_sender().send(messaging::close_queue());
	}
	void run()
	{
		try
		{
			for (;;)
			{
				incoming.wait().handle<issue_money, std::function<void(issue_money const& msg)>,
					messaging::dispatcher>(
						[&](issue_money const& msg)
						{
							{
								std::lock_guard<std::mutex> lk(iom);
								std::cout << "Issuing "
									<< msg.amount << std::endl;
							}
						}, "issue_money"
					).handle < display_insufficient_funds, std::function<void(display_insufficient_funds const& msg)>>(
						[&](display_insufficient_funds const& msg)
						{
							{
								std::lock_guard<std::mutex> lk(iom);
								std::cout << "Insufficient funds" << std::endl;
							}
						}, "display_insufficient_funds").handle<display_enter_pin, std::function<void(display_enter_pin const& msg)>>(
							[&](display_enter_pin const& msg)
							{
								{
									std::lock_guard<std::mutex> lk(iom);
									std::cout
										<< "Please enter your PIN (0-9)"
										<< std::endl;
								}
							}, "display_enter_pin").handle<display_enter_card, std::function<void(display_enter_card const& msg)>>(
								[&](display_enter_card const& msg)
								{
									{
										std::lock_guard<std::mutex> lk(iom);
										std::cout << "Please enter your card (I)"
											<< std::endl;
									}
								}, "display_enter_card").handle<display_balance, std::function<void(display_balance const& msg)>>(
									[&](display_balance const& msg)
									{
										{
											std::lock_guard<std::mutex> lk(iom);
											std::cout
												<< "The balance of your account is "
												<< msg.amount << std::endl;
										}
									}, "display_balance").handle<display_withdrawal_options,
									std::function<void(display_withdrawal_options const& msg)>>(
										[&](display_withdrawal_options const& msg)
										{
											{
												std::lock_guard<std::mutex> lk(iom);
												std::cout << "Withdraw 50? (w)" << std::endl;
												std::cout << "Display Balance? (b)"
													<< std::endl;
												std::cout << "Cancel? (c)" << std::endl;
											}
										}, "display_withdrawal_options"
										).handle < display_withdrawal_cancelled,
										std::function<void(display_withdrawal_cancelled const& msg)>>(
											[&](display_withdrawal_cancelled const& msg)
											{
												{
													std::lock_guard<std::mutex> lk(iom);
													std::cout << "Withdrawal cancelled"
														<< std::endl;
												}
											}, "display_withdrawal_cancelled"
											).handle<display_pin_incorrect_message,
											std::function<void(display_pin_incorrect_message const& msg)>>(
												[&](display_pin_incorrect_message const& msg)
												{
													{
														std::lock_guard<std::mutex> lk(iom);
														std::cout << "PIN incorrect" << std::endl;
													}
												}, "display_pin_incorrect_message"
												).handle < eject_card,
												std::function<void(eject_card const& msg)>>(
													[&](eject_card const& msg)
													{
														{
															std::lock_guard<std::mutex> lk(iom);
															std::cout << "Ejecting card" << std::endl;
														}
													}, "eject_card"
													);
			}
		}
		catch (messaging::close_queue&)
		{
		}
	}
	messaging::sender get_sender()
	{
		return incoming;
	}
};
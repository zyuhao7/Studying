#pragma once
#include "dispatcher.h"
#include "withdraw_msg.h"

class bank_machine
{
public:
    messaging::receiver incoming;
    unsigned balance;

public:
    bank_machine()
        : balance(199)
    {
    }
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
                incoming.wait().handle<verify_pin, std::function<void(verify_pin const &msg)>, messaging::dispatcher>(
                                   [&](verify_pin const &msg)
                                   {
                                       if (msg.pin == "5201314")
                                       {
                                           msg.atm_queue.send(pin_verified());
                                       }
                                       else
                                       {
                                           msg.atm_queue.send(pin_incorrect());
                                       }
                                   },
                                   "verify_pin")
                    .handle<withdraw, std::function<void(withdraw const &msg)>>(
                        [&, this](withdraw const &msg)
                        {
                            if (this->balance >= msg.amount)
                            {
                                msg.atm_queue.send(withdraw_ok());
                                this->balance -= msg.amount;
                            }
                            else
                            {
                                msg.atm_queue.send(withdraw_denied());
                            }
                        },
                        "withdraw")
                    .handle<get_balance, std::function<void(get_balance const &msg)>>(
                        [&](get_balance const &msg)
                        {
                            msg.atm_queue.send(::balance(balance));
                        },
                        "get_balance")
                    .handle<get_balance, std::function<void(withdrawal_processed const &msg)>>(
                        [&](withdrawal_processed const &msg)
                        {
                            std::cout << "withdrawal_processed!!" << std::endl;
                        },
                        "withdrawal_processed")
                    .handle<cancel_withdrawal, std::function<void(cancel_withdrawal const &msg)>>(
                        [&](cancel_withdrawal const &msg)
                        {
                            std::cout << "cancel withdraw !!!" << std::endl;
                        },
                        "cancel_withdrawal");
            }
        }
        catch (messaging::close_queue const &)
        {
        }
    }

    messaging::sender get_sender()
    {
        return incoming;
    }
};
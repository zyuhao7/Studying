#pragma once

#include <iostream>
#include <memory>
#include "Protocol.hpp"

// 业务
namespace CalCulateNS
{
    enum
    {
        Success = 0,
        DivZeroErr,
        ModZeroErr,
        UnKnowOper
    };

    class Calculate
    {
    public:
        Calculate() {}
        std::shared_ptr<Protocol::Response> Cal(std::shared_ptr<Protocol::Request> req)
        {
            std::shared_ptr<Protocol::Response> resp = factory.BuildResponse();
            resp->SetCode(Success);
            switch (req->GetOper())
            {
            case '+':
                resp->SetResult(req->GetX() + req->GetY());
                break;
            case '-':
                resp->SetResult(req->GetX() - req->GetY());
                break;
            case '*':
                resp->SetResult(req->GetX() * req->GetY());
                break;
            case '/':
            {
                if (req->GetY() == 0)
                {
                    resp->SetCode(DivZeroErr);
                }
                else
                {
                    resp->SetResult(req->GetX() / req->GetY());
                }
            }
            break;
            case '%':
            {
                if (req->GetY() == 0)
                {
                    resp->SetCode(ModZeroErr);
                }
                else
                {
                    resp->SetResult(req->GetX() % req->GetY());
                }
            }
            break;
            default:
                resp->SetCode(UnKnowOper);
                break;
            }

            return resp;
        }
        ~Calculate() {}

    private:
        Protocol::Factory factory;
    };
} // namespace CalCulate

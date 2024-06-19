#pragma once
#include <iostream>
#include <memory>

class Request // 请求
{
public:
    Request() {}
    Request(int x, int y, char op)
        : data_x_(x), data_y_(y), op_(op)
    {
    }

    void Debug()
    {
        std::cout << "data_x_ " << data_x_ << std::endl;
        std::cout << "data_y_ " << data_y_ << std::endl;
        std::cout << "op_ " << op_ << std::endl;
    }

    void Inc()
    {
        data_x_++;
        data_y_++;
    }

private:
    int data_x_;
    int data_y_;
    char op_;
};

class Response // 响应
{
public:
    Response() {}
    Response(int result, int code)
        : result_(result), code_(code)
    {
    }

private:
    int result_;
    int code_;
};

// 工厂模式
class Factory
{
public:
    std::shared_ptr<Request> BuildRequest()
    {
        std::shared_ptr<Request> req = std::make_shared<Request>();
        return req;
    }

    std::shared_ptr<Request> BuildRequest(int x, int y, char op)
    {
        std::shared_ptr<Request> req = std::make_shared<Request>(x, y, op);
        return req;
    }

    std::shared_ptr<Response> BuildResponse()
    {
        std::shared_ptr<Response> resp = std::make_shared<Response>();
        return resp;
    }

    std::shared_ptr<Response> BuildResponse(int result, int code)
    {
        std::shared_ptr<Response> resp = std::make_shared<Response>(result, code);
        return resp;
    }
};
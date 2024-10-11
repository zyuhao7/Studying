#pragma once
#include <iostream>
#include <memory>
#include <jsoncpp/json/json.h>

// #define SELF 1 // SELF=1:用自定义，否则用json
namespace Protocol
{
    // 问题: 1. 结构化数据的序列和反序列化.
    //      2. 用户区分报文边界 - 数据报粘包

    const std::string ProSep = " ";
    const std::string LineBreakSep = "\r\n";

    std::string Encode(const std::string &message)
    {
        std::string len = std::to_string(message.size());
        std::string package = len + LineBreakSep + message + LineBreakSep;
        return package;
    }

    bool Decode(std::string &package, std::string *message)
    {
        // 除了解包, 顺便判断报文的完整性, 能否正确处理具有 "边界"的报文.
        auto pos = package.find(LineBreakSep);
        if (pos == std::string::npos)
            return false;
        std::string lens = package.substr(0, pos);
        int msgLen = std::stoi(lens);
        int total = lens.size() + msgLen + 2 * LineBreakSep.size();
        if (package.size() < total)
            return false;
        // 现在来看, package 内部一定有一个完整的报文了!
        *message = package.substr(pos + LineBreakSep.size(), msgLen);
        package.erase(0, total);
        return true;
    }

    class Request // 请求
    {
    public:
        Request() : data_x_(0), data_y_(0), op_(0) {}
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
        // 结构化数据 -> 字符串 -> x op y

        bool Serialize(std::string *out)
        {
#ifdef SELF
            std::string data_x_str = std::to_string(data_x_);
            std::string data_y_str = std::to_string(data_y_);
            *out = data_x_str + ProSep + op_ + ProSep + data_y_str;
            return true;
#else
            Json::Value root;
            root["datax"] = data_x_;
            root["datay"] = data_y_;
            root["oper"] = op_;
            Json::FastWriter writer;
            *out = writer.write(root);
            return true;
#endif
        }

        bool Deserialize(std::string &in) // "x op y"
        {
#ifdef SELF
            // "x op y"
            auto left = in.find(ProSep);
            if (left == std::string::npos)
                return false;
            auto right = in.rfind(ProSep);
            if (right == std::string::npos)
                return false;

            if (left + ProSep.size() + 1 != right)
                return false;

            std::string left_data = in.substr(0, left);
            if (left_data.empty())
                return false;

            std::string right_data = in.substr(right + ProSep.size());
            if (right_data.empty())
                return false;

            op_ = in[right - 1];
            data_x_ = std::stoi(left_data);
            data_y_ = std::stoi(right_data);
            return true;
#else

            Json::Value root;
            Json::Reader reader;
            bool res = reader.parse(in, root);
            if (res)
            {
                data_x_ = root["datax"].asInt();
                data_y_ = root["datay"].asInt();
                op_ = root["oper"].asInt();
            }
            return res;
#endif
        }
        int GetX() { return data_x_; }
        int GetY() { return data_y_; }
        char GetOper() { return op_; }

    private:
        int data_x_;
        int data_y_;
        char op_;
    };

    class Response // 响应
    {
    public:
        Response() : result_(0), code_(0) {}

        Response(int result, int code)
            : result_(result), code_(code)
        {
        }
        bool Serialize(std::string *out)
        {
#ifdef SELF
            std::string result_str = std::to_string(result_);
            std::string code_str = std::to_string(code_);
            *out = result_str + ProSep + code_str;
            return true;
#else
            Json::Value root;
            root["result"] = result_;
            root["code"] = code_;
            Json::FastWriter writer;
            *out = writer.write(root);
            return true;
#endif
        }

        bool Deserialize(std::string &in) //
        {
#ifdef SELF
            // "_result _code"
            auto mid = in.find(ProSep);
            if (mid == std::string::npos)
                return false;
            std::string left_data = in.substr(0, mid);
            if (left_data.empty())
                return false;
            std::string right_data = in.substr(mid + ProSep.size());
            if (right_data.empty())
                return false;

            result_ = std::stoi(left_data);
            code_ = std::stoi(right_data);
            return true;
#else
            Json::Value root;
            Json::Reader reader;
            bool res = reader.parse(in, root);
            if (res)
            {
                result_ = root["result"].asInt();
                code_ = root["code"].asInt();
            }
            return res;
#endif
        }
        void SetResult(int res) { result_ = res; }
        void SetCode(int code) { code_ = code; }
        int GetResult() { return result_; }
        int GetCode() { return code_; }

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
}

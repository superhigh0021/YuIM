#pragma once

#include "LogServer.pb.h"

#include <string>

#include <google/protobuf/service.h>

constexpr int INPUT_SIZE = 128;

class LogServer : public ik::LogServerRpc {
public:
    // 打印INFO日志
    void Log_INFO(const char* file_path, std::string&& msg);

    // 打印ERROR日志
    void Log_ERROR(const char* file_path, std::string&& msg);

    // 打印FATAL日志
    void Log_FATAL(const char* file_path, std::string&& msg);

public:
    void Log_INFO(::google::protobuf::RpcController* controller,
                  const ::ik::LogRequest* request,
                  ::google::protobuf::Empty* response,
                  ::google::protobuf::Closure* done) override;

    void Log_ERROR(::google::protobuf::RpcController* controller,
                   const ::ik::LogRequest* request,
                   ::google::protobuf::Empty* response,
                   ::google::protobuf::Closure* done) override;

    void Log_FATAL(::google::protobuf::RpcController* controller,
                   const ::ik::LogRequest* request,
                   ::google::protobuf::Empty* response,
                   ::google::protobuf::Closure* done) override;

private:
    // 向filePath中写日志
    bool writeFile(const char* filePath, std::string&& msg);

    void Log(const ::ik::LogRequest* request, ::google::protobuf::Closure* done);

private:
    std::string FATAL = "[FATAL]";
    std::string INFO = "[INFO]";
    std::string ERROR = "[ERROR]";
    char inputStr[INPUT_SIZE] = {0};
};

#include "LogServer.h"

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>

#include <sys/stat.h>
#include <sys/types.h>

constexpr int BUF_SIZE = 32;
constexpr int FILE_SIZE = 64;

// 打印INFO日志
void LogServer::Log_INFO(const char* filePath, std::string&& msg) {
    // 添加日志级别信息
    msg.insert(0, INFO.c_str());
    writeFile(filePath, std::move(msg));
}

// 打印ERROR日志
void LogServer::Log_ERROR(const char* filePath, std::string&& msg) {
    // 添加日志级别信息
    msg.insert(0, ERROR.c_str());
    writeFile(filePath, std::move(msg));
}

// 打印FATAL日志
void LogServer::Log_FATAL(const char* filePath, std::string&& msg) {
    // 添加日志级别信息
    msg.insert(0, FATAL.c_str());
    writeFile(filePath, std::move(msg));
}

bool LogServer::writeFile(const char* filePath, std::string&& msg) {
    time_t now = time(nullptr);
    tm* nowTime = localtime(&now);
    char fileName[FILE_SIZE] = {0};
    sprintf(fileName, "%4d-%2d-%2d_log.txt", nowTime->tm_year + 1900, nowTime->tm_mon + 1, nowTime->tm_mday);

    std::string fileStr = filePath;
    fileStr += "/";
    fileStr += fileName;

    // 组织日志格式
    bzero(inputStr, INPUT_SIZE);
    sprintf(inputStr, "%2d:%2d:%2d=> ", nowTime->tm_hour, nowTime->tm_min, nowTime->tm_sec);
    msg.insert(0, inputStr);
    msg += '\n';

    FILE* fp = fopen(fileStr.c_str(), "a+");
    if (fp == nullptr) {
        ::printf("cannot open file: %s", fileStr.c_str());
        return false;
    }
    fputs(msg.c_str(), fp);
    fclose(fp);

    return true;
}

void LogServer::Log(const ::ik::LogRequest* request, ::google::protobuf::Closure* done) {
    std::string node_name = request->name();
    std::string msg = request->msg();

    // 创建目录
    std::string dirPath = "../../log/";
    dirPath += node_name;
    ::mkdir(dirPath.c_str(), 0777);

    // 写日志
    Log_INFO(dirPath.c_str(), std::move(msg));
    done->Run();
}

void LogServer::Log_INFO(::google::protobuf::RpcController* controller,
                         const ::ik::LogRequest* request,
                         ::google::protobuf::Empty* response,
                         ::google::protobuf::Closure* done) {
    Log(request, done);
}

void LogServer::Log_ERROR(::google::protobuf::RpcController* controller,
                          const ::ik::LogRequest* request,
                          ::google::protobuf::Empty* response,
                          ::google::protobuf::Closure* done) {
    Log(request, done);
}

void LogServer::Log_FATAL(::google::protobuf::RpcController* controller,
                          const ::ik::LogRequest* request,
                          ::google::protobuf::Empty* response,
                          ::google::protobuf::Closure* done) {
    Log(request, done);
}
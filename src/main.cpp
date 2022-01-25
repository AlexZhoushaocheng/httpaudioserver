#include <QCoreApplication>
#include <QDir>
#include "server.h"
#include "upload_handle.h"
#include "./player.h"
#include "3rdparty/easylogging/easylogging++.h"

#define AUDIO_FILE_DIR "./audio_file"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Global,
                    el::ConfigurationType::Format, "%datetime %level %msg");
    defaultConf.set(el::Level::Error,
                    el::ConfigurationType::Format, "%datetime %file %level %msg");
    defaultConf.set(el::Level::Global, el::ConfigurationType::Filename, "./audio.log");
    el::Loggers::reconfigureLogger("default", defaultConf);

    LOG(INFO) << "程序启动..";

    // 初始化创建音频存放目录
    QDir dir;
    if (!dir.exists(AUDIO_FILE_DIR))
    {
        if (!dir.mkdir(AUDIO_FILE_DIR))
        {
            LOG(ERROR) << "创建目录失败..";
            return -1;
        }
    }

    Server server;
    auto x = QSharedPointer<UploadHandle>(new UploadHandle);

    server.addHandle(x);

    // 暂停
    server.addHandle("^/audio/pause", QHttpRequest::HttpMethod::HTTP_GET, [](QHttpRequest *req, QHttpResponse *resp)
                     {
                         QByteArray body = "success";
                         resp->setHeader("Content-Length", QString::number(body.size()));
                         resp->writeHead(200);
                         resp->end(body);

                         Player::instance().pause();
                         LOG(INFO) << "收到暂停播放请求..";
                     });

    server.addHandle("^/audio/resume", QHttpRequest::HttpMethod::HTTP_GET, [](QHttpRequest *req, QHttpResponse *resp)
                     {
                         QByteArray body = "success";
                         resp->setHeader("Content-Length", QString::number(body.size()));
                         resp->writeHead(200);
                         resp->end(body);
                         Player::instance().resume();
                         LOG(INFO) << "收到继续播放请求..";
                     });

    server.start();

    return app.exec();
}
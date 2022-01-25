#include "server.h"
#include "qhttpresponse.h"
#include <QMediaPlayer> 
#include <QRegExp>
#include "3rdparty/easylogging/easylogging++.h"

#define LISTEN_PORT 8090

Server::Server(QObject* parent):QObject(parent), m_pHttpserver(new QHttpServer)
{
    connect(m_pHttpserver, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));
}

Server::~Server()
{
}

void Server::addHandle(QSharedPointer<Handle> h) {
    handles.append(h);
}

void Server::addHandle(const QString& path, QHttpRequest::HttpMethod method, std::function<void (QHttpRequest *req, QHttpResponse *resp)>&& function){
    auto spHandle = QSharedPointer<SimpleHandle>(new SimpleHandle(method, path, 0, std::forward<HandleFunc>(function)));
    handles.append(spHandle);
}

void Server::start(){
    m_pHttpserver->listen(LISTEN_PORT);
    LOG(INFO) << "音频服务监听端口:" << LISTEN_PORT;
}

void Server::handleRequest(QHttpRequest *req, QHttpResponse *resp) {
    for(QSharedPointer<Handle>& spHandle : handles){
        QRegExp re(spHandle->path);
        if(re.indexIn(req->path()) != -1 && req->method() == spHandle->mothod){
            spHandle->handle(req, resp);
            return;
        }
    }

    LOG(WARNING) << "未处理的请求:" << req->path().toStdString();
    QByteArray body = "not found";
    resp->setHeader("Content-Length", QString::number(body.size()));
    resp->writeHead(404);
    resp->end(body);
}
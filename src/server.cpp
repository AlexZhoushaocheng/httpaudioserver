#include "server.h"
#include "qhttpresponse.h"
#include <QMediaPlayer> 
#include <QRegExp>

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

void Server::start(){
    // this->m_pHttpserver->listen(8080);
    m_pHttpserver->listen(8080);
}

void Server::handleRequest(QHttpRequest *req, QHttpResponse *resp) {
    for(QSharedPointer<Handle>& spHandle : handles){
        QRegExp re(spHandle->path);
        if(re.indexIn(req->path()) != -1){
            spHandle->handle(req, resp);
            return;
        }
    }
//      Q_UNUSED(req);
    QByteArray body = "not found";
    resp->setHeader("Content-Length", QString::number(body.size()));
    resp->writeHead(404);
    resp->end(body);
}
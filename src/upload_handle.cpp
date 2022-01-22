#include "upload_handle.h"

#include <QDebug>
#include <QCoreApplication>
#include "player.h"

UploadHandle::UploadHandle() : Handle(QHttpRequest::HTTP_POST, "upload_then_play/[^/]+", 0)
{
}

void UploadHandle::handle(QHttpRequest *req, QHttpResponse *resp)
{    
    if (!lock.try_lock())
    {
        //忙碌
        QByteArray body = "busy";
        resp->setHeader("Content-Length", QString::number(body.size()));
        resp->writeHead(400);
        resp->end(body);
        return;
    }
    else
    {
        Pearser* parser = new Pearser(req, resp);
        connect(parser, SIGNAL(success_done(QString)), this, SLOT(on_success_done(QString)));
        lock.unlock();
    }
}


void UploadHandle::on_success_done(QString filename)
{
    Player::instance().play(filename);
}


/************************************ Pearser ****************************************/

Pearser::Pearser(QHttpRequest *req, QHttpResponse *resp) : m_req(req), m_resp(resp)
{
    connect(req, SIGNAL(data(const QByteArray&)), this, SLOT(on_data(const QByteArray&)));
    connect(req, SIGNAL(end()), this, SLOT(reply()));
    connect(m_resp, SIGNAL(done()), this, SLOT(deleteLater()));

    QString file_name = m_req->path().split('/').back();
    
    file_name = QCoreApplication::applicationDirPath() + "/audio_file/" + file_name;
    m_pFile = new QFile(file_name);
}

Pearser::~Pearser()
{
}

void Pearser::on_data(const QByteArray &data) {
    if(!m_pFile->isOpen())
    {
        auto ret = m_pFile->open(QIODevice::Truncate | QIODevice::WriteOnly);
        if (!ret)
        {
            // 打开文件失败
            return;
        }
        
    }
    m_pFile->write(data);
    // qDebug() << "file name: " << file_name;
    // qDebug() << "data size: " << data.size();
}

void Pearser::reply()
{
    //
    QByteArray body = "upload success";
    m_resp->setHeader("Content-Length", QString::number(body.size()));
    m_resp->writeHead(200);
    m_resp->end(body);

    emit success_done(m_pFile->fileName());
    // Player::instance().play("./audio_file/audio.mp4");
}

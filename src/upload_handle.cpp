#include "upload_handle.h"

#include <QDebug>
#include <QCoreApplication>
#include "player.h"
#include "3rdparty/easylogging/easylogging++.h"

/************************************* 被忽略的一些潜在风险 **************************************
 * 
 * 缺少超时检测
 * 如果数据未传完断开
 * 同时有多个请求上传同一份文件,可能出现打开文件失败
*************************************************************************************/

UploadHandle::UploadHandle() : Handle(QHttpRequest::HTTP_POST, "/audio/upload_then_play/[^/]+", 0)
{
}

void UploadHandle::handle(QHttpRequest *req, QHttpResponse *resp)
{    
    LOG(INFO) << "开始处理文件上传请求..";
    Pearser* parser = new Pearser(req, resp);
    connect(parser, SIGNAL(success_done(QString)), this, SLOT(on_success_done(QString)));
}


void UploadHandle::on_success_done(QString filename)
{
    LOG(INFO) << "接收文件成功,文件名:" << filename.toStdString();
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
            LOG(ERROR) << "保存音频，打开文件失败,文件名:" << m_pFile->fileName().toStdString();
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
    LOG(INFO) << "上传文件请求处理完成.";
    emit success_done(m_pFile->fileName());
}



#ifndef UPLOADHANDLE_HEAD_
#define UPLOADHANDLE_HEAD_

#include "handle.h"
#include "qhttpserver.h"
#include "qhttpresponse.h"
#include <QMutex>
#include <QFile>
#include <QObject>

class UploadHandle : public Handle
{
    Q_OBJECT
public:
    UploadHandle();
    ~UploadHandle() = default;

    void handle(QHttpRequest *req, QHttpResponse *resp) override;

private slots:
    void on_success_done(QString filename);

private:
    QMutex lock;
};

class Pearser : public QObject
{
    Q_OBJECT
public:
    Pearser(QHttpRequest *req, QHttpResponse *resp);
    ~Pearser();

signals:
    void success_done(QString);

private slots:
    void on_data(const QByteArray &data);
    void reply();

private:
    QHttpRequest *m_req{nullptr};
    QHttpResponse *m_resp{nullptr};
    QFile *m_pFile{nullptr};
};




#endif // UPLOADHANDLE_HEAD_



#ifndef HANDLE_HEAD_
#define HANDLE_HEAD_

#include "qhttpserver.h"
#include "qhttprequest.h"

#include <QString>
#include <QObject>

class Handle : public QObject
{
    Q_OBJECT
public:
    Handle(QObject* parent = nullptr);

    explicit Handle(QHttpRequest::HttpMethod mothod, const QString path, int l);

    virtual ~Handle();

    virtual void handle(QHttpRequest *req, QHttpResponse *resp) = 0;

    QHttpRequest::HttpMethod mothod;
    QString path;
    int level{0};
};

using HandleFunc = std::function<void (QHttpRequest *, QHttpResponse *)>;

class SimpleHandle : public Handle
{
public:
    SimpleHandle(QHttpRequest::HttpMethod mothod, const QString path, int l, HandleFunc &&func);

    void handle(QHttpRequest *req, QHttpResponse *resp) override;

private:
    HandleFunc handle_func;
};
#endif // HANDLE_HEAD_
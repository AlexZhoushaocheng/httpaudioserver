
#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include "qhttpserver.h"
#include "handle.h"
#include <functional>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    ~Server();

    void start();

    // void addHandle();

    void addHandle(QSharedPointer<Handle> h);

    void addHandle(const QString& path, QHttpRequest::HttpMethod method, std::function<void (QHttpRequest *, QHttpResponse *)>&& function);

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);

    

private:
    QVector<QSharedPointer<Handle>> handles;
    QHttpServer *m_pHttpserver{nullptr};
};

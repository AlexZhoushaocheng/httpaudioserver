
#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include "qhttpserver.h"
#include "handle.h"

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    ~Server();

    void start();

    // void addHandle();

    void addHandle(QSharedPointer<Handle> h);

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);

    

private:
    QVector<QSharedPointer<Handle>> handles;
    QHttpServer *m_pHttpserver{nullptr};
};

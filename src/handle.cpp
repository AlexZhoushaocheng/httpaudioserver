#include "handle.h"
#include "3rdparty/easylogging/easylogging++.h"

Handle::Handle(QObject* parent):QObject(parent)
{
}

Handle::Handle(QHttpRequest::HttpMethod mothod, const QString path, int l) :QObject(nullptr), mothod(mothod), path(path), level(l)
{
}

Handle::~Handle()
{
}


/***************************************************************************************************/

SimpleHandle::SimpleHandle(QHttpRequest::HttpMethod mothod, const QString path, int l, HandleFunc &&func): Handle(mothod, path, l), handle_func(std::forward<HandleFunc>(func))
{
}

void SimpleHandle::handle(QHttpRequest *req, QHttpResponse *resp)
{
    handle_func(req, resp);
}
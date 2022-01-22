#include "handle.h"


Handle::Handle(QObject* parent):QObject(parent)
{
}

Handle::Handle(QHttpRequest::HttpMethod mothod, const QString path, int l) :QObject(nullptr), mothod(mothod), path(path), level(l)
{
}

Handle::~Handle()
{
}
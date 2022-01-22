#include <QCoreApplication>
#include <QDir>
#include "server.h"
#include "upload_handle.h"

#define AUDIO_FILE_DIR "./audio_file"

int main(int argc, char* argv[]){
    QCoreApplication app(argc, argv);
    
    // 初始化创建音频存放目录
    QDir dir;
    if(!dir.exists(AUDIO_FILE_DIR)){
        dir.mkdir(AUDIO_FILE_DIR);
    }

    // UploadHandle upload_h;
    
    Server server;
    auto x = QSharedPointer<UploadHandle>(new UploadHandle);
    
    server.addHandle(x);
    server.start();

    return app.exec();
}
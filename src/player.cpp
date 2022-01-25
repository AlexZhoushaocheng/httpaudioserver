#include "player.h"
#include <QDebug>
#include <QDir>
#include "3rdparty/easylogging/easylogging++.h"

Player::Player(/* args */)
{
}

Player::~Player()
{
}

Player& Player::instance(){
    static Player ins;
    return ins;
}

void Player::play(const QString &filename) {
    LOG(INFO) << "开始播放音频,文件名:" << filename.toStdString();
    player.setMedia(QUrl::fromLocalFile(filename));
    player.play();
}

void Player::resume() {
    player.play();
    LOG(INFO) << "继续播放";
}

void Player::pause() {
    player.pause();
    LOG(INFO) << "暂停播放";
}



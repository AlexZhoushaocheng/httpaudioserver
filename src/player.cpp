#include "player.h"
#include <QDebug>
#include <QDir>

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
    qDebug() << "filename: " << filename;
    player.setMedia(QUrl::fromLocalFile(filename));
    player.play();
}

void Player::resume() {
    player.play();
}

void Player::pause() {
    player.pause();
}



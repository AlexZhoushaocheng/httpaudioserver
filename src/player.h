#include <QMediaPlayer>
#include <QString>

class Player
{
public:
    static Player& instance();

    ~Player();

    void play(const QString& filename);

    void resume();

    void pause();


private:
    Player();
    QMediaPlayer player;
};



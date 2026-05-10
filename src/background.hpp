
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWidget>
#include <iostream>
#include <vector>

class Background : public QWidget {
public:
    Background();
    ~Background();
    void addContents(QUrl& source, int index);
public slots:
    void pause();
    void play();

private:
    std::string getFileType(QUrl& source);
    std::string pformat { "png,jpg,webp,jpeg" }, mformat { "mkv,mp4,webm" };
    void setPicture(QUrl& source);
    void setMovie(QUrl& source);

protected:
};
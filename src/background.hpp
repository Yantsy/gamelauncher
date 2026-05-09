#include <QAudioOutput>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QWidget>

class Background : public QWidget {
public:
    Background();
    ~Background();
    void addContents(QUrl& source, int index);
public slots:
    void pause();
    void play();

private:
    QString getFileType(QUrl& source);
    void setPicture(QUrl& source);
    void setMovie(QUrl& source);

protected:
};
#include "../MyPictureWidget/public.h"
#include "../src/MediaContainer.hpp"
#include <QApplication>
#include <QThread>

#include <iostream>
int main(int argc, char* argv[]) {

    QApplication a(argc, argv);

    qRegisterMetaType<AudioInfo>("AudioInfo&");
    qRegisterMetaType<VideoInfo>("VideoInfo&");
    qRegisterMetaType<std::shared_ptr<VideoFrame>>("std::shared_ptr<VideoFrame>");
    qRegisterMetaType<std::shared_ptr<AudioChunk>>("std::shared_ptr<AudioChunk>");
    qRegisterMetaType<PlayerStatePtr>("PlayerStatePtr");
    MediaContainer w;
    w.show();
    auto glWidget    = new MyGLWidget();
    auto audioWidget = new MyAudioWidget();
    w.mainLayout.addWidget(glWidget);
    w.setPictureOutput(glWidget);
    w.setAudioOutput(audioWidget);
    w.start();
    return a.exec();
}
#include "../MyPictureWidget/public.h"
#include "MediaContainer.hpp"
#include "MyBorder.hpp"
#include "MyMenu.hpp"
#include <QApplication>
#include <QPushButton>
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
    MyBorder m(&w);
    w.show();
    auto glWidget    = new MyGLWidget();
    auto audioWidget = new MyAudioWidget();
    w.mainLayout.addWidget(glWidget);
    w.setPictureOutput(glWidget);
    w.setAudioOutput(audioWidget);
    w.start();
    return a.exec();
}

// 需解决myBorder的弧度设置是否跟随其父组件的问题
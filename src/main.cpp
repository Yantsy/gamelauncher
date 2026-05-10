#include "../MyPictureWidget/audioWidget_sdl2.h"
#include "../MyPictureWidget/demuxer.h"
#include "../MyPictureWidget/public.h"
#include "../MyPictureWidget/videoWidget_gl.h"
#include "../src/background.hpp"
#include "../src/mainwindow.hpp"
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
    MyWindow w;
    w.show();
    QThread mainThread(&w);
    DemuxerPlusDecoder muxDecoder;
    muxDecoder.open("/home/yantsy/workspace/mine/mihoyolauncher/resources/examplevideo.webm");
    muxDecoder.moveToThread(&mainThread);
    MyGLWidget glWidget;
    w.setCentralWidget(&glWidget);
    glWidget.resize(1320, 720);
    MyAudioWidget audioWidget;
    QObject::connect(
        &mainThread, &QThread::started, &muxDecoder, &DemuxerPlusDecoder::processStart);
    QObject::connect(
        &muxDecoder, &DemuxerPlusDecoder::sendVideoInfo, &glWidget, &MyGLWidget::getInfo);
    QObject::connect(&muxDecoder, &DemuxerPlusDecoder::frameReady, &glWidget, &MyGLWidget::frameIn);
    QObject::connect(
        &muxDecoder, &DemuxerPlusDecoder::sendAudioInfo, &audioWidget, &MyAudioWidget::getInfo);
    mainThread.start();
    std::cout << "hello,world\n" << std::flush;
    QObject::connect(&a, &QApplication::aboutToQuit, &w, [&]() {
        muxDecoder.quit();
        glWidget.quit();
        if (&muxDecoder != nullptr) muxDecoder.deleteLater();

        if (&mainThread && mainThread.isRunning()) {
            if (&mainThread != nullptr) mainThread.quit();
            mainThread.wait();
        }
    });

    return a.exec();
}
#include "MediaContainer.hpp"
MediaContainer::MediaContainer() noexcept {
    setFixedSize(1320, 720);
    // setAttribute(Qt::WA_TranslucentBackground);
    //  parameters:0.667,0.667
    this->setLayout(&mainLayout);
    demuxer = new DemuxerPlusDecoder();
    demuxer->loopOn();
    thread = new QThread(this);
    mainLayout.setContentsMargins(1, 1, 0, 0);
    demuxer->moveToThread(thread);
    QObject::connect(thread, &QThread::started, demuxer, &DemuxerPlusDecoder::processStart);
    std::string contents = "/home/yantsy/workspace/mine/mihoyolauncher/resources/examplevideo.webm";
    addContents(contents, 1);
    /// "home/yantsy/Videos/tests/【京吹_秀久】她的睫毛.mp4"
    //"/home/yantsy/workspace/mine/mihoyolauncher/resources/examplevideo.webm"
}
MediaContainer::~MediaContainer() {
    demuxer->quit();
    if (demuxer != nullptr) demuxer->deleteLater();
    if (thread && thread->isRunning()) {
        if (thread != nullptr) thread->quit();
        thread->wait();
    }
}
// 修改边框

void MediaContainer::setPictureOutput(MyGLWidget* glWidget) {
    QObject::connect(demuxer, &DemuxerPlusDecoder::sendVideoInfo, glWidget, &MyGLWidget::getInfo);
    QObject::connect(demuxer, &DemuxerPlusDecoder::frameReady, glWidget, &MyGLWidget::frameIn);
}
void MediaContainer::setAudioOutput(MyAudioWidget* audioWidget) {
    QObject::connect(
        demuxer, &DemuxerPlusDecoder::sendAudioInfo, audioWidget, &MyAudioWidget::getInfo);
}

void MediaContainer::start() { thread->start(); }
void MediaContainer::addContents(const std::string& source, int index) { demuxer->open(source); }

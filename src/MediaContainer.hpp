#pragma once
#include "../MyPictureWidget/audioWidget_sdl2.h"
#include "../MyPictureWidget/demuxer.h"
#include "../MyPictureWidget/videoWidget_gl.h"
#include "MetaWidget.hpp"

class MediaContainer : public MetaWidget {
    Q_OBJECT
public:
    explicit MediaContainer() noexcept;
    ~MediaContainer();
    void setPictureOutput(MyGLWidget* glWidget);
    void setAudioOutput(MyAudioWidget* audioWidget);
    QVBoxLayout mainLayout;
    void start();

private:
    QThread* thread             = nullptr;
    DemuxerPlusDecoder* demuxer = nullptr;
    // 修改圆角弧度

    bool m_isDraging { false };
    QPoint last, latest, offset;

    void addContents(const std::string& source, int index);

protected:
    qreal xr { 10 }, yr { 10 };
};
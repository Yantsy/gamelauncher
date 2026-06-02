#pragma once

#include "MetaWidget.hpp"

class MyBorder : public MetaWidget {
public:
    MyBorder(MetaWidget* parent = nullptr) {
        if (parent != nullptr) setParent(parent);
        drawBoarder(true);
        noSightBlock();
        raise();
        move(0, 0);
        resize(parent->size());
        setRadius(parent->xr, parent->yr);
    }
    ~MyBorder() { }
};
#include "background.hpp"
Background::Background() { }
Background::~Background() { }
void Background::addContents(QUrl& source, int index) { auto type = getFileType(source); }

auto getFileType(QUrl& source) {
    auto path     = source.toString().toStdString();
    auto question = path.find("?");
    if (question != std::string::npos) {
        path = path.substr(0, question);
    }
    auto lastslash = path.find_last_of("/");
    if (lastslash != std::string::npos) {
        path = path.substr(lastslash + 1);
    }
    auto dot = path.find(".");
    if (dot != std::string::npos) {
        path = path.substr(dot + 1);
    }
    return QString::fromStdString(path);
}
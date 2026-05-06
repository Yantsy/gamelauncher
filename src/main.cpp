#include "../src/mainwindow.hpp"
#include <QApplication>
#include <iostream>
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MyWindow w;
    w.show();
    std::cout << "hello,world\n" << std::flush;
    return a.exec();
}
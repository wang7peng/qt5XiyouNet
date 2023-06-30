#include <QApplication>
#include <QSplashScreen>
#include <QtWidgets/QLabel>
#include <QtGui/QMovie>
#include <unistd.h>
using namespace std;

#include "customizewin.h"
#include "profile.h"
#include "home.h"

#define ConfPath "/home/wangpeng/Desktop/qt5XiyouNet/config/"
void customizeSplash(QSplashScreen *sp);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationVersion("0.1");

    QSplashScreen *sp = new QSplashScreen;
    customizeSplash(sp);

    CustomizeWin w;
    w.show();
    sp->finish(&w);

    return app.exec();
}

void customizeSplash(QSplashScreen *sp) {
    QPixmap pix(ConfPath"mv.gif");
    sp->setPixmap(pix);
    QLabel labelMv(sp);
    QMovie *mv = new QMovie(ConfPath "mv.gif");
    labelMv.setMovie(mv);
    mv->start(); 
    sp->show();
    // 最好 98000，太长会把下方旧日期显示出来
    for (int i = 0; i < 62600; i += mv->speed()) {
        QCoreApplication::processEvents();
        usleep(1000);
    }
}

#include "customizewin.h"
#include "ui_customizewin.h"
#include <QPainter>
#include <QDebug>

CustomizeWin::CustomizeWin(QWidget *parent) : QWidget(parent),
    ui(new Ui::CustomizeWin) {
    ui->setupUi(this);
    this->resize(1200, 750);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->menuSetup->addAction(ui->action_novel);
    menuRight = new QMenu;
    menuRight->addAction(ui->action_resize);
    menuRight->addAction(ui->action_maximum);
    menuRight->addAction(ui->action_minimum);

    move((SCREEN_WIDTH - width()) / 2, (SCREEN_HIGH - height()) / 2 - 10);
}

CustomizeWin::~CustomizeWin() {
    delete ui;
}

void CustomizeWin::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton){
        prevPos = event->pos();
    } else if (event->button() == Qt::RightButton){
        // 右键操作窗口
        // TODO 只在边框上操作
        menuRight->exec(QCursor::pos());
    } else {
        event->ignore();
    }
}

// 鼠标移动不要确定是左键还是右键
void CustomizeWin::mouseMoveEvent(QMouseEvent *event) {
    distence = event->pos() - prevPos;

    this->move(pos() + distence);
}

void CustomizeWin::mouseReleaseEvent(QMouseEvent *e) {
    Q_UNUSED(e);
}

void CustomizeWin::moveEvent(QMoveEvent *e) {
    // qDebug() << e->pos();
}

void CustomizeWin::on_btnExit_clicked() {
    this->close();
}

void CustomizeWin::paintEvent(QPaintEvent *e) {
    QPainter *p = new QPainter(this);
    QPixmap pic = QPixmap(":/win/images/bg_sky.png");
    p->drawPixmap(0, 0, width(), height(), pic);
}

void CustomizeWin::on_action_minimum_triggered() {
    showMinimized();
}

void CustomizeWin::on_action_resize_triggered() {
    showNormal();
}

void CustomizeWin::on_action_maximum_triggered() {
    showMaximized();
}

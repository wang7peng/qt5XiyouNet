#ifndef CUSTOMIZEWIN_H
#define CUSTOMIZEWIN_H

#include <QWidget>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QEvent>
#include "home.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HIGH 900

namespace Ui {
class CustomizeWin;
}

class CustomizeWin : public QWidget
{
    Q_OBJECT

public:
    explicit CustomizeWin(QWidget *parent = 0);
    ~CustomizeWin();
protected:
    void mousePressEvent(QMouseEvent *); // 鼠标点击
    void mouseMoveEvent(QMouseEvent *);  // 鼠标移动
    void mouseReleaseEvent(QMouseEvent *); // 鼠标释放
    void moveEvent(QMoveEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_btnExit_clicked();

    void on_action_minimum_triggered();

    void on_action_resize_triggered();

    void on_action_maximum_triggered();

private:
    Ui::CustomizeWin *ui;
    QPoint prevPos;
    QPoint distence;
    Home* ho = NULL;

    QMenu *menuRight;
};

#endif // CUSTOMIZEWIN_H

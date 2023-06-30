#include "profile.h"

#include "ui_profile.h"

#include <QFile>
#include <QImage>
#include <QPixmap>

//void Profile::paintEvent(QPaintEvent *event) {
   // QPainter painter(this);
   // painter.setRenderHint(QPainter::Antialiasing);
   // painter.setBrush(QBrush(Qt::gray));
   // painter.setPen(Qt::transparent);
   // QRect rect = this->rect();
   // rect.setWidth(rect.width()-1);
   // rect.setHeight(rect.height()-1);
   // painter.drawRoundedRect(rect, 15, 15);
   // QFrame::paintEvent(event);
//}

Profile::Profile(QWidget *parent) : QFrame(parent), ui(new Ui::Profile) {
    ui->setupUi(this);

    QFile file("/home/wangpeng/Desktop/qt5XiyouNet/config/qframe-profile.qss");
    if(file.open(QIODevice::ReadOnly)) {
        QString theme = QString::fromLatin1(file.readAll());
        file.close();
        this->setStyleSheet(theme);
    }
  //  setAttribute(Qt::WA_TranslucentBackground);
  //  setWindowFlags(Qt::FramelessWindowHint);
}

Profile::~Profile() { delete ui; }

QLabel* Profile::getName() {
    return ui->label_Name;
}

QLabel* Profile::getDesc() {
    return ui->label_bio;
}

QPushButton* Profile::getBtnGodL() {
    return ui->btnGodL;
}

QPushButton* Profile::getBtnMonsterL() {
    return ui->btnMonsterL;
}

void Profile::setName(QString name) {
    ui->label_Name->setText(name);
}

void Profile::setDesc(QString desc) {
    ui->label_bio->setText(desc);
}

God::God(QWidget *parent) : Profile(parent) {
    QImage *img = new QImage;
    img->load(":/Object/DOgod");

    ui->picHead->setPixmap(QPixmap::fromImage(*img));

    ui->btnMonsterL->setVisible(false);
}

Monster::Monster(QWidget *parent) : Profile(parent) {
    QImage *img = new QImage;
    img->load(":/Object/DOmonster");

    ui->picHead->setPixmap(QPixmap::fromImage(*img));

    ui->btnGodL->setVisible(false);
}

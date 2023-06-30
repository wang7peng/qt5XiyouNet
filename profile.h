#ifndef PROFILE_H
#define PROFILE_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

namespace Ui {
class Profile;
}

class Profile : public QFrame {
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = 0);
    ~Profile();

   // void paintEvent(QPaintEvent *);
    QLabel* getName();
    QLabel* getDesc();
    QPushButton* getBtnGodL();
    QPushButton* getBtnMonsterL();

    void setName(QString);
    void setDesc(QString);

protected:
    Ui::Profile *ui;
};

class God: public Profile {
    Q_OBJECT
public:
    explicit God(QWidget *parent = 0);
private:
    bool isCommGod;
    bool isCommMonster;
};

class Monster: public Profile {
public:
    explicit Monster(QWidget *parent = 0);
private:
    bool isCommGod;
    bool isCommMonster;
};

#endif // PROFILE_H

#ifndef HOME_H
#define HOME_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QFileDialog>
#include "dataglobal.h"

namespace Ui {
class Home;
}

class DomParser;
class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();
    void setTheme(int = 2023);
    void setHomePageContent(QVector<CharacterDA> *);
    void setTreeContent(QVector<CharacterDA> *);

private slots:
    void selectConfig();
    void aboutAppVer(QWidget *parent = 0);

    void on_btnHome_clicked();
    void on_btnComm_clicked();
    void on_btnSearch_clicked();
    void on_btnConfig_clicked();

private:
    Ui::Home *ui;

    QHBoxLayout *layout = nullptr;
    QGridLayout *layoutGrid = nullptr;
};

class DomParser
{
public:
    DomParser();
    DomParser(QTreeWidget *tree);

    bool readFile(QString &fileName);

private:
    QTreeWidget *treeWidget;
//    void parseBookindexElement(const QDomElement &element);
//    void parseEntryElement(const QDomElement &element,
//                           QTreeWidgetItem *parent);
//    void parsePageElement(const QDomElement &element,
//                          QTreeWidgetItem *parent);
};


#endif // HOME_H

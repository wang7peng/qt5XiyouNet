#include "home.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QSpacerItem>
#include <QGridLayout>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QDomDocument>
#include "profile.h"
#include "dataglobal.h"
#include "ui_home.h"

#define iconPath ":/buttonLogo/images/c_red.png"

namespace Xhp {
  //  bool XmlUnmarshal(QdomElement, CharacterDA&);
}

// Note: 定义在头文件会错
QString GfilePath_xml = "";
QVector<CharacterDA> vec_characters;

void setCurTime(QLCDNumber *);
void customizeInfo(QLabel *);
QTimer *ptrTimer;
Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    customizeInfo(ui->LtdInfo);
    setTheme(2023);
    setCurTime(ui->lcdCurTime);

    connect(ui->action_OpenConf, SIGNAL(triggered()), this,
            SLOT(selectConfig()));
    connect(ui->action_AppVer, SIGNAL(triggered()), this, SLOT(aboutAppVer()));
    connect(ui->action_QtVer, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

Home::~Home() { delete ui; }

void customizeInfo(QLabel *label) {
    QFile file("/home/wangpeng/Desktop/qt5XiyouNet/config/widgets-label.qss");
    file.open(QIODevice::ReadOnly);
    label->setStyleSheet(QString::fromLatin1(file.readAll()));
}

// 设置主题，ui中设置了时候，qss中的颜色失效
void Home::setTheme(int flag) {
    switch (flag) {
    case 2023:
    default:
        QFile file("/home/wangpeng/Desktop/qt5XiyouNet/config/theme2023.qss");
        file.open(QIODevice::ReadOnly);
        setStyleSheet(QString::fromLatin1(file.readAll()));

        break;
    }
}

void Home::setHomePageContent(QVector<CharacterDA> *vec) {
    QList<Profile*> listLevelSit;
    QList<Profile*> listLevelBay;
    QList<Profile*> listLevelProc;
    listLevelSit.clear();
    listLevelBay.clear();
    listLevelProc.clear();

    for (auto it = vec->begin(); it!=vec->end(); ++it) {
        if ((*it).belongLevel == "坐控层"){
            qDebug() << (*it).profile->getBtnGodL()->text();
            listLevelSit << (God*)((*it).profile);
        }
        if ((*it).belongLevel == "间隔层")
            listLevelBay << (Profile*)((*it).profile);
        if ((*it).belongLevel == "取经过程层") {
            listLevelProc << (Monster*)((*it).profile);
        }
    }

    if (listLevelSit.count() < 3) {
        layout = new QHBoxLayout(ui->layoutContent_A);
        for (int i = 0; i< listLevelSit.count(); ++i) {
            layout->addWidget(listLevelSit.at(i));
        }
        layout->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding));
    } else {
        layoutGrid = new QGridLayout(ui->layoutContent_A);
        // 每行放置3个
        for (int i = 0; i< listLevelSit.count(); ++i) {
            int row = i / 3;
            int col = i % 3;
            layoutGrid->addWidget(listLevelSit.at(i), row, col, 1, 1);
        }
    }

    QGridLayout *layoutGrid2 = new QGridLayout(ui->layoutContent_B);
    // 每行放置3个
    for (int i = 0; i< listLevelBay.count(); ++i) {
        int row = i / 3;
        int col = i % 3;
        layoutGrid2->addWidget(listLevelBay.at(i), row, col, 1, 1);
    }

    QGridLayout *layoutGrid3 = new QGridLayout(ui->layoutContent_C);
    for (int i = 0; i< listLevelProc.count(); ++i) {
        int row = i / 4;
        int col = i % 4;
        layoutGrid3->addWidget(listLevelProc.at(i), row, col, 1, 1);
    }
}

void Home::setTreeContent(QVector<CharacterDA> *vec) {
    ui->treeCharacters->setHeaderLabel(QString("小说人物角色"));
    auto rootItem = ui->treeCharacters->invisibleRootItem();

    // test data
    int levelSitCount = 0;
    for (auto i = vec->begin(); i!=vec->end(); ++i) {
        qDebug() << (*i).name << (*i).absName;
        if ((*i).belongLevel == "坐控层") levelSitCount++;
    }


    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeCharacters);
    item->setText(0, "坐控层");

    QTreeWidgetItem *itemSon;
    for (auto i = vec->begin(); i!=vec->end(); ++i) {
        if ((*i).belongLevel == "坐控层") {
            itemSon = new QTreeWidgetItem(item);
            itemSon->setText(0, (*i).name);
        }
    }

    item = new QTreeWidgetItem(ui->treeCharacters);
    item->setText(0, "间隔层");
    for (auto i = vec->begin(); i!=vec->end(); ++i) {
        if ((*i).belongLevel == "间隔层") {
            itemSon = new QTreeWidgetItem(item);
            itemSon->setText(0, (*i).name);
        }
    }

    item = new QTreeWidgetItem(ui->treeCharacters);
    item->setText(0, "取经过程层");

    for (auto i = vec->begin(); i!=vec->end(); ++i) {
        if ((*i).belongLevel == "取经过程层") {
            itemSon = new QTreeWidgetItem(item);
            itemSon->setText(0, (*i).name);
        }
    }

}

void setCurTime(QLCDNumber *lcdWidget) {
    lcdWidget->setStyleSheet("font-size: 20px; color: #0000CC;");

    QTimer *ptrTimer = new QTimer();
    QObject::connect(ptrTimer, &QTimer::timeout, lcdWidget, [=] {
        QDateTime cur = QDateTime::currentDateTime();
        QString timeStr = cur.toString("hh:mm:ss");
        lcdWidget->display(timeStr);
    });
    ptrTimer->start(1000);
}

void Home::selectConfig() {
    QString absFilename =
        QFileDialog::getOpenFileName(this, "选择配置文件", "/home",
                                     "XHP Config File (*.xml);;"
                                     "All Files (*.*)");
    if (absFilename.isEmpty()) {
        qDebug() << "未选好文件, 直接关闭窗口";
        return;
    }

    GfilePath_xml = absFilename;
    qDebug() << "get a config file: " << GfilePath_xml;

    DomParser *domP = new DomParser();
    domP->readFile(GfilePath_xml);

    setTreeContent(&vec_characters);
    setHomePageContent(&vec_characters);
}

void Home::aboutAppVer(QWidget *parent) {
    QMessageBox appVersion;
    appVersion.setStyleSheet(
        "QLabel{"
        "max-width: 320px;"
        "}");

    appVersion.setWindowTitle(
        QString("About %1").arg(QCoreApplication::applicationName()));
    appVersion.setText(QString("<h2>西游记人物联络分析系统 Ver%1</h2>")
                           .arg(QCoreApplication::applicationVersion()) +
                       "<p><font size=4>release time 2023.7.1</font></p>"
                       "<p><font face='times New Roman'>Copyright &copy; "
                       "2023 NewHope Power Inc.</font></p>");
    appVersion.setIconPixmap(QPixmap(iconPath));
    appVersion.exec();
}

void Home::on_btnHome_clicked() { ui->stackedWin->setCurrentIndex(0); }

void Home::on_btnComm_clicked() { ui->stackedWin->setCurrentIndex(1); }

void Home::on_btnSearch_clicked() { ui->stackedWin->setCurrentIndex(2); }

void Home::on_btnConfig_clicked() { ui->stackedWin->setCurrentIndex(3); }

// ---------------------- handle xml ----------------------

DomParser::DomParser(){
    treeWidget = nullptr;
}
DomParser::DomParser(QTreeWidget *tree) {
    treeWidget = tree;
}

void readAPElement(QDomElement AP);

bool DomParser::readFile(QString &filepath_xml) {
    QFile f(filepath_xml);
    QDomDocument doc;
    if(!doc.setContent(&f)) {
        f.close();
        return false;
    }
    f.close();

    QDomElement rootEle = doc.documentElement(); // <xcl>
    if (rootEle.tagName() != "XCL") {
        qDebug() << "Error: not a private config file";
        return false;
    }

    QDomNodeList nodes = rootEle.childNodes();
    for (int i = 0; i < nodes.count(); ++i) {
        // 同级注释也算一个节点，被用 #comment 固定名存入
        if (nodes.at(i).isComment()) continue;

        if (nodes.at(i).nodeName() == "Communication") {
            QDomNode AP = nodes.at(i).firstChild(); // <AccessPoint>
            qDebug() << AP.nodeName();
            while (AP.isElement()) {
                if (AP.isNull()) continue;

                auto apEle = AP.toElement();
                if (apEle.hasAttribute("level")) {
                    readAPElement(apEle);
                }
                AP = AP.nextSibling();
            }
        }
        // ignore other case
    }
    return true;
}

void readAPElement(QDomElement ap) {
    qDebug() << ap.attribute("level");
    CharacterDA tmpDA{"", "", nullptr};
    tmpDA.belongLevel = ap.attribute("level");

    auto characters = ap.childNodes();
    for (int i = 0; i < characters.count(); ++i) {
        auto character = characters.at(i).toElement();
        if(0 == character.tagName().compare("LN")) {
            // xhp::Unmarshal(character, &character);
        }
        // 获取属性内容
        if (character.hasAttributes()) {
            QDomNamedNodeMap attrMap = character.attributes();
            for (int index = 0; index < attrMap.count(); ++index) {
                if (attrMap.item(index).nodeName() == "nickName") {
                    tmpDA.name = attrMap.item(index).nodeValue();
                } else if (attrMap.item(index).nodeName() == "absName") {
                    tmpDA.absName = attrMap.item(index).nodeValue();
                }
            }
        }

        if (tmpDA.belongLevel == "坐控层") {
            tmpDA.profile = new God;
            tmpDA.profile->setName(tmpDA.name);
        } else if (tmpDA.belongLevel == "取经过程层") {
            tmpDA.profile = new Monster;
            tmpDA.profile->setName(tmpDA.name);
        } else {
            tmpDA.profile = new Profile;
            tmpDA.profile->setName(tmpDA.name);
        }
        vec_characters.append(tmpDA);
    }
    auto a = ap.lastChildElement("LN");
   // qDebug() << a.text();
}


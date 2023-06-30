#ifndef DATAGLOBAL_H
#define DATAGLOBAL_H
#include <QString>
#include "profile.h"

// 人物公共数据属性，从 xml 中解析得到
struct CharacterDA{
public:
    QString name;
    QString absName;
    QString belongLevel;
    Profile *profile; // 角色肖像
};

extern QString GfilePath_xml;
extern QVector<CharacterDA> vec_characters;

#endif  // DATAGLOBAL_H

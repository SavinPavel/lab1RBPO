#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class student
{
public:
    student(QString _name,int _age,QString _group);
    QString name;
    int age;
    QString group;
    QString toJSON();
    QString toXML();
};

#endif // STUDENT_H

#include <student.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDomDocument>

//test commit

student::student(QString _name, int _age, QString _group)
{
    name=_name;
    age=_age;
    group=_group;
}

QString student::toJSON()
{
    QJsonObject recordObject;
    QJsonObject objObject;
    objObject.insert("name:", name);
    objObject.insert("age", age);
    objObject.insert("group", group);
    recordObject.insert("Person",objObject);
    QJsonDocument doc(recordObject);
    QString jsonString = doc.toJson(QJsonDocument::Indented);
    return jsonString;
}

QString student::toXML()
{
    const int Indent = 4;

    QDomDocument doc;
    QDomElement root = doc.createElement("person");
    QDomElement nameXML = doc.createElement("name");
    QDomElement ageXML = doc.createElement("age");
    QDomElement groupXML = doc.createElement("group");

    doc.appendChild(root);
    root.appendChild(nameXML);
    root.appendChild(ageXML);
    root.appendChild(groupXML);
    nameXML.appendChild(doc.createTextNode(name));
    ageXML.appendChild(doc.createTextNode(QString::number(age)));
    groupXML.appendChild( doc.createTextNode(group));

    return doc.toString(Indent);
}

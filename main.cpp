#include <QCoreApplication>
#include <QStorageInfo>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <windows.h>
#include <student.h>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL,"Rus");
    QTextStream cin(stdin);
    QTextStream cout(stdout);
    cin.setCodec(QTextCodec::codecForName("ibm866"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
    int choice_m;
    cout << QString::fromUtf8("Меню\n1.Информация о дисках\n2.Работа с файлами\n"
                              "3.Работа с форматом JSON\n4.Работа с форматом XML\n");
    cout.flush();
    cin>>choice_m;
    while(choice_m!=0){
        switch (choice_m) {
            case 0:
                break;
            case 1: {
                QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
                for(auto diskInfo:list){
                    cout << "\nstorage path: " << diskInfo.rootPath();
                    cout << "\nstorage name: " << diskInfo.displayName();
                    cout << "\nstorage size: " << diskInfo.bytesTotal();
                    cout << "\nstorage type: " << diskInfo.fileSystemType();
                    cout << "\n----------------------------------";
                }
                cout.flush();
                break;
            }
            case 2: {
                system("cls");
                QString name;
                QFile file;
                QTextStream fs;
                cout << QString::fromUtf8("Введите название файла:\n")<<flush;
                cin >> name;
                name+=".txt";
                file.setFileName(name);
                system("cls");
                cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать строку в файл(в конец)\n"
                                          "3.Вывести файл в консоль\n4.Удалить файл\n5.Изменить имя файла0.Выход\n")<<flush;
                int choice_F;
                cin >> choice_F;
                while(true){
                    switch(choice_F){
                    case 0:
                        break;
                    case 1:{
                        if(!file.isOpen()){
                            if(file.exists())
                                file.open(QIODevice::ReadWrite | QIODevice::Append);
                            else
                                file.open(QIODevice::ReadWrite);
                            fs.setDevice(&file);
                            fs.setCodec(QTextCodec::codecForName("UTF-8"));

                        }
                        else
                            cout<<QString::fromUtf8("Файл уже открыт\n")<<flush;
                        break;
                    }
                    case 2:{
                        if(!file.isOpen())
                            cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                        else{
                            file.close();
                            file.open(QIODevice::ReadWrite | QIODevice::Append);
                            fs.setDevice(&file);
                            fs.setCodec(QTextCodec::codecForName("UTF-8"));
                            QString buf;
                            cout<<QString::fromUtf8("Введите строку:\n")<<flush;
                            cin.skipWhiteSpace();
                            buf=cin.readLine();
                            fs<<buf+'\n'<<flush;
                        }
                         break;

                    }
                    case 3:{     QString buf;
                        if(!file.isOpen()){
                            cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                            break;
                        }
                        else{
                            file.seek(0);
                            QString str,str1;
                            str=file.readAll();
                            cout<<str<<flush;
                            break;
                        }

                    }
                    case 4:{
                        file.close();
                        file.remove();
                        break;
                    }
                    case 5:{
                        file.close();
                        cout << QString::fromUtf8("Введите название файла:\n")<<flush;
                        cin >> name;
                        name+="txt";
                        break;
                    }
                    default:{
                        cout << QString::fromUtf8("Такого пункта нет, выберете действие из предложеного")<<flush;
                        break;
                    }
                    }
                    if(choice_F==0)
                        break;
                    else{                        
                        cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать строку в файл(в конец)\n"
                                                  "3.Вывести файл в консоль\n4.Удалить файл\n5.Изменить имя файла\n0.Выход\n")<<flush;
                        cin >> choice_F;
                        system("cls");
                    }
                }
                file.close();
            }
            case 3:{//json
            QFile file;
            QTextStream JsonStream;
            QString name;
            cout << QString::fromUtf8("Введите название файла:\n")<<flush;
            cin >> name;
            name+=".json";
            file.setFileName(name);
            system("cls");
            cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать данные в файл\n"
                                      "3.Вывести файл в консоль\n4.Удалить файл\n5.Сменить файла\n0.Выход\n")<<flush;
            int choice_J;
            cin>> choice_J;
            while (true) {
                switch(choice_J){
                case 0:{
                    break;
                }
                case 1:{
                    if(!file.isOpen()){
                        if(file.exists())
                            file.open(QIODevice::ReadWrite | QIODevice::Append);
                        else
                            file.open(QIODevice::ReadWrite);
                        JsonStream.setDevice(&file);
                        JsonStream.setCodec(QTextCodec::codecForName("UTF-8"));
                    }
                    else
                        cout<<QString::fromUtf8("Файл уже открыт\n")<<flush;
                    break;
                }
                case 2:{
                    if(file.isOpen()){
                        student *stud=new student("Alex",22,"BISO-04-18");
                        QString buf;
                        buf=stud->toJSON();
                        JsonStream<<buf<<flush;
                        delete stud;
                    }
                    else
                        cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                    break;
                }
                case 3:{
                    if(file.isOpen()){
                        file.seek(0);
                        QString buf;
                        buf=file.readAll();
                        cout<<buf<<flush;
                        file.close();
                        file.open(QIODevice::ReadWrite | QIODevice::Append);
                    }
                    else
                        cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                    break;

                }
                case 4:{
                    if(file.isOpen())
                        file.close();
                    file.remove();
                    break;
                }
                case 5:{
                    if(file.isOpen())
                        file.close();
                    cout << QString::fromUtf8("Введите название файла:\n")<<flush;
                    cin >> name;
                    name+="json";
                    break;
                }
                default:{
                    cout << QString::fromUtf8("Такого пункта нет, выберете действие из предложеного")<<flush;
                    break;
                }
                }

                if(choice_J==0)
                    break;
                else{
                    cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать данные в файл\n3"
                                              ".Вывести файл в консоль\n4.Удалить файл\n5.Сменить файла\n0.Выход\n")<<flush;
                    cin >> choice_J;
                    system("cls");
                }
            }

            file.close();
                break;}
            case 4:{//xml
                QFile file;
                QTextStream xmlStream;
                QString name;
                cout << QString::fromUtf8("Введите название файла:\n")<<flush;
                cin >> name;
                name+=".xml";
                file.setFileName(name);
                system("cls");
                cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать данные в файл\n"
                                          "3.Вывести файл в консоль\n4.Удалить файл\n5.Сменить файла\n0.Выход\n")<<flush;
                int choice_X;
                cin>> choice_X;
                while (true) {
                    switch(choice_X){
                    case 0:{
                        break;
                    }
                    case 1:{
                        if(!file.isOpen()){
                            if(file.exists())
                                file.open(QIODevice::ReadWrite | QIODevice::Append);
                            else
                                file.open(QIODevice::ReadWrite);
                            xmlStream.setDevice(&file);
                            xmlStream.setCodec(QTextCodec::codecForName("UTF-8"));
                        }
                        else
                            cout<<QString::fromUtf8("Файл уже открыт\n")<<flush;
                        break;
                    }
                    case 2:{
                        if(file.isOpen()){
                            student *stud=new student("Alex",22,"BISO-04-18");
                            QString buf;
                            buf=stud->toXML();
                            xmlStream<<buf<<flush;
                            delete stud;
                        }
                        else
                            cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                        break;
                    }
                    case 3:{
                        if(file.isOpen()){
                            file.seek(0);
                            QString buf;
                            buf=file.readAll();
                            cout<<buf<<flush;
                            file.close();
                            file.open(QIODevice::ReadWrite | QIODevice::Append);
                        }
                        else
                            cout<<QString::fromUtf8("Сначала откройте файл\n")<<flush;
                        break;
                    }
                    case 4:{
                        if(file.isOpen())
                            file.close();
                        file.remove();
                        break;
                    }
                    case 5:{
                        if(file.isOpen())
                            file.close();
                        cout << QString::fromUtf8("Введите название файла:\n")<<flush;
                        cin >> name;
                        name+=".xml";
                        break;
                    }
                    default:{
                        cout << QString::fromUtf8("Такого пункта нет, выберете действие из предложеного")<<flush;
                        break;
                    }
                    }
                    if(choice_X==0)
                        break;
                    else{

                        cout << QString::fromUtf8("Меню\n1.Создать/открыть файл\n2.Записать данные в файл\n3"
                                                  ".Вывести файл в консоль\n4.Удалить файл\n5.Сменить файла\n0.Выход\n")<<flush;
                        cin >> choice_X;
                        system("cls");
                    }
                }
                file.close();
                break;
            }
            default:{
                cout << QString::fromUtf8("Такого пункта нет, выберете действие из предложеного")<<flush;
                break;
            }
        }

        if(choice_m!=0){
            cout << QString::fromUtf8("\nМеню\n1.Информация о дисках\n2.Работа с файлами\n3.Работа с форматом JSON\n4.Работа с форматом XML\n");
            cout.flush();
            cin>>choice_m;
            system("cls");
        }
        else
            break;

    }
    return a.exec();
}

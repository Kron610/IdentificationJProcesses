#include "widget.h"

#include <QApplication>



int indexOfPathsList(QString string)
{
    bool flag = false;
    int index = -1;
    for(int i = 0; i < string.size(); i++)
    {
        if (flag)
        {
            if (string.at(i) != '-')
            {
                index = i;
                if (string.at(i) == "\"")
                    index++;
                break;
            }
            flag = false;
            continue;
        }
        if (string.at(i) == ' ')
        {
            flag = true;
            continue;
        }
    }
    return index;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    std::vector<QTableWidgetItem> items;
    std::vector<DWORD> ids = GetProcessByName(L"javaw.exe", L"java.exe");

    size_t appCount = ids.size();
    QTableWidget table(appCount, 1);

    for (auto dwId: ids)
    {

        PWSTR buf;
        int error =  get_cmd_line(dwId, buf);
        if (error != 0)
            return a.exec();
        QString string = QString::fromWCharArray(buf);

        int endOf = string.indexOf("\"", 1);
        QString mainPath = string.mid(1, endOf - 1);
        string = string.mid(endOf + 2);
        string = string.mid(indexOfPathsList(string));
        QStringList list = string.split(';');
        list.removeAll("");
        QString pathOfApp = list[0];
        int indexOfNameApp = pathOfApp.lastIndexOf("\\");
        int indexOfFormat = pathOfApp.lastIndexOf(".");
        QString appName = pathOfApp.mid(indexOfNameApp + 1, indexOfFormat - indexOfNameApp - 1);
        pathOfApp = pathOfApp.left(indexOfNameApp + 1);
        auto wPath = pathOfApp.toStdWString();

        auto images = QStringList();
        bool flag = false;
        enumsubfiles(wPath, L"*.ico", 1, ENUM_FILE, [&images, &flag](const std::wstring &dir_with_back_slant, _wfinddata_t &attrib)->bool
            {
                    QString imageName = QString::fromStdWString(dir_with_back_slant + attrib.name);
                    images.append(imageName);
                    flag = true;
                return true;
            });

        if (!flag)
        {
            pathOfApp.chop(1);
            int indexOfPrevPath = pathOfApp.lastIndexOf("\\");
            pathOfApp = pathOfApp.left(indexOfPrevPath + 1);
            wPath = pathOfApp.toStdWString();
            enumsubfiles(wPath, L"*.ico", 2, ENUM_FILE, [&images, &flag](const std::wstring &dir_with_back_slant, _wfinddata_t &attrib)->bool
                {
                        QString imageName = QString::fromStdWString(dir_with_back_slant + attrib.name);
                        images.append(imageName);
                        flag = true;
                    return true;
                });
        }

        QTableWidgetItem item;
        item.setText(appName);
        QIcon icon;
        icon.addFile(images[0]);
        item.setIcon(icon);
        items.push_back(item);
    }

    table.setGeometry(QRect(0,0,300,250));
    QStringList headers;
    headers.append("Application");
    table.setHorizontalHeaderLabels(headers);

    size_t i = 0;


    for (auto& item: items)
    {
        table.setItem(i++, 0, &item);
    }


    table.show();
    return a.exec();
}

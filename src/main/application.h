#ifndef _ENCLOUD_APPLICATION_H_
#define _ENCLOUD_APPLICATION_H_

#include <QCoreApplication>

namespace encloud {

class Application :
    public QCoreApplication
{
    Q_OBJECT

public:

    // QApplication takes a *reference* to argc
    // (qt-project.org/doc/qt-4.8/qapplication.html)
    Application (int &argc, char **argv);
    ~Application ();

    // reimplemented
    bool notify (QObject *receiver, QEvent *e);
};

}  // namespace encloud

#endif  // _ENCLOUD_APPLICATION_H_

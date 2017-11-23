#include "common.h"
#include "application.h"
#include <encloud/Core>

namespace encloud 
{

//
// public methods
//

Application::Application (int &argc, char **argv)
    : QCoreApplication(argc, argv)
{
    ENCLOUD_TRACE;
}

Application::~Application ()
{
    ENCLOUD_TRACE;
}

bool Application::notify (QObject *receiver, QEvent *e)
{
    try {
        return QCoreApplication::notify(receiver, e);
    } catch (std::exception &e) {
        ENCLOUD_DBG("Caught exception: " << QString(e.what()));
    }
}

}  // namespace encloud

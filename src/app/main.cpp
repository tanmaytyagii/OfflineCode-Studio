#include "presentation/main_window/main_window.h"

#include <QApplication>
#include <QCoreApplication>
//main  import 
int main(int argc, char* argv[]) {
    QApplication application(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("OfflineCode Studio"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1.0-alpha"));
    QCoreApplication::setOrganizationName(QStringLiteral("OfflineCode Studio"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("offlinecode.studio"));

    offlinecode::presentation::MainWindow window;
    window.show();
    return application.exec();
}

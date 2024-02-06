#include <QCoreApplication>
#include <SecureServer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SecureServer * server = new SecureServer;
    Q_UNUSED(server)

    return a.exec();
}

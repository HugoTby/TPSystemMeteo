#include "TPSytemeMeteo.h"
#include <QtWidgets/QApplication>
#include "K8055Adapter.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TPSytemeMeteo w;
    w.show();
    return a.exec();
}

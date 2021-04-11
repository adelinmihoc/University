#include <QApplication>
#include "main_gui.h"
#include <iostream>
//#include "admin_gui.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ArchmageEncyclopedia repo = ArchmageEncyclopedia();
    Enchantment controller = Enchantment(repo);

    MAIN_GUI main_gui{controller};
    main_gui.setMinimumSize(1080, 720);
    main_gui.show();

    return a.exec();
}

#include <QApplication>
#include "gui/forms/mainfrm.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainFrm frm;
	frm.show();
    return a.exec();
}

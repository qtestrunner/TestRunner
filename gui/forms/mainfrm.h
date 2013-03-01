#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>

namespace Ui {
class MainFrm;
}

class MainFrm : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainFrm(QWidget *parent = 0);
	~MainFrm();
	
private:
	Ui::MainFrm *ui;
};

#endif // MAINFRM_H

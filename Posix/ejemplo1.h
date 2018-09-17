#ifndef ejemplo1_H
#define ejemplo1_H
#include <unistd.h>
#include "ui_counterDlg.h"
#include "Timer.h"

class ejemplo1 : public QWidget, public Ui_Counter
{
Q_OBJECT
	
public:
    ejemplo1();
	~ejemplo1();
	int num;
	Timer* t;
	void updateNumber();
	void run(){
        while(t->isRunning()){
            std::this_thread::sleep_for( std::chrono::milliseconds(t->getPeriod()) );
			if(t->isRunning()) this->updateNumber();
        }
    }
    
public slots:
	void doButton();
};

#endif // ejemplo1_H

/****************************************************************************
** Form interface generated from reading ui file 'debugTreiberGUI.ui'
**
** Created: Fri Mar 22 16:36:54 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef DEBUGTREIBERGUI_H
#define DEBUGTREIBERGUI_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QCheckBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QSpinBox;
class QTabWidget;

class DebugTreiberGUI : public QWidget
{ 
    Q_OBJECT

public:
    DebugTreiberGUI( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DebugTreiberGUI();

    QTabWidget* Tab;
    QWidget* SendenTab;
    QLabel* TextLabel1;
    QLabel* TextLabel1_3;
    QPushButton* sendButton;
    QGroupBox* DatenBytes;
    QSpinBox* byte12;
    QSpinBox* byte14;
    QSpinBox* byte5;
    QSpinBox* byte4;
    QSpinBox* byte8;
    QSpinBox* byte13;
    QSpinBox* byte9;
    QSpinBox* byte10;
    QSpinBox* byte1;
    QSpinBox* byte2;
    QSpinBox* byte3;
    QSpinBox* byte7;
    QSpinBox* byte11;
    QSpinBox* byte6;
    QSpinBox* byte0;
    QSpinBox* toOpId;
    QSpinBox* toLength;
    QWidget* EmpfangenTab;
    QGroupBox* DatenBytes_Received;
    QSpinBox* rbyte1;
    QSpinBox* rbyte2;
    QSpinBox* rbyte3;
    QSpinBox* rbyte5;
    QSpinBox* rbyte6;
    QSpinBox* rbyte7;
    QSpinBox* rbyte10;
    QSpinBox* rbyte11;
    QSpinBox* rbyte9;
    QSpinBox* rbyte14;
    QSpinBox* rbyte13;
    QSpinBox* rbyte12;
    QSpinBox* rbyte8;
    QSpinBox* rbyte4;
    QSpinBox* rbyte0;
    QSpinBox* receiveNumber;
    QLabel* TextLabel1_2;
    QLabel* TextLabel4;
    QSpinBox* fromOpId;
    QCheckBox* Pause;
    QWidget* SetupTab;
    QGroupBox* GroupBox5;
    QSpinBox* DeviceID;
    QLabel* toDeviceLabel;
    QCheckBox* broadcast;
    QPushButton* QuitButton;

public slots:
    virtual void newMessage();
    virtual void quit();
    virtual void send();
    virtual void setID(int);
    virtual void setNumberOfDataBytes(int);
    virtual void showReceivedWithNumber(int);

};

#endif // DEBUGTREIBERGUI_H

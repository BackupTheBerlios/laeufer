/****************************************************************************
** Form implementation generated from reading ui file 'debugTreiberGUI.ui'
**
** Created: Fri Mar 22 16:50:05 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "debugTreiberGUI.h"

#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a DebugTreiberGUI which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
DebugTreiberGUI::DebugTreiberGUI( QWidget* parent,  const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "DebugTreiberGUI" );
    resize( 240, 300 ); 
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, sizePolicy().hasHeightForWidth() ) );
    setMinimumSize( QSize( 240, 300 ) );
    setMaximumSize( QSize( 240, 300 ) );
    setCaption( tr( "DebugTreiberGUI" ) );

    Tab = new QTabWidget( this, "Tab" );
    Tab->setEnabled( TRUE );
    Tab->setGeometry( QRect( 0, 0, 240, 300 ) ); 
    QToolTip::add(  Tab, tr( "" ) );

    SendenTab = new QWidget( Tab, "SendenTab" );

    TextLabel1 = new QLabel( SendenTab, "TextLabel1" );
    TextLabel1->setGeometry( QRect( 10, 10, 75, 20 ) ); 
    TextLabel1->setText( tr( "Operation:" ) );

    TextLabel1_3 = new QLabel( SendenTab, "TextLabel1_3" );
    TextLabel1_3->setGeometry( QRect( 10, 40, 141, 20 ) ); 
    TextLabel1_3->setText( tr( "Anzahl Datenbytes:" ) );

    sendButton = new QPushButton( SendenTab, "sendButton" );
    sendButton->setGeometry( QRect( 60, 220, 120, 32 ) ); 
    sendButton->setText( tr( "Senden!" ) );
    sendButton->setDefault( TRUE );
    QToolTip::add(  sendButton, tr( "Daten absenden" ) );

    DatenBytes = new QGroupBox( SendenTab, "DatenBytes" );
    DatenBytes->setGeometry( QRect( 10, 70, 220, 150 ) ); 
    DatenBytes->setTitle( tr( "DatenBytes" ) );

    byte12 = new QSpinBox( DatenBytes, "byte12" );
    byte12->setEnabled( FALSE );
    byte12->setGeometry( QRect( 10, 110, 50, 26 ) ); 
    byte12->setMaxValue( 255 );
    QToolTip::add(  byte12, tr( "Byte 12" ) );

    byte14 = new QSpinBox( DatenBytes, "byte14" );
    byte14->setEnabled( FALSE );
    byte14->setGeometry( QRect( 110, 110, 50, 26 ) ); 
    byte14->setMaxValue( 255 );
    QToolTip::add(  byte14, tr( "Byte 14" ) );

    byte5 = new QSpinBox( DatenBytes, "byte5" );
    byte5->setEnabled( FALSE );
    byte5->setGeometry( QRect( 60, 50, 50, 26 ) ); 
    byte5->setMaxValue( 255 );
    QToolTip::add(  byte5, tr( "Byte 5" ) );

    byte4 = new QSpinBox( DatenBytes, "byte4" );
    byte4->setEnabled( FALSE );
    byte4->setGeometry( QRect( 10, 50, 50, 26 ) ); 
    byte4->setMaxValue( 255 );
    QToolTip::add(  byte4, tr( "Byte 4" ) );

    byte8 = new QSpinBox( DatenBytes, "byte8" );
    byte8->setEnabled( FALSE );
    byte8->setGeometry( QRect( 10, 80, 50, 26 ) ); 
    byte8->setMaxValue( 255 );
    QToolTip::add(  byte8, tr( "Byte 8" ) );

    byte13 = new QSpinBox( DatenBytes, "byte13" );
    byte13->setEnabled( FALSE );
    byte13->setGeometry( QRect( 60, 110, 50, 26 ) ); 
    byte13->setMaxValue( 255 );
    QToolTip::add(  byte13, tr( "Byte 13" ) );

    byte9 = new QSpinBox( DatenBytes, "byte9" );
    byte9->setEnabled( FALSE );
    byte9->setGeometry( QRect( 60, 80, 50, 26 ) ); 
    byte9->setMaxValue( 255 );
    QToolTip::add(  byte9, tr( "Byte 9" ) );

    byte10 = new QSpinBox( DatenBytes, "byte10" );
    byte10->setEnabled( FALSE );
    byte10->setGeometry( QRect( 110, 80, 50, 26 ) ); 
    byte10->setMaxValue( 255 );
    QToolTip::add(  byte10, tr( "Byte 10" ) );

    byte1 = new QSpinBox( DatenBytes, "byte1" );
    byte1->setEnabled( FALSE );
    byte1->setGeometry( QRect( 60, 20, 50, 26 ) ); 
    byte1->setMaxValue( 255 );
    QToolTip::add(  byte1, tr( "Byte 1" ) );

    byte2 = new QSpinBox( DatenBytes, "byte2" );
    byte2->setEnabled( FALSE );
    byte2->setGeometry( QRect( 110, 20, 50, 25 ) ); 
    byte2->setMaxValue( 255 );
    QToolTip::add(  byte2, tr( "Byte 2" ) );

    byte3 = new QSpinBox( DatenBytes, "byte3" );
    byte3->setEnabled( FALSE );
    byte3->setGeometry( QRect( 160, 20, 50, 26 ) ); 
    byte3->setMaxValue( 255 );
    QToolTip::add(  byte3, tr( "Byte 3" ) );

    byte7 = new QSpinBox( DatenBytes, "byte7" );
    byte7->setEnabled( FALSE );
    byte7->setGeometry( QRect( 160, 50, 50, 26 ) ); 
    byte7->setMaxValue( 255 );
    QToolTip::add(  byte7, tr( "Byte 7" ) );

    byte11 = new QSpinBox( DatenBytes, "byte11" );
    byte11->setEnabled( FALSE );
    byte11->setGeometry( QRect( 160, 80, 50, 26 ) ); 
    byte11->setMaxValue( 255 );
    QToolTip::add(  byte11, tr( "Byte 11" ) );

    byte6 = new QSpinBox( DatenBytes, "byte6" );
    byte6->setEnabled( FALSE );
    byte6->setGeometry( QRect( 110, 50, 50, 26 ) ); 
    byte6->setMaxValue( 255 );
    QToolTip::add(  byte6, tr( "Byte 6" ) );

    byte0 = new QSpinBox( DatenBytes, "byte0" );
    byte0->setEnabled( FALSE );
    byte0->setGeometry( QRect( 10, 20, 50, 26 ) ); 
    byte0->setMaxValue( 255 );
    byte0->setValue( 0 );
    QToolTip::add(  byte0, tr( "Byte 0" ) );

    toOpId = new QSpinBox( SendenTab, "toOpId" );
    toOpId->setGeometry( QRect( 160, 10, 58, 25 ) ); 
    toOpId->setMaxValue( 64 );
    QToolTip::add(  toOpId, tr( QString::fromUtf8( "Die auf dem Gerät auszulösende Operation" ) ) );

    toLength = new QSpinBox( SendenTab, "toLength" );
    toLength->setGeometry( QRect( 160, 40, 58, 25 ) ); 
    toLength->setMaxValue( 15 );
    toLength->setValue( 0 );
    QToolTip::add(  toLength, tr( QString::fromUtf8( "Anzahl der zu übertragenden Datenbytes" ) ) );
    Tab->insertTab( SendenTab, tr( "Senden" ) );

    EmpfangenTab = new QWidget( Tab, "EmpfangenTab" );

    DatenBytes_Received = new QGroupBox( EmpfangenTab, "DatenBytes_Received" );
    DatenBytes_Received->setGeometry( QRect( 10, 70, 220, 150 ) ); 
    DatenBytes_Received->setTitle( tr( "DatenBytes" ) );

    rbyte1 = new QSpinBox( DatenBytes_Received, "rbyte1" );
    rbyte1->setEnabled( FALSE );
    rbyte1->setGeometry( QRect( 60, 20, 50, 26 ) ); 
    rbyte1->setMaxValue( 255 );
    QToolTip::add(  rbyte1, tr( "Byte 1" ) );

    rbyte2 = new QSpinBox( DatenBytes_Received, "rbyte2" );
    rbyte2->setEnabled( FALSE );
    rbyte2->setGeometry( QRect( 110, 20, 50, 25 ) ); 
    rbyte2->setMaxValue( 255 );
    QToolTip::add(  rbyte2, tr( "Byte 2" ) );

    rbyte3 = new QSpinBox( DatenBytes_Received, "rbyte3" );
    rbyte3->setEnabled( FALSE );
    rbyte3->setGeometry( QRect( 160, 20, 50, 26 ) ); 
    rbyte3->setMaxValue( 255 );
    QToolTip::add(  rbyte3, tr( "Byte 3" ) );

    rbyte5 = new QSpinBox( DatenBytes_Received, "rbyte5" );
    rbyte5->setEnabled( FALSE );
    rbyte5->setGeometry( QRect( 60, 50, 50, 26 ) ); 
    rbyte5->setMaxValue( 255 );
    QToolTip::add(  rbyte5, tr( "Byte 5" ) );

    rbyte6 = new QSpinBox( DatenBytes_Received, "rbyte6" );
    rbyte6->setEnabled( FALSE );
    rbyte6->setGeometry( QRect( 110, 50, 50, 26 ) ); 
    rbyte6->setMaxValue( 255 );
    QToolTip::add(  rbyte6, tr( "Byte 6" ) );

    rbyte7 = new QSpinBox( DatenBytes_Received, "rbyte7" );
    rbyte7->setEnabled( FALSE );
    rbyte7->setGeometry( QRect( 160, 50, 50, 26 ) ); 
    rbyte7->setMaxValue( 255 );
    QToolTip::add(  rbyte7, tr( "Byte 7" ) );

    rbyte10 = new QSpinBox( DatenBytes_Received, "rbyte10" );
    rbyte10->setEnabled( FALSE );
    rbyte10->setGeometry( QRect( 110, 80, 50, 26 ) ); 
    rbyte10->setMaxValue( 255 );
    QToolTip::add(  rbyte10, tr( "Byte 10" ) );

    rbyte11 = new QSpinBox( DatenBytes_Received, "rbyte11" );
    rbyte11->setEnabled( FALSE );
    rbyte11->setGeometry( QRect( 160, 80, 50, 26 ) ); 
    rbyte11->setMaxValue( 255 );
    QToolTip::add(  rbyte11, tr( "Byte 11" ) );

    rbyte9 = new QSpinBox( DatenBytes_Received, "rbyte9" );
    rbyte9->setEnabled( FALSE );
    rbyte9->setGeometry( QRect( 60, 80, 50, 26 ) ); 
    rbyte9->setMaxValue( 255 );
    QToolTip::add(  rbyte9, tr( "Byte 9" ) );

    rbyte14 = new QSpinBox( DatenBytes_Received, "rbyte14" );
    rbyte14->setEnabled( FALSE );
    rbyte14->setGeometry( QRect( 110, 110, 50, 26 ) ); 
    rbyte14->setMaxValue( 255 );
    QToolTip::add(  rbyte14, tr( "Byte 14" ) );

    rbyte13 = new QSpinBox( DatenBytes_Received, "rbyte13" );
    rbyte13->setEnabled( FALSE );
    rbyte13->setGeometry( QRect( 60, 110, 50, 26 ) ); 
    rbyte13->setMaxValue( 255 );
    QToolTip::add(  rbyte13, tr( "Byte 13" ) );

    rbyte12 = new QSpinBox( DatenBytes_Received, "rbyte12" );
    rbyte12->setEnabled( FALSE );
    rbyte12->setGeometry( QRect( 10, 110, 50, 26 ) ); 
    rbyte12->setMaxValue( 255 );
    QToolTip::add(  rbyte12, tr( "Byte 12" ) );

    rbyte8 = new QSpinBox( DatenBytes_Received, "rbyte8" );
    rbyte8->setEnabled( FALSE );
    rbyte8->setGeometry( QRect( 10, 80, 50, 26 ) ); 
    rbyte8->setMaxValue( 255 );
    QToolTip::add(  rbyte8, tr( "Byte 8" ) );

    rbyte4 = new QSpinBox( DatenBytes_Received, "rbyte4" );
    rbyte4->setEnabled( FALSE );
    rbyte4->setGeometry( QRect( 10, 50, 50, 26 ) ); 
    rbyte4->setMaxValue( 255 );
    QToolTip::add(  rbyte4, tr( "Byte 4" ) );

    rbyte0 = new QSpinBox( DatenBytes_Received, "rbyte0" );
    rbyte0->setEnabled( FALSE );
    rbyte0->setGeometry( QRect( 10, 20, 50, 26 ) ); 
    rbyte0->setMaxValue( 255 );
    rbyte0->setValue( 0 );
    QToolTip::add(  rbyte0, tr( "Byte 0" ) );

    receiveNumber = new QSpinBox( EmpfangenTab, "receiveNumber" );
    receiveNumber->setGeometry( QRect( 160, 10, 58, 25 ) ); 
    receiveNumber->setMaxValue( 0 );
    receiveNumber->setValue( 0 );
    QToolTip::add(  receiveNumber, tr( QString::fromUtf8( "Nummer der Übertragung" ) ) );
    QWhatsThis::add(  receiveNumber, tr( QString::fromUtf8( "Einstellen, welche der gespeicherten Übertragungen angezeiht werden soll" ) ) );

    TextLabel1_2 = new QLabel( EmpfangenTab, "TextLabel1_2" );
    TextLabel1_2->setGeometry( QRect( 10, 40, 80, 20 ) ); 
    TextLabel1_2->setText( tr( "Operation:" ) );

    TextLabel4 = new QLabel( EmpfangenTab, "TextLabel4" );
    TextLabel4->setGeometry( QRect( 10, 10, 80, 20 ) ); 
    TextLabel4->setText( tr( QString::fromUtf8( "Übertragung" ) ) );

    fromOpId = new QSpinBox( EmpfangenTab, "fromOpId" );
    fromOpId->setEnabled( FALSE );
    fromOpId->setGeometry( QRect( 160, 40, 58, 25 ) ); 
    QToolTip::add(  fromOpId, tr( "Die Empfangene Operation" ) );

    Pause = new QCheckBox( EmpfangenTab, "Pause" );
    Pause->setGeometry( QRect( 70, 230, 106, 24 ) ); 
    Pause->setText( tr( "Pause" ) );
    Tab->insertTab( EmpfangenTab, tr( "Empfangen" ) );

    SetupTab = new QWidget( Tab, "SetupTab" );

    GroupBox5 = new QGroupBox( SetupTab, "GroupBox5" );
    GroupBox5->setGeometry( QRect( 8, 10, 220, 90 ) ); 
    GroupBox5->setTitle( tr( QString::fromUtf8( "Geräte-ID" ) ) );

    DeviceID = new QSpinBox( GroupBox5, "DeviceID" );
    DeviceID->setGeometry( QRect( 140, 30, 59, 26 ) ); 
    DeviceID->setMaxValue( 32 );
    DeviceID->setValue( 1 );
    QToolTip::add(  DeviceID, tr( QString::fromUtf8( "ID des zu testenden Gerätes" ) ) );
    QWhatsThis::add(  DeviceID, tr( QString::fromUtf8( "Hier kann man die ID einstellen, für die sich die GUI zuständig fühlt, d.h. die, unter der man Senden und Emfangen möchte." ) ) );

    toDeviceLabel = new QLabel( GroupBox5, "toDeviceLabel" );
    toDeviceLabel->setGeometry( QRect( 12, 30, 70, 20 ) ); 
    toDeviceLabel->setText( tr( QString::fromUtf8( "Gerät" ) ) );

    broadcast = new QCheckBox( GroupBox5, "broadcast" );
    broadcast->setGeometry( QRect( 50, 60, 106, 24 ) ); 
    broadcast->setText( tr( "Broadcast" ) );
    QToolTip::add(  broadcast, tr( "Als Broadcast senden" ) );
    QWhatsThis::add(  broadcast, tr( QString::fromUtf8( "Dies wirkt sich nicht auf das empfangen von Daten aus, da Geräte keine Broadcasts senden können." ) ) );

    QuitButton = new QPushButton( SetupTab, "QuitButton" );
    QuitButton->setGeometry( QRect( 60, 110, 116, 31 ) ); 
    QuitButton->setText( tr( "Beenden" ) );
    QToolTip::add(  QuitButton, tr( "Beendet das Programm" ) );
    Tab->insertTab( SetupTab, tr( "Setup" ) );

    // signals and slots connections
    connect( sendButton, SIGNAL( clicked() ), this, SLOT( send() ) );
    connect( toLength, SIGNAL( valueChanged(int) ), this, SLOT( setNumberOfDataBytes(int) ) );
    connect( DeviceID, SIGNAL( valueChanged(int) ), this, SLOT( setID(int) ) );
    connect( receiveNumber, SIGNAL( valueChanged(int) ), this, SLOT( showReceivedWithNumber(int) ) );
    connect( broadcast, SIGNAL( toggled(bool) ), DeviceID, SLOT( setDisabled(bool) ) );
    connect( QuitButton, SIGNAL( clicked() ), this, SLOT( quit() ) );

    // tab order
    setTabOrder( Tab, sendButton );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
DebugTreiberGUI::~DebugTreiberGUI()
{
    // no need to delete child widgets, Qt does it all for us
}

void DebugTreiberGUI::newMessage()
{
    qWarning( "DebugTreiberGUI::newMessage(): Not implemented yet!" );
}

void DebugTreiberGUI::quit()
{
    qWarning( "DebugTreiberGUI::quit(): Not implemented yet!" );
}

void DebugTreiberGUI::send()
{
    qWarning( "DebugTreiberGUI::send(): Not implemented yet!" );
}

void DebugTreiberGUI::setID(int)
{
    qWarning( "DebugTreiberGUI::setID(int): Not implemented yet!" );
}

void DebugTreiberGUI::setNumberOfDataBytes(int)
{
    qWarning( "DebugTreiberGUI::setNumberOfDataBytes(int): Not implemented yet!" );
}

void DebugTreiberGUI::showReceivedWithNumber(int)
{
    qWarning( "DebugTreiberGUI::showReceivedWithNumber(int): Not implemented yet!" );
}


#include "GoRide.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qpe/qpeapplication.h>
#include <qpixmap.h>
#include <qtimer.h>

#include "Serial.h"

#define LBLINKER_AN 'L'
#define LBLINKER_AUS 'l'
#define RBLINKER_AN 'R'
#define RBLINKER_AUS 'r'
#define FERN_AN 'F'
#define FERN_AUS 'f'
#define ABBLEND_AN 'A'
#define ABBLEND_AUS 'a'


#define BLINK_INTERVAL 750 /* Flashing time in ms */

/*
 *  Constructs a GoRide which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
GoRide::GoRide( QWidget* parent,  const char* name, WFlags fl )
  : GoRideUI( parent, name, fl )
{
  /*
   * Set the font for the Status line
   */
  QFont f("smallsmooth",9,QFont::Normal,false);
  StatusAktuell->setFont(f);
  
 
  /*
   * Connect the Button "LaeuferButton" to the quit action of the app
   */
  QObject::connect( LaeuferButton, SIGNAL( clicked() ), qApp, SLOT( quit()) );
  
  
  /*
   * Create a new serial object.
   * This is used to access the RS232 connector of the device
   */
  com = new Serial();
  com -> openPort();
  
  
  /*
   * Boolean Variables for the different buttons.
   * These default to false
   */
  babblend=false;
  blinks=false;
  brechts=false;
  bfern=false;
  block=false;
  bstaender=false;
  
  
  /*
   * Load the pictures for the buttons from the harddrive
   */
  
  abblendlicht_aktiv = Resource::loadPixmap("Laeufer/abblendlicht_aktiv.png");
  abblendlicht_inaktiv = Resource::loadPixmap("Laeufer/abblendlicht_inaktiv.png");
  
  blinker_links_aktiv = Resource::loadPixmap("Laeufer/blinker_links_aktiv.png");
  blinker_links_inaktiv = Resource::loadPixmap("Laeufer/blinker_links_inaktiv.png");
  
  blinker_rechts_aktiv = Resource::loadPixmap("Laeufer/blinker_rechts_aktiv.png");
  blinker_rechts_inaktiv = Resource::loadPixmap("Laeufer/blinker_rechts_inaktiv.png");
  
  fernlicht_aktiv = Resource::loadPixmap("Laeufer/fernlicht_aktiv.png");
  fernlicht_inaktiv = Resource::loadPixmap("Laeufer/fernlicht_inaktiv.png");
  
  lock_aktiv = Resource::loadPixmap("Laeufer/lock_aktiv.png");
  lock_inaktiv = Resource::loadPixmap("Laeufer/lock_inaktiv.png");
  
  staender_aktiv = Resource::loadPixmap("Laeufer/staender_aktiv.png");
  staender_inaktiv =  Resource::loadPixmap("Laeufer/staender_inaktiv.png");
  
   
  /*
   * Assign these Pictures
   */
  AbblendButton -> setPixmap( abblendlicht_inaktiv );
  BlinkenLinksButton -> setPixmap( blinker_links_inaktiv );
  BlinkenRechtsButton -> setPixmap( blinker_rechts_inaktiv );
  FernlichtButton -> setPixmap( fernlicht_inaktiv );
  LockButton -> setPixmap( lock_inaktiv );
  StaenderButton -> setPixmap( staender_inaktiv );


  /**
   * Create the QTimer needed for the flashing
   */
  timer = new QTimer( this );
  timer -> start(BLINK_INTERVAL, false);
  QObject::connect(timer,SIGNAL(timeout()),this,SLOT(send()));
}





/*
 *  Destroys the object and frees any allocated resources
 */
GoRide::~GoRide()
{
  delete com;
}




/*
 * public slot
 */
void GoRide::abblendlicht( void )
{
  babblend = !babblend;
  if(babblend){
    if(bfern) fernlicht();
    setStatus( "Dimmed Light" );
    AbblendButton->setPixmap(abblendlicht_aktiv);
  }
  else
    {
      com->send(ABBLEND_AUS);
      AbblendButton->setPixmap(abblendlicht_inaktiv);
    }
}


/*
 * public slot
 */
void GoRide::fernlicht(void)
{
  bfern = !bfern;
  if(bfern)
    {
      com->send(FERN_AN);
      if(babblend)
	{
	  abblendlicht();
	}
      setStatus( "Full Beam");
      FernlichtButton->setPixmap(fernlicht_aktiv);
    }
  else
    {
      FernlichtButton->setPixmap(fernlicht_inaktiv);
      com->send(FERN_AUS);
    }
  
}



/*
 * public slot
 */
void GoRide::blinken_links(void){
  blinks = !blinks;

  if(blinks){
    com->send(LBLINKER_AN);
    if(brechts) blinken_rechts();
    setStatus( "Indicate Left");
    BlinkenLinksButton->setPixmap(blinker_links_aktiv);
  }

  else{
    QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(sendL())); 
    com->send(LBLINKER_AUS);
    BlinkenLinksButton->setPixmap(blinker_links_inaktiv);
  }
}




/*
 * public slot
 */
void GoRide::blinken_rechts(void)
{
  brechts=!brechts;

  if(brechts){
    com->send(RBLINKER_AN);
    if(blinks)blinken_links();
    setStatus( "Indicate Right");
    BlinkenRechtsButton->setPixmap(blinker_rechts_aktiv);
  }
  
  else{
    com->send(RBLINKER_AUS);
    BlinkenRechtsButton->setPixmap(blinker_rechts_inaktiv);
  }
}


/*
 * public slot
 */
void GoRide::abschliessen(void)
{
  block = !block;
  
  if(block)
    {
      setStatus( "Lock" );
      LockButton->setPixmap(lock_aktiv);
    }
  else
    {
      LockButton->setPixmap(lock_inaktiv);
    }
  
}




/*
 * public slot
 */
void GoRide::staender(void)
{
  bstaender = !bstaender;
  if(bstaender)
    {
      StaenderButton->setPixmap(staender_aktiv);
      setStatus( "Stand out" );
    }
  
  else
    {
      StaenderButton->setPixmap(staender_inaktiv);
    }
  
}



/**
 * Shows the given text in the status field
 */
void GoRide::setStatus(const QString &str)
{
  StatusAktuell->setText(str);
}






/**
 * Sendet die Befehle
 */
void GoRide::send( void )
{
  if( brechts )
    com->send(RBLINKER_AN);
  else 
    com->send(RBLINKER_AUS);
  if( blinks )
    com->send(LBLINKER_AN);
  else
    com->send(LBLINKER_AUS);
  /* if( babblend )
     com->send(ABBLEND_AN);
     if ( bfern )
     com->send(FERN_AN);  */
}



/**
 *Haesslicher Code fuer Fullscreen Mode
 */

void GoRide::resizeEvent(QResizeEvent *) {
  if(size() != qApp->desktop()->size()) {
    // Widget is not the correct size, so do the fullscreen magic
    enableFullscreen();
  }
}
void GoRide::focusInEvent(QFocusEvent *) {
  // Always do it here, no matter the size.
  enableFullscreen();
}


void GoRide::enableFullscreen() {
  // Make sure size is correct
  setFixedSize(qApp->desktop()->size());
  // This call is needed because showFullScreen won't work
  // correctly if the widget already considers itself to be fullscreen.
  showNormal();
  // This is needed because showNormal() forcefully changes the window
  // style to WSTyle_TopLevel.
  reparent(0, WStyle_Customize | WStyle_NoBorder, QPoint(0,0));
  // Enable fullscreen.
  showFullScreen();
}


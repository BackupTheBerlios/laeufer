#ifndef GORIDE_H
#define GORIDE_H

#include "Serial.h"
#include "GoRideUI.h"
#include <qstring.h>
#include <qtimer.h>
#include <qpe/resource.h>

class GoRide : public GoRideUI
{
   Q_OBJECT

 public:
   GoRide( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
   ~GoRide();
   /**
    * Enables fullscreen operation
    */
   void enableFullscreen( void );
   
   
 public slots:
   /**
    * Set the dimmed light to on or off
    */
   void abblendlicht( void );
 
   /**
    * Set the left indicator to on or off
    */
   void blinken_links( void );
   
   /**
    * Set the right indicator to on or off
    */
   void blinken_rechts( void );
   
   /**
	 * Set the full beam to on or off
    */
   void fernlicht( void );
   
   /**
    * Lock or unlock the device
    */
   void abschliessen( void );
   
   /**
    * Put the stand out or in
    */
   void staender( void );

 private:
   void resizeEvent( QResizeEvent * );
   void focusInEvent(QFocusEvent* );


 private slots:
   void send( void );



   /**
    * Adds a line to the status line
    */
   void setStatus(const QString &str);
   Serial* com;
   bool babblend, blinks, brechts, bfern, block, bstaender;
   
   /*
    * Pixmaps der Buttons
    */
   QPixmap abblendlicht_aktiv, abblendlicht_inaktiv, 
     blinker_links_aktiv, blinker_links_inaktiv, 
     blinker_rechts_aktiv, blinker_rechts_inaktiv,
     fernlicht_aktiv, fernlicht_inaktiv,
     staender_aktiv, staender_inaktiv,
     lock_aktiv, lock_inaktiv;
   
   /*
    * Timer
    */
   QTimer* timer;
      
   
   
};

#endif // GORIDE_H

#ifndef _NOTIFIER_H
#define _NOTIFIER_H
#include <qobject.h>


class QSocketNotifier;
class QObject;

/**
 * File change notifier based on QT.
 *
 * This class provides the "glue" between a QT-Application with all
 * the bells and whistles to normal C-Code which needs to know about a
 * file-change, but not about the presence of QT.
 *
 * This class *NEEDS* a running QT-Application to work.
 *
 * @author Markus Weimer <markus.weimer@web.de>
 * @version 0.1.0
 */
class notifier:public QObject
{
  Q_OBJECT

 public:
  /**
   * The Constructor.
   *
   * @param HANDLE the c-style file-handle for the file to be watched
   *
   * @param F(void) a pointer to the function to call, when the file changes
   * the file changes.
   */
  notifier(int HANDLE, void (*F)(void));
  
  /**
   * Starts the file-watching.
   * 
   * If the file given in the constructor changes, the function given
   * in the constructor will be called from now on.
   */
  void start( void );
  
  private slots:
	/**
	 * This slot is used to call the "real" method only.
	 */
    void notify( void );
  
 private:
  void (*f)(void); /**< The function pointer */
  QSocketNotifier* q; /**< The Notifier */
};
#endif


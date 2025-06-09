//========================
// - Info -
// - Window Class
// - Author : juju80gen -
//========================

#ifndef _WINDOW_CLASS_
#define _WINDOW_CLASS_

//==============
// - INCLUDES -
//==============
#include <QtWidgets>

//================
// - CLASSES -
//================
class Window : QWidget
{
    private:
        QGridLayout *layout;
        // token
        QPushButton *validateToken;
        QTextEdit   *token;
        // git status
        QPushButton *buttonStatus;
    public:
        using QWidget::QObject; // for QObject inheritance

        // events
        void onClickToken(); 
        void onClickStatus();

        // getters
        QString getToken();

        // constructor
        Window();
};

#endif


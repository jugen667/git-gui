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
        QTextEdit   *tokenTxtBox;
        // git status
        QPushButton *buttonStatus;
    public:
        using QWidget::QObject; // for QObject inheritance

        // events
        void onClickToken(); 
        void onClickStatus();

        // widgets population
        void ButtonCreation(QPushButton * pBtn, const char * btnTxt, const char * btnToolTip, int x, int y, int w, int h);
        void TextBoxCreation(QTextEdit * pTxtBox, int x, int y, int w, int h);

        // getters
        QString getToken();

        // constructor
        Window();
};

#endif


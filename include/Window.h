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
#include "GitObj.h"


//================
// - CLASSES -
//================
class Window : QWidget, GitObj
{
    private:
        QGridLayout *layout;
        // to link with a git obj
        GitObj * git_object;
        // git status
        QPushButton *buttonStatus;
        QLabel      *labelStatus;
        QListWidget * changesStatus;
    public:
        using QWidget::QObject; // for QObject inheritance
        // events
        void onClickStatus();
        // void onClickRepo();

        // widgets population
        void ButtonCreation(QPushButton * pBtn, const char * btnTxt, const char * btnToolTip, int x, int y, int w, int h);
        void TextBoxCreation(QTextEdit * pTxtBox, int x, int y, int w, int h);

        // getters
        // const char* getPath();

        // constructor
        Window(GitObj * git_obj);
};

#endif


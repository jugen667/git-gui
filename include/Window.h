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
        // to link with a git obj
        GitObj * git_object;
        QGridLayout *layout;
        // token
        QPushButton *validateToken;
        QTextEdit   *tokenTxtBox;
        // git status
        QPushButton *buttonStatus;
        QLabel      *labelStatus;
        // repo path
        QPushButton *validateRepo;
        QTextEdit   *repoPathTxtBox;
    public:
        using QWidget::QObject; // for QObject inheritance
        // events
        void onClickToken(); 
        void onClickStatus();
        void onClickRepo();

        // widgets population
        void ButtonCreation(QPushButton * pBtn, const char * btnTxt, const char * btnToolTip, int x, int y, int w, int h);
        void TextBoxCreation(QTextEdit * pTxtBox, int x, int y, int w, int h);

        // getters
        QString getToken();
        const char* getPath();

        // constructor
        Window(GitObj * git_obj);
};

#endif


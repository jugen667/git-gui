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
#include <vector>
#include "GitObj.h"

//==============
// -  DEFINES  -
//==============
#define COL_AMT 2 


//================
// - CLASSES -
//================
class Window : QWidget, GitObj
{
    private:
        QGridLayout     * layout;
        // save for the entry
        std::vector<git_status_entry> statusList;
        std::vector<git_status_entry> addList;
        // to link with a git obj
        GitObj          * git_objct;

        // git status
        QPushButton     * buttonStatus;
        QLabel          * labelStatus;
        // git add
        QPushButton     * addButton;
        QLabel          * labelAdd;
        // git commit
        QPushButton     * commitButton;
        QLabel          * labelCommit;
        // GUI tables
        QTableWidget    * changesStatus;
        QTableWidget    * addedFile; 
        // Comment textbox
        QLabel          * labelComment;
        QTextEdit       * commentTextBox;
        // result textbox
        QTextEdit       * resultTextBox;

    public:
        using QWidget::QObject; // for QObject inheritance
        // events
        void onClickStatus();
        void onClickAdd();
        void onClickGenerate();
        // void onClickRepo();

        // widgets population
        void ButtonCreation(QPushButton * pBtn, const char * btnTxt, const char * btnToolTip, int x, int y, int w, int h);
        void TextBoxCreation(QTextEdit * pTxtBox, int x, int y, int w, int h);

        // getters
        const char* getPath();
        const QString getComment();
        bool getCommentEmpty();

        QTableWidget * GetAddedFile();
        Window * GetWindow();
        // constructor
        Window(GitObj * git_obj);
};

#endif


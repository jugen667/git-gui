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
        // generate
        QPushButton     * generateButton;
        // GUI tables
        QTableWidget    * changesStatus;
        QTableWidget    * addedFile; 
        // Comment textbox
        QLabel          * labelComment;
        QTextEdit       * commentTextBox;
        // Repo open textbox
        QPushButton     * repoButton;
        QTextEdit       * repoTextBox;
        // result textbox
        QTextEdit       * resultTextBox;
        // checkboxes
        QCheckBox       * pushCheckBox;
        QCheckBox       * forceCheckBox;
        QCheckBox       * pullCheckBox;
        QCheckBox       * branchCheckBox;
        QTextEdit       * branchTextBox;


    public:
        using QWidget::QObject; // for QObject inheritance
        // events
        void onClickStatus();
        void onClickAdd();
        void onClickGenerate();
        void onClickRepo();
        void onClickPushCheck();
        void onClickBranchCheck();

        // widgets population
        void ButtonCreation(QPushButton * pBtn, const char * btnTxt, const char * btnToolTip, int x, int y, int w, int h);
        void TextBoxCreation(QTextEdit * pTxtBox, int x, int y, int w, int h);

        // getters
        const QString getText(QTextEdit * TextBox);
        bool isTextEmpty(QTextEdit * TextBox);
        Qt::CheckState getCheckBoxState(QCheckBox * CheckBox);
        void SetVisible(QWidget * Widget, bool value);
;
        QTableWidget * GetAddedFile();
        Window * GetWindow();
        // constructor
        Window(GitObj * git_obj);
};

#endif


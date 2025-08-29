//========================
// - Info -
// - about -
// - File -
// - Author : juju80gen -
//========================

//==============
// - INCLUDES -
//==============
#include "../include/includes.h"


//===============
// - METHODS -
//===============

// main window construction
Window::Window(GitObj * git_obj) 
{
    // fields initialization
    layout          =   new QGridLayout;
    buttonStatus    =   new QPushButton(NULL,this); 
    addButton       =   new QPushButton(NULL,this); 
    labelStatus     =   new QLabel(NULL,this); 
    labelAdd        =   new QLabel(NULL,this); 
    changesStatus   =   new QTableWidget(this); 
    addedFile       =   new QTableWidget(this); 
    git_object      =   git_obj;

    ButtonCreation(buttonStatus, "Get status", "Execute git status", 30,30,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);
    labelStatus->setGeometry(30,90,120,30);
    changesStatus->setGeometry(30,170,300,400);
    changesStatus->setColumnCount(COL_AMT);
    
    
    addedFile->setGeometry(350,170,300,400);
    labelAdd->setGeometry(30,130,80,30);
    ButtonCreation(addButton, "Add file(s)", "Add selected files", 130,30,80,30);

    QPushButton::connect(addButton, &QPushButton::clicked, this, &Window::onClickAdd);

    // window display
    this->setFixedSize(1280, 720);
    this->setVisible(true);
}
 

// setup of a button in the window
void Window::ButtonCreation(QPushButton * pBtn, 
                            const char * btnTxt, 
                            const char * btnToolTip, 
                            int x, int y, int w, int h)
{
    pBtn->setText(btnTxt);
    pBtn->setToolTip(btnToolTip);
    pBtn->setGeometry(x,y,w,h);
}

// setup of a textbox in the window
void Window::TextBoxCreation(QTextEdit * pTxtBox, 
                            int x, int y, int w, int h)
{
    pTxtBox->setGeometry(x,y,w,h);
}

// events managements
void Window::onClickStatus()
{
    int count;
    const git_status_entry * entry;
    QTableWidgetItem * tempItem;
    git_status_list_new(Window::git_object->GetGitStatusListAddress(), Window::git_object->GetCurrentGitRepo(), NULL);
    count = git_status_list_entrycount(Window::git_object->GetGitStatusList());
    if(count > 0)
    {
        // clear tables
        changesStatus->clear();
        addedFile->clear();
        QString str;
        str = QString::number(count) + " diff(s) found ";
        Window::labelStatus->setText(str);
        changesStatus->setHorizontalHeaderLabels({"FileName","Status"});
        changesStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
        changesStatus->setSelectionMode(QAbstractItemView::ExtendedSelection);

        changesStatus->setRowCount(count);
        for (int i=0; i<count; i++)
        {
            entry = git_status_byindex(Window::git_object->GetGitStatusList(), i);
            tempItem = new QTableWidgetItem;
            tempItem->setText(entry->index_to_workdir->new_file.path);
            changesStatus->setItem(i, 0, tempItem); 
            qDebug() << tempItem->text();
            tempItem = new QTableWidgetItem;
            tempItem->setText(ReturnStatus(entry));
            changesStatus->setItem(i, 1, tempItem); 
            qDebug() << tempItem->text();
            qDebug() << changesStatus->rowCount(); 
        }
        changesStatus->resizeColumnsToContents();
    }
}

void Window::onClickAdd()
{
    // QTableWidgetItem * tempItem;
    // tempItem = new QTableWidgetItem;
    // tempItem = changesStatus->selectedItems()[0];
    // addFile->setItem(0, 1, tempItem);
    QString str;
    str = "Added files";
    Window::labelAdd->setText(str);
    std::cout << "onclickadd" << std::endl;
}

/*
// --- REPO NOT WORKING WITH CUSTOM PATH ---//
void Window::onClickRepo()
{
    int error;
    std::cout << repoPathTxtBox->toPlainText().toStdString().c_str() << std::endl;
    error = git_repository_open(Window::git_object->GetCurrentGitRepoAddress(), Window::getPath());
    std::cout << error << std::endl;
}

// getters
const char* Window::getPath() 
{
    return repoPathTxtBox->toPlainText().toStdString().c_str();
}
*/


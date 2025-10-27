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

static int curFile = 0;
static int maxFile = 0;
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
    commitButton    =   new QPushButton(NULL,this); 
    labelStatus     =   new QLabel(NULL,this); 
    labelAdd        =   new QLabel(NULL,this); 
    labelCommit     =   new QLabel(NULL,this); 
    changesStatus   =   new QTableWidget(this); 
    addedFile       =   new QTableWidget(this); 
    git_objct       =   git_obj;

    // add author / token field
    // add options checkbox 
    // add comment field


    labelStatus->setGeometry(30,90,120,30);
    ButtonCreation(buttonStatus, "Get status", "Execute git status (resets added files)", 30,30,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);
    labelAdd->setGeometry(350,90,120,30);
    ButtonCreation(addButton, "Add file(s)", "Add selected files", 130,30,80,30);
    QPushButton::connect(addButton, &QPushButton::clicked, this, &Window::onClickAdd);
    labelCommit->setGeometry(670,90,120,30);
    ButtonCreation(commitButton, "Commit file(s)", "Commit added files", 230,30,100,30);
    QPushButton::connect(commitButton, &QPushButton::clicked, this, &Window::onClickCommit);

    changesStatus->setGeometry(30,170,300,400);
    changesStatus->setColumnCount(COL_AMT);    
    addedFile->setGeometry(350,170,300,400);
    addedFile->setColumnCount(COL_AMT);

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
// void Window::onClickStatus0()
// {
//     int count;
//     const git_status_entry * entry;
//     QTableWidgetItem * tempItem;
//     // init list
//     git_status_list_new(Window::git_objct->GetGitStatusListAddress(), Window::git_objct->GetCurrentGitRepo(), Window::git_objct->GetGitStatusOpt());
//     count = git_status_list_entrycount(Window::git_objct->GetGitStatusList());
//     maxFile = count;
//     if(count > 0)
//     {
//         // clear tables
//         changesStatus->clear();
//         addedFile->clear();
//         addedFile->setRowCount(0);
//         curFile = 0;
//         QString str;
//         str = QString::number(count) + " diff(s) found ";
//         Window::labelStatus->setText(str);
//         changesStatus->setHorizontalHeaderLabels({"FileName","Status"});
//         changesStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
//         changesStatus->setSelectionMode(QAbstractItemView::ExtendedSelection);

//         changesStatus->setRowCount(count);
//         for (int i=0; i<count; i++)
//         {
//             entry = git_status_byindex(Window::git_objct->GetGitStatusList(), i);
// #if defined (__DEBUG)
//             DisplayStatus(entry);
// #endif
//             tempItem = new QTableWidgetItem;
//             tempItem->setText(entry->index_to_workdir->new_file.path);
//             changesStatus->setItem(i, 0, tempItem); 
//             tempItem = new QTableWidgetItem;
//             tempItem->setText(ReturnStatus(entry));
//             changesStatus->setItem(i, 1, tempItem);
//         }
//         changesStatus->resizeColumnsToContents();
//     }
// }
void Window::onClickStatus()
{
    int count;
    const git_status_entry * entry;
    QTableWidgetItem * tempItem;
    // init list
    git_status_list_new(Window::git_objct->GetGitStatusListAddress(), Window::git_objct->GetCurrentGitRepo(), Window::git_objct->GetGitStatusOpt());
    count = git_status_list_entrycount(Window::git_objct->GetGitStatusList());
    maxFile = count;
    if(count > 0)
    {
        // clear tables
        changesStatus->clear();
        addedFile->clear();
        addedFile->setRowCount(0);
        curFile = 0;
        QString str;
        str = QString::number(count) + " diff(s) found ";
        Window::labelStatus->setText(str);
        changesStatus->setHorizontalHeaderLabels({"FileName","Status"});
        changesStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
        changesStatus->setSelectionMode(QAbstractItemView::ExtendedSelection);

        changesStatus->setRowCount(count);
        for (int i=0; i<count; i++)
        {
            entry = git_status_byindex(Window::git_objct->GetGitStatusList(), i);
#if defined (__DEBUG)
            DisplayStatus(entry);
#endif
            tempItem = new QTableWidgetItem();
            tempItem->setData(Qt::UserRole, entry);
            tempItem->setData(Qt::DisplayRole, entry->index_to_workdir->new_file.path);
            changesStatus->setItem(i, 0, tempItem); 
            tempItem = new QTableWidgetItem;
            tempItem->setData(Qt::UserRole, entry);
            tempItem->setData(Qt::DisplayRole, ReturnStatus(entry));
            changesStatus->setItem(i, 1, tempItem);
            // tempItem->setText(entry->index_to_workdir->new_file.path);
            // tempItem->setText(ReturnStatus(entry));
        }
        changesStatus->resizeColumnsToContents();
    }
}

// void Window::onClickAdd()
// {
//     // if it works it works
//     QTableWidgetItem * tempItem;
//     int actualSize = 0;
//     addedFile->setRowCount( curFile/2 + changesStatus->selectedItems().size()); 
//     addedFile->setHorizontalHeaderLabels({"FileName","Status"});
//     addedFile->setSelectionBehavior(QAbstractItemView::SelectRows);
//     addedFile->setSelectionMode(QAbstractItemView::ExtendedSelection);
//     if(curFile/2 < maxFile)
//     {
//         for(int i = 0; i < changesStatus->selectedItems().size(); i++)
//         { 
//             // tempItem = new QTableWidgetItem;
//             // tempItem = changesStatus->selectedItems()[i]->clone();
//             addedFile->setItem(i%2 ? curFile/2 + i - 1 : curFile/2 + i, i%2 ? 1 : 0, /*tempItem*/ changesStatus->selectedItems()[i]->clone());
//             actualSize++;
//         }
//         curFile += changesStatus->selectedItems().size();
//         for(int i = 0; i < curFile; i++)
//         {
//             if(!addedFile->item(i, 0))
//             {
//                 addedFile->removeRow(i);
//             }
//         }
//         addedFile->resizeColumnsToContents();
//     }
//     addedFile->setRowCount(curFile/2);
//     QString str;
//     str =  QString::number(curFile/2) + " added files";
//     Window::labelAdd->setText(str);
// }

void Window::onClickAdd()
{
    // if it works it works
    QTableWidgetItem * tempItem;
    int actualSize = 0;
    addedFile->setRowCount( curFile/2 + changesStatus->selectedItems().size()); 
    addedFile->setHorizontalHeaderLabels({"FileName","Status"});
    addedFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    addedFile->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if(curFile/2 < maxFile)
    {
        for(int i = 0; i < changesStatus->selectedItems().size(); i++)
        { 
            // tempItem = new QTableWidgetItem;
            // tempItem = changesStatus->selectedItems()[i]->clone();
            addedFile->setItem(i%2 ? curFile/2 + i - 1 : curFile/2 + i, i%2 ? 1 : 0, /*tempItem*/ changesStatus->selectedItems()[i]->clone());

            actualSize++;
        }
        curFile += changesStatus->selectedItems().size();
        for(int i = 0; i < curFile; i++)
        {
            if(!addedFile->item(i, 0))
            {
                addedFile->removeRow(i);
            }
        }
        addedFile->resizeColumnsToContents();
    }
    addedFile->setRowCount(curFile/2);
    QString str;
    str =  QString::number(curFile/2) + " added files";
    Window::labelAdd->setText(str);
}

void Window::onClickCommit()
{
    git_oid commit_oid,tree_oid;
    git_tree *tree;
    git_index *index;
    git_object *parnt = NULL;
    git_reference *ref = NULL;
    git_signature *author_signature, *committer_signature;
    const char * comment = "Test commit using git-gui"; 
    QString str;
    str =  "Commit !";

#if defined (__DEBUG)
    qDebug() << git_revparse_ext(&parnt, &ref, git_objct->GetCurrentGitRepo(), "HEAD");
    qDebug() << git_repository_index(&index, git_objct->GetCurrentGitRepo());
    qDebug() << git_index_write_tree(&tree_oid, index);
    qDebug() << git_index_write(index);
    qDebug() << git_tree_lookup(&tree, git_objct->GetCurrentGitRepo(), &tree_oid);
    qDebug() << git_signature_now(&author_signature,"", "");
    qDebug() << git_signature_now(&committer_signature,"", "");
    qDebug() << git_commit_create_v(
        &commit_oid,
        git_objct->GetCurrentGitRepo(),
        "HEAD",
        author_signature,
        committer_signature,
        NULL,
        comment,
        tree,
        parnt ? 1 : 0, parnt);
#else
#endif
    Window::labelCommit->setText(str);
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


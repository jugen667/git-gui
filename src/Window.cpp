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
static int actualSize = 0;
static std::vector<std::string> pathList;


enum index_mode {
    INDEX_NONE,
    INDEX_ADD
};

struct index_options {
    int dry_run;
    int verbose;
    git_repository *repo;
    enum index_mode mode;
    int add_update;
};


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
<<<<<<< HEAD
    labelGitName    =   new QLabel(NULL,this); 
    labelGitMail    =   new QLabel(NULL,this); 
    gitNameTextBox  =   new QTextEdit("", this);    
    gitMailTextBox  =   new QTextEdit("", this);
=======
>>>>>>> b557b270115b6e7a1bf0f6f77ad2973107d6dfc5
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

    labelGitName->setGeometry(30,600,300,30);
    labelGitName->setText("Enter your git name : ");
    gitNameTextBox->setGeometry(200,600,300,30);
    labelGitMail->setGeometry(30,650,300,30);
    labelGitMail->setText("Enter your git mail : ");
    gitMailTextBox->setGeometry(200,650,300,30);

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
        pathList.clear();
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
<<<<<<< HEAD
            tempItem = new QTableWidgetItem();
=======
            tempItem = new QTableWidgetItem;
>>>>>>> b557b270115b6e7a1bf0f6f77ad2973107d6dfc5
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
    QString tempStr;
    int flag = 0;
    actualSize = 0;
    addedFile->setRowCount( curFile/2 + changesStatus->selectedItems().size()); 
    addedFile->setHorizontalHeaderLabels({"FileName","Status"});
    addedFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    addedFile->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if(curFile/2 < maxFile)
    {
        for(int i = 0; i < changesStatus->selectedItems().size(); i++)
        {
            std::cout << pathList.size() << std::endl;
            for(int j = 0; j < pathList.size(); j++)
            {
                if(i%2 == 0)
                {
                    std::cout << i << ", " << changesStatus->selectedItems()[i]->text().toStdString() << ", " << pathList[j] << std::endl;
                    if(changesStatus->selectedItems()[i]->text().toStdString() == pathList[j])
                    {
                        std::cout << changesStatus->selectedItems()[i]->text().toStdString() << " already in pathlist at position "  << j << " : " << pathList[j] << std::endl;
                        flag = 1;
                        break;
                    }
                    else
                    {
                        std::cout << "NOT IN PATHLIST" << std::endl;
                        continue;
                    }
                }
            }

            std::cout << "flag :" << flag << std::endl;
            if(flag == 0)
            {
                std::cout << "adding file :" <<changesStatus->selectedItems()[i]->text().toStdString()  << std::endl;
                std::cout << "i : " << i << std::endl;
                std::cout << "i%2 : " << i%2 << std::endl;
                std::cout << "curFile/2 + i - 1 : " << curFile/2 + i - 1 << std::endl;
                std::cout << "curFile/2 + i : " << curFile/2 + i << std::endl;
                addedFile->setItem(i%2 ? curFile/2 + i - 1 : curFile/2 + i, i%2, changesStatus->selectedItems()[i]->clone());
                if(i%2 == 0)
                {
                    pathList.push_back(changesStatus->selectedItems()[i]->text().toStdString());
                }
                actualSize++;
                flag = 0;
            }
            else
            {
                flag = 0;   
                break;
            }
        }
        if(actualSize)
            curFile += actualSize;
        for(int i = 0; i < curFile; i++)
        {
            if(!addedFile->item(i, 0))
            {
                addedFile->removeRow(i);
            }
            
        }
        addedFile->resizeColumnsToContents();
    }
    // for(int i = 0; i < pathList.size(); i++)
    //     std::cout << pathList[i] << std::endl;
    addedFile->setRowCount(curFile/2);
    QString str;
    str =  QString::number(curFile/2) + " added files";
    Window::labelAdd->setText(str);
}

int callbackCheck(const char *path, const char *matched_pathspec, void *payload)
{
    struct index_options *opts = (struct index_options *)(payload);
    int ret;
    unsigned status;
    (void) matched_pathspec;
    // /* Get the file status */
    if (git_status_file(&status, opts->repo, path) < 0)
        return -1;

#if defined (__DEBUG)
    if ((status & GIT_STATUS_WT_MODIFIED) || (status & GIT_STATUS_WT_NEW)) 
    {
        // std::cout << "-> add " <<  path << std::endl;
    }
#endif

    ret = 1;

    for(int i = 0; i < actualSize; i++)
    {
        if((std::string) pathList[i] == path)
        {
            ret = 0;
        }
    }

    return ret;
}

void Window::onClickCommit()
{
    git_oid commit_oid,tree_oid;
    git_tree *tree;
    git_index *index;
    git_object *parnt = NULL;
    git_reference *ref = NULL;
    struct index_options options;
    git_signature *author_signature, *committer_signature;
    const char * comment = "File addition with git-gui"; 
    QString str;
    str =  "Commit !";

    options.repo = git_objct->GetCurrentGitRepo();

#if defined (__DEBUG)
    qDebug() << git_revparse_ext(&parnt, &ref, git_objct->GetCurrentGitRepo(), "HEAD");
    qDebug() << git_repository_index(&index, git_objct->GetCurrentGitRepo());
    qDebug() << git_index_write_tree(&tree_oid, index);
    qDebug() << git_index_update_all(index, NULL, callbackCheck, &options);
    qDebug() << git_index_write(index);
    qDebug() << git_tree_lookup(&tree, git_objct->GetCurrentGitRepo(), &tree_oid);
    qDebug() << git_signature_now(&author_signature, this->getGitName(), this->getGitMail());
    qDebug() << git_signature_now(&committer_signature,this->getGitName(), this->getGitMail());
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

const char* Window::getGitName() 
{
    return gitNameTextBox->toPlainText().toStdString().c_str();
}

const char* Window::getGitMail() 
{
    return gitMailTextBox->toPlainText().toStdString().c_str();
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


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

static unsigned int curFile = 0;
static unsigned int maxFile = 0;
static std::vector<std::string> pathList;
static char tmpStr[64] = {0}; 

//===============
// - METHODS -
//===============

// main window construction
Window::Window(GitObj * git_obj) 
{
    // fields initialization
    git_objct       =   git_obj;
    layout          =   new QGridLayout;
    // buttons
    buttonStatus    =   new QPushButton(NULL,this); 
    addButton       =   new QPushButton(NULL,this); 
    commitButton    =   new QPushButton(NULL,this); 
    pushButton      =   new QPushButton(NULL,this);
    // labels 
    labelStatus     =   new QLabel(NULL,this); 
    labelAdd        =   new QLabel(NULL,this); 
    labelCommit     =   new QLabel(NULL,this); 
    labelPush       =   new QLabel(NULL,this); 
    labelGitName    =   new QLabel(NULL,this); 
    labelGitMail    =   new QLabel(NULL,this); 
    labelComment    =   new QLabel(NULL,this); 
    // lists
    changesStatus   =   new QTableWidget(this); 
    addedFile       =   new QTableWidget(this); 
    // text boxes
    gitNameTextBox  =   new QTextEdit("", this);    
    gitMailTextBox  =   new QTextEdit("", this);
    commentTextBox  =   new QTextEdit("", this);


    // add token field
    // add options checkbox 
    // add comment field


    labelStatus->setGeometry(30,90,120,30);
    ButtonCreation(buttonStatus, "Get status", "Execute git status (resets added files)", 30,30,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);
    labelAdd->setGeometry(350,90,120,30);
    ButtonCreation(addButton, "Add file(s)", "Add selected files", 130,30,80,30);
    QPushButton::connect(addButton, &QPushButton::clicked, this, &Window::onClickAdd);
    labelCommit->setGeometry(800,90,300,30);
    ButtonCreation(commitButton, "Commit file(s)", "Commit added files", 800,30,100,30);
    QPushButton::connect(commitButton, &QPushButton::clicked, this, &Window::onClickCommit);
    labelPush->setGeometry(900,90,120,30);
    ButtonCreation(pushButton, "Push commited files", "Push", 930,30,150,30);
    QPushButton::connect(pushButton, &QPushButton::clicked, this, &Window::onClickPush);

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

    labelComment->setGeometry(800,130,300,30);
    labelComment->setText("Enter your comment : ");
    commentTextBox->setGeometry(800,170,300,200);

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
    QString str;
    const git_status_entry * entry;
    QTableWidgetItem * tempItem;
    // init list
    git_status_list_new(Window::git_objct->GetGitStatusListAddress(), 
                        Window::git_objct->GetCurrentGitRepo(), 
                        Window::git_objct->GetGitStatusOpt());
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
        str = QString::number(count) + " diff(s) found ";
        Window::labelStatus->setText(str);
        changesStatus->setHorizontalHeaderLabels({"FileName","Status"});
        changesStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
        changesStatus->setSelectionMode(QAbstractItemView::ExtendedSelection);

        changesStatus->setRowCount(count);
        for (int i=0; i<count; i++)
        {
            entry = git_status_byindex(Window::git_objct->GetGitStatusList(), i);
            DisplayStatus(entry);
#if defined (__DEBUG)
#endif
            tempItem = new QTableWidgetItem();
            tempItem->setData(Qt::UserRole, entry);
            tempItem->setData(Qt::DisplayRole, entry->index_to_workdir->new_file.path);
            changesStatus->setItem(i, 0, tempItem); 
            tempItem = new QTableWidgetItem();
            tempItem->setData(Qt::UserRole, entry);
            tempItem->setData(Qt::DisplayRole, ReturnStatus(entry));
            changesStatus->setItem(i, 1, tempItem);
        }
        changesStatus->resizeColumnsToContents();
    }
}


void Window::onClickAdd()
{
    QString str;
    bool flag = false;
    int curSize = 0;

    // if it works it works
    addedFile->setRowCount( curFile/2 + changesStatus->selectedItems().size()); 
    addedFile->setHorizontalHeaderLabels({"FileName","Status"});
    addedFile->setSelectionBehavior(QAbstractItemView::SelectRows);
    addedFile->setSelectionMode(QAbstractItemView::ExtendedSelection);
    if(curFile/2 < maxFile)
    {
        for(int i = 0; i < changesStatus->selectedItems().size(); i++)
        {

            // testing presence in the list already
            for(unsigned int j = 0; j < pathList.size(); j++)
            {
                if(i%2 == 0)
                {
#if defined (__DEBUG)
                    std::cout << i << ", " << changesStatus->selectedItems()[i]->text().toStdString() << ", " << pathList[j] << std::endl;
#endif
                    if(changesStatus->selectedItems()[i]->text().toStdString() == pathList[j])
                    {
                        std::cout   << changesStatus->selectedItems()[i]->text().toStdString() 
                                    << " already in pathlist at position "  
                                    << j << " : " << pathList[j] << std::endl;
                        flag = true;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }

            // adding in list if not already in
            if(flag == false)
            {
#if defined (__DEBUG)
                std::cout << "adding file : " << changesStatus->selectedItems()[i]->text().toStdString()  << std::endl;
#endif
                addedFile->setItem(i%2 ? curFile/2 + i - 1 : curFile/2 + i, i%2, changesStatus->selectedItems()[i]->clone());
                if(i%2 == 0)
                {
                    pathList.push_back(changesStatus->selectedItems()[i]->text().toStdString());
                }
                curSize++;
                flag = false;
            }
            else
            {
                flag = false;   
                break;
            }
        }

        // update size
        if(curSize)
        {
            curFile += curSize;
        }

        // clean empty rows
        for(unsigned int i = 0; i < curFile; i++)
        {
            if(!addedFile->item(i, 0))
            {
                addedFile->removeRow(i);
            }
        }
        addedFile->resizeColumnsToContents();
    }

    addedFile->setRowCount(curFile/2);
    str =  QString::number(curFile/2) + " added files";
    Window::labelAdd->setText(str);
}

int callbackCheck(const char *path, const char *matched_pathspec, void *payload)
{
    struct index_options *opts = (struct index_options *)(payload);
    int ret = 1;
    unsigned int status;
    (void) matched_pathspec; // remove a warning
    // /* Get the file status */
    if (git_status_file(&status, opts->repo, path) < 0)
        return -1;

#if defined (__DEBUG)
    if ((status & GIT_STATUS_WT_MODIFIED) || (status & GIT_STATUS_WT_NEW)) 
    {
        std::cout << "-> MODIFIED " << path << std::endl;
    }
#endif

    for(unsigned int i = 0; i < pathList.size(); i++)
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
    QString str = "Commit failed !";
    

    options.repo = git_objct->GetCurrentGitRepo();

    if(this->getGitNameEmpty() == false 
    && this->getGitMailEmpty() == false)            // check to avoid crash
    { 
#if defined (__DEBUG)
        qDebug() << git_revparse_ext(&parnt, &ref, git_objct->GetCurrentGitRepo(), "HEAD");
        qDebug() << git_repository_index(&index, git_objct->GetCurrentGitRepo());
        qDebug() << git_index_write_tree(&tree_oid, index);
        qDebug() << git_index_update_all(index, NULL, callbackCheck, &options);
        qDebug() << git_index_write(index);
        qDebug() << git_tree_lookup(&tree, git_objct->GetCurrentGitRepo(), &tree_oid);
        std::cout << this->getGitName() << std::endl;
        std::cout << this->getGitMail() << std::endl;;
        qDebug() << git_signature_now(&author_signature, this->getGitName(), this->getGitMail());
        qDebug() << git_signature_now(&committer_signature,this->getGitName(), this->getGitMail());
        qDebug() << git_commit_create_v(&commit_oid,
                                        git_objct->GetCurrentGitRepo(),
                                        "HEAD",
                                        author_signature,
                                        committer_signature,
                                        NULL,
                                        comment,
                                        tree,
                                        parnt  ? 1 : 0, parnt);
        str =  "Commit success !";
#else
        if(git_revparse_ext(&parnt, &ref, git_objct->GetCurrentGitRepo(), "HEAD") >= 0)
        {
            if(git_repository_index(&index, git_objct->GetCurrentGitRepo()) >= 0)
            {
                if(git_index_write_tree(&tree_oid, index) >= 0)
                {
                    if(git_index_update_all(index, NULL, callbackCheck, &options) >= 0)
                    {
                        if(git_index_write(index) >= 0)
                        {
                            if(git_tree_lookup(&tree, git_objct->GetCurrentGitRepo(), &tree_oid) >= 0)
                            {
                                if(git_signature_now(&author_signature, this->getGitName(), this->getGitMail()) >= 0
                                && git_signature_now(&committer_signature,this->getGitName(), this->getGitMail()) >= 0)
                                {
                                    if(git_commit_create_v( &commit_oid,
                                                            git_objct->GetCurrentGitRepo(),
                                                            "HEAD",
                                                            author_signature,
                                                            committer_signature,
                                                            NULL,
                                                            comment,
                                                            tree,
                                                            parnt  ? 1 : 0, parnt) >= 0)
                                    {
                                        str =  "Commit success !";
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
#endif
    }
    else
    {
       str =  "Commit failed : empty credentials !";
    }
    Window::labelCommit->setText(str);
}


void Window::onClickPush()
{
    QString str;
    str =  "Push !";
    Window::labelPush->setText(str);
}

const char* Window::getGitName() 
{
    strncpy(tmpStr, gitNameTextBox->toPlainText().toStdString().c_str(), 64);
    return tmpStr;
}

bool Window::getGitNameEmpty() 
{
    return gitNameTextBox->document()->isEmpty();
}

const char* Window::getGitMail() 
{
    strncpy(tmpStr, gitMailTextBox->toPlainText().toStdString().c_str(), 64);
    return tmpStr;
}

bool Window::getGitMailEmpty() 
{
    return gitMailTextBox->document()->isEmpty();
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


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
    labelStatus     =   new QLabel(NULL,this); 
    changesStatus     =   new QListWidget(this); 
    git_object      =   git_obj;

    ButtonCreation(buttonStatus, "Get status", "Execute git status", 30,30,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);
    labelStatus->setGeometry(30,130,80,30);
    changesStatus->setGeometry(30,170,200,100);
    

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
    git_status_list_new(Window::git_object->GetGitStatusListAddress(), Window::git_object->GetCurrentGitRepo(), NULL);
    count = git_status_list_entrycount(Window::git_object->GetGitStatusList());
    if(count > 0)
    {
        changesStatus->clear();
        Window::labelStatus->setText("Diff(s) found");
        for (int i=0; i<count; ++i)
        {
            entry = git_status_byindex(Window::git_object->GetGitStatusList(), i);
            if(ReturnStatus(entry))
            {
                changesStatus->addItem(entry->index_to_workdir->new_file.path);
            }
        }
    }
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


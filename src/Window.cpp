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
    validateToken   =   new QPushButton(NULL,this);
    tokenTxtBox     =   new QTextEdit("",this);
    validateRepo    =   new QPushButton(NULL,this);
    repoPathTxtBox  =   new QTextEdit("",this);
    git_object      =   git_obj;

    // fields options

    ButtonCreation(validateRepo, "Set repository", "Set your repo path", 400,30,80,30);
    QPushButton::connect(validateRepo, &QPushButton::clicked, this, &Window::onClickRepo);
    TextBoxCreation(repoPathTxtBox,30,30,350,30);

    ButtonCreation(buttonStatus, "Get status", "Execute git status", 30,70,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);
    labelStatus->setGeometry(130,70,80,30);

    ButtonCreation(validateToken, "Save token", "Save your git token", 400,110,80,30);
    QPushButton::connect(validateToken, &QPushButton::clicked, this, &Window::onClickToken);
    TextBoxCreation(tokenTxtBox,30,110,350,30);
    
    
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
    std::cout << git_repository_path(Window::git_object->GetCurrentGitRepo()) << std::endl;
    git_status_list_new(Window::git_object->GetGitStatusListAddress(), Window::git_object->GetCurrentGitRepo(), NULL);
    if(git_status_list_entrycount(Window::git_object->GetGitStatusList()) > 0)
    {
        std::cout << "Status diff" << std::endl;
        Window::labelStatus->setText("Diff(s) found");
    }
}

void Window::onClickRepo()
{
    int error;
    std::cout << repoPathTxtBox->toPlainText().toStdString().c_str() << std::endl;
    error = git_repository_open(Window::git_object->GetCurrentGitRepoAddress(), Window::getPath());
    std::cout << error << std::endl;
}

void Window::onClickToken()
{
    std::cout << (getToken()).toStdString() << std::endl;
    Window::tokenTxtBox->setText("");
}

// getters
QString Window::getToken() 
{
    return tokenTxtBox->toPlainText();
}

const char* Window::getPath() 
{
    return repoPathTxtBox->toPlainText().toStdString().c_str();
}


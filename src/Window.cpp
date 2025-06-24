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
Window::Window() 
{
    // fields initialization
    layout          =   new QGridLayout;
    validateToken   =   new QPushButton(NULL,this);
    buttonStatus    =   new QPushButton(NULL,this);
    tokenTxtBox     =   new QTextEdit("",this);


    // fields options
    ButtonCreation(buttonStatus, "Get status", "Execute git status", 30,70,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);

    ButtonCreation(validateToken, "Save token", "Save your git token", 400,30,80,30);
    QPushButton::connect(validateToken, &QPushButton::clicked, this, &Window::onClickToken);

    TextBoxCreation(tokenTxtBox,30,30,350,30);

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
    std::cout << system("git status") << std::endl;
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


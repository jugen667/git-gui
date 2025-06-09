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
Window::Window() {
    // fields initialization
    layout = new QGridLayout;
    validateToken = new QPushButton(NULL,this);
    buttonStatus = new QPushButton(NULL,this);
    token = new QTextEdit("",this);


    // fields options
    buttonStatus->setText("Get status");
    buttonStatus->setToolTip("Execute git status");
    buttonStatus->setGeometry(30,70,80,30);
    QPushButton::connect(buttonStatus, &QPushButton::clicked, this, &Window::onClickStatus);

    validateToken->setText("Save token");
    validateToken->setToolTip("Save your git token");
    validateToken->setGeometry(140,30,80,30);
    QPushButton::connect(validateToken, &QPushButton::clicked, this, &Window::onClickToken);


    token->setGeometry(30,30,100,30);

    // window management
    // layout->addWidget(validateToken, 30, 30);

    // window display
    this->setFixedSize(1280, 720);
    this->setVisible(true);
}

void Window::onClickStatus()
{
    std::cout << system("git status") << std::endl;
}

void Window::onClickToken()
{
    std::cout << (getToken()).toStdString() << std::endl;
}


QString Window::getToken() 
{
    return token->toPlainText();
}

//========================
// - Info -
// - about -
// - File -
// - Author : juju80gen -
//========================

//==============
// - INCLUDES -
//==============
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <QtGui>
#include <QApplication> 
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

static unsigned int counter = 0;

void testFunc(QLabel *Widget)
{
	counter++;
	Widget->setText("Called");
}



//==========
// - MAIN -
//==========
int main(int argc, char **argv) {
	QApplication app(argc, argv); // class for app creation
	
	// windows creation
	QWidget window;
 	window.setFixedSize(1280, 720);

 	// text box
 	QTextEdit textBox("Enter Token",&window);
	textBox.setGeometry(30,30,100,30);
	// button creation
	QPushButton button(NULL,&window);
	button.setText("Button test");
	button.setToolTip("Testing button");
	button.setGeometry(140,30,80,30);

	QLabel text(NULL, &window);
	text.setGeometry(180,30,80,30);

	QObject::connect(&button, SIGNAL (clicked()), &text, SLOT (setText()));

	// loop
	window.show();
	return app.exec();
}
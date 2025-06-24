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

//==========
// - MAIN -
//==========
int main(int argc, char **argv) 
{
	git_libgit2_init();
	QApplication * app = new QApplication(argc, argv); // class for app creation
	// windows creation
	Window window;

	// loop
	return app->exec();
}
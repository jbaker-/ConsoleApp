#include <iostream>

#include "resources.h"

using namespace std;

#define X_DIM 30
#define Y_DIM 15
#define Z_DIM 45

int main(){

	Menu main(X_DIM,Y_DIM,Z_DIM); //needs to get pointer to 

	cout << B_BLACK << WHITE << "init" << endl;

	main.go();

	cout << RESET << endl << "end" << endl;

	return 0;
}
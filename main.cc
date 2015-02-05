#include <iostream>

#include "resources.h"

using namespace std;

#define X_DIM 40
#define Y_DIM 20
#define Z_DIM 20

int main(){

	Menu main(X_DIM,Y_DIM,Z_DIM);
	Timer temp;
	int time;
	int days;
	int hours;
	int minutes;
	int seconds;

	temp.start();

	cout << B_BLACK << WHITE; //set color
	if(DEBUG){
		cout << "init" << endl; //check that color was set
	}

	main.go();

	cout << RESET;//set back to terminal defualt colors
	if(DEBUG){
		cout << endl << "end" << endl; //check color
	}

	temp.stop();
	time = temp.duration_sec();

	if(DEBUG){
		cout << time << endl;
	}

	seconds = time % 60;
	time /= 60;
	minutes = time % 60;
	time /= 60;
	hours = time % 24;
	time /= 24;
	days = time;

	cout << "Program active for " << days << " days " << hours << " hours " 
		 << minutes << " minutes " << seconds << " seconds ( " << temp.duration() << " milliseconds)" << endl;

	return 0;
}
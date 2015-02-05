//this file is to simplify compilation (vs declaring voxel in main.cc)
 
#include <cstdlib>//for timer, rand()
#include <sys/time.h>//for timer

#include "glm/glm/glm.hpp"
#include "colors.h"

#define DEBUG false

//timer class is from http://stackoverflow.com/questions/3797708/millisecond-accurate-benchmarking-in-c
//and was posted without any comments by ccSadegh 

class Timer{
    timeval timer[2];

  public:

    timeval start()
    {
        gettimeofday(&this->timer[0], NULL);
        return this->timer[0];
    }

    timeval stop()
    {
        gettimeofday(&this->timer[1], NULL);
        return this->timer[1];
    }

    int duration() const
    {
        int secs(this->timer[1].tv_sec - this->timer[0].tv_sec);
        int usecs(this->timer[1].tv_usec - this->timer[0].tv_usec);

        if(usecs < 0)
        {
            --secs;
            usecs += 1000000;
        }

        return static_cast<int>(secs * 1000 + usecs / 1000.0 + 0.5);
    }

    int duration_sec() const //I added this part, he didnt have any comments when he posted it on SO
    {
        int secs(this->timer[1].tv_sec - this->timer[0].tv_sec);
        int usecs(this->timer[1].tv_usec - this->timer[0].tv_usec);

        if(usecs < 0)
        {
            --secs;
            usecs += 1000000;
        }

        return static_cast<int>(secs + usecs / 1000000.0 + 0.5);
    }};

struct voxel{

	glm::vec3 position;
	glm::vec3 direction;

	float temperature;
	float pressure;

	int id;
	//0 is empty
	//1
	//2
	//3
	//4 ---work in progress
	//5
	//6
	//7
	//8
	//9 is a special value for edges
};



class Menu{
	public: 
		//constructor 
		Menu(int x_dim, int y_dim, int z_dim);

		void go(); //enters a loop state till exit is selected

		voxel* access(int x1,int y1,int z1); //used to get the information on a voxel
		void set(int x1,int y1,int z1,int seed); //used to update a single voxel

	private:

		//menu functions
		void intro();
		int main_menu();
		int draw_options();
		int display_options();
		int seed_options();
		int update_options();
		void seed(int seed);
		void display(int view);

		//voxel data pointer - represented as long 1D array
		voxel *space;

		//dimensions of represented voxel data
		int x;
		int y;
		int z;
};

Menu::Menu(int x_dim, int y_dim, int z_dim){
	Timer temp;

	x = x_dim;
	y = y_dim; // set dimensions
	z = z_dim;
	
	space = new voxel[x*y*z]; //declare the voxel array of the proper size

	temp.start(); //begin timer
	//initialize dimensions 
	for(int loopx = 0; loopx < x_dim; loopx++){
		for(int loopy = 0; loopy < y_dim; loopy++){
			for(int loopz = 0; loopz < z_dim; loopz++){

				access(loopx,loopy,loopz)->position = glm::ivec3(loopx,loopy,loopz);
				access(loopx,loopy,loopz)->id = 0;
				if(DEBUG){
					cout << endl << "[" << loopz+1 << "] - [" 
						<< access(loopx,loopy,loopz)->position.x 
						<< "/" << access(loopx,loopy,loopz)->position.y 
						<< "/" << access(loopx,loopy,loopz)->position.z 
						<< "]<>[" << loopx << "/"<< loopy <<"/"<< loopz << "] ";
				}
			}
			if(DEBUG){
				cout << endl << "end of line [" << loopy+1 << "] in slice [" << loopx+1 << "]" << endl;
			}
		}
		if(DEBUG){
			cout << endl << "end of slice [" << loopx+1 << "]" << endl << endl;
		}
	}
	temp.stop();//end timer
	cout << endl << "Constructor loop took " << temp.duration() << " miliseconds ("<< temp.duration()*0.001 << " seconds)";
	if(DEBUG){
		cout << "(Note: DEBUG active)" << endl;
	}else{
		cout << endl;
	}//constructor seeds 
}

voxel* Menu::access(int x1,int y1,int z1){
	int index = x*y*z1 + z*y1 + x1;
	return &space[index];
}

void Menu::set(int x1,int y1,int z1,int seed){
	int index = x*y*z1 + z*y1 + x1;
	space[index].id = seed;
}

void Menu::go(){

	intro();

	bool menu_active = true;
	bool submenu_active = false;
	bool subsubmenu_active = false;
	int choice = 0;
	int submenu_choice = 0;
	int subsubmenu_choice = 0;

	while(menu_active){
		switch(choice){
			case 0://inital state

				choice = main_menu();
				break;

			case 1://draw options
				submenu_active = true;
				submenu_choice = 0;

				while(submenu_active){
					switch(submenu_choice){

						case 0://inital state
							submenu_choice = draw_options();
							break;

						case 1://output the solid (->display options)
							subsubmenu_active = true;
							subsubmenu_choice = 0;

							while(subsubmenu_active){
								switch(subsubmenu_choice){

									//case 1: I:(z:0 -> max) / M:(y:max -> 0) / O:(x:0 -> max) 
									//case 2: I:(x:0 -> max) / M:(y:max -> 0) / O:(z:max -> 0)
									//case 3: I:(x:0 -> max) / M:(z:0 -> max) / O:(y:max -> 0)

									case 0://initial state
										subsubmenu_choice = display_options(); 
										break;

									case 1://display case 1
										display(1);
										subsubmenu_choice = 0;
										break;

									case 2://display case 2
										display(2);
										subsubmenu_choice = 0;
										break;

									case 3://display case 3
										display(3);
										subsubmenu_choice = 0;
										break;

									case 99: //exit
										subsubmenu_choice = 0;
										subsubmenu_active = false;
										break;

									case 999: //global quit
										subsubmenu_active = 0;
										submenu_active = 0;
										menu_active = 0;
										break;

									default:
										subsubmenu_choice = 0;
										cout << endl << "Invalid, returning to menu" << endl;
										break;
								}
							}

							submenu_choice = 0;
							break;

						case 2:
							//draw a point
							submenu_choice = 0;
							break;

						case 3:
							//draw a line
							submenu_choice = 0;
							break;

						case 4:
							//draw a sphere
							submenu_choice = 0;
							break;

						case 99:
							submenu_active = false;
							break;

						case 999: //global quit
							subsubmenu_active = 0;
							submenu_active = 0;
							menu_active = 0;
							break;

						default:
							submenu_choice = 0;
							cout << endl << "Invalid, returning to menu" << endl;
							break;
					}
				}

				choice = 0;
				break;

			case 2://seed options
				submenu_active = true;
				submenu_choice = 0;

				while(submenu_active){
					switch(submenu_choice){

						case 0://initial state
							submenu_choice = seed_options();
							break;

						case 1:
						case 2:
						case 3:
						case 4:
							//seed outer layer with special value
							seed(submenu_choice);
							submenu_choice = 0;
							break;

						case 99:
							submenu_active = false;
							break;

						case 999: //global quit
							subsubmenu_active = 0;
							submenu_active = 0;
							menu_active = 0;
							break;

						default:
							submenu_choice = 0;
							cout << endl << "Invaid, returning to menu" << endl;
							break;
					}
				}

				choice = 0;
				break;

			case 3://update options
				submenu_active = true;
				submenu_choice = 0;

				while(submenu_active){
					switch(submenu_choice){
						case 0://inital state
							submenu_choice = update_options();
							break;

						case 1://update one time
							submenu_choice = 0;
							break;

						case 2://update 5 times
							submenu_choice = 0;
							break;

						case 3://update a user-specified number of times
							submenu_choice = 0;
							break;

						case 99://exit
							submenu_active = false;
							break;

						case 999: //global quit
							subsubmenu_active = 0;
							submenu_active = 0;
							menu_active = 0;
							break;

						default:
							submenu_choice = 0;
							cout << endl << "Invalid, returning to menu" << endl;
							break;
					}
				}

				choice = 0;
				break;

			case 99:

				menu_active = false;
				cout << endl << "Goodbye" << endl;
				break;

			case 999: //global quit -- strictly speaking not neccesary here
				subsubmenu_active = 0;
				submenu_active = 0;
				menu_active = 0;
				break;

			default:
				choice = 0; //reset to main menu
				break;
		}
	}
	//outro() -- this remains unimplemented - however, before "return 0" in main
	//this is the last thing to happen at the end of the program
}  

void Menu::intro(){
	cout <<"Welcome- - - - - - - - - - - - - v0.2"<< endl;
	cout <<"count: "<< x*y*z <<" [x: "<< x <<"] [y: "<< y <<"] [z: "<< z <<"]"<< endl;
	cout <<"Bytes used: "<< x * y * z * sizeof(voxel) << endl;
	cout << endl << "Enter 999 at any point in the menu to quit" << endl;
}

int Menu::main_menu(){
	int choice;
	//output main menu options
	cout << endl << endl;
	cout <<"Main-Menu- - - - - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"1-Draw-Options - - - - - - - - - -" << endl;
	cout <<"2-Seed-Options - - - - - - - - - -" << endl;
	cout <<"3-Update-Options - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"99-Exit- - - - - - - - - - - - - -" << endl;
	cout <<"select option" << endl;
	cout <<"> ";
	cin >> choice;
	return choice;
}

int Menu::draw_options(){
	int choice;
	//output and accept draw options
	cout << endl << endl;
	cout <<"Draw-Menu- - - - - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"1-Draw-to-Console- - - - - - - - -" << endl;
	cout <<"2-Draw-a-Point - - - - - - - - - -" << endl;
	cout <<"3-Draw-a-Line- - - - - - - - - - -" << endl;
	cout <<"4-Draw-a-Sphere- - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"99-up- - - - - - - - - - - - - - -" << endl;
	cout <<"select option" << endl;
	cout <<"> ";
	cin >> choice;
	return choice;
}

int Menu::display_options(){
	//an ad hoc notation for console output
	//		  I:inner loop,    M:middle loop,   O:outer loop
	//case 1: I:(z:0 -> max) / M:(y:max -> 0) / O:(x:0 -> max) 
	//case 2: I:(x:0 -> max) / M:(y:max -> 0) / O:(z:max -> 0)
	//case 3: I:(x:0 -> max) / M:(z:0 -> max) / O:(y:max -> 0)

	int choice;
	//output and accept seed options
	cout << endl << endl;
	cout <<"Display-to-Console-Menu- - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"1-Output-view-1-(slices-along-x) -" << endl;
	cout <<"2-Output-view-2-(slices-along-z) -" << endl;
	cout <<"3-Output-view-3-(slices-along-y) -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"99-up- - - - - - - - - - - - - - -" << endl;
	cout <<"select option" << endl;
	cout <<"> ";
	cin >> choice;
	return choice;
}

int Menu::seed_options(){
	int choice;
	//output and accept seed options
	cout << endl << endl;
	cout <<"Seed-Menu- - - - - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"1-Outer-Layer-of-1's - - - - - - -" << endl;
	cout <<"2-Seed-Zero-faces-only - - - - - -" << endl;
	cout <<"3-Seed-Max-faces-only- - - - - - -" << endl;
	cout <<"4-Game of-life setup - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"99-up- - - - - - - - - - - - - - -" << endl;
	cout <<"select option" << endl;
	cout <<"> ";
	cin >> choice;
	return choice;	
}

int Menu::update_options(){
	int choice;
	//output and accept update options
	cout << endl << endl;
	cout <<"Update-Menu- - - - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"1-Update-1-time- - - - - - - - - -" << endl;
	cout <<"2-Update-5-times - - - - - - - - -" << endl;
	cout <<"3-Update-N-times - - - - - - - - -" << endl;
	cout <<" - - - - - - - - - - - - - - - - -" << endl;
	cout <<"99-up- - - - - - - - - - - - - - -" << endl;
	cout <<"select option" << endl;
	cout <<"> ";
	cin >> choice;
	return choice;
}

void Menu::seed(int seed){
	glm::vec3 temp;

	srand(sizeof(seed)*seed);

	switch(seed){
		case 1://outer layer of ones - some strange artifacts exist here, more work to do
			for(int x1 = 0; x1 < x; x1++){
				for(int y1 = 0; y1 < y; y1++){
					for(int z1 = 0; z1 < z; z1++){
						temp = access(x1,y1,z1)->position;

						if(temp.x == 0 || temp.x == (x-1) ||
						   temp.y == 0 || temp.y == (y-1) ||
						   temp.z == 0 || temp.z == (z-1) ){
							access(x1,y1,z1)->id = 1;
							//cout << x1 <<" "<< y1 <<" "<< z1 << endl << endl;
						}else{
							access(x1,y1,z1)->id = 0;
						}
					}
				}
			}
			break;

		case 2:
			for(int x1 = 0; x1 < x; x1++){
				for(int y1 = 0; y1 < y; y1++){
					for(int z1 = 0; z1 < z; z1++){
						temp = access(x1,y1,z1)->position;

						if(temp.x == 0 ||
						   temp.y == 0 ||
						   temp.z == 0 ){
							access(x1,y1,z1)->id = 1;
							//cout << x1 <<" "<< y1 <<" "<< z1 << endl << endl;
						}else{
							access(x1,y1,z1)->id = 0;
						}
					}
				}
			}
			break;

		case 3:
			for(int x1 = 0; x1 < x; x1++){
				for(int y1 = 0; y1 < y; y1++){
					for(int z1 = 0; z1 < z; z1++){

						temp = access(x1,y1,z1)->position;

						if(temp.x == (x-1) ||
						   temp.y == (y-1) ||
						   temp.z == (z-1) ){
							access(x1,y1,z1)->id = 1;
							//cout << x1 <<" "<< y1 <<" "<< z1 << endl << endl;
						}else{
							access(x1,y1,z1)->id = 0;
						}
					}
				}
			}
			break;

		case 4://outer layer of 2's - random 0/1 interior game of life setup
			for(int x1 = 0; x1 < x; x1++){
				for(int y1 = 0; y1 < y; y1++){
					for(int z1 = 0; z1 < z; z1++){

						temp = access(x1,y1,z1)->position;

						if(temp.x == 0 || temp.x == (x-1) ||
						   temp.y == 0 || temp.y == (y-1) ||
						   temp.z == 0 || temp.z == (z-1) ){
							access(x1,y1,z1)->id = 2;
							//cout << x1 <<" "<< y1 <<" "<< z1 << endl << endl;
						}else{
							if(rand()/RAND_MAX > 0.5){
								access(x1,y1,z1)->id = 1;
							}else{
								access(x1,y1,z1)->id = 0;
							}
						}
					}
				}
			}
			break;

		default:
			cout << "Invalid value: " << seed << " passed to seed(int seed)" << endl;
			break;
	}
}

void Menu::display(int view){
	//display function
	voxel temp;
	Timer temp_timer;

	temp_timer.start();

	switch(view){
		case 1://I:(z:0 -> max) / M:(y:max -> 0) / O:(x:0 -> max)
			for(int k = 0; k < x; k++){
				for(int j = (y-1); j >= 0; j--){
					for(int i = 0; i < z; i++){
						temp = *access(k,j,i);
						cout << temp.id;
					}cout << endl;
				}cout << endl << endl;
			}
			cout << '^' << endl << "y/z >  (x represented by slices)";
			break;

		case 2://I:(x:0 -> max) / M:(y:max -> 0) / O:(z:max -> 0)
			for(int l = (z-1); l >= 0; l--){
				for(int m = (y-1); m >= 0; m--){
					for(int n = 0; n < x; n++){
						temp = *access(n,m,l);
						cout << temp.id;
					}cout << endl;
				}cout << endl << endl;
			}cout << '^' << endl << "y/x >  (z represented by slices)";
			break;

		case 3://I:(x:0 -> max) / M:(z:0 -> max) / O:(y:max -> 0)
			for(int o = (y-1); o >= 0; o--){
				for(int p = 0; p < z; p++){
					for(int q = 0; q < x; q++){
						temp = *access(q,o,p);
						cout << temp.id;
					}cout << endl;
				}cout << endl << endl;
			}cout << '^' << endl << "z/x >  (y represented by slices)";
			break;

		default:
			cout << endl << "Invalid parameter view: " << view 
				 << " passed to display(int view)" << endl;
			break;
	}

	temp_timer.stop();
	cout << endl << " display took " << temp_timer.duration() << " miliseconds (" 
			<< temp_timer.duration()*0.001 << " sec)" << endl;
}

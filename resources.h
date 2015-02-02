//this file is to simplify compilation (vs declaring voxel in main.cc)
#include "glm/glm/glm.hpp"
#include "colors.h"

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
	//4
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
		void display(int view);

		//voxel data pointer - represented as long 1D array
		voxel *space;

		//dimensions of represented voxel data
		int x;
		int y;
		int z;
};

Menu::Menu(int x_dim, int y_dim, int z_dim){
	x = x_dim;
	y = y_dim; // set dimensions
	z = z_dim;
	
	space = new voxel[x*y*z]; //declare the voxel array of the proper size
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
							//seed outer layer with special value
							submenu_choice = 0;
							break;

						case 99:
							submenu_active = false;
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

			case 999: //global quit
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
	cout <<"1-Outer-Layer-of-9's - - - - - - -" << endl;
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

void Menu::display(int view){
	//display function
	voxel temp;
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
			break;

		case 2://I:(x:0 -> max) / M:(y:max -> 0) / O:(z:max -> 0)
			for(int l = (z-1); l >= 0; l--){
				for(int m = (y-1); m >= 0; m--){//fix
					for(int n = 0; n < x; n++){
						temp = *access(n,m,l);
						cout << temp.id;
					}cout << endl;
				}cout << endl << endl;
			}
			break;

		case 3://I:(x:0 -> max) / M:(z:0 -> max) / O:(y:max -> 0)
			for(int o = (y-1); o >= 0; o--){
				for(int p = 0; p < z; p++){
					for(int q = 0; q < x; q++){
						temp = *access(q,o,p);
						cout << temp.id;
					}cout << endl;
				}cout << endl << endl;
			}
			break;

		default:
			cout << endl << "Invalid parameter view: " << view 
				 << " passed to display(int view)" << endl;
			break;
	}
}
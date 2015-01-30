#include <iostream>
#include <cstdlib>

#include "colors.h"
using namespace std;

#define X_DIM 80
#define Y_DIM 30
#define Z_DIM 30

struct voxel{
	int id;
};

voxel space[X_DIM][Y_DIM][Z_DIM];

void seed(int seed){
	if(seed == 3){
		float result;
		srand(X_DIM*Y_DIM*Z_DIM);
		cout << "random seeding begins" << endl;
		for(int k = Z_DIM; k > 0; k--){
			for(int j = Y_DIM; j > 0; j--){
				for(int i = 0; i < X_DIM; i++){
					result = rand() / RAND_MAX;

					if(result >= 0.5){
						space[i][j][k].id = 1;
					}else{
						space[i][j][k].id = 0;
					}
					cout << space[i][j][k].id << "]";
				}
				cout << "line " << j << " completed successfully" << endl;
			}
			cout << "end of slice " << k << endl;
		}
	}else{
		cout << "seeding begins" << endl;
		for(int k = Z_DIM; k > 0; k--){
			for(int j = Y_DIM; j > 0; j--){
				for(int i = 0; i < X_DIM; i++){
					space[i][j][k].id = seed;
					cout << "[" << seed << "/";
					cout << space[i][j][k].id << "]";
				}
				cout << "line " << j << " completed successfully" << endl;
			}
			cout << "end of slice " << k << endl;
		}
	}
}

bool display(){
	cout << "begin display" << endl;
	for(int k = Z_DIM; k > 0; k--){
		for(int j = Y_DIM; j > 0; j--){
			for(int i = 0; i < X_DIM; i++){
				cout << space[i][j][k].id;
			}
			cout << " end of line " << j << endl;
		}
		cout << "end of slice " << k << endl;
	}
	return true;
}

void update(int ruleset){

	switch(ruleset){

		case 0:/*
		-RULESET 0-

		Game of Life rules (2D): -- My initial notion is to multiply neccesary totals by 3 because the considered
							 -- space is basically 3x(3x3) squares - the original simulation parameters
		Applies to-
		\-live case
		/-dead case

	    \Any live cell with fewer than two live neighbours dies, as if by needs caused by underpopulation.
 	    \Any live cell with more than three live neighbours dies, as if by overcrowding.
    	\Any live cell with two or three live neighbours lives, unchanged, to the next generation.
    	/Any dead cell with exactly three live neighbours cells will come to life.

		Game of Life rules (3D): TBD

		*/

		int previous_material;
		int neighbor_material;

		bool out_of_bounds_X = false;
		bool out_of_bounds_Y = false;
		bool out_of_bounds_Z = false;

		cout << "updating begins" << endl;
		for(int k = Z_DIM; k > 0; k--){
			for(int j = Y_DIM; j > 0; j--){
				for(int i = 0; i < X_DIM; i++){
					previous_material = space[i][j][k].id;
					cout << "[" << previous_material << "/";

					//update by material - work exists here

					int current0total = 0;
					int current1total = 0;

					switch(previous_material){
						case 0: for(int m = -1; m <= 1; m++){
									for(int o = -1; o <= 1; o++){
										for(int q = -1; q <= 1; q++){

											if(i+m < 0 || i+m >= X_DIM){
												out_of_bounds_X = true;
											}

											if(j+o < 0 || j+o >= Y_DIM){
												out_of_bounds_Y = true;
											}

											if(k+q < 0 || k+q >= Z_DIM){
												out_of_bounds_Z = true;
											}

											if(m==o&&o==q&&m==0){
												//updating cell considering itself
												//do nothing
											}else{
												//cell is considering a neighboring cell
												if(out_of_bounds_X||out_of_bounds_Y||out_of_bounds_Z){
													//output error instead of trying to write to the location
													cout << "ERROR";
												}else{
													neighbor_material = space[i+m][j+o][k+q].id;
													if(neighbor_material == 1){
														current1total++;
													}else if(neighbor_material == 0){
														current0total++;
													}else{
														cout << "sHIT";
													}
												}
											}

											out_of_bounds_X = false;
											out_of_bounds_Y = false;
											out_of_bounds_Z = false;
										}
									}
								}

								//CONWAY RULES
								if(current1total == 9){ //conways rules 2D:3 > 3D:9?
									space[i][j][k].id = 1;
								}else{
									space[i][j][k].id = 0;
								}

								break;//END OF DEAD CELL HANDLING
						case 1: for(int n = -1; n <= 1; n++){
									for(int p = -1; p <= 1; p++){
										for(int r = -1; r <= 1; r++){

											if(i+n < 0 || i+n >= X_DIM){
												out_of_bounds_X = true;
											}

											if(j+p < 0 || j+p >= Y_DIM){
												out_of_bounds_Y = true;
											}

											if(k+r < 0 || k+r >= Z_DIM){
												out_of_bounds_Z = true;
											}

											if(n==p&&p==r&&n==0){
												//updating cell considering itself
												//do nothing
											}else{
												//cell is considering a neighboring cell
												if(out_of_bounds_X||out_of_bounds_Y||out_of_bounds_Z){
													//output error instead of trying to write to the location
													cout << "ERROR";
												}else{
													neighbor_material = space[i+n][j+p][k+r].id;
													if(neighbor_material == 1){
														current1total++;
													}else if(neighbor_material == 0){
														current0total++;
													}else{
														cout << "sHIT";
													}
												}
											}

											out_of_bounds_X = false;
											out_of_bounds_Y = false;
											out_of_bounds_Z = false;
										}
									}
								}

								//CONWAY RULES
								if(current1total < 6 ||  //conways rules 2D:2 > 3D:6? 
								   current1total > 9 ){  //conways rules 2D:3 > 3D:9?
									space[i][j][k].id = 0;
								}else{
									space[i][j][k].id = 1; //conways rules 2D:2-3 > 3D:6-9?
								}

								break;//END OF LIVE CELL HANDLING
						default:break;
					}
					current0total = 0;
					current1total = 0;

					cout << space[i][j][k].id << "]";
				}cout << "line " << j << " completed successfully" << endl;
			}cout << "end of slice " << k << endl;
		}break;

		case 2:/*
		Heat - more work here
		*/

		break;

		default: cout << "Update(int ruleset) did not recieve a valid ruleset value" << endl;
		break;
	};
}

void menu(){
	cout << "-Options----" << endl;
	cout << "1-Display" << endl;
	cout << "2-Seed-the-Display" << endl;
	cout << "3-Update-Submenu" << endl;
	cout << endl << endl << endl;
	cout << "99-EXIT" << endl;
}

void update_submenu(){
	cout << "-Update-Options----" << endl;
	cout << "1-Update-Once" << endl;
	cout << "2-Update-5x" << endl;
	cout << "3-Update-Nx" << endl;
	cout << endl << endl << endl;
	cout << "99-EXIT" << endl;
}

int main(){

	cout << "-Hello and Welcome----" << RED << "v0.1" << RESET << endl;
	cout << "-current voxel count> " << GREEN << Z_DIM*X_DIM*Y_DIM << RESET << endl;
	//display(0);

	bool menu_active = true;
	bool seeded = false;
	int choice = 0;
	int submenu_choice = 0;

	while(menu_active){
		switch(choice){
			case 0: break;

			case 1: display(); 
					break;

			case 2: cout << endl << "-enter-seed-value[integer]>";
					cin >> choice;
					seed(choice);
					choice = 2;
					seeded = true;
					break;

			case 3: while(menu_active){
						switch(submenu_choice){
							case 0: break;
							case 1: break;//update one time
							case 2: break;//update five times
							case 3: break;//update a user specified number of times
							case 99:menu_active = false;
									break;
						};
						update_submenu();
						cout << "-enter-choice> ";
						cin >> submenu_choice;
						if(submenu_choice == 99)
							menu_active = false;
					}
					menu_active=true;
					break;

			case 99:menu_active = false; 
					break;

			default:cout << "-invalid-choice-" << endl;
					break;
		};
		cout << endl << endl << endl;
		menu();
		cout << "-enter-choice> ";
		cin >> choice;
	}
}
#include <iostream>
#include <graphics.h>
#include <dos.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;


struct brick{
	bool isfull;
	int x1;
	int y1;
	int x2;
	int y2;
	int row;
	int col;
	int live;
};

struct myCircle{
	bool isExist;
	int x;
	int y;
	int step;
	int is_on_horizon;
};


//------ GLOBAL VARIABLES ---------------------
int level;                 //------------------
int game_over;             //------------------
int highscores;            //------------------
int score;                 //------------------
int circle_place_x;        //------------------
int circle_place_y;        //------------------
int firstone;
                           //------------------
bool endLevel;             //------------------
                           //------------------
brick bricks[6][5];        //------------------
myCircle circles[500];     //------------------
                           //------------------
double line_eq[500][2];    //------------------
//---------------------------------------------


//------------- FUNCTIONS -----------------------

void line_Equation(int i){
	int x;
	int y;
	
	double x1,y1,x2,y2;
	double m;
	double z;
	getmouseclick(WM_LBUTTONDOWN,x,y);
	x2 = (double)x;
	y2 = (double)y;
	x1 = (double)circle_place_x;
	y1 = (double)circle_place_y;
	m = (x2-x1)/(y2-y1);
	z = (x2 - m*y2);
	line_eq[i][0] = m;
	line_eq[i][1] = z;
	
	clearmouseclick(WM_LBUTTONDOWN);
}

void line_equation2(int x, int y, int i){
	double m = -line_eq[i][0];
	line_eq[i][0] = m;
	double x1,y1;
	x1 = (double)x;
	y1 = (double)y;
	
	double z;
	z = (x1 - m*y1);
	line_eq[i][1] = z;
}

void draw_the_bricks(){
	setcolor(1);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	char arr[10];
	for(int i=0; i<6; i++){
		for(int j=0; j<5; j++){
			if(bricks[i][j].isfull){
				bar(bricks[i][j].x1, bricks[i][j].y1, bricks[i][j].x2, bricks[i][j].y2);
				
				sprintf(arr,"%d",bricks[i][j].live);
				outtextxy(bricks[i][j].x1+20,bricks[i][j].y1+7,arr);
			}
		}
	}
	
}

void draw_circles(){
	for(int i=0; i<level; i++){
		if(circles[i].isExist){
			circle(circles[i].x,circles[i].y,10);
			floodfill(circles[i].x,circles[i].y,6);
		}
	}
}

void set_random_bricks(){
	int count = 0;
	int temp;
	int temp2;
	temp = rand()%4 + 1;
	for(int i=1; i<=temp; i++){
		temp2 = rand()%5;
		if(!bricks[0][temp2].isfull){
			bricks[0][temp2].isfull = 1;
			bricks[0][temp2].live = level;
		}
		else 
			i--;	
	}
	level++;
}

int move_bricks(){
	for(int i=0; i<5; i++){
		if(bricks[5][i].isfull){
			game_over = 1;
			return 0;
		}		
	}
	for(int i=4; i>=0; i--){
		for(int j=0; j<5; j++){
			if(bricks[i][j].isfull){
				bricks[i][j].isfull = 0;
				bricks[i+1][j].isfull = 1;
				bricks[i+1][j].live = bricks[i][j].live;
			}
		}
	}
	return 1;
}

int calculate_x(int y, int i){
	double yy;
	yy = (double)y;
	double temp;
	temp = ( yy*line_eq[i][0] + line_eq[i][1] )*10.00;
	if( (int)temp%10 >= 5)
    {
    	return (int)temp / 10 + 1;
	}
	else 
		return (int)temp / 10 ;
}

void floor_brick_collision(int i){
	
	//------------------ collision in row 1-----------------------
	if(circles[i].y <= 163){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[0][0].isfull){
				
				bricks[0][0].live --;
				
				if(bricks[0][0].live == 0){
					bricks[0][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[0][1].isfull){

				bricks[0][1].live --;
				
				if(bricks[0][1].live == 0){
					bricks[0][1].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[0][2].isfull){

				bricks[0][2].live --;
			
				if(bricks[0][2].live == 0){
					bricks[0][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[0][3].isfull){

				bricks[0][3].live --;
			
				if(bricks[0][3].live == 0){
					bricks[0][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[0][4].isfull){

				bricks[0][4].live --;
				
				if(bricks[0][4].live == 0){
					bricks[0][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
	//----------------------------------------------------END of collision in row 1
	
	
	//-------------------Collision in row 2 ----------------------------------
	if(circles[i].y <= 208){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[1][0].isfull){

				bricks[1][0].live --;
				
				if(bricks[1][0].live == 0){
					bricks[1][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[1][1].isfull){

				bricks[1][1].live --;
				
				if(bricks[1][1].live == 0){
					bricks[1][1].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[1][2].isfull){

				bricks[1][2].live --;
				
				if(bricks[1][2].live == 0){
					bricks[1][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[1][3].isfull){

				bricks[1][3].live --;
				
				if(bricks[1][3].live == 0){
					bricks[1][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[1][4].isfull){

				bricks[1][4].live --;
				
				if(bricks[1][4].live == 0){
					bricks[1][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
	//----------------------------------------------------END of collision in row 2
	
	//-------------------Collision in row 3 ----------------------------------
	if(circles[i].y <= 253){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[2][0].isfull){

				bricks[2][0].live --;
				
				if(bricks[2][0].live == 0){
					bricks[2][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[2][1].isfull){

				bricks[2][1].live --;
				
				if(bricks[2][1].live == 0){
					bricks[2][1].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[2][2].isfull){

				bricks[2][2].live --;

				if(bricks[2][2].live == 0){
					bricks[2][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[2][3].isfull){

				bricks[2][3].live --;
				
				if(bricks[2][3].live == 0){
					bricks[2][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[2][4].isfull){

				bricks[2][4].live --;
			
				if(bricks[2][4].live == 0){
					bricks[2][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
	//----------------------------------------------------END of collision in row 3
	
	//-------------------Collision in row 4 ----------------------------------
	if(circles[i].y <= 298){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[3][0].isfull){

				bricks[3][0].live --;
				
				if(bricks[3][0].live == 0){
					bricks[3][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[3][1].isfull){

				bricks[3][1].live --;
				
				if(bricks[3][1].live == 0){
					bricks[3][1].isfull = 0;
					score++;
				}
			
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[3][2].isfull){

				bricks[3][2].live --;
				
				if(bricks[3][2].live == 0){
					bricks[3][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[3][3].isfull){

				bricks[3][3].live --;

				if(bricks[3][3].live == 0){
					bricks[3][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[3][4].isfull){

				bricks[3][4].live --;
			
				if(bricks[3][4].live == 0){
					bricks[3][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
	//----------------------------------------------------END of collision in row 4
	
	//-------------------Collision in row 5 ----------------------------------
	if(circles[i].y <= 343){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[4][0].isfull){

				bricks[4][0].live --;

				if(bricks[4][0].live == 0){
					bricks[4][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[4][1].isfull){

				bricks[4][1].live --;

				if(bricks[4][1].live == 0){
					bricks[4][1].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[4][2].isfull){

				bricks[4][2].live --;

				if(bricks[4][2].live == 0){
					bricks[4][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[4][3].isfull){

				bricks[4][3].live --;

				if(bricks[4][3].live == 0){
					bricks[4][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[4][4].isfull){

				bricks[4][4].live --;

				if(bricks[4][4].live == 0){
					bricks[4][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
	//----------------------------------------------------END of collision in row 5
	
	//-------------------Collision in row 6 ----------------------------------
	if(circles[i].y <= 388){
			
		if(circles[i].x >= 2 && circles[i].x <= 62){
			if(bricks[5][0].isfull){

				bricks[5][0].live --;

				if(bricks[5][0].live == 0){
					bricks[5][0].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
					
				
			}
		}
		
		if(circles[i].x >= 63 && circles[i].x <= 122){
			if(bricks[5][1].isfull){

				bricks[5][1].live --;

				if(bricks[5][1].live == 0){
					bricks[5][1].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 123 && circles[i].x <= 182){
			if(bricks[5][2].isfull){

				bricks[5][2].live --;
		
				if(bricks[5][2].live == 0){
					bricks[5][2].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 183 && circles[i].x <= 242){
			if(bricks[5][3].isfull){

				bricks[5][3].live --;

				if(bricks[5][3].live == 0){
					bricks[5][3].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
		
		if(circles[i].x >= 243 && circles[i].x <= 305){
			if(bricks[5][4].isfull){

				bricks[5][4].live --;

				if(bricks[5][4].live == 0){
					bricks[5][4].isfull = 0;
					score++;
				}
				
				circles[i].step = -circles[i].step;
				line_equation2(circles[i].x, circles[i].y, i);
				
			}
		}
	}
}

void walls_brick_collision(int i){
	int tx, ty;
		
	ty = circles[i].y+circles[i].step+4;
	tx = calculate_x(ty, i);
	
	//------col 1 ---------------------------------------------------
	if((tx >= 3 && tx <= 7) || (tx >= 58 && tx <= 62)){
		
		if(ty > 110 && ty < 150 && bricks[0][0].isfull){

			bricks[0][0].live --;

			if(bricks[0][0].live == 0){
				bricks[0][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 155 && ty < 195 && bricks[1][0].isfull){

			bricks[1][0].live --;

			if(bricks[1][0].live == 0){
				bricks[1][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 200 && ty < 240 && bricks[2][0].isfull){

			bricks[2][0].live --;

			if(bricks[2][0].live == 0){
				bricks[2][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 245 && ty < 285 && bricks[3][0].isfull){

			bricks[3][0].live --;

			if(bricks[3][0].live == 0){
				bricks[3][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 290 && ty < 330 && bricks[4][0].isfull){

			bricks[4][0].live --;

			if(bricks[4][0].live == 0){
				bricks[4][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 335 && ty < 375 && bricks[5][0].isfull){

			bricks[5][0].live --;

			if(bricks[5][0].live == 0){
				bricks[5][0].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
	}
	
	
	//------col 2 ---------------------------------------------------
	if((tx >= 63 && tx <= 68) || (tx >= 118 && tx <= 122)){
		
		if(ty > 110 && ty < 150 && bricks[0][1].isfull){

			bricks[0][1].live --;

			if(bricks[0][1].live == 0){
				bricks[0][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 155 && ty < 195 && bricks[1][1].isfull){

			bricks[1][1].live --;

			if(bricks[1][1].live == 0){
				bricks[1][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 200 && ty < 240 && bricks[2][1].isfull){

			bricks[2][1].live --;

			if(bricks[2][1].live == 0){
				bricks[2][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 245 && ty < 285 && bricks[3][1].isfull){

			bricks[3][1].live --;

			if(bricks[3][1].live == 0){
				bricks[3][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 290 && ty < 330 && bricks[4][1].isfull){

			bricks[4][1].live --;

			if(bricks[4][1].live == 0){
				bricks[4][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 335 && ty < 375 && bricks[5][1].isfull){

			bricks[5][1].live --;

			if(bricks[5][1].live == 0){
				bricks[5][1].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
	}
	
	//------col 3 ---------------------------------------------------
	if((tx >= 123 && tx <= 128) || (tx >= 178 && tx <= 182)){
		
		if(ty > 110 && ty < 150 && bricks[0][2].isfull){

			bricks[0][2].live --;

			if(bricks[0][2].live == 0){
				bricks[0][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 155 && ty < 195 && bricks[1][2].isfull){

			bricks[1][2].live --;

			if(bricks[1][2].live == 0){
				bricks[1][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 200 && ty < 240 && bricks[2][2].isfull){

			bricks[2][2].live --;

			if(bricks[2][2].live == 0){
				bricks[2][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 245 && ty < 285 && bricks[3][2].isfull){

			bricks[3][2].live --;

			if(bricks[3][2].live == 0){
				bricks[3][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 290 && ty < 330 && bricks[4][2].isfull){

			bricks[4][2].live --;

			if(bricks[4][2].live == 0){
				bricks[4][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 335 && ty < 375 && bricks[5][2].isfull){

			bricks[5][2].live --;

			if(bricks[5][2].live == 0){
				bricks[5][2].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
	}
	
	//------col 4 ---------------------------------------------------
	if((tx >= 183 && tx <= 187) || (tx >= 238 && tx <= 242)){
		
		if(ty > 110 && ty < 150 && bricks[0][3].isfull){

			bricks[0][3].live --;

			if(bricks[0][3].live == 0){
				bricks[0][3].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
		
		}
		
		if(ty > 155 && ty < 195 && bricks[1][3].isfull){

			bricks[1][3].live --;

			if(bricks[1][3].live == 0){
				bricks[1][3].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 200 && ty < 240 && bricks[2][3].isfull){

			bricks[2][3].live --;

			if(bricks[2][3].live == 0){
				bricks[2][3].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 245 && ty < 285 && bricks[3][3].isfull){

			bricks[3][3].live --;

			if(bricks[3][3].live == 0){
				bricks[3][3].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 290 && ty < 330 && bricks[4][3].isfull){

			bricks[4][3].live --;

			if(bricks[4][3].live == 0){
				bricks[4][3].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 335 && ty < 375 && bricks[5][3].isfull){

			bricks[5][3].live --;

			if(bricks[5][3].live == 0){
				bricks[5][3].isfull = 0;
				score++;
			}
		
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
	}
	
	//------col 5 ---------------------------------------------------
	if((tx >= 243 && tx <= 247) || (tx >= 298 && tx <= 302)){
		
		if(ty > 110 && ty < 150 && bricks[0][4].isfull){

			bricks[0][4].live --;

			if(bricks[0][4].live == 0){
				bricks[0][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 155 && ty < 195 && bricks[1][4].isfull){

			bricks[1][4].live --;

			if(bricks[1][4].live == 0){
				bricks[1][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
		
		}
		
		if(ty > 200 && ty < 240 && bricks[2][4].isfull){

			bricks[2][4].live --;

			if(bricks[2][4].live == 0){
				bricks[2][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 245 && ty < 285 && bricks[3][4].isfull){

			bricks[3][4].live --;
		
			if(bricks[3][4].live == 0){
				bricks[3][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 290 && ty < 330 && bricks[4][4].isfull){

			bricks[4][4].live --;

			if(bricks[4][4].live == 0){
				bricks[4][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
		
		if(ty > 335 && ty < 375 && bricks[5][4].isfull){

			bricks[5][4].live --;

			if(bricks[5][4].live == 0){
				bricks[5][4].isfull = 0;
				score++;
			}
			
			line_equation2(circles[i].x, circles[i].y, i);
			
		}
	}
	
}

void full_Brick_Array(){
	int temp = 5;
	for(int i=0; i<6; i++){
		for(int j=0; j<5; j++){
			bricks[i][j].row = i;
			bricks[i][j].col = j;
			bricks[i][j].isfull = 0;
			bricks[i][j].live = 0;
			if( i == 0){
				bricks[i][j].y1 = 110;
				bricks[i][j].y2 = 150;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
			else if( i == 1){
				bricks[i][j].y1 = 155;
				bricks[i][j].y2 = 195;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
			else if( i == 2){
				bricks[i][j].y1 = 200;
				bricks[i][j].y2 = 240;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
			else if( i == 3){
				bricks[i][j].y1 = 245;
				bricks[i][j].y2 = 285;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
			else if( i == 4){
				bricks[i][j].y1 = 290;
				bricks[i][j].y2 = 330;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
			else if( i == 5){
				bricks[i][j].y1 = 335;
				bricks[i][j].y2 = 375;
				bricks[i][j].x1 = temp;
				temp += 55;
				bricks[i][j].x2 = temp;
				temp += 5;
			}
		}
		temp = 5;
	}
}

void full_Circles_Array(){
	for(int i=0; i<500; i++){
		if(i == 0){
			circles[i].isExist = 1;
			circles[i].x = 150;
			circles[i].y = 400;
			circles[i].step = 4;
			circles[i].is_on_horizon = 1;
		}
		else {
			circles[i].isExist = 0;
			circles[i].x = circle_place_x;
			circles[i].y = 400;
			circles[i].step = 4;
			circles[i].is_on_horizon = 1;
		}
	}
}

void splash_screen(int y){
	cleardevice();
	setcolor(8);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtextxy(40,y,"Swipe Brick Breaker");
	setcolor(6);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(85,y+45,"Fateme Noori");
	
	if(y == 155){
	setcolor(4);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	outtextxy(70,310,"Click to continue...");
	}
}

void show_gameover_msg(){
	cleardevice();
	setcolor(4);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
	outtextxy(55,200,"GAME OVER");
	setcolor(6);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(105,280,"SCORE");
	char arr[5];
	sprintf(arr,"%d",score);
	outtextxy(130,305,arr);
}

void primary_show(){
	setcolor(0);
	setlinestyle (SOLID_LINE, 0, THICK_WIDTH);
	line(0,100,310,100);
	
	setlinestyle (SOLID_LINE, 0, THICK_WIDTH);
	line(0,410,310,410);
	
	//show game title and programer name
	setcolor(8);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtextxy(40,15,"Swipe Brick Breaker");
	setcolor(6);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(85,60,"Behnam M Karimi");
	bar (0, 410, 310, 560);
	
	//show scores
	setcolor(6);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(15,450,"Score");
	char arr[5];
	sprintf(arr,"%d",score);
	outtextxy(30,480,arr);
	
	//show high scores
	setcolor(6);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(185,450,"High Score");
	sprintf(arr,"%d",highscores);
	outtextxy(222,480,arr);
	
	//show ball
	draw_circles();
	
	//show bricks in thier apropriate place
	draw_the_bricks();
}

int flying_balls_counter(){
	int count = 0;
	for(int i = 0; i < level; i++){
		if(circles[i].y < 400)
			count ++;
	}
	return count;
}

void reshape(){
	
	int counter = 0;
	
	for(int i = 0; i < level; i++)
		circles[i].step = 4;
		
	while(!endLevel){
		
	//	primary_show();
		
		for(int i = 0; i < level; i++){
					
			if(!circles[i].is_on_horizon){
				circles[i].y = circles[i].y - circles[i].step;
				circles[i].x= calculate_x(circles[i].y, i);		
				
				//colision to the roof
				if(circles[i].y <= 113 ){
					circles[i].step = -circles[i].step;
					line_equation2(circles[i].x, circles[i].y, i);
				}
				
				//colision to walls
				if(circles[i].x >= 296 || circles[i].x <= 5 ){
					line_equation2(circles[i].x, circles[i].y, i);
				}
				
				//circle is on the floor
				if(circles[i].y >= 397 && firstone == 1){
					circle_place_x = circles[i].x;
					circles[i].y = 400;
					firstone = 0;
					circles[i].is_on_horizon = 1;
					counter++;
					
				}
				
				if(circles[i].y >= 397 && firstone == 0){
					circles[i].y = 400;
					circles[i].is_on_horizon = 1;
					counter++;
				}
					
				//collision to floor of a brick
				floor_brick_collision(i);
				
				//collision to walls of a brick
				walls_brick_collision(i);
				
				delay(5);
				cleardevice();
				primary_show();
				
				if(!flying_balls_counter())
					endLevel = 1;
			}
		//delay(15);
		}
		primary_show();
	}
	
}

//-----------------------------------------------


int main()
{  
    srand(time(NULL));
    circle_place_x = 150;
	circle_place_y = 400;
	full_Brick_Array();
	full_Circles_Array();
	level = 3;
	game_over = 0;
	score = 0;
	
	for(int i = 0; i < 500; i++){
		line_eq[i][0] = 0;
		line_eq[i][1] = 0;
	}
	
	ifstream inFile;
	inFile.open("data.txt");
	inFile >> highscores;
	inFile.close();
	
	set_random_bricks();
	
	initwindow(310, 560," ",500,200, 1,0);
	setbkcolor(7);
	cleardevice();
	
	splash_screen(155);
	while(!ismouseclick(WM_LBUTTONDOWN)){
			delay(100);
	}
	for(int i = 155; i>= 15; i-= 2){
		splash_screen(i);
		delay(15);
	}
	clearmouseclick(WM_LBUTTONDOWN);
	cleardevice();
	
	while(!game_over){
		endLevel = 0;
		firstone = 1;
		
		for(int i = 0; i < level; i++)
		{
			circles[i].y = 400;
			circles[i].x = circle_place_x;
			circles[i].is_on_horizon = 0;
		}
		
		primary_show();
		while(!ismouseclick(WM_LBUTTONDOWN)){
			delay(50);
		}
		
		line_Equation(0);
		for(int i = 1; i < level; i++){
			line_eq[i][0] = line_eq[0][0];	
			line_eq[i][1] = line_eq[0][1];
		}
		
		reshape();
				
		if(move_bricks()){
			set_random_bricks();
		}
		cleardevice();
		
		circles[level - 1].isExist = 1;
	}
	
	if(score > highscores)
		highscores = score;
		
	ofstream outFile;
	outFile.open("data.txt");
	outFile << highscores << endl;
	outFile.close();
		
	show_gameover_msg();
		
	getch();
    return 0;
}


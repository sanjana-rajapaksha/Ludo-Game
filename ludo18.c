#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


int Dice,Rand,output,clr,piece,num,x,piece_count,six_count; 
int win_count = 0;
char players[][7]={"Yellow","Blue","Red","Green"};
int inboard_piece_count[4]={0,0,0,0};//{Y,B,R,G}
int in_home_piece[4]={0,0,0,0};//{Y,B,R,G}
char clr_pieces[4]={'Y','B','R','G'};
int firstPlyArry[4];
char winners[4];

int loc[4][4] = {{ 0 ,0 ,0 ,0},   // {Y1,Y2,Y3,Y4},
                 {13,13,13,13},   // {B1,B2,B3,B4},
                 {26,26,26,26},   // {R1,R2,R3,R4},
                 {39,39,39,39}};  // {G1,G2,G3,G4}

int start_loc[4][4] = {{ 0 ,0 ,0 ,0},    // {Y1,Y2,Y3,Y4},
                       {13,13,13,13},    // {B1,B2,B3,B4},
                       {26,26,26,26},    // {R1,R2,R3,R4},
                       {39,39,39,39}};   // {G1,G2,G3,G4}

int to_home_enty[4][4] = {{50,50,50,50},   // {Y1,Y2,Y3,Y4},
                          {50,50,50,50},   // {B1,B2,B3,B4},
                          {50,50,50,50},   // {R1,R2,R3,R4},
                          {50,50,50,50}};  // {G1,G2,G3,G4}
					  
int to_home[4][4] = {{6,6,6,6},   // {Y1,Y2,Y3,Y4},
                     {6,6,6,6},   // {B1,B2,B3,B4},
                     {6,6,6,6},   // {R1,R2,R3,R4},
                     {6,6,6,6}};  // {G1,G2,G3,G4}
				  
bool is_board[4][4] = {{false,false,false,false},   // {Y1,Y2,Y3,Y4},
                       {false,false,false,false},   // {B1,B2,B3,B4},
                       {false,false,false,false},   // {R1,R2,R3,R4},
		       {false,false,false,false}};  // {G1,G2,G3,G4}

			                    	  
void check_piece();
int enter();
void New_Out_Check();

void dice()
{ 
    int randomNumber = (rand() % 6) + 1;    // give random value (1-6)
    printf("%d\n", randomNumber);
    Dice = randomNumber;    
}

void randomNum()
{
    int randomNum = (rand() % x); // give random value (0 - (x-1))
    num = randomNum;
}

void status()
{
	printf("%s player now has %d/4 pieces on the board and %d/4 pieces on the base\n",players[clr],inboard_piece_count[clr],4-inboard_piece_count[clr] - in_home_piece[clr]);

	printf("____________________________________________________\n");
	printf("----------------------------------------------------\n");
	printf("         Location of pieces %s\n",players[clr]);
	printf("____________________________________________________\n");
	printf("----------------------------------------------------\n");
		
	for(int i=0;i<4;i++) //check piece one after other
	{
		printf("Piece %c%d -> ",clr_pieces[clr],i+1);

		if(is_board[clr][i]==true) // check is that piece onthe board
		{
			if(to_home_enty[clr][i] >= 0) // check is that piece before the home straight
			{
				printf("L%d\n",loc[clr][i]);
			}
			else
			{
				printf("H%d\n",6-to_home[clr][i]);  // check is that piece on the home straight
			}
		}
		else if(is_board[clr][i]==false && to_home[clr][i]==0)  // check is that piece on the home
		{
			printf("Home\n"); 
		}
		else  // if not any above conditions are true that piece on the base
		{
			printf("Base\n");
		}
	}
}

void In_home()
{
			printf("%s piece %c%d Go to Home and finish the game...\n",players[clr],clr_pieces[clr],piece + 1);
                        is_board[clr][piece] = false;    //move to home
                        inboard_piece_count[clr]=inboard_piece_count[clr]-1;  //decrement piece count onboard by 1
                        in_home_piece[clr]=in_home_piece[clr]+1; //increment piece count in home by 1

			if(in_home_piece[clr]==4)
                	{
				winners[win_count] = clr;
                        	win_count++;

                        	printf("##################################################################\n");
                        	printf("##################################################################\n");
                        	printf("                   %s finish the game...              \n" ,players[clr]);
                        	printf("##################################################################\n");
                        	printf("##################################################################\n");

                        	enter();
                	}
}

void home()
{

	if(to_home[clr][piece] >= Dice)  
	{
 		printf("%s_%d move H%d ",players[clr],piece + 1,6 - to_home[clr][piece]);
        	to_home[clr][piece] = to_home[clr][piece] - Dice;  // move thought home straight
        	printf("to H%d\n ",6 - to_home[clr][piece]);

        	if(to_home[clr][piece]==0)  //check piece came to home  
        	{
			In_home();   // if above condition true go to In_home function
        	}	
	}
}

void home_enty()
{
		printf("to H%d\n",-to_home_enty[clr][piece]);
		to_home[clr][piece]=to_home[clr][piece] + to_home_enty[clr][piece]; // how many squres to home
		if(to_home[clr][piece]==0)
		{
			In_home();
		}
	
}

void can_capture()  // check that moved piece can capture others pieces
{
	int k=0;
        for(int i = 0; i<4 ; i++) // check other colour one after other (i = colour)
        {
                if(i != clr ) // checking colour not equal to moved piece colour
                {
                        for(int j=0; j<4; j++) // check piece one by one (j = piece number)
                        {
                                if(is_board[i][j]==true && loc[clr][piece] == loc[i][j] && to_home_enty[i][j]>=0 ) // check is there any other colour piece on the moved piece new location 
                                {
                                        is_board[i][j]=false; // captured piece move to base
                                        loc[i][j] = start_loc[i][j]; // set its location to stating point
					to_home_enty[i][j]=50; // set its how much squre to home straight value 50
					inboard_piece_count[i] = inboard_piece_count[i] - 1; // decrement the pieces count on board by 1
                                        k = 1;
                                        printf("%s piece %c%d lands on square %d,captures %s piece %c%d,and return it to the base.\n",players[clr],clr_pieces[clr],piece + 1,loc[clr][piece],players[i],clr_pieces[i],j +1);
                                        break;
                                }
                        }
                }
                if(k==1) // if one piece captured no need to check othre piece so break the loop
                {
                        break;
                }
        }
}

    
void Go() // move pieces before home straight and print locations
{
        if(to_home_enty[clr][piece] >= 0) // check,is the piece location on before the home straight
        {
                printf("%s move piece %c%d from location L%d ",players[clr],clr_pieces[clr],piece + 1,loc[clr][piece]);
                loc[clr][piece]=loc[clr][piece]+Dice;    // new location = previous location + dice value
                to_home_enty[clr][piece]=to_home_enty[clr][piece]-Dice;  // how many squares to home straight

                if(loc[clr][piece]>=52)  // the next square after L52 is L0,so check the location value > 52
                {
                        loc[clr][piece]=loc[clr][piece] - 52; // then -52 to change the value for correct order
                }

                if(to_home_enty[clr][piece] < 0) // after move by dice value if piece come to home straight then go to home_entry function
                {
		       	home_enty();
                }

                else    // after move by dice value if piece still not come to home straight then print the new loc
                {
                        printf("to L%d by %d units\n",loc[clr][piece],Dice);
                }
                can_capture(); 
        }
        else // if the piece location on home straight then go to home function
        {
                home();
        }
}

void selectPiece() // check and select the piece that can be move
{

	int p=0,q=0,r=0,s=0; // p for piece 1,q for piece 2,r for piece 3,s for piece 4
	int count=0;	

			while(1)
			{
				x=4;
				randomNum();  // to get 4 random numbers (0,1,2,3),select one piece randomly

				switch(num)
				{
					case 0 : p=1;    // if piece 1 check p=1
						 break;

					case 1 : q=1;    // if piece 2 check q=1
                                                 break;
                                                 
					case 2 : r=1;    // if piece 3 check r=1
                                                 break;

                                        case 3 : s=1;    // if piece 4 check s=1
                                                 break;

				}

					if(is_board[clr][num] == true && to_home_enty[clr][num] < 0 && to_home[clr][num] >=  Dice)  //check,is the selected piece on home straight and can it move by dice value
					{
						int k = 0;

						for(int i=0;i<4;i++)  //if above condition is true then check if any piece of same colour is on the landing squre
						{
							if(num!=i && is_board[clr][i]==true && loc[clr][num]+Dice == loc[clr][i])
							{	
								k=1;    //if above condition true that piece can't move 
								break;  //No need to check other pieces block or not break the loop and select other piece
							}
						}
						 if(k==0)  // if above condition is false k remain 0 so no piece block selected piece path
                                         	 { 
                                                	piece = num;    // piece = selected piece
                                                	home();
							break;
                                       		 }
					
					}
					else if(is_board[clr][num] == true && to_home_enty[clr][num] >= 0) // check,is the selected piece on the board and before the home straight
					{
						int n=0;

						for(int i=0 ; i<4 ; i++)  //if above condition is true then check if any piece of same colour is on the landing squre
                                                {
                                                        if(num!=i && is_board[clr][i]==true && loc[clr][num]+Dice == loc[clr][i])
                                                        {
								n=1;    //if above condition true that piece can't move
                                                                break;  //No need to check other pieces block or not break the loop and select other piece
                                                        }
                                                }
                                                 if(n==0)  //if above condition is false n remain 0 so no piece block selected piece path
                                                 {
                                                        piece = num;     // piece = selected piece
                                                        Go();
							break;
                                                 }
					
					}
					if(p==1 && q==1 && r==1 && s==1)   // if all 4 pieces checked and no piece go thought above conditions that mean no piece on board can move.
					{
						if(Dice==6 && (inboard_piece_count[clr]+in_home_piece[clr])<4) // then check if dice = 6 and is there any piece on base
						{
							New_Out_Check();  
							break;
						}
				
						else  // if not any above conditions are true,it mean there is no piece can move.. turn goes to player 
						{
							printf("No %s piece can move...Dice goes to next player...\n",players[clr]);
							break;
						}
					}	
				
			}

		if(Dice == 6 && six_count < 2)  // if dice = 6 and six count < 2 player has anothr chance to roll 
        {
                printf("%s player rolled ",players[clr]);
                dice();
        }
		
}

void NewPiece_out(int i)
{
	if(i<4)
	{
                         printf("%s player move piece %c%d to the starting point\n",players[clr],clr_pieces[clr],i+1);
		         printf("%s player now has %d/4 pieces on the board and %d/4 pieces on the base\n",players[clr],i+1, 3-i); 
                        // enter();
			 if(six_count < 2) //	If six count is less than 2(0 or 1) dice again
			 {
			 	printf("%s player rolled ",players[clr]);
                         	dice();
			 }
	}
}

void New_Out_Check()
{
	int i;  // piece number

	for(i =0;i<4;i++)
	{
		if(is_board[clr][i] == false && to_home[clr][i]!=0) // check for piece one by one is on the base and not on the home
		{
			is_board[clr][i] = true;	// If a piece satisfy the above condition then it move out to board from base
			inboard_piece_count[clr] = inboard_piece_count[clr] + 1;  // In board piece count of that colour increment by one
			break;   // If one piece satisfy the condition no need for check other pieces.so break loop
		}
	}
	NewPiece_out(i);	// Goto NewPiece_out function with piece number(i)
}

void check_piece()	// choose one action either move a new piece out from base or move a piece that is already on board 
{	
	 if(Dice == 6 && inboard_piece_count[clr]==0)   // if dice = 6 and no piece on the board then check,can new piece move out from base
	 {
		New_Out_Check();
	 }

	 else if(Dice == 6 && (inboard_piece_count[clr] + in_home_piece[clr]) < 4) // if dice six and total pieces out of the base is less than 4 then choose 1 below option
   	 {
   		x=2; 
   		randomNum(); //for get 2 random numbers(0,1)
    			
    			if(num == 0)	
    			{	
    				selectPiece();		// if random num = 0 then check for move a piece that already on the board
   			}
			else
			{
				New_Out_Check();        // if random num = 1 then check for can new piece move out from base
			}
   	 }

	 else  // If dice is not six check for move a piece that already on the board
   	 {
	 	selectPiece();
	 }
}

void check_six()  // check six count in one row 
{
	while(Dice==6 && six_count < 2)		// if six count less than 2 (0 or 1) goto check_piece function and increment six count by one
	{
		check_piece();
		six_count = six_count +1;
	}
			
	if(Dice==6 && six_count == 2)		// if six count = 2(actally 3 because 0,1,2) roll ignores and dice goes to next player
	{
		printf("You got three 6 in row...Roll terminate..\n");
	}
	
	else
	{
		check_piece();
	}
}

int enter()
{
    printf("\nPress Enter to continue...\n");
    getchar(); // Waits for the user to press Enter
    scanf("%*[^\n]");
    return 0;
}

void colour(int i)
{
        clr = i;          // clr = i = output (0=Yellow, 1=Blue, 2=Red, 3=Green)
        six_count = 0;	  // six count for check how many times get six in one row

        if(Dice == 6)
        {
                check_six();  
        }
        else
        {
		check_piece();
        }
}

void first_player()
{
	while(1)
	{
			printf("selecting 1st player...\n\n");

			int first_dice;
			char players[][7]={"Yellow","Blue","Red","Green"};

			for (int i = 0; i < 4; i++)        // give random values (1-6) for each player
			{
			printf("%s rolls :",players[i]);
			dice();
			firstPlyArry[i]= Dice;       // store given value in array
			}

			int y = firstPlyArry[0];
			int b = firstPlyArry[1];
			int r =  firstPlyArry[2];
			int g = firstPlyArry[3];

			if(y>r && y>g && y>b)  //  if Yellow is greater than others
			{
					printf("Yellow player has highest roll and will begin the game\n");
					printf("The order of a single round is Yellow,Blue,Red,Green\n");
					output = 0;
					break;
			}
			else if(b>r && b>g && b>y)    //  if Blue is greater than others
			{
					printf("Blue player has highest roll and will begin the game\n");
					printf("The order of a single round is Blue,Red,Green,Yellow\n");
					output = 1;
					break;
			}

			else if(r>g && r>y && r>b)    //  if Red is greater than others
			{
					printf("Red player has highest roll and will begin the game\n");
					printf("The order of a single round is Red,Green,Yellow,Blue\n");
					output = 2;
					break;
			}
			else if(g>r && g>y && g>b)     //  if Green is greater than others
			{
					printf("Green player has highest roll and will begin the game\n");
					printf("The order of a single round is Green,Yellow,Blue,Red\n");
					output = 3;
					break;
			}
			else
			{
					printf("\nCan't select player.. roll again..\n");  // if there are more than one highest values dice roll again and again untill get one highst value
					continue;
			}
	}
}
 
void start_game()
{
	while(1)
{	
	if(win_count>3)		// check how many players have finished the game and if all palyers finished, end the loop and finish game
	{ 
		int a = winners[0];
		int b = winners[1];
		int c = winners[2];
		int d = winners[3];

		printf("\n1st place -> %s\n2nd place -> %s\n3rd place -> %s\n4th place -> %s\n",players[a],players[b],players[c],players[d]);
		break;
	}
//	enter();
	printf("\n%s player rolled ",players[output]);
        dice(); 		// call dice function to get random value between 1 to 6

	if(inboard_piece_count[output] == 0)     // output {0=Yellow ,1=Blue ,2=Red ,3=Green}   
	{					 // check no piece of that colour start the game					
		if(Dice == 6)
        	{
                        printf("%s can start game\n",players[output]);   // if no piece on the board and dice = 6 ,that colour can start game
                        colour(output);
		  	status();	
                        output = output + 1;  // Increase the output by 1 to pass the dice to the next player
               
                        if(output==4)	// If output = 3 it mean Green is the currunt player and next dice should go to Yellow after increament the output=4 but it should be output= 0 so if output=4 then it change to output=0;
                        {
                                output = 0;
                        }
                }

                else
                {
                         printf("%s can't start game\n",players[output]);

                         output = output + 1;

                        if(output==4)
                        {
                                output = 0;
                        }

                        printf("Dice goes to %s\n",players[output]);
                }
	}

	else
	{
        	colour(output);
		status();

		output = output + 1;

                if(output==4)
                {
                        output = 0;
                }
	}	
}

}


int main()
{
	srand(time(0));
	       
	enter();

	first_player();

	enter();

	start_game();
}



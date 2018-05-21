/*Author: Adam Powell
/Date: March 12, 2018
/COP 2220
/Professor Hunchuck
/Assignment 5: Zack Goes To The Track
/This program allows users to place bets on winners of horse races.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define PAUSE system("pause")
#define CLEAR system("cls")
#define MAX 8
#define WAIT Sleep(1000)

typedef struct {
	char name[20];
	int payout;
	int odds;
	int number;
	int racesWon;
}HORSE;



typedef struct {//did this for extra practice only
	double wallet;
	double bankAcct;

}GAMBLER;


void addMoney(GAMBLER *bank);
void makeBets(FILE *fp, GAMBLER *);
void menu();
void raceHorses(HORSE *A, HORSE *);
void myFlush();
void title();
void winsList(HORSE *, FILE *fp, int Flag);

main() {
	FILE *fp;
	srand(time(NULL));//seed srand function
	char input;
	GAMBLER *player;
	GAMBLER play;
	player = &play;
	player->wallet = 0;
	player->bankAcct = 1500;
	int FLAG = 0;

	do {
		
		input = 0;
		title();
		menu();
		scanf(" %c", &input);
		myFlush();
		input = toupper(input);

		switch (input) {
		case 'A'://GO to the Track
			makeBets(&fp, player);
			CLEAR;
			break;
		case 'B'://Past Winners
			CLEAR;
			title();
			winsList(NULL, &fp, FLAG);
			PAUSE;
			CLEAR;
			break;
		case 'C'://Add Money From ATM
			addMoney(player);
			CLEAR;
			break;
		case 'Q':
			CLEAR;
			title();
			printf("\n\n\n\t\t\t\t\t\t      Thanks for Playing!");
			WAIT; WAIT;
			break;
		default:
			printf("Invalid input! Try Again.");
			input = 0;
			break;
		}

	} while (input == 0 || input != 'Q');



	printf("\n");
	



}//end main()



void addMoney(GAMBLER *bank) {
	CLEAR;
	title();
	char joke;
	int num = 1;
	char userIn;
	int amount;

	
	if (bank->bankAcct <= 0) {
		CLEAR;
		printf("\n\n\n\t\t\t\t\tInsufficient Funds... Loading Main Menu");
		WAIT; WAIT; WAIT;
		
	}
	while ( num == 1) {

		if (bank->wallet == 0) {
		printf("\n\n\t\t\t\t\tYour out of cash!  Withdraw money from ATM? [Y/N]: ");
	}
	else {
		printf("\n\n\t\t\t\t\tWould you like to add cash? Your bank account has: $%.02f: [Y/N]: ", bank->bankAcct);
	}
	
		scanf("%c", &userIn);
		myFlush();
		userIn = toupper(userIn);
	do {	if (userIn == 'Y') {
			printf("\n\n\t\t\t\t\tBank Balance:....  $%.2lf \n\t\t\t\t\t Enter Withdrawel Amount: ", bank->bankAcct);
			scanf("%i", &amount);
			if (bank->bankAcct < amount&& bank->bankAcct > 0) {
				printf("\n\t\t\t\t\tYou dont have that much available, try again.");
				num = 1;
			}
			else{
				bank->bankAcct = bank->bankAcct - amount;
				bank->wallet = bank->wallet + amount;
				
					printf("\n\n\t\t\t\t\tYour balance is now $%.2lf, and your wallet now has: $%.2lf\n\n\t\t\t\t\tWould You Like to Print Your Receipt?? [Y/N]:  ", bank->bankAcct, bank->wallet);
					scanf(" %c", &joke);
					joke = toupper(joke);
					if (joke == 'Y') {
						do {
						printf("\n\t\t\t\t\tAre you sure you want to print a receipt? [Y/N]: ");
						scanf(" %c", &joke);
						joke = toupper(joke);
					} while (joke == 'Y');
						printf("\n\t\t\t\t\tThanks for saving our Green Earth by not wasting paper!!!");
					}
				
				printf("\n\n\t\t\t\t\t\t\tHave a Nice Day!");
				num = 0;
				WAIT; WAIT;
			}
		}else 
		if (userIn == 'N') {
			num = 0;
			}//end outer if/Else
	} while (num == 1 );//end do while

	if (userIn == 'N') {
		printf("Have a nice day");
		
		WAIT; WAIT;
	}//end if
	}//end outer while

	
	WAIT;
}//END OF addmoney

void makeBets(FILE *fp, GAMBLER *player) {
	int i = 0;
	int FLAG = 1;
	int choice = 0;
	char input;
	int wager = 0;
	HORSE *nWins;
	HORSE *hHorse;
	HORSE D = { 0 };;
	HORSE E = { 0 };
	nWins = &D;
	hHorse = &E;




	char playAgain = 0;

	do {



		CLEAR;
		title();
		while ( player->wallet <= 0 && player->bankAcct > 0) {
			addMoney(player);
			i++;
			if (i == 3) {
				printf("\n\n\t\t\t\tLoading Main Menu");
				WAIT; WAIT; WAIT;
				break;
			}
		}
		while (i < 2) {
			if (player->wallet <= 0 && player->bankAcct <= 0) {
				CLEAR;
				printf("\n\n\n\t\t\t\t\tInsufficient Funds... Loading Main Menu");
				WAIT; WAIT; WAIT;
				}

			printf("\n\n\t\t\t\t\t   HORSES   \t\t  PAYS          WIN ODDS\n");
			printf("\t\t\t\t\t____________________________________________________\n");
			printf("\t\t\t\t\t[1] HorestGump    \t 2 to 1 \t  40%% \n");
			printf("\t\t\t\t\t[2] NaySayer      \t 5 to 1 \t  10%% \n");
			printf("\t\t\t\t\t[3] BedHead       \t10 to 1 \t   8%% \n");
			printf("\t\t\t\t\t[4] PunyRoony     \t15 to 1 \t   6%% \n");
			printf("\t\t\t\t\t[5] AntsInPants   \t50 to 1 \t   1%% \n");
			printf("\t\t\t\t\t[6] Mr.Sniffles   \t20 to 1 \t   4%% \n");
			printf("\t\t\t\t\t[7] TooFless     \t10 to 1 \t   8%% \n");
			printf("\t\t\t\t\t[8] HoofHurtBad   \t 5 to 1 \t  10%% \n");
			printf("\t\t\t\t\t[9] Nut'nButOats  \t 3 to 1 \t  13%% \n");
			do {
				printf("\n\t\t\t\t\tPick your Pony:  ");
				scanf("%i", &choice); myFlush();
				printf("\t\t\t\t\tEnter your bet, can't bet more than $%.2lf:  ", player->wallet);
				scanf("%i", &wager); myFlush();


			} while (wager > player->wallet || choice < 1 || choice > 9 || wager < 1);

			player->wallet -= wager;
			raceHorses(nWins, hHorse);//calls race function

			winsList(nWins, &fp, FLAG);//saves result to bin file

			printf("\n\t\t\t\t\t\tRACE IN PROGRESS... \n");
			WAIT; WAIT; WAIT;

			if (choice >= 1 && choice <= 9) {
				if (choice == nWins->number) {

					wager = wager * (nWins->payout);
					player->wallet += wager;
					printf("\n\t\t\t\t\tCongratulations! %s WON $%d!\n", nWins->name, wager);
					printf("\t\t\t\t\t\tCurrent Cash: $%.02lf\n\n", player->wallet);
					PAUSE;
				}
				else
					if (nWins->number != choice) {
						printf("\n\t\t\t\t\tSorry %s won the race...You Lost $%d \n", nWins->name, wager);

						printf("\t\t\t\t\t\tCurrent Cash: $%.2lf\n", player->wallet);
						WAIT; WAIT; WAIT;
					}//end if/else

				if (player->bankAcct <= 0 && player->wallet == 0) {
					printf("\n\t\t\t\t        OoOoOhh...  YOU JUST WENT BUST!!....  YOUCH! \n\n\t\t\t\t\tCome on back when you have more money!!!\n\t\t\t\t\t");
					PAUSE;
					i = 3;
				}//end if
			}
			if (player->wallet > 0) {
				do {//ASK IF THEY WANT TO PLAY AGAIN
					printf("\n\t\t\t\tWant to Bet Again??,\n\t\t\t     You have: $%.2lf available to wager [Y/N]: ", player->wallet);
					scanf(" %c", &playAgain); myFlush();
					playAgain = toupper(playAgain);
					if (playAgain == 'N') {
						i = 3;
						break;
					}
				} while (playAgain != 'Y' && playAgain != 'N');//END DO WHILE
			}else
				if (player->wallet <= 0 && player->bankAcct > 0) {
					printf("\n\t\t\t\t\tYou Need to Add More Funds From ATM\n\n\n");
					WAIT; WAIT; WAIT;
					i = 3;
				}

		}//end while loop 
		
	}while (player->wallet > 0 && playAgain != 'N');//end of outer most do while
	
}//end makeBets

void menu() {//main menu
	printf("\t\t\t\t\t\t     [A] Go To The Races\n\n");
	printf("\t\t\t\t\t\t     [B] Past Winners\n\n");
	printf("\t\t\t\t\t\t     [C] Get Cash From ATM\n\n");

	printf("\t\t\t\t\t\t     [Q] Quit (Scores Save Automatically)\n\n");
	printf("\n\t\t\t\t\t\t     Enter Selection: ");
}//end menu()

void raceHorses(HORSE *wins, HORSE*horses) {
	//struct Vars

	int num = 1;
	HORSE horse1 = { "HorestGump", 2, 40 , 1, 0 };
	HORSE horse2 = { "NaySayer", 5, 50, 2 , 0 };
	HORSE horse3 = { "BedHead", 10, 58, 3, 0 };
	HORSE horse4 = { "PunyRoony", 15, 64, 4, 0 };
	HORSE horse5 = { "AntsInPants", 50, 65, 5, 0 };
	HORSE horse6 = { "Mr.Sniffles", 20, 69, 6 , 0 };
	HORSE horse7 = { "TooFless", 10, 77, 7, 0, };
	HORSE horse8 = { "HoofHurtBad", 5, 87, 8 , 0 };
	HORSE horse9 = { "Nut'nButOats", 3, 100, 9, 0 };

	int number;

	//wins = calloc(1, sizeof(HORSE*));
	//horses = calloc(9, sizeof(HORSE*));


	/*horses[0] = &horse1;
	horses[1] = &horse2;
	horses[2] = &horse3;
	horses[3] = &horse4;
	horses[4] = &horse5;
	horses[5] = &horse6;
	horses[6] = &horse7;
	horses[7] = &horse8;
	horses[8] = &horse9;
	*/
	
	//Generate a random number between 1 and 100
	
		number = ((rand() % 100) + 1);
		
	
	if (number <= 40) {


		strcpy(wins->name, horse1.name);
		wins->number = horse1.number;
		wins->odds = horse1.odds;
		wins->payout = horse1.payout;
		wins->racesWon = horse1.racesWon;

		strcpy(horses->name, horse1.name);
		horses->number = horse1.number;
		horses->odds = horse1.odds;
		horses->payout = horse1.payout;
		horses->racesWon = horse1.racesWon;

	}
	else
		if (number <= 50 && number > 40) {
			strcpy(wins->name, horse2.name);
			wins->number = horse2.number;
			wins->odds = horse2.odds;
			wins->payout = horse2.payout;
			wins->racesWon = horse2.racesWon;
		}

		else
			if (number <= 58 && number > 50) {
				strcpy(wins->name, horse3.name);
				wins->number = horse3.number;
				wins->odds = horse3.odds;
				wins->payout = horse3.payout;
				wins->racesWon = horse3.racesWon;
			}
			else
				if (number <= 64 && number > 58) {
					strcpy(wins->name, horse4.name);
					wins->number = horse4.number;
					wins->odds = horse4.odds;
					wins->payout = horse4.payout;
					wins->racesWon = horse4.racesWon;
				}
				else
					if (number == 65) {
						strcpy(wins->name, horse5.name);
						wins->number = horse5.number;
						wins->odds = horse5.odds;
						wins->payout = horse5.payout;
						wins->racesWon = horse5.racesWon;
					}
					else
						if (number <= 69 && number > 65) {
							strcpy(wins->name, horse6.name);
							wins->number = horse6.number;
							wins->odds = horse6.odds;
							wins->payout = horse6.payout;
							wins->racesWon = horse6.racesWon;
						}
						else
							if (number <= 77 && number > 69) {
								strcpy(wins->name, horse7.name);
								wins->number = horse7.number;
								wins->odds = horse7.odds;
								wins->payout = horse7.payout;
								wins->racesWon = horse7.racesWon;
							}
							else
								if (number <= 87 && number > 77) {
									strcpy(wins->name, horse8.name);
									wins->number = horse8.number;
									wins->odds = horse8.odds;
									wins->payout = horse8.payout;
									wins->racesWon = horse8.racesWon;
								}
								else
									if (number <= 100 && number > 87) {
										strcpy(wins->name, horse9.name);
										wins->number = horse9.number;
										wins->odds = horse9.odds;
										wins->payout = horse9.payout;
										wins->racesWon = horse9.racesWon;
									}
}//end of raceHorses()

void myFlush() {//clears the buffer
	char nothing;
	while (scanf("%c", &nothing) == NULL);
}//end myFlush

void title() {
	CLEAR;
	printf("\n\n        ============================================================================================================\n");
	printf("        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           Derby Dash Day           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("        ============================================================================================================\n\n");
}// end title()

void winsList(HORSE *w, FILE *fp, int FLAG) {
	int i;
	int counter = 1;


	HORSE allHorses[9] = { 0 };

	int horseNumber = 9;

	if (FLAG == 1) {
		horseNumber = w->number - 1;//to match horseArray
	}
	fp = fopen("savedWins.bin", "ab+");
	if (fp == NULL) {
		printf("Failed to open file, quitting program");
		WAIT; WAIT;
		exit(-1);
	}
	fread(allHorses, sizeof(HORSE), 9, fp);


	if (allHorses[horseNumber].number == 0 && FLAG == 1) {
		allHorses[horseNumber] = *w;
	}
	if (FLAG == 1) {
		allHorses[horseNumber].racesWon += 1;
	}
	fclose(fp);


	if (FLAG == 1) {

		fp = fopen("savedWins.bin", "wb");
		if (fp == NULL) {
			printf("Failed to open file, quitting program");
			WAIT; WAIT;
			exit(-1);
		}

		fwrite(&allHorses, sizeof(HORSE), 9, fp);

		fclose(fp);
	}// end if
	printf("\n\t\t\t\t\t             ALL TIME WINS BOARD            \n");
	printf("\t\t\t\t\t _^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_\n\t\t\t\t\t|\t\t\t\t\t     |\n");
	printf("\t\t\t\t\t|\t\t  WELCOME TO                 |\n");
	printf("\t\t\t\t\t|     *~  DERBY DOWNS ABUSEMENT PARK  ~*     |\n");
	printf("\t\t\t\t\t|- - - - - - - - - - - - - - - - - - - - - - |\n");

	for (i = 0; i < 9; i++) {
		if (allHorses[i].racesWon != 0) {
			printf("\t\t\t\t\t| %i.  #<%i> %s\t\t  %i\t     |\n", counter++, allHorses[i].number, allHorses[i].name, allHorses[i].racesWon);
		}
	}
	printf("\t\t\t\t\t|\t\t\t\t\t     |\n \t\t\t\t\t_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_^_\n\t\t\t\t\t   ||       ||      ||        ||        ||       \n");
	printf(" \t\t\t\t\t   []       []      []        []        []        \n");
	printf(" \t\t\t\t\t  /__\\     /__\\    /__\\      /__\\      /__\\      \n");
	printf("\n\t\t\t\t\t\t");
	

}//end winsList()

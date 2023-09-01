#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUESTIONS 20
#define MAX_USERS 100
#define MAX_NAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 30
struct User {
    char username[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};
struct Question {
    char question_text[500];
    char options[4][100];
    char correct_option;
};

void read_questions(FILE *file, struct Question *questions, int num_questions) {
    int i,j;
	for ( i = 0; i < num_questions; i++) {
        fscanf(file, "%499[^\n]\n", questions[i].question_text);
        for ( j = 0; j < 4; j++) {
            fscanf(file, "%99[^\n]\n", questions[i].options[j]);
        }
        fscanf(file, "%c\n", &questions[i].correct_option);
    }
}
void show_record() {
    FILE *f = fopen("score.txt", "r");
    if (f == NULL) {
        printf("No high score available.\n");
        return;
    }
    
    char name[MAX_NAME_LENGTH];
    float score;
    
    fscanf(f, "%s%f", name, &score);
    printf("\n\n\t\t*************************************************************");
    printf("\n\n\t\t %s has secured the Highest Score %.2f", name, score);
    printf("\n\n\t\t*************************************************************");
    
    fclose(f);
    getchar(); 
}

void reset_score() {
    FILE *f = fopen("score.txt", "w");
    if (f == NULL) {
        printf("Error opening score file.\n");
        return;
    }
    
    fprintf(f, "%s %.2f", "NoName", 0.0);
    
    fclose(f);
    printf("\n\n\t\tScore is reset to zero.\n");
}


void help()
	{system("cls");
    printf("\n\n                              HELP");
    printf("\n -------------------------------------------------------------------------");
    printf("\n ......................... C program Quiz Game...........");
    printf("\n >> There are two rounds in the game, WARMUP ROUND & CHALLANGE ROUND");
    printf("\n >> In warmup round you will be asked a total of 3 questions to test your general");
    printf("\n    knowledge. You will be eligible to play the game if you can give atleast 2");
    printf("\n    right answers otherwise you can't play the Game...........");
    printf("\n >> Your game starts with the CHALLANGE ROUND. In this round you will be asked");
    printf("\n    total 10 questions each right answer will be awarded $100,000.");
    printf("\n    By this way you can win upto ONE MILLION cash prize in USD...............");
    printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
    printf("\n    right option");
    printf("\n >> You will be asked questions continuously if you keep giving the right answers.");
    printf("\n >> No negative marking for wrong answers");

	printf("\n\n\t*********************BEST OF LUCK*********************************");
	printf("\n\n\t*****C PROGRAM QUIZ GAME is developed by Technical Team 5********");}

void edit_score(float score, char plnm[20]) {
    system("cls");
    float sc;
    char nm[20];
    FILE *f;
    f = fopen("score.txt", "r");
    fscanf(f, "%s%f", nm, &sc);  // Corrected line
    if (score >= sc) {
        sc = score;
        fclose(f);
        f = fopen("score.txt", "w");
        fprintf(f, "%s\n%.2f", plnm, sc);
        fclose(f);
    }
}
void shuffle_questions(struct Question arr[], int n) {
	int i,j;
    srand(time(NULL));
    for (i = n - 1; i > 0; i--) {
        j = rand() % (i + 1);
        struct Question temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
void register_user() {
    struct User users[MAX_USERS];
    int num_users = 0;
    int i;

    // Read existing user data from file
    FILE *users_file = fopen("users.txt", "r");
    if (users_file) {
        while (fscanf(users_file, "%s %s", users[num_users].username, users[num_users].password) != EOF) {
            num_users++;
        }
        fclose(users_file);
    }

    // Register a new user
    char new_username[MAX_NAME_LENGTH];
    char new_password[MAX_PASSWORD_LENGTH];
    printf("\nEnter a new username: ");
    scanf("%s", new_username);
    
    // Check if the username already exists
	int username_exists = 0;
	for (i = 0; i < num_users; i++) {
    	if (strcmp(new_username, users[i].username) == 0) {
        	username_exists = 1;
        	break;
    	}
	}

	if (username_exists) {
    	printf("Username already exists. Registration failed.\n");
	}
	else {
    	printf("Enter a password: ");
    	scanf("%s", new_password);

    	// Add the new user to the array
    	strcpy(users[num_users].username, new_username);
    	strcpy(users[num_users].password, new_password);
    	num_users++;

    	// Write the updated user data back to the file
    	users_file = fopen("users.txt", "w");
    	for (i = 0; i < num_users; i++) {
    	    fprintf(users_file, "%s %s\n", users[i].username, users[i].password);
    	}
    	fclose(users_file);

    	printf("User registered successfully!\n");
    	getch();
	}
}
char player_name[MAX_NAME_LENGTH];
int login() {
    struct User users[MAX_USERS];
    int num_users = 0;
    int i;

    // Read user data from file
    FILE *users_file = fopen("users.txt", "r");
    if (users_file) {
        while (fscanf(users_file, "%s %s", users[num_users].username, users[num_users].password) != EOF) {
            num_users++;
        }
        fclose(users_file);
    }

    // Prompt for login credentials
    char entered_username[MAX_NAME_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];
    printf("LOGIN");
    printf("\nEnter your username: ");
    scanf("%s", entered_username);
    printf("Enter your password: ");
    scanf("%s", entered_password);

    // Check if the entered credentials match any user
    for (i = 0; i < num_users; i++) {
        if (strcmp(entered_username, users[i].username) == 0 && strcmp(entered_password, users[i].password) == 0) {
        	printf("\n\n  LOGIN SUCCESSFUL");
        	strcpy(player_name, entered_username);
            return 1; // Login successful
            
        }
    }
    return 0; // Login failed
}
int main()
     {
    int count = 0;
    int i, n,ch;
    float score;
    char choice;
    struct Question questions[15];
	struct Question football[MAX_QUESTIONS];
    struct Question gk[MAX_QUESTIONS];
    struct Question sports[MAX_QUESTIONS];
    struct Question TV[MAX_QUESTIONS];
    struct Question music[MAX_QUESTIONS];
    struct Question geography[MAX_QUESTIONS];
    struct Question cricket[MAX_QUESTIONS];
    FILE *questions_file= fopen("questions.txt","r");
    FILE *football_file = fopen("football.txt", "r");
    FILE *gk_file = fopen("gk.txt", "r");
    FILE *sports_file = fopen("sports.txt", "r");
    FILE *TV_file=fopen("TV.txt","r");
    FILE *music_file=fopen("music.txt","r");
    FILE *geography_file=fopen("geography.txt","r");
    FILE *cricket_file=fopen("cricket.txt","r");
    
    if (football_file && gk_file && sports_file && TV_file && music_file && geography_file && cricket_file) {
        // Read questions from files into arrays
        read_questions(questions_file, questions, 15);
        read_questions(football_file, football, MAX_QUESTIONS);
        read_questions(gk_file, gk, MAX_QUESTIONS);
        read_questions(sports_file, sports, MAX_QUESTIONS);
        read_questions(TV_file, TV, MAX_QUESTIONS);
        read_questions(music_file, music, MAX_QUESTIONS);
        read_questions(geography_file, geography, MAX_QUESTIONS);
        read_questions(cricket_file, cricket, MAX_QUESTIONS);
        
        // Close the question files
        fclose(questions_file);
        fclose(football_file);
        fclose(gk_file);
        fclose(sports_file);
        fclose(TV_file);
        fclose(music_file);
        fclose(geography_file);
        fclose(cricket_file);
    } else {
        printf("Error opening question files.\n");
        return 1;
    }

    mainhome:
    printf("\n\n\t\t\tC PROGRAM QUIZ GAME");
    printf("\n\n\t\t________________________________________");

    printf("\n\t\t\t   WELCOME ");
    printf("\n\t\t\t      to ");
    printf("\n\t\t\t   THE GAME ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\n\t\t > Press S to start the game");
    printf("\n\t\t > Press V to view the highest score");
    printf("\n\t\t > Press R to reset score");
    printf("\n\t\t > Press H for help");
    printf("\n\t\t > Press N to register");
    printf("\n\t\t > Press Q to quit");
    printf("\n\t\t________________________________________\n\n\t\t ");
    choice = toupper(getch());

    if (choice == 'V') {
        show_record();
        goto mainhome;
    }
    else if (choice == 'H') {
        help();
        getch();
        goto mainhome;
    }
    else if (choice == 'R') {
        reset_score();
        printf("\n\n\t\tScore is reset to zero.");
        getch();
        goto mainhome;
    }
    else if (choice == 'Q')
        return 0;
    else if (choice == 'N') {
    	printf("REGISTRATION");
        register_user();
        goto mainhome;
    }
    else if (choice == 'S') {
    	if (login()) {
            goto start;
        } else {
            printf("\nLogin failed. Press any key to return to the main menu.");
            getch();
            goto mainhome;
        }
		start:
    	    system("cls");
    	    printf("\n ------------------  Welcome %s to C Program Quiz Game --------------------------", player_name);
    	    printf("\n\n Here are some tips you might wanna know before playing:");
    	    printf("\n ********************************************************************************");
    	    printf("\n >> There are two rounds in this Quiz Game, WARMUP ROUND & CHALLANGE ROUND");
    	    printf("\n >> In warmup round, you will be asked a total of 3 questions to test your general knowledge.");
    	    printf("\n    You need to answer at least 2 questions correctly to qualify for the next round.");
    	    printf("\n >> Your game starts with the CHALLANGE ROUND. In this round, you will be asked a total of 10 questions.");
    	    printf("\n    Each correct answer will be awarded $100,000.");
    	    printf("\n    By this way you can win up to ONE MILLION cash prize in USD.");
    	    printf("\n >> You will be given 4 options and you have to press A, B, C or D for the right option.");
        	printf("\n >> You will be asked questions continuously as long as you keep giving the right answers.");
    	    printf("\n >> There is no negative marking for wrong answers.");
    	    printf("\n\n\t\t!!!!!!!!!!!!! BEST OF LUCK !!!!!!!!!!!!!");
    	    printf("\n\n\n Press Y if you are ready to start the game!");
    	    printf("\n Press any other key to return to the main menu!");
    	    if (toupper(getch()) == 'Y') {
    	        goto home;
    	    } else {
    	        goto mainhome;
    	    }

    	home:
        	system("cls");
        	score = 0;
        	printf("\n ------------------  WARMUP ROUND --------------------------");
        	shuffle_questions(questions, sizeof(questions) / sizeof(questions[0]));

        	for (i = 0; i < 3; i++) {
            	printf("\n\n%s\n", questions[i].question_text);
            	for (n = 0; n < 4; n++) {
                	printf("\n\t%s", questions[i].options[n]);
            	}
            	printf("\n\n\n");
            	choice = toupper(getch());
            	if (choice == questions[i].correct_option) {
                	printf("\n\nCorrect!");
                	count += 1;
                	getch();
            	} else {
                	printf("\n\nWrong!");
                	printf("\n\nThe correct option is %c", questions[i].correct_option);
                	getch();
            	}
        	}
        	if(count>=2)
			{	
				goto test;}
			else
			{
				system("cls");
				printf("\n\nSORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME");
				getch();
				goto mainhome;
			}
		test:
			system("cls");
     	printf("\n\n\t*** CONGRATULATION %s you are eligible to play the Game ***",player_name);
     	printf("\n\n\n\n\t!Press any key to Start the Game!");
     	if(toupper(getch())=='p')
		{goto game;}
		game:
			system("cls");
			printf("\n ------------------  CHALLENGE ROUND --------------------------");
			printf("\n\t\tEnter your choice of Interest\n\n");
			printf("\n\t\t1. Football\n\n");
			printf("\n\t\t2. General Knowledge\n\n");
			printf("\n\t\t3. Sports\n\n");
			printf("\n\t\t4. TV Shows and Movies\n\n");
			printf("\n\t\t5. Music or Song\n\n");
			printf("\n\t\t6. Geography\n\n");
			printf("\n\t\t7. Cricket\n\n");
			scanf("%d",&ch);
			if(ch==1){
					system("cls");
       				 score = 0;
        
        			shuffle_questions(football, sizeof(football) / sizeof(football[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", football[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", football[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == football[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", football[i].correct_option);
                			getch();
           				 }
        			}
        		}
        	else if(ch==2){
        			system("cls");
       			 	score = 0;
        
        			shuffle_questions(gk, sizeof(gk) / sizeof(gk[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", gk[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", gk[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == gk[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", gk[i].correct_option);
                			getch();
           			 	}
        		}
        	}
			else if(ch==3){
					system("cls");
       				 score = 0;
        
        			shuffle_questions(sports, sizeof(sports) / sizeof(sports[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", sports[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", sports[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == sports[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", sports[i].correct_option);
                			getch();
           				}
        			}
        		}
			else if(ch==4){
					system("cls");
       				 score = 0;
        
        			shuffle_questions(TV, sizeof(TV) / sizeof(TV[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", TV[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", TV[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == TV[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", TV[i].correct_option);
                			getch();
           				}
        			}
        		}
			else if(ch==5){
				system("cls");
       			 score = 0;
        
        		shuffle_questions(music, sizeof(music) / sizeof(music[0]));

        		for (i = 0; i < 10; i++) {
           			printf("\n\n%s\n", music[i].question_text);
           			for (n = 0; n < 4; n++) {
               			 printf("\n\t%s", music[i].options[n]);
            		}
           			printf("\n\n\n");
            		choice = toupper(getch());
            		if (choice == music[i].correct_option) {
               			printf("\n\nCorrect!");
               			score += 100000;
               			getch();
            		} 
					else {
                		printf("\n\nWrong!");
                		printf("\n\nThe correct option is %c", music[i].correct_option);
                		getch();
           			}
        		}
        	}
			else if(ch==6){
					system("cls");
       				 score = 0;
        
        			shuffle_questions(geography, sizeof(geography) / sizeof(geography[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", geography[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", geography[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == geography[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", geography[i].correct_option);
                			getch();
           				}
        			}
        		}
			else if(ch==7){
					system("cls");
       				 score = 0;
        
        			shuffle_questions(cricket, sizeof(cricket) / sizeof(cricket[0]));

        			for (i = 0; i < 10; i++) {
           				 printf("\n\n%s\n", cricket[i].question_text);
           				 for (n = 0; n < 4; n++) {
               				 printf("\n\t%s", cricket[i].options[n]);
            			}
           				printf("\n\n\n");
            			choice = toupper(getch());
            			if (choice == cricket[i].correct_option) {
               				 printf("\n\nCorrect!");
               				 score += 100000;
               				 getch();
            			} 
						else {
                			printf("\n\nWrong!");
                			printf("\n\nThe correct option is %c", cricket[i].correct_option);
                			getch();
           				}
        			}
        		}	
        	else{
        		printf("\n\t\tINVALID OPTION\n\t\tEXITING!!!");
        		goto mainhome;
			}
        		
			goto score;
		score:
    	system("cls");
		if(score>10.00 && score<1000000.00)
		{
	   	printf("\n\n\t\t**************** CONGRATULATION *****************");
	   	printf("\n\t You won $%.2f",score);goto go;}

	 	else if(score==1000000.00)
		{
	    	printf("\n\n\n \t\t**************** CONGRATULATION ****************");
	    	printf("\n\t\t\t\t YOU ARE A MILLIONAIRE!!!!!!!!!");
	    	printf("\n\t\t You won $%.2f",score);
	    	printf("\t\t Thank You!!");
		}
	 	else
		{
	 		printf("\n\n\t******** SORRY YOU DIDN'T WIN ANY CASH ********");
	    	printf("\n\t\t Thanks for your participation");
	    	printf("\n\t\t TRY AGAIN");goto go;}

		go:
		puts("\n\n Press Y if you want to play next game");
		puts(" Press any key if you want to go main menu");
		if (toupper(getch())=='Y')
			goto home;
		else
		{
			edit_score(score,player_name);
			goto mainhome;
		}	
	}
	else{
		printf("Invalid choice");
		goto mainhome;
	}
	
}

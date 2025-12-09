#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


#define food_char (char)3
#define empty_char ' '
#define snake_char (char)254
#define head_char (char)1


typedef struct node{
	int data;
	int x;
	int y;
	struct node *next;
	
}node;

int rows,colms;
int score=0;
int gameover=0;
int foodx,foody;
int direction=1;
int fensx,fensy;
int hardmode=0;
int newfens=50;

node *head=NULL;
node *tail=NULL;

void add (int x,int y){
	node *n=malloc(sizeof(node));
	n->x=x;
	n->y=y;
	n->next=head;
	head=n;
	if(tail==NULL){
		tail=n;
	}
}

void rmv(){
	node *temp;
	if(head==tail){
		return;
		
	}
	temp=head;
	while(temp->next!=tail){
		
		temp=temp->next;
		
	}
	free(tail);
	tail=temp;
	tail->next=NULL;
	
}

int snakelocation(int x,int y){
	node *temp=head;
	while(temp!=NULL){
		if(temp->x==x && temp->y==y){
			return 1;
		}
		
		temp=temp->next;
		
	}
	return 0;
	
}
void placefood(){
	do{
		foodx=rand() % colms;
		foody=rand() % rows;
	}
	while(snakelocation(foodx,foody));
}

//hadi lel hard mode:

void placefens(){
	do{
		fensx=rand() % colms;
		fensy=rand() % rows;
	}
	while(snakelocation(fensx,fensy)|| (fensx==foodx && fensy==foody));
}



void keybinds(){
	if(_kbhit()){
		char c= _getch();
		if((c=='w' || c=='W')&&direction!=2){
			direction = 0;
		}
		if((c=='a' || c=='A')&&direction!=1){
			direction = 3;
		}
		if((c=='s' || c=='S')&&direction!=0){
			direction = 2;
		}
		if((c=='d' || c=='D')&&direction!=3){
			direction = 1;
		}
		if(c=='x' || c=='X'){
			gameover=1;
		}
		if(c=='p' || c=='P'){
			system("pause");
		}
		
		
		
	}
	
}
void gamelogic(){
	
	//nbdaw b movment:
	int headx = head->x;
	int heady = head->y;
	
	if(direction==0){
		heady--;
	}
	if(direction==1){
		headx++;
	}
	if(direction==2){
		heady++;
	}
	if(direction==3){
		headx--;
	}
	
	
	//losing case kyn 2:
	
	// 1-border case :
	
	if(headx<0 || headx >=colms || heady<0 || heady >=rows){
		gameover=1;
	}
	
	// 2-self case :
	if(snakelocation(headx,heady)){
		gameover=1;
	}
	
	//hna win ysra illusion t3 movment :
	
	// ndiro head w ida kla n5lo tail ida mklach n7oh :
	
	add(headx,heady);
	
	//+1 ki ykol:
	
	
	if(headx==foodx && heady==foody){
		score+=10;
		placefood();
		if(hardmode==1){
			placefens();
			
		}
		
	}
	else{
		rmv();
	}
	
	//fens f ns trig kol ma yakol ybdl plasto :
	
	if(headx==fensx && heady==fensy){
		gameover=1;
	}

}

void printing(){
	
	int i , y , x; 
	system("cls");
	
	
	printf("\nScore : %d\n",score);
	
	for(i=0;i<colms+2;i++){
		printf("*");
	}
	printf("\n");
	for(y=0;y<rows;y++){
		printf("*");
		for(x=0;x<colms;x++){
			if(x==head->x && y==head->y){
				printf("%c",head_char);
			}
			else if(snakelocation(x,y)){
				printf("%c",snake_char);
			}
			else if(x==foodx && y==foody){
				printf("%c",food_char);
			}
			else if(hardmode==1 && x==fensx && y==fensy){
				printf("#");
			}
			else{
				printf("%c",empty_char);
			}
			
		}
		printf("*\n");
	}
	for(i=0;i<colms+2;i++){
		printf("*");
	}
	
}



//HADI MAIN GAME :

void SnakeGame(int speed,int fens){
	system("title SnakeGame");
	
	printf("Size of the board 'rows / colms' :");
	scanf("%d %d",&rows,&colms);
	
	int firstx=colms/2;
	int firsty=rows/2;
	hardmode=fens;
	
	srand(time(NULL));
	
	add(firstx,firsty);
	placefood();
	if(hardmode==1){
		placefens();		
	}
	
	
	
	while(gameover==0){
		
		printing();
		keybinds();
		gamelogic();
		Sleep(speed);
		
		
		
	}
	system("color 4");
	printf("\nGameOver ! Your Score is : %d",score);
}


// Snakegame menuu: 

void snakeModsMenu(){
    int mod;

    system("cls");
    printf("=====================================\n");
    printf("            SNAKE GAME MODS          \n");
    printf("=====================================\n");
    printf("  [1] Easy Mode  (slow snake)\n");
    printf("  [2] Hard Mode  (fast snake)\n");
    printf("  [0] Back to Main Menu\n");
    printf("=====================================\n");

    do {
        printf("Choose a mode: ");
        scanf("%d", &mod);
    } while (mod < 0 || mod > 2);

    switch(mod){
        case 1:
            SnakeGame(150,0);  
            break;
        case 2:
            SnakeGame(40,1);    
            break;
        case 0:
            main();
            break;
    }
}




//==============================================================================================Game2;


typedef struct {
	node *top;
}stack;

void init(stack *s){
	s->top=NULL;
}

void push(stack *s,int x){
	node *n=malloc(sizeof(node));
	n->data=x;
	n->next=s->top;
	s->top=n;
}

void pop (stack *s){
	if(s->top==NULL){
		printf("\nStack Is Empty\n");
		return;
	}
	else{
		node *temp=s->top;
		s->top=s->top->next;
		free(temp);
	}
}

void show(stack *s){
	if(s->top == NULL){
		printf("\nNo Fails !\n");
	}
	else{
		system("cls");
		node *temp = s->top;
		int i=1;
		printf("===========================\n");
		printf("    YOUR FAILED GUESSES    \n");
		printf("===========================\n");
		while(temp!=NULL){
			printf("Attempt %d -> %d\n",i,temp->data);
			temp=temp->next;
			i++;
		}
		printf("===========================\n");
		
	}
}



void modes(int triesnum,int mod){
	
	stack s;
	init(&s);
	
	srand(time(NULL));
	int random = (rand() % mod) + 1 ;
	
	int n,tries=0,Wincase=0;
	do{
		printf("Guess The Number :");
		scanf("%d",&n);
		if(n==random){
			int l;
			system("cls");
			system("color 2");
			printf("======================================\n");
			printf("You Won ! The Number Was %d\n",random);
			printf("======================================\n");
			printf("[0] Back to Main Menu\n");
			printf("======================================\n");
			printf("Play Again ? :");
			scanf("%d",&l);
			if(l==0){
				main();
			}
			Wincase=1;
			break;
		}
		else if(n>random){
			printf("\nToo High !\n");
			push(&s,n);
		}
		else {
			printf("\nToo Low !\n");
			push(&s,n);
		}
	
		tries++;
	}while(tries<triesnum);
	if(!Wincase){
		int y;
		system("cls");
		system("color 4");
		printf("======================================\n");
		printf("Game Over ! The Number Was %d\n",random);
		printf("======================================\n");
		printf("  [1] Your Fails !\n");
		printf("  [0] Back to Main Menu\n");
		printf("======================================\n");
		do{
			printf("Choose :");
			scanf("%d",&y);
		}while(y<0 || y>1);
		
		switch(y){
			case 1:
				show(&s);
				break;
			
			case 0:
				main();
				break;	
		}
		
	}
}

void GTNModsMenu(){
	
	int mod;

    system("cls");
    system("color F");
    printf("=====================================\n");
    printf("        GuessTheNumber GAME MODS        \n");
    printf("=====================================\n");
    printf("  [1] Easy Mode   (1-20)(5 tries)\n");
    printf("  [2] Medium Mode (1-50)(7 tries)\n");
    printf("  [3] Hard Mode   (1-100)(10 tries)\n");
    printf("  [0] Back to Main Menu\n");
    printf("=====================================\n");

    do {
        printf("Choose a mode: ");
        scanf("%d", &mod);
    } while (mod < 0 || mod > 3);
    
    system("cls");
    
    switch(mod){
    	case 1 : 
			modes(5,20);
			break;
		
		case 2 :
			modes(7,50);
			break;
			
		case 3 : 
			modes (10,100);
			break;
			
		case 0 :
			exit(0);
			break;			
	}
	
}


// =================================================================================================================

//memory game ;

/*=================== MEMORY GAME STRUCTURES ===================*/

int MEMSIZE;

/* A permanent record of moves (displayed at the end) */
typedef struct MoveMemory {
    int row1, col1;
    int row2, col2;
    struct MoveMemory* next;
} MoveMemory;

/* To undo during gameplay */
typedef struct StackNodeMemory {
    int row1, col1;
    int row2, col2;
    struct StackNodeMemory* next;
} StackNodeMemory;

/*=================== MEMORY GAME FUNCTIONS ===================*/

/* Printing the moves from first to last */
void printMovesMemory(MoveMemory* head) {
    MoveMemory* reversed = NULL;
    MoveMemory* current = head;
    MoveMemory* newNode;
    MoveMemory* temp;
    int step = 1;

    printf("\n");
    printf("========================================\n");
    printf("    GAME STEPS - COMPLETE MOVE LIST    \n");
    printf("========================================\n\n");

    /* Reverse the list */
    while (current != NULL) {
        newNode = (MoveMemory*)malloc(sizeof(MoveMemory));
        newNode->row1 = current->row1;
        newNode->col1 = current->col1;
        newNode->row2 = current->row2;
        newNode->col2 = current->col2;

        newNode->next = reversed;
        reversed = newNode;

        current = current->next;
    }

    /* Print in correct order */
    current = reversed;

    while (current != NULL) {
        printf("  Step %2d: (%d,%d) -> (%d,%d)\n",
               step,
               current->row1, current->col1,
               current->row2, current->col2);
        step++;

        temp = current;
        current = current->next;
        free(temp); 
    }

    printf("\n========================================\n");
}

/* Adding a new move to the top of the stack to implement the Undo feature */
void pushMemory(StackNodeMemory** top, int r1, int c1, int r2, int c2) {
    StackNodeMemory* newNode = (StackNodeMemory*)malloc(sizeof(StackNodeMemory));
    newNode->row1 = r1;
    newNode->col1 = c1;
    newNode->row2 = r2;
    newNode->col2 = c2;
    newNode->next = *top;
    *top = newNode;
}

/* Removing the last element from the stack and retrieving its values */
int popMemory(StackNodeMemory** top, int* r1, int* c1, int* r2, int* c2) {
    StackNodeMemory* temp;
    if (*top == NULL) return 0;
    temp = *top;
    *r1 = temp->row1; *c1 = temp->col1;
    *r2 = temp->row2; *c2 = temp->col2;
    *top = temp->next;
    free(temp);
    return 1;
}

/* Adding a new move to the moves list (linked list) */
void addMoveMemory(MoveMemory** head, int r1, int c1, int r2, int c2) {
    MoveMemory* newMove = (MoveMemory*)malloc(sizeof(MoveMemory));
    newMove->row1 = r1; newMove->col1 = c1;
    newMove->row2 = r2; newMove->col2 = c2;
    newMove->next = *head;
    *head = newMove;
}

/* Drawing the game board on the screen */
void printBoardMemory(int board[10][10], int revealed[10][10]) {
    int i, j;
    
    printf("\n   ");
    for (j = 0; j < MEMSIZE; j++) printf(" %d ", j);
    printf("\n");

    for (i = 0; i < MEMSIZE; i++) {
        printf("%d  ", i);
        for (j = 0; j < MEMSIZE; j++) {
            if (revealed[i][j])
                printf("%d  ", board[i][j]);
            else
                printf("*  ");
        }
        printf("\n");
    }
    printf("\n");
}

/* Placing the numbers on the board as random pairs */
void shuffleBoardMemory(int board[10][10]) {
    int total = MEMSIZE * MEMSIZE;
    int cards[50];
    int i, j, k, tmp;

    for (i = 0; i < total; i++)
        cards[i] = i / 2 + 1;

    for (i = total - 1; i > 0; i--) {
        j = rand() % (i + 1);
        tmp = cards[i];
        cards[i] = cards[j];
        cards[j] = tmp;
    }

    k = 0;
    for (i = 0; i < MEMSIZE; i++)
        for (j = 0; j < MEMSIZE; j++)
            board[i][j] = cards[k++];
}

/* Determining whether the game has ended or not */
int isFinishedMemory(int revealed[10][10]) {
    int i, j;
    for (i = 0; i < MEMSIZE; i++)
        for (j = 0; j < MEMSIZE; j++)
            if (!revealed[i][j]) return 0;
    return 1;
}

/*=================== MEMORY GAME MENU ===================*/

void memorygamemenu() {
    int board[10][10];
    int revealed[10][10] = {0};
    MoveMemory* moves = NULL;
    StackNodeMemory* undoStack = NULL;
    int r1, c1, r2, c2;
    int level;
    int i, j;
    
    srand(time(NULL));
    
	
   
    system("cls");
    /* Choosing the game level */
    printf("\n");
    printf("==========CHOOSE GAME LEVEL:==========\n\n");
    printf("0 - 2x2 (Test)\n");
    printf("1 - 3x3 (Easy)\n");
    printf("2 - 4x4 (Medium)\n");
    printf("3 - 5x5 (Hard)\n\n");
    printf("Enter choice: ");
    scanf("%d", &level);
    
    /* Entering the game level */
    if (level == 0) MEMSIZE = 2;
    else if (level == 1) MEMSIZE = 3;
    else if (level == 2) MEMSIZE = 4;
    else if (level == 3) MEMSIZE = 5;
    else {
        /* If the level is unavailable */
        system("cls");
        printf("\n");
        printf("==========ERROR==========\n\n");
        printf("SORRY! Invalid choice!\n");
        printf("Default = 4x4\n\n");
        printf("=========================\n\n");
        MEMSIZE = 4;
        
        printf("Press Enter to continue...");
        getchar(); 
        getchar();
    }
    
    /* Preparing the game */
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            revealed[i][j] = 0;

    shuffleBoardMemory(board);

    /* Playing */
    while (!isFinishedMemory(revealed)) {
        system("cls");
        printBoardMemory(board, revealed);
        
        /* Selecting the first card */
        printf("Select first card (row): ");
        scanf("%d", &r1);
        printf("Select first card (col): ");
        scanf("%d", &c1);
        
        /* Checking the validity of the first card */
        if (r1 < 0 || r1 >= MEMSIZE || c1 < 0 || c1 >= MEMSIZE || revealed[r1][c1]) {
            system("cls");
            printf("\n");
            printf("==========Error==========\n\n");
            printf("Invalid move!\n\n");
            printf("=========================\n\n");
            printf("Press Enter to continue...");
            getchar();
            getchar();
            continue;
        }
        
        /* Revealing the first card */
        revealed[r1][c1] = 1;
        system("cls");
        printBoardMemory(board, revealed);
        
        /* Selecting the second card */
        printf("Select second card (row): ");
        scanf("%d", &r2);
        printf("Select second card (col): ");
        scanf("%d", &c2);
        
        /* Checking the validity of the second card */
        if (r2 < 0 || r2 >= MEMSIZE || c2 < 0 || c2 >= MEMSIZE || revealed[r2][c2] ||(r1 == r2 && c1 == c2)) {
            printf("\n");
            printf("==========Invalid move!==========\n\n");
            printf("That position is not valid!\n\n");
            printf("=================================\n\n");
            revealed[r1][c1] = 0;
            printf("Press Enter to continue...");
            getchar();
            getchar();
            continue;
        }
        
        /* Revealing the second card and displaying the board */
        revealed[r2][c2] = 1;
        system("cls");
        printBoardMemory(board, revealed);
        
        /* Recording the move */
        addMoveMemory(&moves, r1, c1, r2, c2);
        pushMemory(&undoStack, r1, c1, r2, c2);
        
        /* Checking for a match */
        if (board[r1][c1] != board[r2][c2]) {
            printf("\n==========Not a match!==========\n");
            printf("Cards: %d and %d\n", board[r1][c1], board[r2][c2]);
            printf("Try to remember their positions!\n");
            printf("================================\n\n");
            revealed[r1][c1] = revealed[r2][c2] = 0;
        } else {
            printf("\n==========Match!==========\n");
            printf("Great job! Both cards: %d\n", board[r1][c1]);
            printf("Keep going!\n");
            printf("==========================\n\n");
        }

        printf("Press Enter to continue...");
        getchar(); 
        getchar();
    }
    
    /* Clearing the screen and displaying the final board */
    system("cls");
    printBoardMemory(board, revealed);
    
    /* Congratulating the player */
    printf("\n");
    printf("==========Congratulations!==========\n\n");
    printf("You matched all cards!\n");
    printf("Well done!\n\n");
    printf("====================================\n");

    /* Printing the moves record */
    printMovesMemory(moves);
}



void rulesmenu(){
	system("cls");
    
    /* Explaining the rules of the game */
    printf("\n");
    printf("==========GAME RULES==========\n\n");
    printf("=The player chooses two cards and flips them over\n");
    printf("=If the two images match:\n");
    printf("    -The player keeps the pair.\n");
    printf("    -They score a point.\n");
    printf("    -They continue playing and flip another pair.\n");
    printf("=If they do not match:\n");
    printf("    -The two cards are turned face down again.\n");
    printf("    -The turn passes to the other player (if there is one)\n");
    printf("=Click on 9-> enter -> 9 to undo\n\n");
    printf("=[1] Play !\n");
    printf("=[0] Back\n");
    printf("==============================\n\n");
    int x;
    printf("Choose :");
    scanf("%d",&x);
    
    switch(x){
    	case 1:
    		memorygamemenu();
    	break;
    	case 0:
    		main();
    		break;
	}
    
}
















//========================================================================================================

//tictactoe;



/*====================== TIC TAC TOE STRUCTURES ======================*/

typedef struct {
    int position[100];
    char player[100];
    int count;
} MovesArrayTTT;

typedef struct StackNodeTTT {
    int position;
    char player;
    struct StackNodeTTT* next;
} StackNodeTTT;

typedef struct QueueNodeTTT {
    char player;
    struct QueueNodeTTT* next;
} QueueNodeTTT;

typedef struct {
    QueueNodeTTT* front;
    QueueNodeTTT* rear;
} QueueTTT;

/*====================== TIC TAC TOE HISTORY LIST ======================*/

typedef struct MoveNodeTTT {
    char action[20];
    struct MoveNodeTTT* next;
} MoveNodeTTT;

MoveNodeTTT* moveHistoryTTT = NULL;

void addHistoryTTT(MoveNodeTTT** head, const char* action) {
    MoveNodeTTT* newNode = (MoveNodeTTT*)malloc(sizeof(MoveNodeTTT));
    MoveNodeTTT* temp;
    strcpy(newNode->action, action);
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void printHistoryTTT(MoveNodeTTT* head) {
    MoveNodeTTT* temp = head;
    int num = 1;
    
    printf("\n");
    printf("========================================\n");
    printf("         MOVE HISTORY - GAME RECORD         \n");
    printf("========================================\n");
    
    while (temp != NULL) {
        printf("  %2d. %s\n", num++, temp->action);
        temp = temp->next;
    }
    
    printf("========================================\n");
}

/*====================== TIC TAC TOE MOVES ARRAY FUNCTIONS ======================*/

void addMoveTTT(MovesArrayTTT* moves, int pos, char player) {
    moves->position[moves->count] = pos;
    moves->player[moves->count] = player;
    moves->count++;
}

/*====================== TIC TAC TOE STACK (UNDO) ======================*/

void pushTTT(StackNodeTTT** top, int pos, char player) {
    StackNodeTTT* newNode = (StackNodeTTT*)malloc(sizeof(StackNodeTTT));
    newNode->position = pos;
    newNode->player = player;
    newNode->next = *top;
    *top = newNode;
}

int popTTT(StackNodeTTT** top, int* pos, char* player) {
    StackNodeTTT* temp;
    if (*top == NULL) return 0;
    temp = *top;
    *pos = temp->position;
    *player = temp->player;
    *top = temp->next;
    free(temp);
    return 1;
}

void limitStackTTT(StackNodeTTT** top) {
    int count = 0;
    StackNodeTTT* temp = *top;
    StackNodeTTT* curr;
    StackNodeTTT* prev;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    while (count > 6) {
        curr = *top;
        prev = NULL;
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        if (prev != NULL) prev->next = NULL;
        else *top = NULL;
        free(curr);
        count--;
    }
}

/*====================== TIC TAC TOE QUEUE FUNCTIONS ======================*/

void initQueueTTT(QueueTTT* q) {
    q->front = q->rear = NULL;
}

void enqueueTTT(QueueTTT* q, char player) {
    QueueNodeTTT* newNode = (QueueNodeTTT*)malloc(sizeof(QueueNodeTTT));
    newNode->player = player;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

char dequeueTTT(QueueTTT* q) {
    QueueNodeTTT* temp;
    char p;
    if (q->front == NULL) return '?';

    temp = q->front;
    p = temp->player;

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
    return p;
}

/*====================== TIC TAC TOE CLEAR INPUT BUFFER ======================*/

void clearInputBufferTTT() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*====================== TIC TAC TOE GAME ======================*/

void displayBoardTTT(char b[]) {
    printf("\n");
    printf("     %c | %c | %c \n", b[1], b[2], b[3]);
    printf("    ---+---+---\n");
    printf("     %c | %c | %c \n", b[4], b[5], b[6]);
    printf("    ---+---+---\n");
    printf("     %c | %c | %c \n\n", b[7], b[8], b[9]);
}

int checkWinTTT(char b[]) {
    int wins[8][3] = {
        {1,2,3},{4,5,6},{7,8,9},
        {1,4,7},{2,5,8},{3,6,9},
        {1,5,9},{3,5,7}
    };
    int i;

    for (i = 0; i < 8; i++) {
        if (b[wins[i][0]] == b[wins[i][1]] && 
            b[wins[i][1]] == b[wins[i][2]] && 
            b[wins[i][0]] != ' ') {
            return 1;
        }
    }
    return 0;
}

int boardFullTTT(char b[]) {
    int i;
    for (i = 1; i <= 9; i++)
        if (b[i] == ' ') return 0;
    return 1;
}

/*====================== TIC TAC TOE COMPUTER MOVE ======================*/

int computerMoveTTT(char b[]) {
    int pos;
    do {
        pos = (rand() % 9) + 1;
    } while (b[pos] != ' ');

    return pos;
}

/*====================== TIC TAC TOE MENU ======================*/



void tictactoegamemenu() {
    char board[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
    MovesArrayTTT moves;
    StackNodeTTT* undoStack = NULL;
    QueueTTT turn;
    char player;
    char input[5];
    int pos;
    
    srand(time(NULL));

   

    moves.count = 0;

    initQueueTTT(&turn);
    enqueueTTT(&turn, 'X');
    enqueueTTT(&turn, 'O');
    
    printf("Press Enter to continue...");
    getchar(); 

    while (1) {
        system("cls");

        displayBoardTTT(board);

        player = dequeueTTT(&turn);
        enqueueTTT(&turn, player);

        if (player == 'X') {
            printf("Player X, enter position (1-9) or 'u' to undo: ");
            scanf("%s", input);
            clearInputBufferTTT();

            if (input[0] == 'u') { 
                int p1, p2;
                char c1, c2;
                QueueNodeTTT* prevFront;
                QueueNodeTTT* prevRear;
                QueueNodeTTT* temp;
            
                if (undoStack==NULL){
                    system("cls");
                    printf("\n");
                    printf("==========Error==========\n\n");
                    printf("=There is no move to undo\n");
                    printf("=Your turn will be skipped :(\n\n");
                    printf("=========================\n\n");
                    
                    printf("Press Enter to continue...");
                    getchar();
                    continue;
                }

                if (popTTT(&undoStack, &p2, &c2)) board[p2] = ' ';
                if (popTTT(&undoStack, &p1, &c1)) board[p1] = ' ';

                addHistoryTTT(&moveHistoryTTT, "Undo");
                system("cls");
                printf("\n");
                printf("==========Undo successful!==========\n\n");
                printf("Your turn again, Player X.\n\n");
                printf("====================================\n\n");
                
                prevFront = turn.front;
                prevRear = turn.rear;

                turn.front = turn.rear = NULL;
                printf("Press Enter to continue...");
                getchar();
                enqueueTTT(&turn, 'X'); 

                temp = prevFront;
                while (temp != NULL) {
                    if (temp->player != 'X') {
                        enqueueTTT(&turn, temp->player);
                    }
                    temp = temp->next;
                }
            
                continue;
            }
            
            pos = atoi(input);

            if (pos < 1 || pos > 9 || board[pos] != ' ') {
                printf("\n");
                printf("==========Invalid move!==========\n\n");
                printf("That position is already taken!\n");
                printf("Wait for your next turn, Player X.\n\n");
                printf("=================================\n\n");
                printf("Press Enter to continue...");
                getchar();
                
            } else {
                char msg[20];
                board[pos] = player;
                addMoveTTT(&moves, pos, player);
                pushTTT(&undoStack, pos, player);
                limitStackTTT(&undoStack);

                sprintf(msg, "%c at %d", player, pos);
                addHistoryTTT(&moveHistoryTTT, msg);
            }
        }
        else {
            char msg[20];
            
            pos = computerMoveTTT(board);
            addMoveTTT(&moves, pos, player);

            board[pos] = player;
            
            pushTTT(&undoStack, pos, player);
            limitStackTTT(&undoStack);

            sprintf(msg, "%c at %d", player, pos);
            addHistoryTTT(&moveHistoryTTT, msg);
            
            printf("Computer O played at position %d\n\n", pos);
            printf("Press Enter to continue...");
            getchar();
        }

        if (checkWinTTT(board)) {
            system("cls");
            displayBoardTTT(board);
            printf("\n");
            printf("==========Player %c wins!==========\n", player);
            printf("Congratulations!\n\n");
            printf("==================================\n\n");
            printf("Press Enter to see history...");
            getchar();
            system("cls");
            break;
        }

        if (boardFullTTT(board)) {
            system("cls");
            displayBoardTTT(board);
            printf("\n");
            printf("==========Draw!==========\n");
            printf("Well played!\n\n");
            printf("=========================\n\n");
            printf("Press Enter to see history...");
            getchar();
            system("cls");
            break;
        }
    }
    
    printHistoryTTT(moveHistoryTTT);
}



void tictactoerules(){
	system("cls");
    printf("==========Welcome to XO Game==========\n");
    printf("GAME RULES :\n\n");
    printf("=You are X, Computer is O.\n");
    printf("=Enter 1-9 to make a move.\n");
    printf("=Enter 'u' to undo last round.\n");
    printf("=Be careful! If you choose an already reserved spot, your turn will be skipped!!!!!\n\n");
    printf("Board Position Guide:\n");
    printf("     1 | 2 | 3 \n");
    printf("    ---+---+---\n");
    printf("     4 | 5 | 6 \n");
    printf("    ---+---+---\n");
    printf("     7 | 8 | 9 \n\n");
    printf("=[1] Play !\n");
    printf("=[0] Back\n");
    printf("==========Let's start!==========\n\n");
    
    int x;
    printf("Choose :");
    scanf("%d",&x);
    
    switch(x){
    	case 1:
    		tictactoegamemenu();
    	break;
    	case 0:
    		main();
    		break;
	}
    
}














// maiin menu w main function :

int main(){
    int choice;

    system("cls");
    system("color F");
    printf("=====================================\n");
    printf("             GAME LIBRARY            \n");
    printf("=====================================\n");
    printf("  [1] Snake Game\n");
    printf("  [2] GuessTheNumber\n");
    printf("  [3] Memory Game\n");
    printf("  [4] TicTacToe\n");
    printf("  [0] Exit\n");
    printf("=====================================\n");

    do {
        printf("Choose an option: ");
        scanf("%d", &choice);
    } while (choice < 0 || choice > 4);

    switch(choice){
        case 1:
            snakeModsMenu();  
            break;
        case 2:
            GTNModsMenu();
            break;
        case 3:
            rulesmenu();
            break;
        case 4:
			tictactoerules();
			break;
        case 0:
            printf("Goodbye!\n");
            exit(0);
    }
}



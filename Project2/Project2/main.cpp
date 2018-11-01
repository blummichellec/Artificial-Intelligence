/* Main Program
 
 The purpose of this project is to solve the 8-puzzle
 problem using A*.
 
 Michelle Blum
 CMPT 420 - Artificial Intelligence
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Assigning directions to these values makes the code more readable
#define H2
#define RIGHT 3
#define LEFT 2
#define UP 1
#define DOWN 0

//Group these variables into a single unit
//All of these variables are parts of the output
struct output_vars
{
    int block[9];
    char* str;
    int pathcost;
    int valid;
    int totalcost;
    output_vars* next;
};

//Declare all functions written within this program
int manDist(int block[]);
void prepend(output_vars* newnode, output_vars* oldnode, int operator1);
int goal(int* block);
int unexplored(int block[]);
output_vars* best_node();
void print_block(int* block);
int apply (int* newstate, int* oldstate, int op);
output_vars* newelement();
int op(char);
char to_char(int i);

//Declare arrays
char rep[] = "dulr"; //Characters used to represent directions
int notvalid1[4] = { 6, 0, 0, 2 };
int notvalid2[4] = { 7, 1, 3, 5 };
int notvalid3[4] = { 8, 2, 6, 8 };
int applyparam[4] = { +3, -3, -1, +1 };
int goal_block[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8}; //8 indicates no tile; this will be used to hold the goal state
int maxdepth;
output_vars* top;

//Main program can be placed here because functions declared above
int main()
{
    int block[9];
    
    printf("\nWelcome to the Eight-Puzzle Game!\n");
    
    printf("\nHow would you like the initial state to look? \n\n"
           "TIPS:\nIndicate tiles with numbers 1 through 8, and the blank space with 'x'. \n"
           "Type values of tiles from left to right for each row. Start from the topmost row to the bottommost row. \n"
           "Your final string will look similar to this '1 4 2 3 x 6 7 8 5'. \n"
           "Remember to include spaces in between tiles. \n");
    
    //Verifies that user input is valid before continuing through program
    //Now we have the initial state
    int i = 0;
    while(i<9)
    {
        char tile;
        tile = fgetc(stdin);
        if (tile==32) continue;
        if (tile=='x') block[i] = 8;
        else if (tile >= '1' && tile <= '9') block[i] = tile - '1';
        else { printf("Invalid Input. Read the rules above and try again.", tile); return 1; }
        i++;
    }
    
    fgetc(stdin); //flush out the end of line character to allow for new input
    
    printf("\nEnter the goal state. (Usually, x 1 2 3 4 5 6 7 8): \n");
    
    //Verifies that user input is valid before continuing through program
    //Now we have the final state
    i = 0;
    while(i<9)
    {
        char tile;
        tile = fgetc(stdin);
        if (tile==32) continue;
        if (tile=='x') goal_block[i] = 8;
        else if (tile >= '1' && tile <= '9') goal_block[i] = tile - '1';
        else { printf("Invalid Input. Read the rules above and try again.",(int) tile); return 1; }
        i++;
    }
    
    //Select a maximum depth that the program will run
    printf("How deep would you like the computer to try and expand the graph? ");
    scanf("%d", &maxdepth);
    
    //Keep user posted while computer generates outcome
    printf("\nHmmm, thinking...");
    
    top = newelement();
    for(i=0; i<9; i++)
        top->block[i] = block[i];
    top->totalcost = manDist(block);
    
    output_vars* newnode = newelement();
    
    //After max depth is reached or the goal node is reached in the queue
    while (1)
    {
        output_vars* node = best_node();
        if (node == NULL) {
            printf("Looks like the thinking is over..\n");
            printf("There is no solution to this of less than %d depth.\n", maxdepth);
            printf("You should try again with an increased depth\n");
            printf(", but do not forget to consider that your initial state may be unsolvable.\n\n");
            break;
        }
        else if (goal(node->block)) {
            char chr[15];
            printf("Looks like the thinking is over.. \nFound the solution of least number of steps (%d).", node->pathcost);
            printf("\nWould you like to see a graphical display of each step? (Y/N)? ");
            scanf("%s", chr);
            if(chr[0] =='n' || chr[0]=='N') {
                printf("\n (Move Blank u=up, d=down, l=left, r=right)\n");
                printf(node->str);
                printf("\n");
                break;
            }
            
            int block2[9];
            for (i=0; i<node->pathcost; i++)
            {
                print_block(block);
                apply(block2, block, op(node->str[i]));
                for(int j=0; j<=8; j++)
                    block[j] = block2[j];
            }
            print_block(block);
            
            printf("\nAll steps are now being displayed.\nSteps taken: (Move blank u=up, d=down, l-left, r=right)\n");
            printf(node->str);
            printf("\n");
            break;
            
        }
        
        if (node->totalcost > maxdepth) continue;
        
        for(i=0; i<=3; i++) {
            if (apply(newnode->block, node->block, i) == -1)
                continue;
            
            if (unexplored(newnode->block)) {
                prepend(newnode, node, i);
                newnode = newelement();
                if (newnode==NULL) { printf ("ERROR!! Insufficient memory; try decreasing depth!"); return 1; }
            }
        }
        
    }
    return 0;
}

//The heuristic function
int manDist(int* block)
{
#ifdef H2
    int to_return = 0;
    
    for(int i=0; i<9; i++)
    {
        to_return += abs((i/3) - (block[i]/3));
        to_return += abs((i%3) - (block[i]%3));
    }
    return to_return;
    
#else
    int to_return = 0;
    
    for(int i=0; i<9; i++)
    {
        if (block[i] != i) to_return++;
    }
    return to_return;
    
    
#endif
    
}

//Add node to queue
void prepend(output_vars* newnode, output_vars* oldnode, int op)
{
    newnode->next = top;
    top = newnode;
    
    strcpy(newnode->str, oldnode->str);
    newnode->str[oldnode->pathcost] = rep[op];
    newnode->str[oldnode->pathcost+1] = 0;
    
    newnode->pathcost = oldnode->pathcost+1;
    newnode->totalcost = newnode->pathcost + manDist(newnode->block);
    if (newnode->totalcost < oldnode->totalcost) newnode->totalcost = oldnode->totalcost;
}

//Have we reached the goal?
int goal(int* block)
{
    int* g_block = goal_block;
    
    for(int i=0; i<9; i++)
        if ((*(block++))!=(*(g_block++)))
            return 0;
    
    return 1;
}

//Look through present queue to decide if node is already waiting to be explored
int unexplored(int* block)
{
    int i,j;
    output_vars* t = top;
    
    while (t!=NULL)
    {
        for(i=0; i<9; i++)
            if (t->block[i] != block[i]) break;
        if (i==9) return 0;
        
        t = t->next;
    }
    return 1;
}

//Which member of the queue should be explored next?
output_vars* best_node()
{
    output_vars* t = top;
    int min_totalpathcost = 1000;
    int totalpathcost;
    output_vars* to_return = NULL;
    
    while (t != NULL)
    {
        if (t->valid==1 && t->totalcost < min_totalpathcost)
        {
            min_totalpathcost = t->totalcost;
            to_return = t;
        }
        t = t->next;
    }
    
    if (to_return != NULL) to_return->valid = 0;
    
    return to_return;
}

//Apply the computer's chosen action to generate the next state
int apply (int* newstate, int* oldstate, int op)
{
    int j;
    int blank;
    
    for (j=0; j<9; j++)
        if (oldstate[j]==8) { blank=j; break; }
    
    if (blank==notvalid1[op] || blank==notvalid2[op] || blank==notvalid3[op])
        return -1;
    
    for (j=0; j<9; j++)
        newstate[j] = oldstate[j];
    
    newstate[blank] = newstate[blank+applyparam[op]];
    newstate[blank+applyparam[op]] = 8;
    
    return 1;
}

output_vars* newelement()
{
    output_vars* t = new output_vars;
    if (t==NULL) return NULL;
    t->valid = 1;
    t->str = new char[maxdepth+1];
    if (t->str ==NULL) return NULL;
    t->str[0] = 0;
    t->pathcost = t->totalcost = 0;
    t->next = NULL;
    return t;
}

//Print the 8-puzzle board
void print_block(int* block)
{
    printf("\n");
    printf ("\n-------");
    printf ("\n|%c|%c|%c|", to_char(block[0]), to_char(block[1]), to_char(block[2]));
    printf ("\n-------");
    printf ("\n|%c|%c|%c|", to_char(block[3]), to_char(block[4]), to_char(block[5]));
    printf ("\n-------");
    printf ("\n|%c|%c|%c|", to_char(block[6]), to_char(block[7]), to_char(block[8]));
    printf ("\n-------");
}

char to_char(int i)
{
    if (i>=0 &&i<=7) return i+'1';
    else if (i==8) return 'x';
    else { printf("ERROR in Program!"); return -1; }
    
}

//Case statement used to define direction representations for final output path
int op(char i)
{
    switch (i)
    {
        case 'd': return 0;
        case 'u': return 1;
        case 'l': return 2;
        case 'r': return 3;
        default: printf("ERROR"); return -1;
    }
}






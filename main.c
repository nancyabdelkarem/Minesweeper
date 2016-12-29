#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define str_len 256
/*Global variables*/
char name[str_len+1];
long long playerscore;
int flags_number= 0,question_number= 0,moves= 0;//variables for counting moves,flags and question marks
int min=0;//variable for counting minutes
int extime=0;//variable for counting seconds
int rows,columns; //2 variables for the size of the grid
long long time1;//variables for counting score and total time
long long game1[30]; //array for columns numbered
long long game2[30]; //array for rows numbered
char game[30][30]; // board used for build random mines
long long game3[30][30]; // board used for build random mines
char game4[30][30]; //game board
typedef struct name_scores_pair{
    char name[str_len+1];
    long long playerscore;
    }name_scores_pair_t;
/* main menu function*/
int welcome_game(){
    int x; //variable for knowing which choice the player takes
    flags_number=0,question_number=0,moves=0,min=0,extime=0;
    printf("main menu:\n");
    printf("to start game enter 1\n\n");
    printf("to load game enter 2\n\n");
    printf("to show players ordered with their scores enter 3\n");
    scanf("%d",&x);
    system("cls");  // Get rid of welcome screen
    return x;
}
void open_game(int x){
if(x==1){
    play_game();
  }
  if (x==2){
    load_game();
  }
  if (x==3){
    scores_list();
  }
}
/* function for build game board*/
void play_game(){
    long long i,j;
printf("Enter the numbers of rows and columns:");
scanf("%llu%llu",&rows,&columns); //taking the size of the grid
// columns numbered
 game1[0]= 0;
  for (i=1;i<=columns;i++)
    game1[i]=i;
//rows numbered
  game2[0]= 0;
  for (i=1;i<=rows;i++)
    game2[i]=i;
//build game board
  for(i=0;i<rows;i++)
  { for(j=0;j<columns;j++){
    game[i][j]='x';
     game4[i][j]='x';
}
}

print_first_cell(0,0);//calling function for print the board
start_game();
}
/* function for making the player choose from 4 actions*/
void start_game(){
int y; //variable for knowing which action the player chooses
if (moves==0){
printf("to open cell enter 1\n\n");
printf("to put flags enter 2\n\n");
printf("to put questions enter 3\n\n");
printf("to remove flags or questions enter 4\n\n");
scanf("%d",&y);
}
else{
clock_t start,end;
start=clock();
printf("to open cell enter 1\n\n");
printf("to put flags enter 2\n\n");
printf("to put questions enter 3\n\n");
printf("to remove flags or questions enter 4\n\n");
scanf("%d",&y);
end=clock();
 extime= (end-start)/CLOCKS_PER_SEC+extime;//calculating time in seconds
 while(extime>59) //transforming time into minutes and seconds
{
min=min+1;
extime=extime-60;
}}

if (y==1){
    if(moves==0)
        {
          random_game();
        }
    else{
        opencells();
    }
}
if (y==2) use_flags();
if (y==3) use_questions();
if (y==4) unmark_cells();
}
/* function for taking the first cell and making random depending on it*/
void random_game(){
long int x,y;
clock_t start,end;
start=clock();
  printf("Enter x,y to open your first cell:\n");
scanf("%ld %ld",&x,&y);//coordinates of the first cell
end=clock();
 extime= (end-start)/CLOCKS_PER_SEC+extime;//calculating time in seconds
 while(extime>59) //transforming time into minutes and seconds
{
min=min+1;
extime=extime-60;
}
  long long number_of_mines;
  number_of_mines = 1 +(rows*columns)/10; //formula for calculating the number of mines
srand(time(NULL)); //using for making random  every time the player starts playing
long long r=0,c=0,m,n,flage=0,i,j;
//loop for making the first cell the player chooses does not contain mines
    for( m= 0; m < number_of_mines; m++)
    {
       r=rand()%(rows);
       c=rand()%(columns);
        if(((r==x-1)&&(c==y-1))||(game[r][c]=='*'))
          {
            m--;
          }
        else{
        game[r][c]='*';
        }
        }
//loop for calculating numbers around mine cells
for(i=0;i<rows;i++)
  { for(j=0;j<columns;j++)
    { n=0;
      flage=0;
      if(game[i][j]=='*')
      {   flage=1;
          game3[i][j]=9;
      }
      else{
        if(game[i][j-1]=='*')
            n++;
        if(game[i][j+1]=='*')
            n++;
        if(game[i-1][j]=='*')
            n++;
        if(game[i+1][j]=='*')
            n++;
        if(game[i-1][j-1]=='*')
            n++;
        if(game[i-1][j+1]=='*')
            n++;
        if(game[i+1][j-1]=='*')
            n++;
        if(game[i+1][j+1]=='*')
            n++;
      }
      if(flage==0)
       {game3[i][j]=n;
    }
   }
   }
 open(x,y); //calling function to open the cell the player chooses
 for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
    if(game3[i][j]==0){
     game[i][j]=' ';
     }
     else if(game3[i][j]==9){
        game[i][j]='*';}
     else game[i][j]=game3[i][j]+'0';
    }
}
//showing for the player the number of moves ,flags , question marks and the time he took every move
 printf("%d moves\n\n", moves);
 printf("%d flags\n\n", flags_number);
 printf("%d question mark\n\n", question_number);
 printf("%d min:%d sec\n\n", min,extime);

 start_game();//calling function to make the player choosing the action he wants every move
}
//function for taking the cells the player wants to open
void opencells(){
    long int x, y;

clock_t start,end;
start=clock();
printf("Enter x,y to open  cell:\n");
scanf("%ld %ld",&x,&y);
end=clock();
extime= ((end-start)/CLOCKS_PER_SEC)+extime;
while(extime>59)
{
min=min+1;
extime=extime-60;
}
opening_cells(x,y); //calling function to know if the player has chosen this cell before and doing some actions based on that
printf("\n");
printf("%d moves\n\n",moves);
printf("%d flags\n\n",flags_number);
printf("%d question mark\n\n",question_number);
printf("%d min:%d sec\n\n",min,extime);

start_game();
}
//function for taking the cell the player wants to put flag on it
void use_flags(){

int m,l;
long int x, y;
clock_t start,end;
start=clock();
printf("enter x,y of the cell to put flag:");
scanf("%d %d",&m,&l);
end=clock();
extime= ((end-start)/CLOCKS_PER_SEC)+extime;
while(extime>59)
{
min=min+1;
extime=extime-60;}
//checking if this cell is closing so the player can put flag on it
if(game4[m-1][l-1]=='x'){
flags_number++;
game4[m-1][l-1]='F';
}

print_first_cell(0,0);//call function to print the new board with the moves the player took
printf("\n");
printf("%d moves\n\n",moves);
printf("%d flags\n\n",flags_number);
printf("%d question mark\n\n",question_number);
printf("%d min:%d sec\n\n",min,extime);
start_game();
}
//function for taking the cell the player wants to put question mark on it
void use_questions(){

int m,l;
clock_t start,end;
start=clock();
printf("enter x,y of the cell to put question mark:");
scanf("%d %d",&m,&l);
end=clock();
 extime= ((end-start)/CLOCKS_PER_SEC)+extime;
while(extime>59)
{
min=min+1;
extime=extime-60;
}
//checking if this cell is closing so the player can put question mark on it
if(game4[m-1][l-1]=='x'){
question_number++;
game4[m-1][l-1]='?';
}
print_first_cell(0,0);
printf("\n");
printf("%d moves\n\n",moves);
printf("%d flags\n\n",flags_number);
printf("%d question mark\n\n",question_number);
printf("%d min:%d sec\n\n",min,extime);

start_game();
}
//function for taking the cells the player wants to remove flags or question marks
void unmark_cells(){

int m,l;
clock_t start,end;
start=clock();
printf("enter x,y of the cell to unmark :");
scanf("%d %d",&m,&l);
end=clock();
 extime= ((end-start)/CLOCKS_PER_SEC)+extime;
while(extime>59)
{
min=min+1;
extime=extime-60;
}
//checking if there is flag or question mark on cell or not
if(game4[m-1][l-1]=='F'){
flags_number--;
game4[m-1][l-1]='x';
}
if(game4[m-1][l-1]=='?'){
question_number--;
game4[m-1][l-1]='x';
}
print_first_cell(0,0);

printf("\n");
printf("%d moves\n\n",moves);
printf("%d question mark\n\n",question_number);
printf("%d flags\n\n",flags_number);
printf("%d min:%d sec\n\n",min,extime);

start_game();
}
//function for print the game board with new changes
void print_first_cell(long int x,long int y){
  int i,j;
  //opening file to save the board every time the player is making action
  FILE * fpointer;
fpointer=fopen("save.txt","w");
fprintf(fpointer,"%d %d\n",rows,columns);//saving the size of the grid in the file
//saving the board that shows the place of mines
for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
        fprintf(fpointer,"%llu ",game3[i][j]);
    }
    fprintf(fpointer,"\n");
}
fprintf(fpointer,"\n\n");
//print the game board for the player
  for(i=0;i<=rows;i++)
{ for(j=0;j<=columns;j++){
      if (i==0)
    {  if(j==0)
      { printf("  ");
        }
       else
      {

       printf("%llu ",game1[j]);
        }
    }else if(j==0)
     {
         printf("%llu ",game2[i]);
       }
     else{
        printf("%c ",game4[i-1][j-1]);

     }
    }
printf("\n\n");

}
//saving the game board
for(i=0;i<rows;i++){
for(j=0;j<columns;j++){
if (game4[i][j]==' ')
fprintf(fpointer,"%c ",'0');
else
fprintf(fpointer,"%c ",game4[i][j]);}
fprintf(fpointer,"\n");}
fprintf(fpointer,"\n");
fprintf(fpointer,"%d %d %d %d %d",moves,flags_number,question_number,min,extime);//saving the number of moves ,flags ,question marks and the time
fclose(fpointer);
}
//function for opening the cells the player has chosen
void open(long int x,long int y){
int i,j;
for(i=0;i<rows;i++)
{for(j=0;j<columns;j++)
{if((i==x-1)&&(j==y-1)&&(game4[i][j]=='x'))
 {if((game3[i][j]!=0)&&(game3[i][j]!=9))
 {game4[i][j]=game3[i][j]+'0';//changing the numbers to characters in  the game board
  moves++;
  //checking if the player opened all cells except the cells with mines
  //if he opened all cells except the cells with mines then he wins
  int a,b,flage=0;
  for(a=0;a<rows;a++){
    for(b=0;b<columns;b++){
        if((game4[a][b]=='x')&&(game3[a][b]!=9)){
            flage=1;
        }
    }
  }
  if(flage==0){
    win();
  }
 }
 //checking if the player selected a mine cell
 //if that happened he loses
  else if(game3[i][j]==9)
     {game4[i][j]='!';
      moves++;
      int k,l;
    for(k=0;k<rows;k++)
     {for(l=0;l<columns;l++){
       if((game3[k][l]==9)&&(game4[k][l]=='F')){
        game4[k][l]='*';
       }
        if((game3[k][l]!=9)&&(game4[k][l]=='F')){
                game4[k][l]='-';
                }
        if((game3[k][l]==9)&&(game4[k][l]=='x')){
                game4[k][l]='M';
                }
  }
  }
   print_first_cell(x,y);//print the board with the places of mines
    printf("%d moves\n\n", moves);
 printf("%d flags\n\n", flags_number);
 printf("%d question mark\n\n", question_number);
 printf("%d min:%d sec\n\n", min,extime);
  printf("\n******LOSE********\n\n to try again enter 1\n\n to exit enter 2\n\n");
  int s;
  scanf("%d",&s);
  system("cls");
  //asking the player if he want to play again or not
  if(s==1) open_game(welcome_game());
  if(s==2) exit(0);
}

//checking if the player selected empty cell
  else  if(game3[i][j]==0){
    game4[i][j]=' ';
     moves++;
    rec(i,j);//calling  function for making recursion
    rec1(x,y);
    int a,b,flage=0;
  for(a=0;a<rows;a++){
    for(b=0;b<columns;b++){
        if((game4[a][b]=='x')&&(game3[a][b]!=9)){
            flage=1;
        }
    }
  }
  if(flage==0){
    win();
  }
}

  }
 }
 }


 print_first_cell(x,y);
  }
//function for opening cells around opened cell
void open1(long int x,long int y){
int i,j;
for(i=0;i<rows;i++)
{for(j=0;j<columns;j++)
{if((i==x-1)&&(j==y-1)&&(game4[i][j]=='x'))
 {if((game3[i][j]!=0)&&(game3[i][j]!=9))
 {game4[i][j]=game3[i][j]+'0';
    int a,b,flage=0;
  for(a=0;a<rows;a++){
    for(b=0;b<columns;b++){
        if((game4[a][b]=='x')&&(game3[a][b]!=9)){
            flage=1;
        }
    }
  }
  if(flage==0){
    win();
  }
 }
  else if(game3[i][j]==9)
     {game4[i][j]='!';

      int k,l;
    for(k=0;k<rows;k++)
     {for(l=0;l<columns;l++){
       if((game3[k][l]==9)&&(game4[k][l]=='F')){
        game4[k][l]='*';
       }
        if((game3[k][l]!=9)&&(game4[k][l]=='F')){
                game4[k][l]='-';
                }
        if((game3[k][l]==9)&&(game4[k][l]=='x')){
                game4[k][l]='M';
                }

     }
  }
  print_first_cell(x,y);
  printf("%d moves\n\n",moves);
printf("%d question mark\n\n",question_number);
printf("%d flags\n\n",flags_number);
printf("%d min:%d sec\n\n",min,extime);
  printf("\n******LOSE********\n\n to try again enter 1\n\n to exit enter 2\n\n");
  int s;
  scanf("%d",&s);
  system("cls");
  if(s==1)  open_game(welcome_game());
  if(s==2) exit(0);
}


  else  if(game3[i][j]==0){
    game4[i][j]=' ';
    rec(i,j);
    rec1(x,y);
      int a,b,flage=0;
  for(a=0;a<rows;a++){
    for(b=0;b<columns;b++){
        if((game4[a][b]=='x')&&(game3[a][b]!=9)){
            flage=1;
        }
    }
  }
  if(flage==0){
    win();
  }
}

  }
 }
 }
}
//function for opening all empty cells related to the empty cell that the player has selected
void rec(int i,int j){
 if((i<rows)&&(i>=0)&&(j>=0)&&(j<columns)){ //condition for making recursion in all directions just in the size of the grid
         if((game3[i][j-1]==0)&&(game4[i][j-1]== 'x')) //checking that the cell is empty and it is still closed in the game board
         {game4[i][j-1]=' ';
          rec(i,j-1);
         }
        if((game3[i][j+1]==0)&&(game4[i][j+1]== 'x'))
          {game4[i][j+1]=' ';
          rec(i,j+1);
          }
        if((game3[i-1][j]==0)&&(game4[i-1][j]== 'x'))
          {game4[i-1][j]=' ';
          rec(i-1,j);
          }
        if((game3[i+1][j]==0)&&(game4[i+1][j]== 'x'))
          {game4[i+1][j]=' ';
          rec(i+1,j);
          }
        if((game3[i-1][j-1]==0)&&(game4[i-1][j-1]== 'x'))
           {game4[i-1][j-1]=' ';
           rec(i-1,j-1);
           }
        if((game3[i-1][j+1]==0)&&(game4[i-1][j+1]== 'x'))
           {game4[i-1][j+1]=' ';
           rec(i-1,j+1);
           }
        if((game3[i+1][j-1]==0)&&(game4[i+1][j-1]== 'x'))
           {game4[i+1][j-1]=' ';
          rec(i+1,j-1);
           }
        if((game3[i+1][j+1]==0)&&(game4[i+1][j+1]== 'x'))
           {game4[i+1][j+1]=' ';
           rec(i+1,j+1);
           }
}
}
//function for opening the cells with numbers around the empty cells
void rec1(long int x,long int y){
    int i,j;
    for(i=0;((i<rows)&&(i>=0));i++){
        for(j=0;((j<columns)&&(j>=0));j++){
            if(game4[i][j]==' '){
        if((game3[i][j-1]!=0)&&game4[i][j-1]=='x'){
           game4[i][j-1]=game3[i][j-1]+'0';
           }
        if((game3[i][j+1]!=0&&game4[i][j+1]=='x')){
            game4[i][j+1]=game3[i][j+1]+'0';
        }
        if((game3[i-1][j]!=0&&game4[i-1][j]=='x')){
            game4[i-1][j]=game3[i-1][j]+'0';
        }
        if((game3[i+1][j]!=0&&game4[i+1][j]=='x')){
            game4[i+1][j]=game3[i+1][j]+'0';
        }
        if((game3[i-1][j-1]!=0&&game4[i-1][j-1]=='x')){
            game4[i-1][j-1]=game3[i-1][j-1]+'0';
        }
        if((game3[i-1][j+1]!=0&&game4[i-1][j+1]=='x')){
            game4[i-1][j+1]=game3[i-1][j+1]+'0';
        }
        if((game3[i+1][j-1]!=0)&&game4[i+1][j-1]=='x'){
            game4[i+1][j-1]=game3[i+1][j-1]+'0';
        }
        if((game3[i+1][j+1]!=0)&&game4[i+1][j+1]=='x'){
            game4[i+1][j+1]=game3[i+1][j+1]+'0';
        }
}
}
}
}
//function for opening opened cell
void opening_cells(long int x,long int y){
    long int p,q;
    p=x-1;
    q=y-1;
if (game4[p][q]==(game3[p][q]+'0')){ //checking if the cell in the game board is opening

    int n=0;
    //calculating the number of flags around the opened cell
         if(game4[p][q-1]=='F')
            n++;
        if(game4[p][q+1]=='F')
            n++;
        if(game4[p-1][q]=='F')
            n++;
        if(game4[p+1][q]=='F')
            n++;
        if(game4[p-1][q-1]=='F')
            n++;
        if(game4[p-1][q+1]=='F')
            n++;
        if(game4[p+1][q-1]=='F')
            n++;
        if(game4[p+1][q+1]=='F')
            n++;
            //checking if the number of flags around the opened cell is equal to the number in the opened cell
    if(n==game3[p][q]){
            moves++;
            //opening all cells around the opened cells except those with flags
        if(game4[p][q-1]!='F')
            open1(p+1,q);
        if(game4[p][q+1]!='F')
            open1(p+1,q+2);
        if(game4[p-1][q]!='F')
          open1(p,q+1);
        if(game4[p+1][q]!='F')
           open1(p+2,q+1);
        if(game4[p-1][q-1]!='F')
          open1(p,q);
        if(game4[p-1][q+1]!='F')
          open1(p,q+2);
        if(game4[p+1][q-1]!='F')
           open1(p+2,q);
        if(game4[p+1][q+1]!='F')
           open1(p+2,q+2);
    }
print_first_cell(x,y); //print the new game board
}
else open(x,y); //if the cell was not open then calling function open to open it

}
//function if the player win
void win(){
int i,j;
//open file to save the names of the winners and their scores
FILE *list;
list=fopen("list .txt","a+");
//loop for replacing all the mines with F and printing it
for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
        if(game3[i][j]==9){
            game4[i][j]='F';
        }
    }
}
time1=extime+(min*60);//calculating the total time
print_first_cell(0,0); //printing the board with the places of mines
printf("%d moves\n\n",moves);
printf("%d question mark\n\n",question_number);
printf("%d flags\n\n",flags_number);
printf("%d min:%d sec\n\n",min,extime);

printf("********win********\n\nEnter your name: ");
scanf(" %[^\t\n]s",&name); //taking the name of the player
printf("\n");
//changing the name from capital to small characters
for(i=0;name[i]!='\0';i++){
    if((name[i]>='A')&&(name[i]<='Z')){
        name[i]-=('A'-'a');
}
}
printf("%s",name);
printf("\n\n");
playerscore = (pow(rows,4)*pow(columns,4))/(time1*moves);//formula for calculating the score
printf("your score: %d",playerscore);
printf("\n\n");
//saving the name and the score

fprintf(list,"%llu  %s",playerscore,name);
fprintf(list,"\n");
fclose(list);
//asking the player if he wants to play again
printf(" to play again enter 1\n\n to exit enter 2\n\n");
  int s;
  scanf("%d",&s);
  if(s==1)  open_game(welcome_game());
  if(s==2) exit(0);
}
//function for showing the list of the players names and their scores
void scores_list(){
    //open the file to read from it
FILE *list;
list=fopen("list .txt","r+");
int num=10;//the maximum  number of the list
int k=0;
int i=0,j,l,flage;
name_scores_pair_t *arr = (name_scores_pair_t *) malloc(sizeof(name_scores_pair_t) * num);//create an array of struct
    //read from the file until the lines end
while(!feof(list)){
   fscanf(list,"%llu  %[^\t\n]s ",&arr[i].playerscore,&arr[i].name);
   fscanf(list,"\n");
   i++;
    }
fclose(list);//close the file
int z=i;
for (j = 0; (j < i); j++){
     k=0;
  while(k<i){
     for(l=0;arr[j].name[l]!='\0';l++){
        if(arr[j].name[l]==arr[j+k+1].name[l]){
          flage=1;
        }
        else {
            flage=0;
            break;
        }
     }
     if(flage==1)
    {arr[j].playerscore+=arr[j+k+1].playerscore;
      arr[j+k+1].playerscore=0;
    }
   k++;
}
}
sorting(num, arr);//call function for sorting

for (j = 0;((j < i)&&(arr[j].playerscore!=0)); j++)
{
printf("%d-%llu \t %s \n",j+1,arr[j].playerscore,arr[j].name);
}
free(arr);
 open_game(welcome_game());
}
//function for sorting the list
void sorting(int n, name_scores_pair_t *array)
{
 int i, j;
name_scores_pair_t temp;
for (i = 0; i < n; i++)
{
    for (j = 0; j < (n - i - 1); j++)
    {
        if (array[j].playerscore < array[j + 1].playerscore)
        {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}
}

//function for load and continue game
void load_game(){
int i,j;
//opening file for reading from it the names and the scores
FILE *fpointer;
fpointer=fopen("save.txt","r");
fscanf(fpointer,"%d %d\n",&rows,&columns);//reading the size of the grid from the file
//reading the board with the mines places from the board
for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
        fscanf(fpointer,"%llu ",&game3[i][j]);
    }
    fscanf(fpointer,"\n");
}
fscanf(fpointer,"\n\n");
//reading the game board from the file
for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
        fscanf(fpointer,"%c ",&game4[i][j]);
    }
    fscanf(fpointer,"\n");
}
fscanf(fpointer,"\n");
fscanf(fpointer,"%d %d %d %d %d",&moves,&flags_number,&question_number,&min,&extime);//reading the number of moves.....
fclose(fpointer);
//replacing the cells with 0 to space
   for(i=0;i<rows;i++){
    for(j=0;j<columns;j++){
    if(game4[i][j]=='0')
    game4[i][j]=' ';
        }}

    game1[0]= 0;
  for (i=1;i<=columns;i++)
    game1[i]=i;

  game2[0]= 0;
  for (i=1;i<=rows;i++)
    game2[i]=i;

print_first_cell(0,0);

printf("\n");
printf("%d moves\n\n",moves);
printf("%d question mark\n\n",question_number);
printf("%d flags\n\n",flags_number);
printf("%d min:%d sec\n\n",min,extime);
start_game();//continue the game

}
//main function
int main(){
    open_game(welcome_game());

return 0;
}


#include<iostream>
#include <cstdio>
#include<conio.h>
#include<math.h>
using namespace std;
#define MAX 25   //limit of size of sudoku board

//Function to get input from user of unsolved Sudoku Board & it's size as well
int takeInput(int sudoku[MAX][MAX])
{
    int size = 0;
    cout<<"\t\t.................\n\t\t| SUDOKU SOLVER |\n\t\t.................\nChoose the size of board:\nEnter 1 for  4 X 4\n";
    cout<<"Enter 2 for  9 X 9\nEnter 3 for 16 X 16\nEnter 4 for 25 X 25\nYour Selection:\n";
    cin>>size;
    cout<<endl;

    for( ; ; )
    {
        if(size == 1)
        {
            size = 4;
            break;
        }
        else if(size == 2)
        {
            size = 9;
            break;
        }
        else if(size == 3)
            size = 16;
        else if(size == 4)
        {
            size = 25;
            break;
        }
        else
        {
            cout<<"Wrong input."<<endl;
            getch();
            return 0;
        }
    }

    cout<<"Enter the Initial "<<size<<" X "<<size<<" Sudoku Board:"<<endl;
    cout<<"Enter 0 for blank\n"<<endl;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            cin>>sudoku[i][j];
        }
    }

    return size;
}

//Function to display solved Sudoku Board
void displaySolution(int sudoku[MAX][MAX], int size)
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            printf("%3d", sudoku[i][j]);
        }
        cout<<endl;
    }
    cout<<"\n\n*************************************\n\n";
}

// Function to check if board is solved now i. e. it has no vacancies
// If the board is full then it is solved correctly
// This is true because, for each number we put in any cell,  we always check if all other vacant places can be
// filled by some numbers such that board is always in valid state

bool isFull(int sudoku[MAX][MAX], int size)
{
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            if(!sudoku[i][j])
                return false;
        }
    }
    return true;
}

//Function gives all different possible numbers those can be put on board such that board will be in valid
// state, and this is done by checking numbers already appeared in row, column and block
//Function to find various possible values at position (r, c)
//Returns no. of possible values at that position
//and those values in array a[]
int findPossibleValues(int sudoku[MAX][MAX], int size, int a[], int r, int c)
{
    int n=0;
    int i,j;
    int s=(int)(sqrt(size));
    int b[MAX+1]= {0};

    //Number of s appeared in current row
    for(i=0; i<size; i++)
    {
        b[sudoku[r][i]]=1;
    }

    //Number of s appeared in current column
    for(i=0; i<size; i++)
    {
        b[sudoku[i][c]]=1;
    }

    //Number of s appeared in current block
    r=(r/s)*s, c=(c/s)*s;

    for(i=r; i<r+s; i++)
    {
        for(j=c; j<c+s; j++)
        {
            b[sudoku[i][j]]=1;
        }
    }

    //Fill array a[] with number of s did not appear in current row, column and block
    for(i=1; i<=size; i++)
    {
        if(!b[i])
            a[n++]=i;
    }

    return n;
}



void SolveSudoku(int sudoku[MAX][MAX], int size, int &solution_num, bool &solved_flag, bool &enough)
{
    int i,j, a[MAX+1]= {0}, n=0;

    if(enough) //true if user does not want more solutions
        return;

    if(isFull(sudoku, size))    //true if now sudoku board is solved completely
    {

        if(!solved_flag)
        {
            cout<<"Sudoku Solved Successfully!"<<endl;
        }

        solved_flag = 1;

        //show the solution
        cout<<"\n\n        Solution no."<<(solution_num++)<<"\n       ...............\n\n"<<endl;
        displaySolution(sudoku, size);
        char more;
        cout<<"Do you want more solutions?"<<endl;
        cout<<"Press 1 for 'YES', anything OTHERWISE:\t";
        cin>>more;
        cout<<"\n\n*************************************************\n\n";

        if(more != '1')
        {
            enough = true;
        }

        return;
    }

    //Finding vacant place/position
    int break_flag = 0;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            if(!sudoku[i][j])
            {
                break_flag = 1;
                break;
            }
        }
        if(break_flag)
            break;
    }

    //check possibilities at that vacant place
    n = findPossibleValues(sudoku, size, a, i, j);
    for(int l=0; l<n; l++)
    {
        //put value at vacant place
        sudoku[i][j]=a[l];
        //now solve the updated board
        SolveSudoku(sudoku, size, solution_num, solved_flag, enough);
    }

    // if we come at this step, it means we have already checked all possible values at
    // sudoku[i][j] and we couldn't find the solution
    // so we make this sudoku[i][j] again a vacant cell and try to correct our previous guesses.
    sudoku[i][j]=0;
}

int main()
{
    int sudoku[MAX][MAX] = {0}, size;
    size = takeInput(sudoku);

    //cout<<"size ="<<size<<endl;
    if(size!= 4 && size!= 9 && size!= 16 && size!= 25)
    {
        return 0;
    }

    int solution_num = 1;
    bool solved_flag = 0;
    bool enough = 0;

    cout<<". . . . .Finding Solutions. . . . .\n\n"<<endl;
    SolveSudoku(sudoku, size, solution_num, solved_flag, enough);

    if(!solved_flag)
    {
        cout<<"Invalid Board!\nProgram Closing!"<<endl;
        getch();
        return 0;
    }

    cout<<"No more solutions.\nProgram Closing!"<<endl;
    getch();
    return 0;
}

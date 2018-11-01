/*Main Program
 
 The purpose of this project is to solve the 8-puzzle
 problem using Breadth-first search.
 
 Michelle Blum
 CMPT 420 - Artificial Intelligence
 */

#include <time.h>
#include "BFS.h"

using namespace std;

int main()
{
    //Initialize input state and goal state variables
    _BFS Initial, Target;
    
    cout << "Enter initial state in the form: \n0 1 2 3 4 5 6 7 8 \nThe value 0 indicates the blank space.\n\n";
    //Calls function with BFS.cpp to input state
    Initial.USER_INPUT();
    
    cout << "Enter Goal state in the form: \n0 1 2 3 4 5 6 7 8 \nThe value 0 indicates the blank space.\n\n";
    //Calls function with BFS.cpp to input state
    Target.USER_INPUT();
    
    //Print the initial and target states so that user can confirm they were received as intended
    cout << "\nInitial:\n" << endl;
    Initial.PrintBFS();
    cout << "\nTarget:\n" << endl;
    Target.PrintBFS();
    
    //Start the clock
    cout << "Let's begin searching for a solution!\n" << endl;
    clock_t t_begin, t_end;
    t_begin = clock();
    
    //
    vector<_BFS> Solution;
    Solution = _BFS::SearchSolution(Initial, Target);
    
    //Solution status concluded
    t_end = clock();
    //If solution function found result, print the steps taken and state the amount of steps
    if (Solution.empty()==false)
    {
        for (int i = 0; i < Solution.size(); i++)
        {
            cout << "\nStep " << i << ": \n" << endl;
            Solution[i].PrintBFS();
        }
        cout << endl << Solution.size()-1 << " step(s) in total. \n" << endl;
    }
    //If solution found no result, there is no solution
    else
        cout << "No Solution." << endl;
    
    //Either way, print the time elapsed in seconds
    cout << "Total time to find result: " << endl << (t_end - t_begin)/1000 << "s" << endl;
    
    return 0;
}

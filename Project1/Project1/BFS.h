#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector> //C++ does not allow to return entire array, so use vectors
#include <queue> //BFS uses FIFO
#include <unordered_map> //Allows to reference elements by mapped value, not by absolute position

using namespace std;

class _BFS_Solution;

//Create _BFS class and declare variables/ functions to be used within
class _BFS
{
public:
    _BFS();
    void PrintBFS();
    typedef unsigned int STATUS;
    typedef unsigned int MOVE;
    typedef int SERIAL;
    STATUS USER_INPUT();
    STATUS MoveZeroUp();
    STATUS MoveZeroDown();
    STATUS MoveZeroLeft();
    STATUS MoveZeroRight();
    STATUS Move(MOVE);
    static const STATUS ERROR = 0, DONE = 1;
    static const MOVE UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
    static SERIAL Encode(_BFS&);
    static _BFS Decode(SERIAL);
    static vector<_BFS> SearchSolution(_BFS&,_BFS&);
    bool operator ==(_BFS &);
    bool operator ==(_BFS const &);
    bool operator !=(_BFS &);
    bool operator !=(_BFS const &);
    
private:
    unsigned int State[9]; //This will be used to store 8-puzzle state
    unsigned int BlankSpace(_BFS);
    
    
};

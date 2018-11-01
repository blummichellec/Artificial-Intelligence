/* Main Program
 
 The purpose of this project is to create a Tic Tac Toe game using the Minimax algorithm without alpha-beta pruning.
 
 Michelle Blum
 CMPT 420 - Artificial Intelligence
 */

#include <iostream>
#include <algorithm>
#include <iomanip> //setw used
#include <limits> //Numeric limits used

const int gridsize = 3;

class TicTacToe
{
    //Use enum to create data types as the choice of contents for the game board
    enum class Player
    {
        none = '-',
        human = 'X',
        computer = 'O'
    };
    
    //Each play will be in a row and column form
    struct Play
    {
        int row= 0;
        int col = 0;
    };
    
    //The board is defined as 3x3
    Player board[gridsize][gridsize];
    
public:
    
    //This no argument constructor generates the initial state of the board
    TicTacToe()
    {
        for (int i = 0; i < gridsize; i++)
        {
            for (int j = 0; j < gridsize; j++)
            {
                board[i][j] = Player::none;
            }
        }
    }
    
    //Output a sqaure board
    const void printBoard()
    {
        std::cout << "-------------------";
        for (int i = 0; i < gridsize; i++)
        {
            std::cout << "\n|";
            for (int j = 0; j < gridsize; j++)
            {
                //displays the vertical sides of the playing board with grid entries in between
                std::cout << std::setw(gridsize) << static_cast<char>(board[i][j]) << std::setw(gridsize) << " |";
            }
        }
        std::cout << "\n-------------------\n";
    }
    
    //Check each column for remaining play spaces to determine if game is tied
    const bool TiedGame()
    {
        for (int i = 0; i < gridsize; i++)
        {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }
    
    //Check each horizontal, vertical, and diagonal to see if same enumeration type connected 3 times
    const bool Winner(Player player)
    {
        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;
        
        for (unsigned int i = 0; i < gridsize; i++)
        {
            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
            
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
        }
        return false;
    }
    
    Play minimax()
    {
        //Numeric limits provides information about properties of arithmetic types
        //Max is a member of numeric limits that finds the maximum finite value
        int score = std::numeric_limits<int>::max();
        Play Play;
        
        //The computer decides where to place an O
        for (int i = 0; i < gridsize; i++)
        {
            for (int j = 0; j < gridsize; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    
                    //Call max -> call min
                    int temp = maxSearch();
                    
                    if (temp < score)
                    {
                        score = temp;
                        Play.row = i;
                        Play.col = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }
        
        return Play;
    }
    
    //What would max do?
    int maxSearch()
    {
        //Evaluate if any of these options are true before continuing
        if (Winner(Player::human)) { return 10; }
        else if (Winner(Player::computer)) { return -10; }
        else if (TiedGame()) { return 0; }
        
        int score = std::numeric_limits<int>::min();
        
        for (int i = 0; i < gridsize; i++)
        {
            for (int j = 0; j < gridsize; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::human;
                    //Now that we know the best option (score) for max, let's move onto min
                    score = std::max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        
        return score;
    }
    
    //What would min do?
    int minSearch()
    {
        if (Winner(Player::human)) { return 10; }
        else if (Winner(Player::computer)) { return -10; }
        else if (TiedGame()) { return 0; }
        
        int score = std::numeric_limits<int>::max();
        
        for (int i = 0; i < gridsize; i++)
        {
            for (int j = 0; j < gridsize; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    //Return to max once min decides
                    //Repeat until all options evaluated
                    score = std::min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }
        
        return score;
    }
    
    void getHumanPlay()
    {
        bool undecided = true;
        int row= -1, col = -1;
        
        while (undecided)
        {
            std::cout << "Your Play: ";
            
            char c;
            std::cin >> c;
            row= (c-1) - '0';
            std::cin >> c;
            col = (c-1) - '0';
            
            undecided = board[row][col] != Player::none;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        }
        
        board[row][col] = Player::human;
    }
    
    void play()
    {
        bool turn = 0;
        bool exit = false;
        
        printBoard();
        std::cout << "Enter your play in the form [row,col]. \nEx. For the upper left corner enter 11.\n";
        
        
        while(!exit)
        {
            //Human makes a move
            //Initialized as 0 because human has first turn
            if (turn == 0)
            {
                if (Winner(Player::computer))
                {
                    std::cout << "LOSER\n";
                    exit = true;
                    std::cout << "\n\nTime to play again!\n";
                    TicTacToe tictactoe;
                    tictactoe.play();
                }
                
                getHumanPlay();
                
            }
            //Computer makes a move
            else
            {
                if (Winner(Player::human))
                {
                    std::cout << "WINNER!\n";
                    exit = true;
                    std::cout << "\n\nTime to play again!\n";
                    TicTacToe tictactoe;
                    tictactoe.play();
                }
                
                std::cout << "\nComputer Play:\n";
                
                Play aiPlay = minimax();
                board[aiPlay.row][aiPlay.col] = Player::computer;
                
            }
            
            if (TiedGame())
            {
                std::cout << "\nLooks like it's a tie...\n";
                exit = true;
                std::cout << "\n\nTime to play again!\n";
                TicTacToe tictactoe;
                tictactoe.play();
            }
            
            turn ^= 1;
            printBoard();
            
        }
    }
};

int main()
{
    TicTacToe tictactoe;
    tictactoe.play();
}

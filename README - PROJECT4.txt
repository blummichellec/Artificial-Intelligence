Project #4
Michelle Blum

Algorithm Description:

	Create a tic tac toe game using the Minimax algorithm without alpha-beta pruning. This is a backtracking algorithm 	which finds the optimal move for a player. In other words, it minimizes the maximum risk for player n.

Input format: RowCol
Output format: 3x3 game board with X's and O's

Data Structures/Functions used:

	printBoard outputs a square board

	TiedGame checks each column for remaining spaces in order to determine if the players tied

	Winner checks the horizontal, vertical, and diagonal directions to see if there are 3 X's or 3 O's in a row

	minimax calls maxSearch and minSearch

	maxSearch determines the move that would be made in a maximizing situation

	minSearch determines the move that would be made in a minimizing situation

	getHumanPlay allows the non-computer to input their choice

	play initiates the game and decides if computer or human is next; game outcome also decided here

	main calls the play function within the tic tac toe class

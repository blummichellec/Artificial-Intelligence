Project #2
Michelle Blum

Easy Initial State: 
	1 3 4 8 6 2 7 x 5

Easy Goal State: 
	1 2 3 8 x 4 7 6 5 (could not find 
	and easy one to test with the other goal state..)

Hard Initial State:
	 x 1 3 5 7 2 4 6 8

Easy Output: 
	5 steps - uruld

Hard Output: 
	18 steps - ddruuldrurdluldrul 

Note: 
	States in board form can be seen by testing code. Thought showing a bunch of 		photos of states in this file would be too much.

Data Structures/Functions used:
	
	manDist - defines the Manhattan Distance 
	heuristic
	
	prepend - adds node to front of queue

	goal - tests to see if goal state has been reached

	unexplored - tests to see if a node is 	presently in the queue

	best_node - uses heuristic value of nodes to 
	determine which is the best choice for 	expansion

	print_block - draws the game board

	apply - perform selected action on board

	op - facilitates display of final output path

	to_char - ensures that 8 in initialization of 
	goal_state will represent blank space

	A* uses a priority queue. To implement this, 	one must get the node with the 		lowest cost and decrease the cost of arbitrary elements.


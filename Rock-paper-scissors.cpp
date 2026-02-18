// Rock-Paper-Scissors Game
// Written by Arianna Almond
// Purpose: For the user and computer to play a game of rock-paper-scissors then output the winner with their score
// Presented 10/29/25 (Edited 12/16/25)


#include <iostream>
#include <fstream>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

// Function: getPlayer
// Purpose: Obtain the users move
// Input: Variable of the player's move
// Output: Players chosen move
char getPlayer() {
	char pMove;
	do {
		cout << " Please enter a move (R, P, S): "; // Input from user
		cin >> pMove;
		pMove = toupper(pMove);
	} while (pMove != 'R'&& pMove!='P'&& pMove!='S');

	return pMove; // Returns move value
}
// Function: getRandM
// Purpose: Generate a random number between 1 and 3 to determine the computer's move
// Input:Random generator
// Output: Random Move from computer
char getRandM() { // Random number/ move from computer
	char M;
	int random = rand() % 3 + 1; //calculate correct Move
	if (random == 1) { // Rock move
		M = 'R';
	}
	else if (random == 2) { // Paper move
		M = 'P';
	}
	else if (random == 3) { // Scissors move
		M = 'S';
	} 
	return M;
}
// Function: getWinner
// Purpose: Choose a Winner
// Input: Player move and computer move determines the winner
// Output:Winner of Game
string getWinner(char playmove, char compmove) { // determining for winner
	cout << " The computer picked: " << compmove << endl;
	string Tie;
	if (playmove == compmove) { // Same Move Ties the game
		return Tie; 
	}
	if (playmove == 'R' && compmove == 'S' || playmove == 'S' && compmove == 'P' || playmove == 'P' && compmove == 'R') {
		return "Player"; // player wins round
	}
	if (compmove == 'S' && playmove == 'P' || compmove == 'R' && playmove == 'S' || compmove == 'P' && playmove == 'R') {
		return "Computer"; //computer wins round
	}
	}

int main() {

	int rounds; 
	int score=0; // Score starts @ 0 for computer & user
	int playerScore = 0;
	int computerScore = 0;
	cout << " Welcome to the Rock-Paper-Scissors Game!\n"
		"How many rounds would you like to play? (1-3 rounds): ";
	cin >> rounds; // # of rounds the user inputs
	for (int i = 1; i <=rounds; i++) {
		char playermove = getPlayer(); // calling function for player's move
		char computermove = getRandM(); // calling function for computer's (random) move
		string winner= getWinner(playermove, computermove); // calling function to obtain winner of game
		if (winner == "Player") {  // player's win will display if player won round
			playerScore++;   // adds & outputs  player's score
		}
		else { // computer's win will display if computer wins round
			computerScore++;  // adds & outputs computer's score

		}
	}
	return 0;

}

//------------------------------------------------------------------------------
// File Name: EvilHangman.cpp
// Name: Gouri Yerra
// CWID: 10818827
// Class: CSCI 262 - Data Structures
// Assignment: Evil Hangman game
// Date: 3/2/2017
// Purpose: To build a significant application from scratch
//			To practice choosing and applying various data structures
//			To build a game(that is no fun to play, but may be fun to 
//			watch others play)
//------------------------------------------------------------------------------

// Header files
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct WordFamily {
	int freq;
	set<string> family;
};

// Prompt user for an integer
int getNonNegInteger(string& prompt){
	cout << prompt;
	int x = 0;
	while (!(cin >> x)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	return x;
}

// Prints a vector on screen 
void printVector(vector<char> word){
	cout << '\n' << endl;
	for (size_t i = 0; i < word.size(); i++) {
		cout << word[i];
	}
	cout << '\n' << endl;
}

// Outputs the result after each turn including word, no. of guesses, letters used
void printWordFamilyOthers(vector<char> word, int noGuesses,
	set<char> lettersUsed, set<string>& masterList){
	printVector(word);
	cout << "Number of wrong guesses left: " << noGuesses << endl;
	cout << "Letters used: ";

	for (char f : lettersUsed) {
		cout << f << ", ";
	}
	cout << "\b\b " << endl;
	cout << endl;
}


// Update blank word with the guessed letter
int updateWord(string wordCode, string badGuess, char nextCh, vector<char>& word){
	if (wordCode == badGuess)
		return 0;

	int count = 0;
	for (int i = 0; i < wordCode.length(); i++) {
		if (wordCode[i] == '1') {
			word[i] = nextCh;
			count++;
		}
	}
	return count;
}

// Forms the map of word families with their frequencies
void formWordFamilies(char nextCh, set<string> masterList, map< string, WordFamily>& wordFamilies){
	// Loop over each word in the masterlist
	string tempWord;
	for (set<string>::iterator itr = masterList.begin(); itr != masterList.end(); ++itr) {
		tempWord = *itr;

		// Replace word with the position locator of nextCh    
		for (int i = 0; i < tempWord.length(); i++) {
			if (tempWord[i] == nextCh)
				tempWord[i] = '1';
			else tempWord[i] = '0';
		}

		// Add the word to some family in the map and increment family's frequency
		if (wordFamilies.find(tempWord) == wordFamilies.end()) {
			// Object of the struct WordFamily containing a family & its frequency
			WordFamily wordFamily;

			wordFamily.freq = 1;
			wordFamily.family.insert(*itr);
			wordFamilies.insert(pair<string, WordFamily>(tempWord, wordFamily));
		}
		else {
			wordFamilies[tempWord].freq++;
			wordFamilies[tempWord].family.insert(*itr);
		}
	}
}

// Comparator function to be used with max_element for set 
bool mapCompare(const pair<string, WordFamily >& lhs, const pair<string, WordFamily >& rhs){
	return lhs.second.freq < rhs.second.freq;
}

// Checks whether the letter entered by user was used already 
bool isLetterUsed(char nextCh, set<char> lettersUsed){
	if (lettersUsed.find(nextCh) == lettersUsed.end()) return 0;
	else return 1;
}

// Trims dictionary to keep only the specific words of a certain length 
void trimDictionary(size_t wordLen, set<string>& masterList, set<string>& english, string prompt){
	while (masterList.empty()) {
		for (string f : english) {
			if (f.size() == wordLen)
				masterList.insert(f);
		}
		if (masterList.empty()) {
			cout << "No word that long in the dictionary. Try Again!" << endl;
			wordLen = getNonNegInteger(prompt);
		}
	}
}

// Generates a word of all zeros to represent an incorrect gguess 
string badGuessString(int wordLen){
	string zeros;
	for (int i = 0; i < wordLen; i++) {
		zeros += '0';
	}
	return zeros;
}

// Prompt user for an alphabet
char getAlphabet(string prompt){
	char ch;
	cout << prompt;
	cin >> ch;
	return ch;
}

// Prompt user for a y/n answer
bool getChoice(string& prompt){
	char ch;
	while (true) {
		cout << prompt;
		cin >> ch;
		ch = toupper(ch);

		if (ch == 'Y')
			return 1;
		else if (ch == 'N')
			return 0;

		cout << "Incorrect Y/N answer. Try again!" << endl;
	}
}

int main() {
	ifstream infile;
	infile.open("dictionary.txt");

	if (!infile.is_open()) {
		cout << "Unable to load dictionary.txt" << endl;
		return 0;
	}

	set<string> english;
	string aWord;
	cout << "Hello! Welcome to hangman!" << endl;
	cout << "Loading dictionary words to memory! Please wait..\n" << endl;
	while (getline(infile, aWord))
		english.insert(aWord);

	bool reTry = 1; // Keep playing until stopped

	while (reTry) { 
		// Prompt for the no of guesses
		string prompt = "Enter the number of guesses desired (between 0 to 30):  ";
		int noGuesses = getNonNegInteger(prompt);

		if (!noGuesses) {
			prompt = "Nice try, but you have no more guesses! Would you like to play again (Y/N)? ";
			reTry = getChoice(prompt);
			if (reTry)
				continue;
			else
				break;
		}

		// Prompt user for the word length
		prompt = "Enter a word length: ";
		size_t wordLen = getNonNegInteger(prompt);
		cout << endl;

		string badGuess = badGuessString(wordLen); // string of all 0's indicating incorrect guess

		// Trim the Dictionary to Match the Word Length & reprompt if no word exists of the desired length
		set<string> masterList;
		trimDictionary(wordLen, masterList, english, prompt);

		vector<char> word(wordLen, '-'); // Initialize vector of chars containing dashes to be replaced with letters
		printVector(word); // Print Word
		set<char> lettersUsed; // Initialize vector of all letters used

		// Repeat until word length is met or the no. of guesses == 0
		while (wordLen > 0 && noGuesses > 0) {
			prompt = "Enter Your Next Guess: "; // Prompt for next Guess and update results
			char nextCh = getAlphabet(prompt);

			// Check if letter is not used already
			bool isBadCh = isLetterUsed(nextCh, lettersUsed);
			if (isBadCh) {
				cout << "Letter used already. Try again!" << endl;
				continue;
			}
			else
				lettersUsed.insert(nextCh);

			map< string, WordFamily> wordFamilies; // word families master map updated everytime user enters a guess
			formWordFamilies(nextCh, masterList, wordFamilies); // Form a Map of All Word Families

			// Check which Word Family has the highest frequency
			pair<string, WordFamily> maxWordFamily = *max_element(wordFamilies.begin(), wordFamilies.end(), mapCompare); 

			// Change the contents of the master list to the current highest freq. family
			masterList.clear();
			masterList = maxWordFamily.second.family;

			// Change the "word" vector 
			string wordCode = maxWordFamily.first;
			int lettersGuessed = updateWord(wordCode, badGuess, nextCh, word);

			// Update wordLen & noGuesses
			if (lettersGuessed == 0)
				noGuesses--;
			else
				wordLen -= lettersGuessed;

			printWordFamilyOthers(word, noGuesses, lettersUsed, masterList); // Print Word
		}

		// Results
		if (noGuesses == 0) {
			cout << "The word was: " << *masterList.begin() << "\n" << endl;
		}
		else
			cout << "Good job! You beat the computer..\n" << endl;

		// Ask user to play again
		prompt = "Would you like to play again (Y/N)? ";
		reTry = getChoice(prompt);
		cout << endl;
	}
	return 0;
}
#include <string>
#include <iostream>
#include "integer_list.h"
#include "utilities.h"
#include <sstream>
#include <fstream>
/**This file contains functions used in the main not contained in the IntegerList class*/

/**Prompts the user to enter a filename.Checks that filename is valid
@return filename
*/
std::string ValidateFilenameInput() {
	std::string filename;
	
	while (true) {
		std::cout << "Enter a .txt filename (included file integerList.txt) ";
		std::cin >> filename;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << std::endl;
		if (filename == "q") { exit(0); }
		if (filename.size() < 5) {
			std::cout << "Filename not long enough" << std::endl << std::endl;
			continue;
		}
		std::size_t findPeriod = filename.find(".");
		std::string fileExtension = filename.substr(findPeriod);
		if (fileExtension != ".txt") {
			std::cout << "Invalid file type provided" << std::endl << std::endl;
			continue;
		}
		else {
			return filename;
		}
	}

}
/** ensures that user provided input is an integer
@return validated integer
*/
int ValidateIntegerInput() {
	int validInput;
	std::string userInput;
	while (true) {
		std::cin >> userInput;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		if (userInput == "q") {exit(0); }
		try {
			validInput = stoi(userInput);
			break;
		}
		catch (...) {
			std::cout << "An invalid input was received. Enter a valid integer. ";
		}
	}
	return validInput;
}
/** Overloaded version of previous function.  Accepts a string ensures that user provided input is an integer
@param input string
@return validated integer
*/
int ValidateIntegerInput(std::string userInput) {
	int validInput;
	try {
		validInput = stoi(userInput);
	}
	catch (...) {
		std::cout << "An invalid input was received from the file. " << std::endl;
		return -1;
	}
	return validInput;
}

/* Simply prints the welcome message at startup*/
void PrintWelcomeMessage() {
	std::cout << "Hello," << std::endl << std::endl <<
		"This program reads input from a txt file." << std::endl << 
		"You can then modify the data using the Menu Options." << std::endl <<
		"You may type 'q' at any time to exit the program" << std::endl << std::endl;
}
/** This function builds the 'integer list arrar from a filename
@param intList an IntegerList object passed by reference
@param filename a validated filename
*/
void BuildArray(IntegerList& intList, std::string filename) {
	std::ifstream inSS;
	std::string line;
	std::istringstream lineStream;
	std::string fileVal;
	int validVal;
	inSS.open(filename);
	if (!inSS) { throw std::runtime_error("Unable to open the file."); }
	for (int i = 0; !inSS.eof(); i++) {
		getline(inSS, line);
		lineStream = std::istringstream(line);
		while (!lineStream.eof()) {
			lineStream >> fileVal;
			validVal = ValidateIntegerInput(fileVal);
			if (validVal != -1) {
				OldValNewVal x = intList.overwriteIntegerAtIndex(intList.incrIntListSize(), validVal);
			}
			else {
				continue;
			}
		}
		lineStream.clear();
	}
	inSS.close();
}
/**Prints menu to screen.  Prompts user for a selecton.  Loops until valid selection is made
@return Menu selection
*/
char PrintMenuGetSelection() {
	char userSelection;
	std::string userInput;
	while (true) {
		std::cout << "          Main Menu" << std::endl << std::endl <<
			"Search for a value in the array - type 's'" << std::endl <<
			"Delete a value from the array   - type 'd'" << std::endl <<
			"Overwrite a value in the array  - type 'o'" << std::endl <<
			"Append a value to the array     - type 'a;" << std::endl <<
			"Retrieve a value from the array - type 'r'" << std::endl <<
			"Output the array to the screen  - type 'p'" << std::endl <<
			"Enter a new file to be read     - type 'f'" << std::endl <<
			"Write array to a file           - type 'w'" << std::endl <<
			"Quit                            - type 'q'" << std::endl <<
			std::endl <<
			"What would you like to do?: ";
		std::cin >> userInput;

		if (userInput.size() > 1) {
			std::cout << "Invalid selection. Try again." << std::endl; 
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}
		else { userSelection = userInput[0]; }
		std::cout << std::endl;
		if (userSelection == 'q') { exit(0); }
		if ((userSelection != 's') && (userSelection != 'd') && (userSelection != 'o') && (userSelection != 'a')
			&& (userSelection != 'r') && (userSelection != 'p') && (userSelection != 'f') && (userSelection != 'w')) {
			std::cout << "Invalid selection. Try again" << std::endl;
		}
		else {
			break;
		}
	}
	return userSelection;
}
/** Main fuctionality of program. Calls appropriate functions based on user Menu seleciton
@param integerList, the integerList object built by BuildArray
@param MenuSelection the menuchoice provided by PrintMenuGetSelection
*/
bool MenuOperations(IntegerList& integerList, char MenuSelection) {
	int index, value;
	OldValNewVal x;
	try {
		switch (MenuSelection) {
		case 's':
			std::cout << "Enter the value you want to search for ";
			value = ValidateIntegerInput();
			std::cout << std::endl;
			index = integerList.searchIntListForInt(value);
			std::cout << value << " found at index " << index << std::endl << std::endl;
			break;
		case 'd':
			std::cout << "Enter the index of the value you want to delete. ";
			index = ValidateIntegerInput();
			std::cout << std::endl;
			x = integerList.deleteIntegerFromIntList(index);
			std::cout << "Value at index " << index << " was " << x.OldVal << " has been deleted. Now the value at that index is " << x.NewVal << std::endl << std::endl;
			break;
		case 'o':
			std::cout << "Enter the index of the value you want to overwrite. ";
			index = ValidateIntegerInput();
			std::cout << std::endl;

			std::cout << "Enter the new value ";
			value = ValidateIntegerInput();
			std::cout << std::endl;
			x = integerList.overwriteIntegerAtIndex(index, value);
			std::cout << x.OldVal << " at index " << index << " replaced by " << x.NewVal << std::endl << std::endl;
			break;
		case 'a':
			std::cout << "Enter the new value ";
			value = ValidateIntegerInput();
			std::cout << std::endl;
			integerList.appendIntegerToIntList(value);
			std::cout << value << " was added to the end of the array. " << std::endl << std::endl;
			break;
		case 'r':
			std::cout << "Enter the index of the value you want to retrieve. ";
			index = ValidateIntegerInput();
			std::cout << std::endl;
			value = integerList.getIntegerAtIndex(index);
			std::cout << "The value at index " << index << " is " << value;
			break;
		case 'p':
			integerList.printIntList();
			break;
		case 'w':
			integerList.writeToFile();
			std::cout << "File successfully written. " << std::endl << std::endl;
			break;

		case 'f':
			integerList.setIntListSizeToZero();
			std::cout << std::endl << std::endl;
			return false;
		default:
			std::cout << "An invalid input was passed to the menu operations function." << std::endl;
		}
	}
	catch(std::runtime_error& e) { std::cout << e.what() << std::endl << std::endl; }
	catch (...) { std::cout << "an unexpected error occurred." << std::endl << std::endl; }
	return true;
}
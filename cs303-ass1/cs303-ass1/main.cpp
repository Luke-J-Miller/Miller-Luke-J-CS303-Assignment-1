#include "integer_list.h"
#include "utilities.h"
#include <string>
#include <iostream>
#include <stdexcept>


int main() {

	PrintWelcomeMessage();
	
	while (true) {
		IntegerList myIntList;
		std::string filename;
		while (true) {
			filename = ValidateFilenameInput();
			try {
				BuildArray(myIntList, filename);
				break;
			} catch (std::runtime_error& excpt) { std::cout << excpt.what() << std::endl; }
		}
		bool continueWithSameFile = true;
		while (continueWithSameFile) {
			char userSelection = PrintMenuGetSelection();
			continueWithSameFile = MenuOperations(myIntList, userSelection);
		}
	}
	return 0;
	}
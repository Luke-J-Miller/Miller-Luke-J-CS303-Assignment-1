#pragma once
#include <string>
#include "integer_list.h"
/**Header file for utitlites.cpp, source file providing functions to main not contained in the integer_list class*/
std::string ValidateFilenameInput();
int ValidateIntegerInput();
int ValidateIntegerInput(std::string userInput);
void PrintWelcomeMessage();
char PrintMenuGetSelection();
bool MenuOperations(IntegerList& integerList, char menuSelection);
void BuildArray(IntegerList& intList, std::string filename);

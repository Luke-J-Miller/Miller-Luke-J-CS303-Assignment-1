#include<string>
#include<iostream>
#include "integer_list.h"
#include "utilities.h"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

/** Searches the array for the value.  If array is empty, or value is not found, it throws an error caught in the menuOpeations function in utilities.cpp
@return index of the found integer
*/
const int IntegerList::searchIntListForInt(int value) {
	int foundAt = -1;
	if (intListSize == 0) { throw std::runtime_error("The array is empty"); }
	for (int i = 0; i < intListSize; i++) {
		if (intList[i] == value) {foundAt = i;}
	}
	if (foundAt == -1) { throw std::runtime_error("The value is not in the array."); }
	return foundAt;
}
/** Replaces the integer at the provided index with provided value.  
If the index is not in the array, it throws an error caught in the menuOpeations function in utilities.cpp
@return OldValNewVal containing the new value and the value replace
*/
OldValNewVal IntegerList::overwriteIntegerAtIndex(int index, int value) {
	if (intListSize < index) { throw std::runtime_error("The index is larger than the array."); }
	int oldVal = intList[index];
	intList[index] = value;
	int newVal = intList[index];
	OldValNewVal returnTuple = OldValNewVal(oldVal, newVal);
	return returnTuple;
}
/** Adds the provided value at the end of the array. If the size of the array is reached, it creates a new larger array.
*/
void IntegerList::appendIntegerToIntList(int value) {

	if (!(intListSize < intListCapacity)) {
		*this = doubleCapacityOfIntegerList(*this);
	}
	intList[intListSize] = value;
	intListSize += 1;
}
/** Deletes the integer at the provided index.
If the index is not in the array, it throws an error caught in the menuOpeations function in utilities.cpp
@return OldValNewVal containing the new value and the value replace.
*/
OldValNewVal IntegerList::deleteIntegerFromIntList(int index) {
	int oldval = intList[index];

	if (!(intListSize > index)) { throw std::runtime_error("The index is larger than the array."); }
	for (int i = index; i < intListSize - 1; i++) {
		intList[i] = intList[i + 1];
	}
	int newval = intList[index];
	OldValNewVal x(oldval, newval);
	intListSize -= 1;
	return x;
}
/** returns the integer at the provided index.
If the index is not in the array, it throws an error caught in the menuOpeations function in utilities.cpp
@param index desired index location
@return integer at index.
*/
int IntegerList::getIntegerAtIndex(int index) {

	if (intListSize < index) { throw std::runtime_error("The index is larger than the array."); }
	return intList[index];
}

/** returns the size of the array. Used by other fuctions.
@return size of the array.
*/
const int IntegerList::getIntListSize() {
		return intListSize;
}
/** returns the size of the array. Then, it increments the array by one. Used by other fuctions.
@return size of the array.
*/
int IntegerList::incrIntListSize() {
	int returnValue = intListSize;
	intListSize++;
	return returnValue;
}
/** resets the size of the array to zero. Used by other fuctions.
*/
void IntegerList::setIntListSizeToZero() { intListSize = 0; }
/** returns the capacity of the array. Used by other fuctions.
@return capacity of the array.
*/
const int IntegerList::getIntListCapacity() {

		return intListCapacity;
}
/**Prints the array to the screen.
If the array size is zero, it throws an error caught in the menuOpeations function in utilities.cpp
*/
const void IntegerList::printIntList() {

	if (intListSize == 0) { throw std::runtime_error("The array is empty."); }

	for (int i = 0; i < intListSize; i ++) {
		if (i % 10 == 0) { std::cout << std::endl; }
		std::cout << std::setw(4) << intList[i] << " ";
	}
	std::cout << std::endl << std::endl;
}
/**Outputs the array to a file.
If the array size is zero, or it is unable to open the file,  it throws an error caught in the menuOpeations function in utilities.cpp
*/
const void IntegerList::writeToFile() {

	if (intListSize == 0) { throw std::runtime_error("The array is empty."); }
	std::ofstream outFS;
	std::string outFile = ValidateFilenameInput();
	outFS.open(outFile);
	if (!outFS) { throw(std::runtime_error("Unable to open file.")); }
	for (int i = 0; i < intListSize; i++) {
		if (i % 10 == 0) { outFS << "\n"; }
		outFS << std::setw(4) << intList[i] << " ";
	}
	outFS << "\n\n";
	outFS.close();
}
/**default constructor*/
IntegerList::IntegerList() {
	intListSize = 0;
	intListCapacity = 200;
	intList = new int[intListCapacity];
}
/**Overloaded constructor using array capacity to create the instance*/
IntegerList::IntegerList(int capacity) {
	intListSize = 0;
	intListCapacity = capacity;
	intList = {};
}

//The assignment operator overload copies the size and information of the array, but not the capacity
IntegerList& IntegerList::operator=(const IntegerList& objToCopy) {
	intList = objToCopy.intList;
	return *this;

}
//Creates a new IntegerList with double the capacity of the previous and copies array and size information
IntegerList doubleCapacityOfIntegerList(IntegerList objToCopy) {
	IntegerList biggerList(objToCopy.getIntListCapacity() * 2);
	biggerList = objToCopy;
	return biggerList;
}
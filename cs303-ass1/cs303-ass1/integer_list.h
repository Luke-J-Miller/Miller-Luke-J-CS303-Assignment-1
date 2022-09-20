#pragma once
#include <string>
/**class created to return two values from functions*/
class OldValNewVal {
public:
	int OldVal;
	int NewVal;
public:
	OldValNewVal() {
		OldVal = -1;
		NewVal = -1;
	}
	OldValNewVal(int oldVal, int newVal) {
		OldVal = oldVal;
		NewVal = newVal;
	}
};
/**Class used to pass arrays to functions that edit, resize and delete items*/
class IntegerList {
private:
	int intListSize;
	int intListCapacity;
	int* intList = new int[intListCapacity];
public:
	const int searchIntListForInt(int value);
	OldValNewVal overwriteIntegerAtIndex(int index, int value);
	void appendIntegerToIntList(int value);
	OldValNewVal deleteIntegerFromIntList(int index);
	int getIntegerAtIndex(int index);
	const int getIntListSize();
	int incrIntListSize();
	void setIntListSizeToZero();
	const int getIntListCapacity();
	const void printIntList();
	const void writeToFile();
	IntegerList();
	IntegerList(int capacity);
	IntegerList& operator=(const IntegerList& objToCopy);

};
IntegerList doubleCapacityOfIntegerList(IntegerList objToCopy);

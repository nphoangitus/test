#include "../header/struct.h"
#include "../header/prototype.h"
#include <iostream>
#include <fstream>

template <class T>
Array<T>* initArray(const int size) {
    Array<T>* arr = new (std::nothrow) Array<T>;
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return arr;
    }

    arr->data = new (std::nothrow) T[size];
    if (!arr->data) {
        std::cout << "Allocation failed!\n";
        
        delete arr;
        arr = nullptr;

        return arr;
    }

    arr->size = size;

    return arr;
}

template <class T>
void freeArray(Array<T>*& arr) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    delete[] arr->data;
    arr->data = nullptr;
    delete arr;
    arr = nullptr;
}

template <class T>
void resizeArray(Array<T>*& arr, int newSize) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    T* newData = new (std::nothrow) T[newSize];
    if (!newData) {
        std::cout << "Allocation failed!\n";

        return;
    }

    for (int i = 0; i < ((newSize < arr->size) ? newSize : arr->size); ++i) {
        newData[i] = arr->data[i];
    }

    delete arr->data;
    arr->data = newData;
    arr->size = newSize;
}

template <class T>
void readInputFile(Array<T>*& arr) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    std::ifstream inFile("../resource/input.txt", std::ios::in);
    if (!inFile.is_open()) {
        std::cout << "Can't open file!\n";

        return;
    }

    int index = 0;

    while (!inFile.eof()) {
        inFile >> arr->data[index++];
    }

    resizeArray(arr, index);
    arr->size = index;

    inFile.close();
}

template <class T>
void printArray(const Array<T>* arr) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    for (int i = 0; i < arr->size; ++i) {
        std::cout << arr->data[i] << " ";
    }

    std::cout << "\n";
}

template <class T>
void deletePos(Array<T>*& arr, int pos) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    for (int i = pos; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i + 1];
    }

    resizeArray(arr, arr->size - 1);
}

template <class T>
void insertPosVal(Array<T>*& arr, int pos, T val) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    resizeArray(arr, arr->size + 1);

    for (int i = arr->size - 1; i >= pos; --i) {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[pos] = val;
}

template <class T>
void pushBack(Array< Stack<T> >*& stack, Stack<T>& data) {
    if (!stack) {
        std::cout << "Alloction failed!\n";

        return;
    }

    int nItem = stack->size;
    resizeArray(stack, nItem + 1);
    stack->data[nItem].history = data.history;
    stack->data[nItem].pos = data.pos;
    stack->data[nItem].val = data.val;
}

template <class T>
void popBack_Undo(Array<T>*& arr, Array< Stack<T> >*& firstStack, Array< Stack<T> >*& secondStack) {
    if (!arr || !firstStack || !secondStack) {
        std::cout << "Alloction failed!\n";

        return;
    }
    
    int nItem = firstStack->size;
    if (nItem == 0) {
        return;
    }

    if (firstStack->data[nItem - 1].history == deleteAction) {
        insertPosVal(arr, firstStack->data[nItem - 1].pos, firstStack->data[nItem - 1].val);
        pushBack(secondStack, firstStack->data[nItem - 1]);
        resizeArray(firstStack, nItem - 1);
    } else {
        deletePos(arr, firstStack->data[nItem - 1].pos);
        pushBack(secondStack, firstStack->data[nItem - 1]);
        resizeArray(firstStack, nItem - 1);
    }
}

template <class T>
void popBack_Redo(Array<T>*& arr, Array< Stack<T> >*& firstStack, Array< Stack<T> >*& secondStack) {
    if (!arr || !firstStack || !secondStack) {
        std::cout << "Alloction failed!\n";

        return;
    }
    
    int nItem = firstStack->size;
    if (nItem == 0) {
        return;
    }

    if (firstStack->data[nItem - 1].history == insertAction) {
        insertPosVal(arr, firstStack->data[nItem - 1].pos, firstStack->data[nItem - 1].val);
        pushBack(secondStack, firstStack->data[nItem - 1]);
        resizeArray(firstStack, nItem - 1);
    } else {
        deletePos(arr, firstStack->data[nItem - 1].pos);
        pushBack(secondStack, firstStack->data[nItem - 1]);
        resizeArray(firstStack, nItem - 1);
    }
}

template <class T>
void saveOutputFile(Array<T>* arr) {
    if (!arr) {
        std::cout << "Allocation failed!\n";

        return;
    }

    std::ofstream outFile("../resource/output.txt", std::ios::out);
    if (!outFile.is_open()) {
        std::cout << "Can't open file!\n";

        return;
    }

    for (int i = 0; i < arr->size; ++i) {
        outFile << arr->data[i];
        outFile << " ";
    }

    outFile.close();
}

void inputChecking(int& num) {
	bool check;

	do {
		check = false;
		std::cin >> num;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cout << "\t Invalid input! Input again: ";
			check = true;
		}
		std::cin.ignore();

	} while (check);
}

void inputPosition(int& pos, const int& sizeOfArray) {
	bool check = false;

	do 	{
		if (check) {
			std::cout << "\t Invalid position! Input again\n";
		}
		std::cout << "\t Please input position you want to delete: ";
		inputChecking(pos);
		check = true;
	} while (pos < 0 || pos >= sizeOfArray);
}

void inputPositionAndValue(int& pos, int& val, const int& sizeOfArray) {
	bool check = false;

	do {
		if (check) {
			std::cout << "\t Invalid position! Input again\n";
		}
		std::cout << "\t Please input position you want to insert: ";
		inputChecking(pos);
		std::cout << "\t Please input value you want to insert: ";
		inputChecking(val);
		check = true;
	} while (pos < 1 || pos > sizeOfArray);
}

void menu() {
    std::cout << "\n\t _______________________MENU_______________________\n"
        << "\t|\t1. Delete element at position              |\n"
        << "\t|\t2. Insert element at position with value   |\n"
        << "\t|\t3. Undo last operation                     |\n"
        << "\t|\t4. Redo last undone operation              |\n"
        << "\t|\t5. Save array to file                      |\n"
        << "\t|\t6. Reset workspace                         |\n"
        << "\t|\t7. Quit                                    |\n"
        << "\t|__________________________________________________|\n";
    std::cout << "\t Please input: ";
}

template Array<int>* initArray(const int);
template Array< Stack<int> >* initArray(const int);
template void freeArray(Array<int>*&);
template void freeArray(Array< Stack<int> >*&);
template void resizeArray(Array<int>*&, int);
template void readInputFile(Array<int>*&);
template void printArray(const Array<int>*);
template void deletePos(Array<int>*&, int);
template void insertPosVal(Array<int>*&, int, int);
template void pushBack(Array< Stack<int> >*&, Stack<int>&);
template void popBack_Undo(Array<int>*&, Array< Stack<int> >*&, Array< Stack<int> >*&);
template void popBack_Redo(Array<int>*&, Array< Stack<int> >*&, Array< Stack<int> >*&);
template void saveOutputFile(Array<int>*);

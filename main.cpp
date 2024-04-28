#include "../header/struct.h"
#include "../header/prototype.h"
#include "../header/const.h"
#include <iostream>
#include <fstream>

int main() {
    bool reset = false;
    do {
        Array<int>* arr = initArray<int>(MAX_SIZE);
        Array< Stack<int> >* undoStack = initArray < Stack<int> >(0);
        Array< Stack<int> >* redoStack = initArray < Stack<int> >(0);
        int pos = 0, val = 0, choice = 0, nItem = 0;
        bool isRunning = true;
        
        readInputFile(arr);
        
        while (isRunning) {
            system("clear");
            printArray(arr);
            menu();
            std::cin >> choice;

            switch (choice) {
            case 1: {
                inputPosition(pos, arr->size);

                Stack<int> data;
                data.history = deleteAction;
                data.pos = pos;
                data.val = arr->data[pos];
                pushBack<int>(undoStack, data);
                
                deletePos(arr, pos);
                system("clear");
                break;
            }

            case 2: {
                inputPositionAndValue(pos, val, arr->size);

                Stack<int> data;
                data.history = insertAction;
                data.pos = pos;
                data.pos = val;
                pushBack<int>(undoStack, data);

                insertPosVal(arr, pos, val);
                system("clear");
                break;
            }

            case 3: {
                popBack_Undo(arr, undoStack, redoStack);
                system("clear");
                break;
            }

            case 4: {
                popBack_Redo(arr, redoStack, undoStack);
                system("clear");
                break;
            }

            case 5: {
                saveOutputFile(arr);
                system("clear");
                break;
            }

            case 6: {
                reset = true;
                isRunning = false;
                system("clear");
                break;
            }

            case 7: {
                isRunning = false;
                break;
            }
            
            default:
                std::cout << "Invalid number!\n";
                break;
            }
        }

        freeArray(arr);
        freeArray(undoStack);
        freeArray(redoStack);

    } while (reset);
    
    return 0;
}
#include "Column.h"

// Task 1
Column::Column()
: totalRows(0), rowHead(nullptr), prev(nullptr), next(nullptr){}

// Task 2
Column::Column(Column *prev)
{
    totalRows = 0;
    rowHead = nullptr;
    this->prev = prev;
    this->next = nullptr;
}

// Task 3
Column::Column(const Column &c)
:totalRows(c.totalRows), prev(nullptr), next(nullptr)
{
    if(c.rowHead == nullptr){
        rowHead = c.rowHead;
        return;
    }
    else{
        rowHead = new Cell{c.rowHead->value, nullptr, nullptr};
        Cell* current = c.rowHead;
        Cell* current1 = rowHead;
        while(current->next != nullptr){
            current = current -> next;
            Cell* newCell = new Cell{current -> value, current1, nullptr};
            current1 -> next = newCell;
            current1 = current1 -> next;
        }
    }
}

// Task 4
Column::~Column() {
    Cell* current = rowHead;
    while(current != nullptr){
        Cell* next = current->next;
        delete current;
        current = next;
    }
}

// Task 5
Cell *Column::findCell(int rowNum)
{    
    Cell* current = rowHead;
    for(int i = 0; i < rowNum; i++){
        if(current == nullptr){
            return nullptr;
        }
        current = current ->next;
    }
    if(current == nullptr){
        return nullptr;
    }
    else{
        return current; 
    }
}

// Task 6
void Column::modifyCell(int rowNum, const string &value) {
    if (totalRows > rowNum) {
        Cell* current = rowHead;
        for(int i = 0; i<rowNum; i++){
            current = current -> next;
        }
        current->value = value;
    } 
    else {
        if(rowHead == nullptr){
            Cell* newCell = new Cell;
            newCell->value = "";
            newCell -> next = nullptr;
            newCell -> prev = nullptr;
            rowHead = newCell;
        }
        Cell* current = rowHead;
        
        int i = 0;
        while(current->next != nullptr){
            i++;
            current = current -> next;
        }
        
        while(i < rowNum){
            i++;
            Cell* newone = new Cell;
            newone -> value = "";
            newone -> prev = current;
            newone -> next = nullptr;
            current -> next = newone;
            current = newone;
        }

        totalRows = rowNum + 1;
        current -> value = value;
    }
}

// Task 7
void Column::clearCell(int rowNum)
{
    if(rowNum >= totalRows){
        return;
    }
    else if(rowNum < totalRows - 1){
        Cell* current = findCell(rowNum);
        current -> value = "";
    }
    else{
        if(rowNum == totalRows - 1){
            Cell* current = findCell(rowNum);
            if(rowNum == 0){
                rowHead = nullptr;
                delete current;
                totalRows--;
                return;
            }

            Cell* previous = current -> prev;
            previous -> next = nullptr;
            delete current;
            totalRows--;

            while(previous -> value == ""){
                if(totalRows == 1){
                    rowHead = nullptr;
                    delete previous;
                    totalRows--;
                    return;
                }
                else{
                    Cell* before = previous -> prev;
                    before -> next = nullptr;
                    delete previous;
                    previous = before;
                    totalRows--;
                }
            }
        }
    }
}

// Task 8
void Column::clearAllCells()
{
    Cell* current = rowHead;
    while (current != nullptr) {
        Cell* next = current->next;
        delete current;
        current = next;
    }

    totalRows = 0;
    rowHead = nullptr;
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Column::printColumn() const
{
    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');



    cout << "totalRows: " << totalRows << endl;

    // table header
    cout << doubleline + doubleline << endl;
    cout << " " << std::setw(10) << "" << " ";
    cout << "|" << std::setw(10)  << "column " << "|" <<endl;   
    cout << doubleline + doubleline << endl;

    // table body (row by row)
    Cell* current = rowHead;
    for (int i =0 ; i < totalRows; ++i){
        cout << " " << std::setw(10) << "row " + to_string(i) + " " << " " ;
        cout << "|" << std::setw(10) << current->value << "|" << endl;
        current = current->next;
        cout << doubleline + line << endl;
    }

    cout << endl;

}

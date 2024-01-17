 #include "Table.h"

// Task 9
Table::Table():totalColumns(0), columnHead(nullptr){}

// Task 10
Table::~Table()
{
    Column* current = columnHead;
    while(current != nullptr){
        Column* next = current->next;
        delete current;
        current = next;
    }
}

// Task 11
Column* Table::findColumn(int colNum) const
{
    Column* current = columnHead;
    for(int i = 0; i<colNum; i++){
        if(current == nullptr){
            return nullptr;
        }
        current = current -> next;
    }
    if(current == nullptr){
        return nullptr;
    }
    else{
        return current;
    }
}

// Task 12
void Table::copyInsertColumn(int fromColNum, int toColNum)
{
    if(fromColNum >= totalColumns){
        Column* current = findColumn(toColNum);
        if(current == nullptr && toColNum >= totalColumns){
            return;
        }
        Column* newColumn = new Column();
        if(toColNum == 0){
            columnHead = newColumn;
            current->prev = newColumn;
            newColumn->next = current;
            totalColumns++;
            return;
        }
        Column* previous = current -> prev;
        newColumn -> prev = previous;
        previous -> next = newColumn;
        newColumn -> next = current;
        current -> prev = newColumn;
        totalColumns++;
    }
    else if(findColumn(fromColNum)->getRowHead() == nullptr && toColNum >= totalColumns){
        return;
    }
    else if(toColNum < totalColumns){
        Column* later = findColumn(toColNum);
        Column* now = findColumn(fromColNum);
        Column* Copy = new Column(*now);
        if(toColNum == 0){
            Column* before = later -> prev;
            later->prev = Copy;
            Copy->next = later;
            Copy->prev = before;
            columnHead = Copy;
            totalColumns+=1;
            return;
        }
        
        Column* before = later -> prev;
        before->next = Copy;
        later->prev = Copy;
        Copy->next = later;
        Copy->prev = before;
        totalColumns+=1;
    }
    else if(toColNum >= totalColumns){
        Column* current = columnHead;

        int i = 0;

        while(current->next != nullptr){
            current = current -> next;
            i++;
        }

        for(;i < toColNum - 1; i++){
            Column* newColumn = new Column;
            current -> next = newColumn;
            newColumn -> prev = current;
            current = newColumn;
            totalColumns++;
        }

        Column* now = findColumn(fromColNum);
        Column* Copy = new Column(*now);
        current -> next = Copy;
        Copy -> prev = current;
        totalColumns++;
    }
}

// Task 13
void Table::deleteColumn(int colNum)
{
    if(colNum >= totalColumns){
        return;
    }
    else if(colNum < totalColumns - 1){
        if(colNum == 0){
            Column* current = findColumn(colNum);
            Column* after = current -> next;
            after -> prev = nullptr;
            columnHead = after;
            delete current;
            totalColumns--;
        }
        else{
            Column* current = findColumn(colNum);
            current -> clearAllCells();
            Column* before = current -> prev;
            before -> next = current -> next;
            Column* after = current -> next;
            before -> next = after;

            delete current;
            totalColumns--;
        }
    }
    else{
        if(colNum == totalColumns - 1){
            if(colNum == 0){
                Column* current = findColumn(colNum);
                columnHead = nullptr;
                delete current;
                totalColumns--;
            }
            else{
                Column* current = findColumn(colNum);
                Column* before = current -> prev;
                before -> next = nullptr;
                delete current;
                totalColumns--;

                while((before -> getRowHead()) == nullptr){
                    if(before -> prev == nullptr){
                        totalColumns--;
                        columnHead = nullptr;
                        delete before;
                        break;
                    }
                    Column* past = before -> prev;
                    past -> next = nullptr;
                    delete before;
                    before = past;
                    totalColumns--;
                }
            }
        }
    }
}

// Task 14
Cell *Table::findCell(int colNum, int rowNum) const
{   
    Column* current = columnHead; 
    for(int i = 0; i<colNum; i++){
        if(current == nullptr){
            return nullptr;
        }
        current = current -> next;
    }
    if(current == nullptr){
        return nullptr;
    }

    Cell* lost = current -> findCell(rowNum);
    return lost;
}

// Task 15
void Table::modifyCell(int colNum, int rowNum, const string &value) {
    if(totalColumns <= colNum){
        if(columnHead == nullptr){
            columnHead = new Column;
        }

        int i = 0;
        Column* current = columnHead;
        while(current->next != nullptr){
            current = current -> next;
            i++;
        }

        while(i < colNum){
            i++;
            Column* newColumn = new Column;
            current -> next = newColumn;
            newColumn -> prev = current;
            newColumn -> next = nullptr;
            current = current -> next;
        }

        current -> modifyCell(rowNum, value);
        totalColumns = colNum + 1;
    }

    else{
        Column* current = columnHead;
        for(int i = 0; i < colNum; i++){
            current = current -> next;
        }
        current->modifyCell(rowNum, value);
    }
}

// Task 16
void Table::clearCell(int colNum, int rowNum)
{
    Column* current = findColumn(colNum);
    if(current == nullptr){
        return;
    }
    
    else if(colNum == totalColumns - 1){
        current -> clearCell(rowNum);

        while((current -> getRowHead()) == nullptr){
            Column* previous = current -> prev;
            if(previous == nullptr){
                columnHead = nullptr;
                delete current;
                totalColumns--;
                return;
            }
            else{
                previous -> next = nullptr;
                delete current;
            }
            totalColumns--;
            current = previous;
        }
    }

    else{
        current -> clearCell(rowNum);
    }
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Table::printTable() const
{

    // find the max number of rows
    int maxRows = 0;
    Column *currCol = columnHead;
    while (currCol != nullptr)
    {
        if (currCol->getTotalRows() > maxRows)
        {
            maxRows = currCol->getTotalRows();
        }
        currCol = currCol->next;
    }

    cout << "totalColumns: " << totalColumns << "\t ";
    cout << "maxRows: " << maxRows << endl;


    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');
    string headerline((totalColumns+1)*12, '=');


    // print table table header
    cout << headerline << endl;
    cout << " " << std::setw(10) << "" << "|";
    for (int i = 0; i < totalColumns; ++i)
    {
        cout<< "|" << std::setw(10) << "column "+to_string(i)+ " " << "|";
    }
    cout << endl;
    cout << headerline << endl;
    

    // print table body (row by row)
    string hline;
    for (int i = 0; i < maxRows; ++i)
    {
        hline = doubleline;    
        cout<< " " << std::setw(10) << "row "+to_string(i) + "  "<< " ";


        currCol = columnHead;

        while (currCol != nullptr)
        {
            Cell *currCell = currCol->findCell(i);
            if (currCell == nullptr)
            {
                hline += space;
                cout << " "<< std::setw(10) <<"" << " ";
            }
            else
            {
                hline += line;
                cout << "|" << std::setw(10) << currCell->value << "|";
            }
            currCol = currCol->next;
        }
        cout << endl;

        cout << hline << endl;
    }

    cout << endl;
    return;

}

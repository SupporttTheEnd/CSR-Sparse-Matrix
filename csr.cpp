// Title: mytest.cpp
// Author: Andrew Tang
// Date: 9/27/2023
// Description: This is the implementation file for csr.h

#include "csr.h"
///////////////CSR Class Implementation///////////////

// Name - CSR()
// Desc - This is the default constructor. It creates an empty object. 
// An empty object does not hold any memory. The constructor must initialize all member variables.
// Preconditions - None
// Postconditions - Makes an empty object
CSR::CSR(){
    // set every member variable to its null value
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
    m_next = nullptr;
}

// Name - ~CSR()
// Desc - This is the destructor and it deallocates the memory.
// Preconditions - None
// Postconditions - Makes an empty object
CSR::~CSR(){
    // deallocates the three member arrays
    if (m_values != nullptr) {
        delete[] m_values;
    }
    if (m_col_index != nullptr) {
        delete[] m_col_index;  
    }
    if (m_row_index != nullptr) {
        delete[] m_row_index;
    }
}


// Name - CSR(const CSR & rhs)
// Desc - Copy constructor creates a deep copy of rhs.
// Preconditions - None
// Postconditions - Copies the rhs object
CSR::CSR(const CSR & rhs){
    // if the rhs is empty; this prevents memory from being allocated
    if (rhs.empty()){
        // initializes member variables to null 
        m_values = nullptr;
        m_col_index = nullptr;
        m_row_index = nullptr;
        m_nonzeros = 0;
        m_m = 0;
        m_n = 0;
        m_next = nullptr;
        return; 
    }

    // initializes member variables
    m_m = rhs.m_m;
    m_n = rhs.m_n;
    m_nonzeros = rhs.m_nonzeros;
    m_values = new int[m_nonzeros];
    m_col_index = new int[m_nonzeros];
    m_row_index = new int[m_m + 1];
    m_next = nullptr;

    // copies the arrays
    for (int i = 0; i < m_nonzeros; i++) {
        m_values[i] = rhs.m_values[i];
    }
    for (int i = 0; i < m_nonzeros; i++) {
        m_col_index[i] = rhs.m_col_index[i];
    }
    for (int i = 0; i <= m_m; i++) {
        m_row_index[i] = rhs.m_row_index[i];
    }
}

// Name - CSR::clear()
// Desc - This function deallocates all memory and converts the object to an empty CSR object.
// Preconditions - None
// Postconditions - Deallocates and makes object empty
void CSR::clear(){
     // deallocates the three member arrays
    if (m_values != nullptr) {
        delete[] m_values;
    }
    if (m_col_index != nullptr) {
        delete[] m_col_index;
    }
    if (m_row_index != nullptr) {
        delete[] m_row_index;
    }
    // set every member variable to its null value
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
    m_next = nullptr;
}

// Name - empty() const
// Desc - This function returns true if the object is empty, otherwise it returns false.
// Preconditions - None
// Postconditions - Returns if the object is empty with a bool
bool CSR::empty() const{
    // checks if all member varaibles are in their null state
    if (m_nonzeros == 0 && m_m == 0 && m_n == 0 && m_values == nullptr && m_col_index == nullptr && m_row_index == nullptr) {
        return true; 
    } else {
        return false; 
    }
}

// Name - compress(int m, int n, int array[], int arraySize)
// Desc - This function receives a sparse matrix in the form of an array and 
// creates a compressed version of the sparse matrix. All required memory allocation 
// happens in this function. Since the function can be re-called on the same object 
// the function needs to re-create new memory for the new sparse matrix that is passed 
// to the function. Moreover, the compress(...) function initializes all member variables.
// Preconditions - The row and column are valid and correspond to the array and arraySize
// Postconditions - Allocates memory and populates the member variables
void CSR::compress(int m, int n, int array[], int arraySize){
    // clear in case there was still data
    if (m_values != nullptr) {
        delete[] m_values;
    }
    if (m_col_index != nullptr) {
        delete[] m_col_index;
    }
    if (m_row_index != nullptr) {
        delete[] m_row_index;
    }
    // set every member variable to its null value
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;

    if (m <= 0 || n <= 0) {
        return; 
    }

    // initializes member variables
    m_m = m;
    m_n = n;
    m_nonzeros = 0;
    m_values = new int[arrayCounter(array, arraySize)];
    m_col_index = new int[arrayCounter(array, arraySize)];
    m_row_index = new int[m + 1];

    // variable that prevents indexing over the size of the given array 
    int count = 0; 

    // populates the arrays
    for (int i = 0; i < m; i++) {
        // sets the row index
        m_row_index[i] = m_nonzeros;
        for (int j = 0; j < n; j++) {
            // captures the values for each row
            if (count < arraySize){
                if (array[i * n + j] != 0) {
                    m_values[m_nonzeros] = array[i * n + j];
                    m_col_index[m_nonzeros] = j;
                    m_nonzeros++;
                }
            }
            count ++; 
        }
    }

    // adds the last row index
    m_row_index[m] = m_nonzeros;
}

// Name - getAt(int row, int col) const
// Desc -Returns the value of the matrix member at indices row and col. 
// If the requested indices do not exist (they are out of range) the function 
// throws a runtime_error exception. The exception is defined in <stdexcept> 
// library and is available from std namespace.
// Preconditions - row and col indexes are valid 
// Postconditions - Returns the value found at the said row and col
int CSR::getAt(int row, int  col) const{
    // checks if the range is valid
    if (row < 0 || col < 0 || col >= m_n || row >= m_m ) {
        throw runtime_error("Exception Error: Indices are not in valid range.");
    }
    
    // loop goes through however many populated items there are in each row
    for (int i = m_row_index[row]; i < m_row_index[row + 1]; i++) {
        if (m_col_index[i] == col) {
            return m_values[i];
        }
    }
    
    // if not found, just return 0 
    return 0;
} 

// Name - operator==(const CSR & rhs) const
// Desc - Overloaded equality operator returns true if all members of two matrices are equal.
// Preconditions - None
// Postconditions - Returns if the two objects are the same
bool CSR::operator==(const CSR & rhs) const{
    // check if these member variables are all equal
    if (m_m != rhs.m_m || m_n != rhs.m_n || m_nonzeros != rhs.m_nonzeros) {
        return false;
    }

    // edgecase if the matrices are empty
    if (empty() && rhs.empty()){
        return true; 
    }

    // go through these two arrays to check if all the items are the same
    for (int i = 0; i < m_nonzeros; i++) {
        if (m_values[i] != rhs.m_values[i] || m_col_index[i] != rhs.m_col_index[i]) {
            return false;
        }
    }
    
    // check if the row array has the same values
    for (int i = 0; i <= m_m; i++) {
        if (m_row_index[i] != rhs.m_row_index[i]) {
            return false;
        }
    }

    return true;
}

// Name - sparseRatio()
// Desc - Returns the sparsity ratio for the CSR object. 
// It returns the ratio as percentage, e.g. if the ratio is 0.656, 
// the function returns 0.656 x 100 = 65 as integer. 
// If the CSR object is empty this function returns zero. 
// If all members of the matrix are zero the function returns 100.
// Preconditions - None
// Postconditions - return the sparcity ratio
int CSR::sparseRatio(){
    // find the percent of null entries in matrix 
    if (empty()){
        return 0; 
    }
    else{
        // cast into the double to do decimal division, subtract by one to get the complement and then turn it into a percentage, finally turn it into an int
        return int((1 - (double(m_nonzeros)/ (m_m * m_n))) * 100);
    }
}

// Name - dump()
// Desc - Prints out the contents of the array
// Preconditions - None
// Postconditions - None
void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

//////////////CSRList Class Implementation///////////////

// Name - CSRList()
// Desc - This is the default constructor. 
// It creates an empty object. An empty object does not hold any memory. 
// The constructor must initialize all member variables.
// Preconditions - None
// Postconditions - Sets member variables to null values
CSRList::CSRList(){
    // set member variables to null
    m_head = nullptr; 
    m_size = 0;
}

// Name - CSRList(const CSRList & rhs)
// Desc - Copy constructor creates a new CSRList object from rhs.
// Preconditions - None
// Postconditions - Copies the rhs object
CSRList::CSRList(const CSRList & rhs){
    m_head = nullptr; 
    m_size = 0;
    CSR* curr = rhs.m_head;
    while (curr != nullptr) {
        insertAtTail(*curr);
        curr = curr->m_next;
    }
}

// Name - ~CSRList()
// Desc - This is the destructor and it deallocates the memory.
// Preconditions - None
// Postconditions - Deallocates the memory
CSRList::~CSRList(){
    // go through the linked list and delete everything
    while (m_head != nullptr) {
        CSR* curr = m_head;
        m_head = m_head->m_next;
        delete curr;
    }
}

// Name - empty()
// Desc - This function returns true if the list is empty, otherwise it returns false.
// Preconditions - None
// Postconditions - returns true if the list is empty and vice versa
bool CSRList::empty() const{
    if (m_head == nullptr && m_size == 0) {
        return true; 
    }
    return false; 
}

// Name - insertAtHead(const CSR & matrix)
// Desc - This function inserts the CSR object at the head of the CSRList object.
// Preconditions - None
// Postconditions - Inserts an object to the start of the list
void CSRList::insertAtHead(const CSR & matrix){
    CSR* newNode = new CSR(matrix);
    newNode->m_next = m_head;
    m_head = newNode;
    m_size++;
}

// Name - clear()
// Desc - This function resets the CSRList object to its initial, empty state.
// Preconditions - None
// Postconditions - Deallocates the memory and resets member variables. 
void CSRList::clear(){
    // go through the linked list and delete everything
    while (m_head != nullptr) {
        CSR* curr = m_head;
        m_head = m_head->m_next;
        delete curr;
    }
    m_size = 0;
}

// Name - getAt(int CSRIndex, int row, int col)
// Desc - This function returns the value of a matrix member with 
// row and col indices, from the matrix at the position CSRIndex 
// in the CSRList object. If the requested indices do not exist 
// (they are out of range in the matrix or the matrix does not exist in the list) 
// the function throws a runtime_error exception. The exception is 
// defined in <stdexcept> library and is available from std namespace.
// Preconditions - None
// Postconditions - Copies the rhs object
int CSRList::getAt(int CSRIndex, int row, int col) const{
    // check if the index matches with the size of the linked list
    if (CSRIndex < 0 || CSRIndex >= m_size) {
        throw runtime_error("Exception Error: Object is not in the list!");
    }

    // go to the correct matrix
    CSR* curr = m_head;
    for (int i = 0; i < CSRIndex; i++) {
        curr = curr->m_next;
    }

    return curr->getAt(row, col);
}

// Name - operator==(const CSRList & rhs)
// Desc - The overloaded equality operator returns true if both lists have 
// the same matrices and in the same order, otherwise returns false.
// Preconditions - None
// Postconditions - Returns a bool that signifies if the two linked lists are equal
bool CSRList::operator==(const CSRList & rhs) const{
    // check that the size of both linked lists match
    if (m_size != rhs.m_size){
        return false; 
    }

    CSR* curr = m_head; 
    CSR* currRHS = rhs.m_head; 
    
    // goes through the linked list and matches each matrix
    while (curr != nullptr){
        if (!(*curr == *currRHS)) {
            return false;
        }
        curr = curr->m_next;
        currRHS = currRHS->m_next;
    }

    return true; 
}

// Name - operator=(const CSRList & rhs)
// Desc - The overloaded equality operator returns true if both lists have the 
// same matrices and in the same order, otherwise returns false.
// Preconditions - None
// Postconditions - Copies the rhs object
const CSRList& CSRList::operator=(const CSRList & rhs){
    // check for self assignment
    if(this == &rhs) {
        return *this; 
    }
    
    // deallocate any existsing memory
    clear();

    // copy the rhs items
    CSR* curr = rhs.m_head;
    while (curr != nullptr){
        insertAtTail(*curr);
        curr = curr->m_next; 
    }
    return *this;
}

// Name - averageSparseRatio()
// Desc - This function returns the average sparse ratio for all 
// matrices stored in the CSRList object. It returns the ratio as 
// percentage, e.g. if the ratio is 0.656, the function returns 
// 0.656 x 100 = 65 as integer.
// Preconditions - None
// Postconditions -  Returns the average sparse ratio
int CSRList::averageSparseRatio(){
    // if there is nothing in the linked list, return 0; doing this prevents a division by size of 0 
    if (empty()) {
        return 0;
    }

    double total = 0;

    //  totals each of the sparse ratio for the matrices
    CSR* curr = m_head;
    while (curr != nullptr) {
        total += curr->sparseRatio();
        curr = curr->m_next;
    }
    
    return int(total/m_size); 
}

// Name - dump()
// Desc - Prints out the contents of the list
// Preconditions - None
// Postconditions - None
void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}

// Name - insertAtTail(const CSR & matrix)
// Desc - insert a node at the tail of the list
// Preconditions - None
// Postconditions - Inserts a node at the end
void CSRList::insertAtTail(const CSR & matrix){
    // create a new node
    CSR* newNode = new CSR(matrix);
    newNode->m_next = nullptr;
    
    // if the list is empty, the new head is the newNode
    if (m_head == nullptr) {
        m_head = newNode; 
    }
    // otherwise, navigate to the last node and insert there
    else {
        CSR* curr = m_head;
        while (curr->m_next != nullptr) {
            curr = curr->m_next;
        }
        curr->m_next = newNode;
    }
    m_size++; 
}

// Name - arrayCounter(int array[], int arraySize)
// Desc - counts the amount of nonzeros as a way to determine how big to make the member arrays 
// Preconditions - None
// Postconditions - Returns said count 
int CSR::arrayCounter(int array[], int arraySize) {
    int count = 0; 
    for (int i = 0; i < arraySize; i++) {
        if (array[i] != 0) {
            count++; 
        }
    }
    return count; 
}

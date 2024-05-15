// Title: mytest.cpp
// Author: Andrew Tang
// Date: 9/27/2023
// Description: This is a tester file for csr.cpp

#include "csr.h"

class Tester{
    public:

    // ==================================================| Test Cases for the CSR Class |============================================================
    
    //Function: CSR::compress(int m, int n, int array[], int arraySize)
    //Case: Normal Case: it populates the member variables of the class with the expected values for an array of data.
    //Expected result: I push in an premade array, and I set the expected values of the member arrays. I then compare the member arrays
    // with these true member arrays. I also compare the member variables of int type. 
    bool compressNormal() {
        bool result = true;

        // create an object 
        CSR object;
        int test[] = {1, 2, 3, 0, 0, 0, 0, 4, 0, 5, 0, 0, 0, 0, 6, 7, 8, 9, 0, 0, 0, 0, 0, 10};
        
        // these are the arrays that we expect to come out 
        int trueValues[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int trueCol[] = {0, 1, 2, 1, 3, 2, 3, 4, 5, 5};
        int trueRow[] = {0, 3, 5, 9, 10};

        object.compress(4, 6, test, 24);

        // Make sure the member variables are as expected
        if (object.m_m != 4 || object.m_n != 6 || object.m_nonzeros != 10) {
            result = false;
        }
        
        // makes sure value and col arrays are as expected
        for (int i = 0; i < object.m_nonzeros; i++) {
            if (object.m_values[i] != trueValues[i] || object.m_col_index[i] != trueCol[i]) {
                result = false;
            }
        }

        // makes sure row arrays are as expected
        for (int i = 0; i <= object.m_m; i++) {
            if (object.m_row_index[i] != trueRow[i]) {
                result = false;
            }
        }

        cout << "TEST 1 RESULTS:" << endl; 

        return result;
    }

    //Function: CSR::compress(int m, int n, int array[], int arraySize)
    //Case: Error Case: the user provides data which is less than the asking matrix size.
    //Expected result: I push in an premade array which is less than the asking matrix size, and I set the 
    // expected values of the member arrays, which basically undefined parts as zero. I then compare the member arrays
    // with these true member arrays. I also compare the member variables of int type. 
    bool compressError() {
        bool result = true;

        CSR object;
        int test[] = {1, 2, 3, 0, 0}; 
        
        // these are the arrays that we expect to come out 
        int trueValues[] = {1, 2, 3};
        int trueCol[] = {0, 1, 2};
        int trueRow[] = {0, 3, 3, 3, 3, 3};

        object.compress(5, 5, test, 5); 

        // make sure the member variables are as expected
        if (object.m_m != 5 || object.m_n != 5 || object.m_nonzeros != 3) {
            result = false;
        }
        
        // makes sure value and col arrays are as expected
        for (int i = 0; i < object.m_nonzeros; i++) {
            if (object.m_values[i] != trueValues[i] || object.m_col_index[i] != trueCol[i]) {
                result = false;
            }
        }

        // makes sure row arrays are as expected
        for (int i = 0; i <= object.m_m; i++) {
            if (object.m_row_index[i] != trueRow[i]) {
                result = false;
            }
        }

        cout << "TEST 2 RESULTS:" << endl; 
        return result; 
    }

    //Function: CSR::compress(int m, int n, int array[], int arraySize)
    //Case: Error Case: Test whether the compress(...) function works correctly for an error case, e.g. the user asks for a 0 x 0 matrix but provides data.
    //Expected result: I push in an premade array as well as m and n of 0x0. This should result in an empty matrix, which I test for with the member variables. 
    bool compressError2() {
        bool result = true;

        CSR object;
        int test[] = {1, 2, 3, 0, 0}; 

        // makes size 0 by 0 but provides data
        object.compress(0, 0, test, 5); 
        
        // checks that the object is empty
        if (object.m_nonzeros != 0 || object.m_m != 0 || object.m_n != 0) { 
            result = false; 
        }
 
        if (object.m_values != nullptr || object.m_col_index != nullptr || object.m_row_index != nullptr) {
            result = false; 
        }
        
        cout << "TEST 3 RESULTS:" << endl; 
        return result; 
    }

    //Function: CSR::operator==(const CSR & rhs)
    //Case: Normal Case: Test whether the overloaded equality operator works correctly for a normal case.
    //Expected result: Makes two objects with the same data and makes sure that they are equal
    bool equalityNormal() {
        bool result = true;

        CSR object1;
        CSR object2;

        // makes two objects
        int test1[] = {1, 0, 3, 0, 4, 5};
        int test2[] = {1, 0, 3, 0, 4, 5};

        object1.compress(3, 2, test1, 6);
        object2.compress(3, 2, test2, 6);
        
        // checks if they are equal
        if (!(object1 == object2)) {
            result = false; 
        }
        
        cout << "TEST 4 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::operator==(const CSR & rhs)
    //Case: Edge Case: Test whether the overloaded equality operator works correctly for a edge case, i.e. both objects are empty.
    //Expected result: Makes two empty objects and makes sure that they are equal
    bool equalityEdge() {
        bool result = true;

        // make two empty objects
        CSR object1;
        CSR object2;
        
        // sees if they are equal
        if (!(object1 == object2)) {
            result = false; 
        }
        
        cout << "TEST 5 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::getAt(int row, int  col)
    //Case: Error Case: Test whether the getAt(...) function throws an exception for an error case, i.e. the requested index numbers do not exist in the object."
    //Expected result: Calling GetAt with invalid parameters will throw an error
    bool getAtError() {
        bool result = true;

        try {
            // create a object
            int test[] = {1, 2, 3, 4, 5, 6};
            CSR object;
            object.compress(3, 2, test, 6);

            // get a invalid index
            object.getAt(3, 3); 

            result = false;
        } 
        catch (const exception& e) {
            // we expect an exception to be caught
            result = true;
            cout << "Exception thrown: " << e.what() << endl; 
        }

        cout << "TEST 6 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::CSR(const CSR & rhs)
    //Case: Edge Case: Test whether the copy constructor works properly in an edge case where the rhs is an empty object
    //Expected result: when the rhs is empty, the lhs will also become empty
    bool copyConstructorEdge() {
        bool result = true;
        CSR object1;
        CSR object2(object1);
        
        // we expect that object 2 is empty
        if (object2.m_nonzeros != 0 || object2.m_m != 0 || object2.m_n != 0) { 
            result = false; 
        }
 
        if (object2.m_values != nullptr || object2.m_col_index != nullptr || object2.m_row_index != nullptr) {
            result = false; 
        }

        cout << "TEST 7 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::CSR(const CSR & rhs)
    //Case: Normal Case: Test whether the copy constructor works properly in an normal case
    //Expected result: the rhs will be equal to the lhs
    bool copyConstructorNormal() {
        bool result = true;

        // create an object and populate it
        int test[] = {1, 2, 3, 4, 5, 6};
        CSR object1;
        object1.compress(3, 2, test, 6);

        // copy the object 
        CSR object2(object1);

        // see if the original and copied objects are the same
        if (!(object1 == object2)) {
            result = false;
        }

        cout << "TEST 8 RESULTS:" << endl;
        return result;
    }

    //Function: CSR::compress(int m, int n, int array[], int arraySize)
    //Case: Edge Case: Test whether the compress(...) function works correctly for an edge case, e.g. the input array is greater than (m x n)
    //Expected result: the function uses the array to initialize the matrix, and the rest of array data will be ignored.
    bool compressEdge() {
        bool result = true;

        CSR object;
        int test[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
        
        // these are the arrays that we expect to come out 
        int trueValues[] = {1, 2, 3, 4, 5, 6};
        int trueCol[] = {0, 1, 2, 0, 1, 2};
        int trueRow[] = {0, 3, 6};

        object.compress(2, 3, test, 12); 

        // make sure the member variables are as expected
        if (object.m_m != 2 || object.m_n != 3 || object.m_nonzeros != 6) {
            result = false;
        }
        
        // makes sure value and col arrays are as expected
        for (int i = 0; i < object.m_nonzeros; i++) {
            if (object.m_values[i] != trueValues[i] || object.m_col_index[i] != trueCol[i]) {
                result = false;
            }
        }

        // makes sure row arrays are as expected
        for (int i = 0; i <= object.m_m; i++) {
            if (object.m_row_index[i] != trueRow[i]) {
                result = false;
            }
        }

        cout << "TEST 9 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::compress(int m, int n, int array[], int arraySize)
    //Case: Edge Case: Test whether the compress(...) function works correctly for an edge case, e.g. matrix size is specified but there is no data
    //Expected result: that would be considered an empty object, even if user provides data in the array.
    bool compressEdge2() {
        bool result = true;

        CSR object;
        int test[] = {};
        
        // these are the arrays that we expect to come out 
        int trueValues[] = {};
        int trueCol[] = {};
        int trueRow[] = {0, 0, 0};

        object.compress(2, 3, test, 0); 

        // make sure the member variables are as expected
        if (object.m_m != 2 || object.m_n != 3 || object.m_nonzeros != 0) {
            result = false;
        }
        
        // makes sure value and col arrays are as expected (for this case we dont even expect this loop to run)
        for (int i = 0; i < object.m_nonzeros; i++) {
            if (object.m_values[i] != trueValues[i] || object.m_col_index[i] != trueCol[i]) {
                result = false;
            }
        }

        // makes sure row arrays are as expected
        for (int i = 0; i <= object.m_m; i++) {
            if (object.m_row_index[i] != trueRow[i]) {
                result = false;
            }
        }

        cout << "TEST 10 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::getAt(int row, int  col)
    //Case: Normal Case: Test whether the getAt(...) works correctly for a normal case, it returns the expected answer.
    //Expected result: The correct value at the index will have been gotten
    bool getAtNormal() {
        bool result = true;
        // create a object
        int test[] = {1, 2, 3, 4, 5, 6};
        CSR object;
        object.compress(3, 2, test, 6);

    
        if (object.getAt(2, 1) != 6){
            result = false;
        }

        cout << "TEST 11 RESULTS:" << endl;
        return result; 
    }

    //Function: CSR::sparseRatio()
    //Case: Edge Case: Test whether the sparseRatio(...) function works correctly in the edge case where it is called upon an empty object
    //Expected result: 0 should be returned
    bool sparseRatioEdge() {
        bool result = true;

        CSR object;

        // see if the sparseRatio matches the expected
        if (object.sparseRatio() != 0) {
            result = false;
        }

        cout << "TEST 12 RESULTS:" << endl;
        return result;
    }

    //Function: CSR::sparseRatio()
    //Case: Edge Case: Test whether the sparseRatio(...) function works correctly in the normal case
    //Expected result: The correct sparse ratio should be returned
    bool sparseRatioNormal() {
        bool result = true;

        // make a matrix
        int test[] = {1, 0, 0, 0, 0, 1};
        CSR object;
        object.compress(2, 3, test, 6);

        // see if the sparseRatio matches the expected
        if (object.sparseRatio() != 66) {
            result = false;
        }
        
        cout << "TEST 13 RESULTS:" << endl;
        return result;
    }

    // ==================================================| Test Cases for the CSRList Class |============================================================

    //Function: CSRList::operator=(const CSRList & rhs)
    //Case: Normal Case: Test whether the overloaded assignment operator works correctly for a normal case.
    //Expected result: rhs should be the same as lhs
    bool assignmentListNormal(){
        bool result = true;

        // make two objects
        CSR object1;
        CSR object2;

        int test1[] = {1, 0, 3, 0, 4, 5};
        int test2[] = {1, 2, 3, 4, 5, 6};

        object1.compress(3, 2, test1, 6); 
        object2.compress(3, 2, test2, 6); 
        
        // make two lists
        CSRList list1;
        CSRList list2;

        list1.insertAtHead(object1);
        list1.insertAtHead(object2);

        // assign list 1 to list 2
        list2 = list1; 

        // check if the two lists say that they are equal
        if (!(list1 == list2)){
            result = false; 
        }
        
        cout << "TEST 14 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::operator=(const CSRList & rhs)
    //Case: Edge Case: Test whether the overloaded assignment operator works correctly for an edge case, e.g. the case of assigning an empty object to an object that contains data.
    //Expected result: list 1 should be empty as well
    bool assignmentListEdge(){
        bool result = true;

        CSR object1;
        CSR object2;
    
        int test1[] = {1, 0, 3, 0, 4, 5};
        int test2[] = {1, 2, 3, 4, 5, 6};

        object1.compress(3, 2, test1, 6); 
        object2.compress(3, 2, test2, 6); 

        CSRList list1;
        CSRList list2;

        list1.insertAtHead(object1);
        list1.insertAtHead(object2);

        // assign list 2 to list 1, where list2 is empty; 
        list1 = list2; 

        if (!(list1 == list2)){
            result = false; 
        }

        // check that list1 is indeed empty
        if (!(list1.empty())){
            result = false; 
        }

        cout << "TEST 15 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::getAt(int CSRIndex, int row, int col)
    //Case: Error Case: Test whether the getAt(...) function throws an exception for an error case, i.e. the list of matrices is empty."
    //Expected result: an error should be thrown
    bool getAtListError(){
        bool result = true;

        try {
            // perfrom a getAt on an empty list
            CSRList list; 
            list.getAt(1, 1, 1); 

            result = false; 
        } 
        catch (const exception& e) {
         
            result = true;
            cout << "Exception thrown: " << e.what() << endl;
        }

        cout << "TEST 16 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::getAt(int CSRIndex, int row, int col)
    //Case: Normal Case: Test whether the getAt(...) works correctly for a normal case, it returns the expected answer.
    //Expected result: the correct value at the index shoud have been gotten
    bool getAtListNormal (){
        bool result = true;
        
        CSR object;
        int test[] = {1, 2, 3, 4, 5, 6};
        object.compress(2, 3, test, 6);

        CSRList list; 
        list.insertAtHead(object);

        // checks if first row has right getAt values
        if (list.getAt(0, 0, 0) != 1 || list.getAt(0, 0, 1) != 2 || list.getAt(0, 0, 2) != 3) {
            result = false;
        }
        
        // checks if second row has right getAt values
        if (list.getAt(0, 1, 0) != 4 || list.getAt(0, 1, 1) != 5 || list.getAt(0, 1, 2) != 6) {
            result = false;
        }
        cout << "TEST 17 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::averageSparseRatio()
    //Case: Normal Case: Test whether the averageSparseRatio() works correctly for a normal case, it returns the expected answer.
    //Expected result: the correct average sparse ratio should be returned
    bool averageSparseRatioListNormal(){
        bool result = true;
        
        CSR object;
        int test[] = {1, 0, 3, 4, 0, 6};
        object.compress(2, 3, test, 6);
        CSR object1;
        
        CSRList list; 
        // add some more objects into the list
        list.insertAtHead(object);
        list.insertAtHead(object1);
        list.insertAtHead(object);
        list.insertAtHead(object1);
        
        // make sure that the sparse ratio is 33
        if (list.averageSparseRatio() != 16){
            result = false; 
        }
        cout << "TEST 18 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::averageSparseRatio())
    //Case: Edge Case: Test whether the averageSparseRatio() works correctly for a edge case, it returns 0 where it is an empty list.
    //Expected result: when the list is empty, it should return 0
    bool averageSparseRatioListEdge(){
        bool result = true;
        // makes an empty list
        CSRList list; 
        
        // make sure that the sparse ratio is 0
        if (list.averageSparseRatio() != 0){
            result = false; 
        }
        cout << "TEST 19 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::operator==(const CSRList & rhs)
    //Case: Normal Case: Test whether the overloadedEquality() works correctly for a normal case, it correctly identifies that two list objects are equal
    //Expected result: it shoud see that list 1 and list 2 are equal
    bool equalityListNormal(){
        bool result = true;

        // make sime objects 
        CSR object1;
        CSR object2;
        int test1[] = {1, 2, 3, 0, 4, 5};
        int test2[] = {1, 2, 3, 4, 5, 0};
        object1.compress(2, 3, test1, 6);
        object2.compress(2, 3, test2, 6);
        CSRList list; 
        
        // Create two CSRList objects and put in the two csr objects
        CSRList list1;
        CSRList list2;
        list1.insertAtHead(object1);
        list1.insertAtHead(object2);
        
        list2.insertAtHead(object1);
        list2.insertAtHead(object2);

        // Compare the lists using the overloaded equality
        if (!(list1 == list2)) {
            result = false;
        }
        cout << "TEST 20 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::operator==(const CSRList & rhs)
    //Case: Edge Case: Test whether the overloadedEquality() works correctly for a edge case, it correctly identifies that two list objects are equal when they are both empty
    //Expected result: two empty objects shoudl be equal
    bool equalityListEdge(){
        bool result = true;
        // makes empty lists
        CSRList list1;
        CSRList list2;
        
        // Compare the lists using the overloaded equality
        if (!(list1 == list2)) {
            result = false;
        }
        cout << "TEST 21 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::insertAtHead(const CSR & matrix)
    //Case: Normal Case: Test whether the insertAtHead() works correctly for a normal case
    //Expected result: it should insert at head like expected
    bool insertAtHeadListNormal() {
        bool result = true;

        // create a object
        CSR object;
        int test[] = {1, 2, 3, 0, 4, 5};
        object.compress(2, 3, test, 6);

        CSR object2;
        int test2[] = {1, 2, 3, 4, 5, 6};
        object2.compress(2, 3, test2, 6);

        // create a object list and insert the object into it
        CSRList list;
        list.insertAtHead(object2);
        list.insertAtHead(object);
        

        // make sure that the inserted matches the original object
        if (!(list.m_head != nullptr && *(list.m_head) == object)) {
            result = false;
        }

        // make sure that the second inserted item matches the original
        if (!(list.m_head->m_next != nullptr && *(list.m_head->m_next) == object2)) {
            result = false;
        }

        // make sure the length of the list is indeed 2
        if (list.m_size != 2){
            result = false; 
        }
        cout << "TEST 22 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::insertAtHead(const CSR & matrix)
    //Case: Edge Case: Test whether the insertAtHead() works correctly for a edge case where you insert multiple of one object
    //Expected result: there should not be a problem inserting multiple of the same item
    bool insertAtHeadListEdge() {
        bool result = true;

        // create a object
        CSR object;
        int test[] = {1, 2, 3, 0, 4, 5};
        object.compress(2, 3, test, 6);

        // create a object list and insert the object into it
        CSRList list;
        list.insertAtHead(object);
        list.insertAtHead(object);
        list.insertAtHead(object);
        list.insertAtHead(object);
        list.insertAtHead(object);

        // loop through the list to make sure that each item is the same as the object
        CSR* curr = list.m_head;
        while (curr != nullptr){
            if (!(*(curr) == object)) {
                result = false;
            }
            curr = curr->m_next;
        }

        // make sure the length of the list is indeed 5
        if (list.m_size != 5){
            result = false; 
        }
        cout << "TEST 23 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::CSRList(const CSRList & rhs)
    //Case: Normal Case: Test whether the copyconstructor works correctly for a normal case.
    //Expected result: rhs should be the same as lhs
    bool copyConstructorListNormal(){
        bool result = true;

        // make two objects
        CSR object1;
        CSR object2;

        int test1[] = {1, 0, 3, 0, 4, 5};
        int test2[] = {1, 2, 3, 4, 5, 6};

        object1.compress(3, 2, test1, 6); 
        object2.compress(3, 2, test2, 6); 
        
        // make a list
        CSRList list1;

        list1.insertAtHead(object1);
        list1.insertAtHead(object2);

        // assign list 1 to list 2
        CSRList list2(list1); 

        // check if the two lists say that they are equal
        if (!(list1 == list2)){
            result = false; 
        }
        cout << "TEST 24 RESULTS:" << endl;
        return result;
    }

    //Function: CSRList::CSRList(const CSRList & rhs)
    //Case: Edge Case: Test whether the copyConstructor works correctly for an edge case, e.g. the case of assigning an empty object
    //Expected result: list 1 should be empty as well
    bool copyConstructorListEdge(){
        bool result = true;

        // make two lists
        CSRList list1;
        CSRList list2(list1);

        if (!(list1 == list2)){
            result = false; 
        }

        // check that list1 is indeed empty
        if (!(list1.empty())){
            result = false; 
        }
        cout << "TEST 25 RESULTS:" << endl;
        return result;
    }


    private:
    
    /**********************************************
    * If we need helper functions to be reused in *
    *   test functions they can be declared here!
    **********************************************/
};

int main(){
    Tester tester;
    cout << endl << "\033[1;31m=============================|Test Cases for the CSR Class|==============================\033[0m" << endl;
    // Test Cases for the CSR Class
    cout << "________________________________________________________" << endl; 
    
    cout << "Test whether the compress(...) function works correctly for a normal case, e.g. it populates the member variables of the class with the expected values for an array of data." << endl; 

    if (tester.compressNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m Compress function passed for a normal test" << endl;
    } 
    else {
        cout << "FAILURE: Compress function failed for a normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 
    
    cout << "Test whether the compress(...) function works correctly for an error case, e.g. the user provides data which is less than the asking object size." << endl; 

    if (tester.compressError()) {
        cout << "\033[1;32mSUCCESS\033[0m Compress function passed for an error test" << endl;
    } 
    else {
        cout << "FAILURE: Compress function failed for an error test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the compress(...) function works correctly for an error case, e.g. the user asks for a 0 x 0 object but provides data." << endl; 

    if (tester.compressError2()) {
        cout << "\033[1;32mSUCCESS\033[0m Compress function passed for an error test" << endl;
    } 
    else {
        cout << "FAILURE: Compress function failed for an error test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloaded equality operator works correctly for a normal case." << endl; 

    if (tester.equalityNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m Overloaded equality function passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE: Overloaded equality function failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloaded equality operator works correctly for a edge case, i.e. both objects are empty." << endl; 

    if (tester.equalityEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m Overloaded equality function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: Overloaded equality function failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the getAt(...) function throws an exception for an error case, i.e. the requested index numbers do not exist in the object." << endl; 

    if (tester.getAtError()) {
        cout << "\033[1;32mSUCCESS\033[0m getAt function passed for an error test" << endl;
    } 
    else {
        cout << "FAILURE: getAt function failed for an error test" << endl;
    }

    // more test cases for the csr class
    cout << endl << "\033[1;93m=============================|More Test Cases for the CSR Class|==============================\033[0m" << endl;

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the copy constructor works properly in an edge case where the rhs is an empty object" << endl; 

    if (tester.copyConstructorEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m copy constructor function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: copy constructor function failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the copy constructor works properly in an normal case" << endl; 

    if (tester.copyConstructorNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m copy constructor function passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE: copy constructor function failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the compress(...) function works correctly for an edge case, e.g. the input array is greater than (m x n)" << endl; 

    if (tester.compressEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m Compress function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: Compress function failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the compress(...) function works correctly for an edge case, e.g. matrix size is specified but there is no data" << endl; 

    if (tester.compressEdge2()) {
        cout << "\033[1;32mSUCCESS\033[0m Compress function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: Compress function failed for an edge test" << endl;
    }
    
    cout << "________________________________________________________" << endl; 

    cout << "Test whether the getAt(...) works correctly for a normal case, it returns the expected answer." << endl; 

    if (tester.getAtNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m getAt function passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE:getAt function failed for an normal test" << endl;
    }

        cout << "________________________________________________________" << endl; 

    cout << "Test whether the sparseRatio(...) function works correctly in the edge case where it is called upon an empty object" << endl; 

    if (tester.sparseRatioEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m sparseRatio function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: sparseRatio function failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the sparseRatio(...) function works correctly in the normal case" << endl; 

    if (tester.sparseRatioNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m sparseRatio function passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE: sparseRatio function failed for an normal test" << endl;
    }

    // Test Cases for the CSRList Class
    cout << endl << "\033[1;34m=============================|Test Cases for the CSRList Class|==============================\033[0m" << endl;

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloaded assignment operator works correctly for a normal case." << endl; 

    if (tester.assignmentListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m overloaded assignment from list function passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE: overloaded assignment from list function failed for an normal test" << endl;
    }
    
    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloaded assignment operator works correctly for an edge case, e.g. the case of assigning an empty object to an object that contains data." << endl; 

    if (tester.assignmentListEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m overloaded assignment from list function passed for an edge test" << endl;
    } 
    else {
        cout << "FAILURE: overloaded assignment from list function failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the getAt(...) function throws an exception for an error case, i.e. the list of matrices is empty." << endl; 

    if (tester.getAtListError()) {
        cout << "\033[1;32mSUCCESS\033[0m getAt function from list passed for an error test" << endl;
    } 
    else {
        cout << "FAILURE:getAt function from list failed for an error test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the getAt(...) works correctly for a normal case, it returns the expected answer." << endl; 

    if (tester.getAtListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m getAt function from list passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE:getAt function from list failed for an normal test" << endl;
    }

    // more test cases for the csr list class
    cout << endl << "\033[1;35m=============================|More Test Cases for the CSRList Class|==============================\033[0m" << endl;

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the averageSparseRatio() works correctly for a normal case, it returns the expected answer." << endl; 

    if (tester.averageSparseRatioListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m averageSparseRatio function from list passed for an normal test" << endl;
    } 
    else {
        cout << "FAILURE: averageSparseRatio function from list failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the averageSparseRatio() works correctly for a edge case, it returns 0 where it is an empty list." << endl; 

    if (tester.averageSparseRatioListEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m averageSparseRatio function from list passed for an edge test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: averageSparseRatio function from list failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloadedEquality() works correctly for a normal case, it correctly identifies that two list objects are equal" << endl; 

    if (tester.equalityListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m overloadedEquality function from list passed for an normal test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: overloadedEquality function from list failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the overloadedEquality() works correctly for a edge case, it correctly identifies that two list objects are equal when they are both empty" << endl; 

    if (tester.equalityListEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m overloadedEquality function from list passed for an edge test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: overloadedEquality function from list failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the insertAtHead() works correctly for a normal case" << endl; 

    if (tester.insertAtHeadListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m insertAtHead function from list passed for an normal test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: insertAtHead function from list failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the insertAtHead() works correctly for a edge case where you insert multiple of one object" << endl; 

    if (tester.insertAtHeadListEdge()) {
        cout << "\033[1;32mSUCCESS\033[0m insertAtHead function from list passed for an edge test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: insertAtHead function from list failed for an edge test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the CopyContructor() works correctly for a normal case" << endl; 

    if (tester.copyConstructorListNormal()) {
        cout << "\033[1;32mSUCCESS\033[0m CopyContructor function from list passed for an normal test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: CopyContructor function from list failed for an normal test" << endl;
    }

    cout << "________________________________________________________" << endl; 

    cout << "Test whether the CopyContructor() works correctly for a edge case where an empty object is passed in" << endl; 

    if (tester.copyConstructorListEdge()) {
        cout << "\033[1;32mSUCCESS:\033[0m CopyContructor function from list passed for an edge test" << endl;
    } 
    else {                                                                                                                                                                                                                              
        cout << "FAILURE: CopyContructor function from list failed for an edge test" << endl;
    }
   
    return 0;
}

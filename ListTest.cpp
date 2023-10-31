//-----------------------------------------------------------------------------
// ListTest.cpp
// Test Client for the List ADT
// Bradley Haire
// bhaire
// pa6
//-----------------------------------------------------------------------------


#include "List.h"
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char** argv) {

    List* my_list = new List();
    cout << my_list->length() << endl;

    for(int i = 0; i < 10; i += 1) {
        cout << "done " << std::to_string(i) << " many iterations" << endl;
        my_list->insertAfter(i);
        my_list->moveNext();
    }
    cout << "newline" << endl;
    cout << my_list->to_string(); // this should check both the overridden function and to_string()
    cout << endl;
    List* test = new List();
    for(int i = 0; i < 10; i += 1) {
        test->insertAfter(i);
        test->moveNext();
    }
    List* test_2 = new List();
    for(int i = 0; i < 10; i += 1) {
        test_2->insertAfter(i);
    }
    cout << my_list->to_string() << endl;
    cout << test->to_string() << endl;
    cout << endl;
    cout << my_list->equals(*test) << endl;
    cout << "the above should be 1" << endl;
    cout << endl;
    cout << my_list->equals(*test_2) << endl;
    cout << "the above should be 0" << endl;
    cout << endl;

    cout << endl;
    for(int i = 0; i < 5; i += 1) {
        my_list->insertAfter(i);
        my_list->moveNext();
    }
    cout << *my_list;
    cout << endl;
    my_list->cleanup();
    cout << endl;
    cout << "printing cleaned list below" << endl;
    cout << *my_list << endl;
    my_list->moveFront();
    for (int i = 0; i < 4; i += 1) {
        my_list->moveNext();
    }
    my_list->eraseBefore();
    cout << "printing 1 erased list below" << endl;
    cout << *my_list << endl;

    cout << "doing tests on copied list now: " << endl;
    List* copy_test = new List(*my_list);
    cout << *copy_test << endl;
    cout << my_list->equals(*copy_test) << endl;
    cout << "the above should be 1" << endl;
    // cursor should be at 0 for this new list
    copy_test->moveFront();
    cout << copy_test->peekNext() << endl;
    cout << copy_test->moveNext() << endl;
    cout << copy_test->peekPrev() << endl;
    cout << "the above 3 values should all be the same (should be the value 0)" << endl;
    cout << "checking find functions" << endl;
    cout << copy_test->findNext(4) << endl; 
    cout << copy_test->findNext(11) << endl;
    cout << "the position of the cursor: " << copy_test->position() << endl;

    cout << copy_test->findPrev(5) << endl;
    cout << "the position of the cursor: " << copy_test->position() << endl;
    cout << copy_test->findPrev(-1) << endl;
    List concatenated = (*copy_test).concat(*my_list);

    cout << *copy_test << endl;
    cout << *my_list << endl;
    cout << "below should be a concatenated list of the two above lists" << endl;
    cout << concatenated << endl;
    
    cout << concatenated.front() << endl;
    cout << concatenated.back() << endl;
    concatenated.moveFront();
    concatenated.setAfter(22);
    concatenated.moveBack();
    concatenated.setBefore(800);

    cout << concatenated << endl;

    cout << concatenated.front() << endl;
    cout << concatenated.back() << endl;
    cout << "got to line 102 in the listTest" << endl;
    
    concatenated.moveBack();
    concatenated.movePrev();
    cout << "starting cursor position: " << concatenated.position() << endl;
    concatenated.cleanup();
    cout << "ending cursor position: " << concatenated.position() << endl;
    cout << concatenated.peekNext() << endl;
    cout << concatenated.peekPrev() << endl;
    concatenated.clear();
    cout << concatenated << endl;
    // the above should also test the edge case of trying to print an empty list




    delete copy_test;
    delete my_list;
    delete test;
    delete test_2;
    return 0;
}
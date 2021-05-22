#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void quickSort(ListNode*& front) {
    /* TODO: Implement this function. */
}

//ListNode* partition(ListNode* front) {

//}

//ListNode* concatenate(ListNode* left, ListNode* middle, ListNode* right) {

//}
/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   while (front != nullptr) {
       cout << front->data;
       if (front->next != nullptr){
           cout << ", ";
       }
       front = front->next;
   }
   cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
    // This deallocating code was obtained from Lecture 20
    while (front != nullptr) {
        ListNode *temp = front;
        front = front->next;
        delete temp;
    }
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in
 * the same order. It can be used to confirm a linked list's contents
 * match the expected.
 */
ListNode* createList(Vector<int> values){
    if (values.size() > 0) {
        ListNode* front = new ListNode(values[0], nullptr);
        for (int i = 1; i < values.size(); i++) {
            ListNode* nextNode = new ListNode(values[i], nullptr);
            // This method of going through the linked list and adding to the end was obtained in lecture 20.
            ListNode* cur = front;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = nextNode;
        }
        return front;
    }
    return nullptr;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
    int vSize = v.size();
    if (front == nullptr && v.size() == 0)
        return true;
    for (int i = 0; i < vSize; i++) {
        if (front->data != v[0])
            return false;
        if (front->next == nullptr && v.size() > 1)
            return false;
        if (front->next != nullptr && v.size() == 1)
            return false;
        front = front->next;
        v.remove(0);
    }
    return true;
}

STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 2, 3, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);
    printList(list);
    cout << values.toString() << endl;
    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}

STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values;
    for (int i = 0; i < 50; i++)
        values.add(i);
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);
    printList(list);

    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));
    values.remove(49);
    cout << values.toString() << endl;
    EXPECT(!areEquivalent(list, values));
    values.add(49);
    values.remove(25);
    cout << values.toString() << endl;
    EXPECT(!areEquivalent(list, values));

    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
    deallocateList(testList);
}
PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }
    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}

/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}


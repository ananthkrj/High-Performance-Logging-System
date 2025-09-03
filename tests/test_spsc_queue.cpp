/*
For now just include an external spscqueue
implementation to test 

*/

#include <rigtorps_spsc_queue.hpp>
#include <gtest/gtest.h>

// for now just include an external spscqueue
// implementation to test this one, then test
// the custom built spsc_queue class

/*
Comment constructor tests out for now

TEST(SPSCQueue, constructor) {

}

TEST(SPSCQueue, destructor) {

}

*/

/*
1. Initialize the queue
2. capture initial size of the queue
3. emplace a value
4. check that new size
5. test front
*/
TEST(SPSCQueue, emplace) {
    // regular emplacing
    highLogger::SPSCQueue<int> regQueue(10);
    size_t initialSize = regQueue.size();

    regQueue.emplace(38);
    
    size_t newSize = regQueue.size();
    ASSERT_EQ(newSize, initialSize + 1);

    int* frontElement = regQueue.front();
    ASSERT_NE(frontElement, nullptr);
    // need to dereference frontElement
    ASSERT_EQ(*frontElement, 38);

    
    // Can't test blocking functionality 
    // in emplace because that messes up
    // the gtest

    // multi queue testing
    highLogger::SPSCQueue<int> fullQueue(3);
    
    fullQueue.emplace(1);
    fullQueue.emplace(2);
    fullQueue.emplace(3);

    // size assertion
    ASSERT_EQ(fullQueue.size(), 3);

    // emplace works after pop ocurrs

    int* frontElement1 = fullQueue.front();
    ASSERT_NE(frontElement1, nullptr);
    ASSERT_EQ(*frontElement1, 1);

    fullQueue.pop();
    ASSERT_EQ(fullQueue.size(), 2);
}



TEST(SPSCQueue, try_emplace) {
    // try emplace when the queue has space
    highLogger::SPSCQueue<int> tryQueue(3);

    bool result = tryQueue.try_emplace(20);
    ASSERT_TRUE(result);
    ASSERT_EQ(tryQueue.size(), 1);

    // multiple try emplace operations
    ASSERT_TRUE(tryQueue.try_emplace(21));
    ASSERT_TRUE(tryQueue.try_emplace(22));
    ASSERT_EQ(tryQueue.size(), 3);

    // try emplace fails when queue is full
    bool fullQueue = tryQueue.try_emplace(23);
    ASSERT_FALSE(fullQueue);
    ASSERT_EQ(tryQueue.size(), 3);

    // verify front element
    int* tryfrontElement = tryQueue.front();
    ASSERT_NE(tryfrontElement, nullptr);
    ASSERT_EQ(*tryfrontElement, 20);

    // try emplace succeeds after making space
    // utilize pop. Actually test the blocking
    // operation. SHould add after making space
    
    tryQueue.pop();
    ASSERT_TRUE(tryQueue.try_emplace(23));
    ASSERT_EQ(tryQueue.size(), 3);
}

// push has a void return type, dont use
// any bools or speciifc types to return
TEST(SPSCQueue, push) {
    highLogger::SPSCQueue<int> pQueue(3);
    int* frontElement2 = pQueue.front();

    // test individual push
    pQueue.push(5);
    ASSERT_EQ(pQueue.size(), 1);

    // test multiple pushes
    pQueue.push(6);
    pQueue.push(7);
    ASSERT_EQ(pQueue.size(), 3);
    
    // push after pop
    pQueue.pop();
    pQueue.push(8);
    ASSERT_EQ(pQueue.size(), 3);
}

/*
TEST(SPSCQueue, push) {
    highLogger::SPSCQueue<int> pushQueue(3);

    // first test individual element
    pushQueue.push(3);

    int* frontElement = pushQueue.front();
    ASSERT_NE(frontElement, nullptr);
    ASSERT_EQ(*frontElement, 3);
    ASSERT_EQ(pushQueue.size(), 1);

    // now test pushing multiple elements
    pushQueue.push(4);
    pushQueue.push(5);
    int* newFrontElement = pushQueue.front();
    ASSERT_EQ(*newFrontElement, 3);
    ASSERT_EQ(pushQueue.size(), 3);
}

TEST(SPSCQueue, front) {
    // figure out if i need to do multiple references
    // to frontElement or if this can act akin 
    // to global variable
    highLogger::SPSCQueue<int> pQueue(3);
    int* frontElement = Queue.front();

    // test one push
    pQueue.push(10);
    ASSERT_NE(frontElement, nullptr);
    ASSERT_EQ(*frontElement, 10);

    // second push
    pQueue.push(20);
    ASSERT_EQ(*frontElement, 10);

    // then emplace
    pQueue.emplace(30);
    ASSERT_EQ(*frontElement, 10);

    // test change of front with pop after push
    pQueue.pop();
    ASSERT_EQ(*frontElement, 20);

    // new queue with push then emplace
    highLogger::SPSCQueue<int> peQueue(2);
    int* frontElement = peQueue.front();

    peQueue.push(30);
    ASSERT_NE(frontElement1, nullptr);
    ASSERT_EQ(*frontElement1, 30);

    peQueue.emplace(40);
    ASSERT_EQ(*frontElement, 40);

    // test change of front with pop after push
    peQueue.pop();
    ASSERT_EQ(*frontElement1, 40);

    // new queue with emplace then push
    highLogger::SPSCQueue<int> epQueue(2);
    int* frontElement2 = epQueue.front();

    epQueue.emplace(7);
    ASSERT_NE(frontElement2, nullptr);
    ASSERT_EQ(*frontElement2, 7);

    epQueue.push(8);
    ASSERT_EQ(*frontElement2, 8); 

    // test change of front with pop after push
    epQueue.pop();
    ASSERT_EQ(*frontElement2, 8);
}

TEST(SPSCQueue, pop) {
    // test pop for pure pushes
    highLogger::SPSCQueue<int> pQueue(3);

    pQueue.push(1);
    pQueue.push(2);
    pQueue.push(3);
    int* frontElement = pQueue.front()
    size_t initialSize = pQueue.size();

    pQueue.pop();

    ASSERT_EQ(*frontElement, 2);
    size_t newSize = pQueue.size();
    ASSERT_EQ(initialSize, newSize + 1);

    // test pop for pure emplaces
    highLogger::SPSCQueue<int> EQueue(3);
    
    EQueue.emplace(4);
    EQueue.emplace(5);
    Equeue.emplace(6);
    int* frontElement1 = Equeue.front();
    size_t initialSize = Equeue.size();

    Equeue.pop();
    ASSERT_EQ(*frontElement1, 5);
    size_t newSize = Equeue.size();
    ASSERT_EQ(initialSiz, newSize + 1);
    
    // test pop then emplace
    highLogger::SPSCQueue<int> peQueue(2);
    
    peQueue.push(10);
    peQueue.emplace(11);
    size_t initialSize = peQueue.size();
    int* frontElement2 = peQueue.front();

    peQueue.pop()
    ASSERT_EQ(*frontElement2, 11);
    size_t newSize = peQueue.size();
    ASSERT_EQ(initialSize, newSize - 1);
    
    // test emplace then pop
    highLogger::SPSCQueue<int> epQueue(2);

    epQueue.emplace(5);
    epQueue.push(6);
    size_t initialSize = epQueue.size();
    int* frontElement3 = epQueue.front();

    epQueue.pop();
    ASSERT_EQ(*frontElement3, 6);
    size_t newSize = epQueue.front();
    ASSERT_EQ(newSize, initialSize + 1);
}

TEST(SPSCQueue, size) {

}

TEST(SPSCQueue, empty) {

}

TEST(SPSCQueue, capacity) {

}

// move onto fixture tests after function validation done
*/

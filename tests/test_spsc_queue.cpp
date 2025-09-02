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

    testQueue.emplace(38);
    
    size_t newSize = regQueue.size();
    ASSERT_EQ(newSize, initialSize + 1);

    int* frontElement = regQueue.front();
    ASSERT_NE(frontElement, nullptr);
    // need to dereference frontElement
    ASSERT_EQ(*frontElement, 38);

    // functionlity testing
    // when queue is full as emplaces
    // beyond the capacity will lead to
    // a blocked operation
    highLogger::SPSCQueue<int> fullQueue(1);
    fullQueue.emplace(10);
    fullQueue.emplace(20);

    // size assertion which will block
    // overflowing
    ASSERT_EQ(fullQueue.size(), 1);

    // space is created so should actually emplace 20
    // due to waiting in emplace mechnism
    fullQueue.pop(10);

    ASSERT_EQ(fullQueue.size(), 1);

    int* frontElement = fullQueue.front();
    ASSERT_NE(frontElement, nullptr);
    ASSERT_EQ(*frontElement, 10);
}


TEST(SPSCQueue, try_emplace) {
    // regular emplace when queue is not full or blocked
    highLogger::SPSCQueue<int> tryRegQueue(3);
    size_t initialSize = tryRegQueue.size();

    tryRegQueue.try_emplace(22);

    // assert the size difference
    size_t newSize = tryRegQueue.size();
    ASSERT_EQ(newSize, initialSize + 1);

    // check if front works for try_emplace
    int* frontElement = tryRegQueue.front();
    ASSERT_NE(frontElement, nullptr);
    ASSERT_EQ(*frontElement, 22);

    // try_emplace focused implementation which
    // will test 
    highLogger::SPSCQueue<int> fullQueue(1);
    fullQueue.emplace(3);
    fullQueue.emplace(4);

    // No need to pop or anything after to
    // make space. Point of try emplace
    // is to instantly return false
    // once queue is false
    ASSERT_EQ(fullQueue.size(), 1);

    // maybe test that makes sure return
    // type of function is false later on

}

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
/*
For now just include an external spscqueue
implementation to test 

*/

#include <rigtorps_spsc_queue.hpp>
#include <gtest/gtest.h>

// for now just include an external spscqueue
// implementation to test this one, then test
// the custom built spsc_queue class

TEST(SPSCQueue, constructor) {

}

TEST(SPSCQueue, destructor) {

}


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
    size_t initialSize = testQueue.size();

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
}


TEST(SPSCQueue, try_emplace) {
    // regular emplace when queue is not full or blocked
    highLogger::SPSCQueue<int> tryRegQueue(3);
    size_t initialSize = tryRegQueue.size();

    tryRegQueue.try_emplace(22);

    // assert the size difference
    size_t newSize = tryRegQueue.size();
    ASSERT_EQ(newSize, initialSize + 1);

    // check if front works for 


}

TEST(SPSCQueue, push) {

}

TEST(SPSCQueue, front) {

}

TEST(SPSCQueue, pop) {

}

TEST(SPSCQueue, size) {

}

TEST(SPSCQueue, empty) {

}

TEST(SPSCQueue, capacity) {

}

// move onto fixture tests after function validation done
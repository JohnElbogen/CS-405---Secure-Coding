// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_FALSE(collection->empty());
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // store our current size
    int startSize = collection->size();

    add_entries(5);

    // is there atleast 5 entries?
    // if so, is current size less the previous size equal to 5?
    ASSERT_TRUE(collection->size() > 4);
    EXPECT_EQ(collection->size() - startSize, 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsMaxSizeGTESizeOfEntries)
{
    // store max size of collection
    int maxSize = collection->max_size();
    // Check we start with empty and 0 entries
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    // check max size against 0 entries
    ASSERT_TRUE(maxSize >= collection->size());
    // check max size against 1 entries
    add_entries(1);
    ASSERT_TRUE(collection->size(), 1);
    ASSERT_TRUE(maxSize >= collection->size());
    // check max size against 5 entries
    add_entries(4);
    ASSERT_TRUE(collection->size(), 5);
    ASSERT_TRUE(maxSize >= collection->size());
    // check max size against 10 entries
    add_entries(5);
    ASSERT_TRUE(collection->size(), 10);
    ASSERT_TRUE(maxSize >= collection->size());
}


// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsCapacityGTESizeOfEntries)
{
    // check max size against 0 entries
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // check max size against 1 entries
    add_entries(1);
    ASSERT_EQ(collection->size(), 1);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // check max size against 5 entries
    add_entries(4);
    ASSERT_EQ(collection->size(), 5);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // check max size against 10 entries
    add_entries(5);
    ASSERT_EQ(collection->size(), 10);
    ASSERT_TRUE(collection->capacity() >= collection->size());
}
// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, DidResizeIncreaseVectorSize)
{
    // store our current size
    int startSize = collection->size();
    // resize by one more than our start size
    collection->resize(startSize + 1);
    // check new size is more than start size
    ASSERT_TRUE(collection->size() > startSize);
}
// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, DidResizeDecreaseVectorSize)
{
    // store our current size
    int startSize = collection->size();
    // check startSize is not 0 (cannot have negative vector size, and add 1 entry, then test)
    if (startSize == 0) {
        add_entries(1);
        startSize = collection->size();
    }
    // resize by one less than our start size
    collection->resize(startSize - 1);
    // check new size is more than start size
    ASSERT_TRUE(collection->size() < startSize);
}
// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, DidResizeDecreaseVectorSizeToZero)
{
    // store our current size
    int startSize = collection->size();
    // resize by our start less than our start size which should equal zero
    collection->resize(startSize-startSize);
    // check new size is zero, and empty
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}
// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, CanClearEraseCollection)
{
    // store our current size
    int startSize = collection->size();
    // check startSize is not 0 (cannot have negative vector size, and add 1 entry, then test)
    if (startSize == 0) {
        add_entries(1);
    }
    // clear the collection
    collection->clear();
    // check new size is 0 and collection is cleared
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}
// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CanEraseClearCollection)
{
    // store our current size
    int startSize = collection->size();
    // check startSize is not 0 (cannot have negative vector size, and add 1 entry, then test)
    if (startSize == 0) {
        add_entries(1);
    }

    // resize erase by start elements, through end element of collection
    collection->erase(collection->begin(), collection->end());
    // check new size is 0 and collection is cleared
    ASSERT_EQ(collection->size(), 0);
    ASSERT_TRUE(collection->empty());
}
// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CanReserveAddCapacityButNotSizeOfCollection)
{
    // store our current size
    int startSize = collection->size();
    int startCapacity = collection->capacity();
    // check that our capacity is not equal to max capacity, because you cannot increase the capacity greater than max_size()
    ASSERT_FALSE(startCapacity == collection->max_size());
    // resize erase by start elements, through end element of collection
    collection->reserve(startCapacity + 1);
    // check the size remained the same, but the new capacity is greater than the start
    EXPECT_EQ(collection->size(), startSize);
    ASSERT_TRUE(collection->capacity() > startCapacity);
}
// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CanOutOfRangeExceptionThrow)
{
    int startSize = collection->size();
    //Simply checks that the statement throws our of range exception, calling at, with 1 greater than the size of the collection
    ASSERT_THROW(collection->at(startSize + 1), std::out_of_range);
}
// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, CanLengthErrorExceptionThrow)
{
        //Simply checks that the statement throws length error, when trying to reserve a capacity of -1 in the collection
        ASSERT_THROW(collection->reserve(-1), std::length_error);
}

TEST_F(CollectionTest, CanPopBackCollection) 
{
    // store our current size
    int startSize = collection->size();
    // check startSize is not 2, and adjusts it to be 2 entries for the test)
    if (startSize != 2) {
        collection->clear();
        add_entries(2);
    }

    // Get the first element
    int firstElement = collection->at(0);
    // creating our own second element which is greater than the first (for our assert later)
    int secondElement;
    secondElement = firstElement + 1;
    // place that element in the second position in the vector (to make sure we remove the element from the back position
    collection->at(1) = secondElement;
    
    collection->pop_back();

    // check that our collection size is now 1 (since we remove 1)
    ASSERT_EQ(collection->size(), 1);
    // check that the first element remained, and was not removed.
    ASSERT_TRUE(collection->at(0) < secondElement);
}
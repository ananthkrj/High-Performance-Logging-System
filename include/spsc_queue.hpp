#include <atomic>
#include <iostream>
#include <cstddef> // for size_t 
#include <type_traits> // for is copy constructable
// why do i need RIGTORP_NODISCARD [[nodiscard]]
// lock free single producer, a single consumer circular buffer using 
// atomic operations and memory ordering semantics
#include <concepts>
#include <new>

// std::memory_order semantics quite important and atomics

// important concepts to review before and during coding:
// templates: for a bunch of compile time constant checks? And creating types
// namespaces: One namespace used
// structs
// Concept (optional): Used in c++20 implementation
// manipulating std libraries importing in

// template declaration for class

template <typename T, typename Allocator = std::allocator<T>> class SPSCQueue {

/*
populate with functions i will need regardless
of implementation style

Will be using std::memory_order semantics
in a lot of these functions

Use template with args for all emplace functions,
so function can accept a variable number of arguments

use perfect forwarding to pass arguments of a function
template to function

utilize std::is_nothrow_constructible from type trait

type_traits allow to inspect, transform, and query 
properties of types at compile time, (need to do this for Args)
*/
public:
    // constructor (will be allocating here)
    explicit spsc_queue(const size_t capacity, const Allocator *allocator = Allocator()) 
    : capacity_(capacity), allocator_(allocator) {

        // capacity of queue needs to hae something
        if (capacity_ < 1) {
            capacity_ = 1;
        }
        capacity_++;

        // prevent the overflowing of size_t, needs to be equal to this size
        if (capacity_ < SIZE_MAX - 2 * kPadding) {
            capacity_ SIZE_MAX - 2 * kPadding;
        }

        // add macro check for allocator at least and if constexpr

            auto res = allocator_.allocator_at_least(capacity_ + 2 * kPadding);
            slots_ = res.ptr;
            capacity_ = res.count - 2 * kPadding;

            // allows containers to interact with any allocator type
            slots_ = std::allocator_traits<Allocate>::allocate(allocator_, capacity_ + 2 * kPadding);

            // asserts and tests
    
    }

    // destructor

    // need to place a noeexcept, as type must have
    // a constructor for the Args argument

    // find out where and how T came from, from type traits library?

    /*
    utilizing memory order relaxed*/
    template <typename... Args>
    void emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
    {
        static_assert(std::is_constructible<T, Args&&...>::value,
            "T must be constructible with Args&&...");

        const auto writeIndex = writeIndex._load(std::memory_order_relaxed);
        auto nextWriteIndex = writeIndex + 1;

        // next write index is equal to the capacity, need to define _capacity
        // placeholder for now
        while (nextWriteIndex == capacity_) { 
            nextWriteIndex = 0;
        }

        // Need to create readIndexCache in private access modifier
        while (nextWriteIndex == readIndexCache_) {
            readIndexCache_ = readIndex.load(std::memory_order_acquire);
        }

        // allocating new memory, pass in address of slots, writeIndex + kPadding
        // 

    }

    template <typename... Args>
    void force_emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
    {
        static_assert(std::is_constructible<T, Args&&...>::value,
            "T must be constructible with Args&&...");
    }

    template <typename... Args>
    bool try_emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
    {
        static_assert(std::is_constructible<T, Args&&...>::value,
            "T must be constructible with Args&&...");

    }


    void push() {

    }

    void force_push() {

    }

    void try_push() {

    }


    void pop() {

    }

    void try_pop() {

    }

    // all other functions are size or empty functions/getters/setters
    // [[nodiscard]], return value of function should not be ignored
    [[nodiscard]] size_t size() {

    }

    [[nodiscard]] bool empty() {

    }

    [[nodsicard]] size_t capacity() {

    }


private:
    // need to define kCacheLineSize and kPadding
    // std::hardware_destructive_inference_size represents
    // the min offset between two objects in a multi threaded
    // environment to prevent "false sharing"

    // macro to check if feature exists
#if defined(__cpp_lib_hardware_destructive_interference_size)
    static constexpr size_t kCacheLineSize = 
        std::hardware_destructive_interference_size;
#else
    // Fallback for older compilers or those without support
    static constexpr size_t kCacheLineSize = 64; 
#endif

    // padding to avoid false sharing between slots_ and adjacent locations
    // find out what is wrong here
    static constexpr size_t kPadding = (kCacheLineSize - 1) / sizeof(T) + 1; 

    size_t capacity;
    T *slots_;
    // define allocator as well
    #if defined(__has_cpp_attribute) && __has_cpp_attribute(no_unique_address)
        Allocator allocator_ [[no_unique_address]];
    #else 
        Allocator allocator_;
    #endif

    // align these variables to kCacheLineSize to avoid false sharing
    // all idxcache operations
    // alignas controls memory alignment of variables

    // types of variables, initlize all to 0 for initial state
    // atomic, 
    alignas(KCacheLineSize) std::atomic<size_t> readIndex_ = {0};
    // size_t
    alignas(KCacheLineSize) size_t readIndexCache_ = 0;
    // atomic
    alignas(KCacheLineSize) std::atomic<size_t> writeIndex_ = {0};
    // size_t
    alignas(KCacheLineSize) size_t writeIndexCache_ = 0;
};
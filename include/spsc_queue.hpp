// lock free single producer, a single consumer circular buffer using 
// atomic operations and memory ordering semantics

#include <atomic>
#include <iostream>
#include <cstddef> // for size_t 
#include <type_traits> // for is copy constructable
// why do i need RIGTORP_NODISCARD [[nodiscard]] (states that function return value should not be ignored)
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

// feature test macro that check if these two features are avaialble
#if defined(__cpp_if_constexpr) && defined(_cpp_lib_void_t)
// find out what this means, what the two struct initializations do
// what do importance of the type delcarations using templates do
  template <typename Alloc2, typename = void>
  struct has_allocate_at_least : std::false_type {};

  template <typename Alloc2>
  struct has_allocate_at_least<
      Alloc2, std::void_t<typename Alloc2::value_type,
                          decltype(std::declval<Alloc2 &v>().allocate_at_least(
                            size_t{})) : std::try_type{};
#endif
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
    explicit SPSCQueue(const size_t capacity, const Allocator *allocator = Allocator()) 
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
    #if defined(__cpp_if_constexpr) && defined(__cpp_lib_void_t)
        if constexpr (has_allocate_at_least<Allocator>::value) {
            auto res = allocator_.allocator_at_least(capacity_ + 2 * kPadding);
            slots_ = res.ptr;
            capacity_ = res.count - 2 * kPadding;
        } else {
            // allows containers to interact with any allocator type
            slots_ = std::allocator_traits<Allocator>::allocate(allocator_,
            capacity_ + 2 * kPadding);
        }
    #else
        slots_ = std::allocator_traits<Allocator>::allocate(allocator_,
        capacity_ + 2 * kPadding);
    #endif

        // asserts and tests
    }

    // destructor
    ~SPSCQueue() {
        while (front()) {
            pop();
        }
        // deallocate using allocator traits
        std::allocator_traits<Allocator>::deallocate(allocator_, slots_, capacity + 2 * kPadding);
    }

    // non copyable and non moveable portion, find out what this does
    spsc_queue(const spsc_queue &) = delete;
    spsc_queue &operator=(const spsc_queue &) = delete;

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
        // utilize perfect forwarding to pass arguments of T 
        // release memroy through std::memory_order_release
        new(&slots_[writeIndex + kPadding]) T(std::forward<args>(args)...);
        writeIndex_.store(nextWriteIndex, std::memory_order_release);
    }

    template <typename... Args>
    bool try_emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
    {
        static_assert(std::is_constructible<T, Args&&...>::value,
            "T must be constructible with Args&&...");
        
        const writeIndex = writeIndex._load(std::memory_order_relaxed);
        const nextWriteIndex = writeIndex + 1;

        if (nextWriteIndex == capacity_){
            nextWriteIndex = 0;
        }
        if (nextWriteIndex == readIndexCache_) {
            readIndexCache_ = readIndex_.load(std::memory_order_acquire);
            if (nextWriteIndex == readIndexCache_) {
                return false;
            }
        }

        new(&slots[writeIndex + kPadding]) T(std::forward<Args>(args...));
        writeIndex_.store(nextWriteIndex, std::memory_order_release);
        return true;
    }

    // throw a no except: which means to check if an object of
    // type T can be constructed without throwing
    // an exception
    void push(const T &v) noexcept(std::is_nothrow_constructible<T>::value) 
    {
        static_assert(std::is_copy_constructible<T>::value, 
            "T must be copy constructible");
        emplace(v);
    }

    // alternative push with P type and std::forward<P>(v) pass in
    // function template is only valid if T is constructed from P&&
    template<typename P, typename> = typename std::enable_if<
                                std::is_constructible<T, P &&>::value::type>
    
    // type T and P can be constructed without throwing an exception
    void push(P &&v) noexcept(std::is_nothrow_constructible<T, P>::value)
    {
        emplace(std::forward<P>(v));
    }

    // regular try push
    // type T can be constructed without throwing an exception
    [[nodiscard]] bool
    try_push(const T &v) noexcept(std::is_nothrow_constructible<T>::value)
    {
        static_assert(std::is_copy_constructible<T>::value,
            "T must be copy constructible");
        return try_emplace(v);
    }

    // alternative try push
    // template function is only valid if T is construxted from P&&
    template<typename P, typename> = typename std::enable_if<
                                std::is_constructible<T, P &&>::value::type>
    [[nodiscard]] bool
    try_push(P &&v) noexcept(std::is_nothrow_constructible<T, P>::value);
    {
        return try_emplace(std::forward<P>(v));
    }

    [[nodiscard]] T *front() noexcept
    {
        auto const readIndex = readIndex_.load(std::memory_order_relaxed);
        if (readIndex_ == writeIndexCache_) {
            writeIndexCache_ = writeIndex_.load(std::memory_order_acquire);
            if (read_index_ == writeIndexCache_) {
                return nullptr;
            }
        }
        return &slots_[readIndex + kpadding];

    }

    void pop() noexcept(){
        static_assert(std::is_nothrow_destructible<T>::value,
                    "T must be nothrow destructible");
            
        auto const readIndex = readIndex_.load(std::memory_order_relaxed);

        // implement assert for front to return a non nullptr
        // to occur before pop later

        slots_[readIndex + kPadding].~T();
        const nextReadIndex = readIndex + 1;
        if (nextReadIndex == capacity_) {
            nextReadIndex = 0;
        }
        readIndex_.store(nextReadIndex, std::memory_order_release);
    }


    /*
    Create pointer that is diff between writeIndex and readIndex
    for memory_order_acquire. return the diff used size_t

    if the diff is less than 0, increment diff with capacity_

    hold diff between two pointers which even can be neghative
    */
    [[nodiscard]] size_t size() const noexcept {
        std::ptrdiff_t diff = writeIndex_.load(std::memory_order_acquire) -
                              readIndex_.load(std::memory_order_acquire);
        
        if (diff < 0) {
            diff += capacity_;
        }
        return static_cast<size_t>(diff);
    }

    /*
    Difference between memory order acquiring for writeindex
    and readindex, figure out why it has to be acquire
    */
    [[nodiscard]] bool empty() const noexcept {
        return writeIndex_.load(std::memory_order_acquire) ==
               readIndex_.load(std::memory_order_acquire);
    }

    /*
    Return total capacity with negative indexing
    */
    [[nodiscard]] size_t capacity() const noexcept {
        return capacity_ - 1;
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

    // find out point of capacity and slots
    size_t capacity_;
    T *slots_;

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

    // find out what these variables do
    alignas(KCacheLineSize) std::atomic<size_t> readIndex_ = {0};
    // size_t
    alignas(KCacheLineSize) size_t readIndexCache_ = 0;
    // atomic
    alignas(KCacheLineSize) std::atomic<size_t> writeIndex_ = {0};
    // size_t
    alignas(KCacheLineSize) size_t writeIndexCache_ = 0;
};
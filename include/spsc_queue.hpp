#include <atomic>
#include <iostream>
#include <cstddef> // for size_t 
#include <type_traits> // for is copy constructable
// why do i need RIGTORP_NODISCARD [[nodiscard]]
// lock free single producer, a single consumer circular buffer using 
// atomic operations and memory ordering semantics
#include <concepts>

// std::memory_order semantics quite important and atomics

// important concepts to review before and during coding:
// templates: for a bunch of compile time constant checks? And creating types
// namespaces: One namespace used
// structs
// Concept (optional): Used in c++20 implementation
// manipulating std libraries importing in

class SPSCQueue {
private:

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

    // destructor

    // need to place a noeexcept, as type must have
    // a constructor for the Args argument

    // find out where and how T came from, from type traits library?

    template <typename... Args>
    void emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
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

    template <typename... Args>
    void push_emplace(Args&&... args) noexcept(std::is_nothrow_constructible<T, Args&&...>::value)
    {
        static_assert(std::is_constructible<T, Args&&...>::value,
            "T must be constructible with Args&&...");
    }

    void push() {

    }

    void try_push() {

    }

    void force_push() {

    }

    void pop() {

    }

    void try_pop() {

    }

    // all other functions are size or empty functions/getters/setters
 
};
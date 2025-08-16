#include <atomic>
#include <iostream>
#include <cstddef> // for size_t 
#include <type_traits> // for is copy constructable
// why do i need RIGTORP_NODISCARD [[nodiscard]]
// lock free single producer, a single consumer circular buffer using 
// atomic operations and memory ordering semantics

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
*/
public:

    void emplace() {

    }

    bool try_emplace() {

    }

    void push_emplace() {

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
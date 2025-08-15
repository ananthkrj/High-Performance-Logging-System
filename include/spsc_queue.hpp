// lock free queue implementation (foundation)

// lock free single producer, a single consumer circular buffer using 
// atomic operations and memory ordering semantics

// This is the bottleneck elminator, removes all the locking overhead between
// log producers and writer thread
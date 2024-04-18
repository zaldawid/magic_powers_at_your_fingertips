# DEBUG_ME_06

> ***Warning: the description contains bug spoilers!***

## Description

This program is used for learning advanced debugging techniques. Setting breakpoints with commands and conditional watchpoints are demonstrated. 

## Instructions

The following commands can be demonstrated using this program:

* Creating breakpoints with commands
* Creating location watchpoitns
* Using convenience functions like `$_any_caller_is`
* Debugging multi-threaded programs

## Bugs (SPOILERS)

(Scroll down.)


































There is one small and one big bug in this program. The small one is in the `Pot::add_deposit`. It's a wrong upper bound in the loop that copies deposits. This triggers a SIGABRT because of a `std::bad_alloc`. The big one is a race condition in the experimental `compactor`. This happens in a separate thread and results in damaging the deposits. It can be only observed after five seconds have passed and if there are more than `DEFAULT_COMPACT_LIMIT` (32) deposits.

## Instructions

1. First let's handle simple watches. 
   
    * Run the program, add deposits 2x when asked. 
    * `bt` will show that the program crashes because of an exception being thrown in a `basic_string` function.
    * Extract the suspicious address:
    
        ```bash
        gdb ./debug_me_06
        (gdb) bt
        (gdb) f 13 #(that's one of frames with __str='cannot read memory at...')
        (gdb) p __str
        (gdb) p &__str
        ```
    
    * Set a watchpoint on the address. It's conditional, otherwise there will be 100 hits. This uses a convenience function `$_any_caller_is`. It will most likely hit anyway too soon. Disable it then and set a breakpoint on the line that asks about the deposits. Enable the watchpoint again when this breakpoint is hit and continue.
    
        ```bash
        (gdb) rwatch -location __str if !$_any_caller_is("pot::PotManager::reset")
        (gdb) r
        (gdb) dis 1
        (gdb) tb debug_me_06.cpp:14
        (gdb) ena 1
        (gdb) c
        ```
    
    * This will break at the illegal read of a `std::string` from a memory at `deposits_[16].name_`, which is out of bounds. Fix the upper condition in the loop in the `Pot::add_deposit` function.
    
        ```cpp
        for (size_t i = 0; i < deposits_size_; ++i) {
        ```

2. Demonstrate

    * Setting a watchpoint, an `rwatch` and an `awatch`.
    * Setting a conditional watchpoint.
    * Ignoring a watchpoint.

3. Run the program. Nothing bad will happen, however, if more than `DEFAULT_COMPACT_LIMIT` deposits are added, the compactor will start working. This will result in ruining the deposits_ array. Since this is happening on a separate thread, it's hard to catch it in action. Run the program and when asked for how many times deposits should be added, enter 10. This will trigger the bug after ~5 seconds. You have to wait at the end of the program, when asked to press a key to continue to observe the effects. 
   
   * This bug is hard to catch because it happens in a separate thread. One way of doing it is with:

        ```bash
        gdb ./debug_me_06
        (gdb) tb Pot::size
        (gdb) commands
        watch -location *deposits_ if !($_any_caller_is("main", 20))
        c
        end
        (gdb) r
        ```

        Alternatively, this can be also done with something like:

        ```bash 
        (gdb) tb Pot::size
        (gdb) commands
        watch -location *deposits_ if $_thread != 1
        c
        end
        (gdb) r
        ```

    * When the watchpoint hits, `bt` will show the `compact` function in the trace. Go to it and see what bad it does. It's an unfixable race condition.
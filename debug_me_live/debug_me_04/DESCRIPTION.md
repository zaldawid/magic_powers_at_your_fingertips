# DEBUG_ME_04

> ***Warning: the description contains bug spoilers!***

## Description

This program is used for learning debugging techniques. `gdb` commands like: `backtrace`, `frame`, `disp`, `dprintf`, `call` and `set` are used to debug it. Demonstrating debug print (`dprintf`) is also possible.

## Instructions

The following commands can be demonstrated using this program:

* Loading a core file.
* `bt` and `f`
* `print`
* `disp`, `info disp`, `undisp`
* `dprintf`, `info b`, `del`
* `call` vs `print`
* `set`
* `set $var = ...`

## Bugs (SPOILERS)

(Scroll down.)


































The following bugs are included:

1. In function `Pot::to_lower` the characters are iterated by copy instead of by reference.
2. In function `Pot::add_deposit` the `deposits_size` is pre-incremented instead of post-incremented.
3. In function `Pot::is_contributor` the local deposit variable is not checked for null.
4. `Pot::goal` has a nasty bug related to how the type of the conditional expression is determined. In a nutshell, both the second and third operands are converted to `std::string` before returning the result. Yes, that includes the `goal_`, which already is of type `std::string`. A copy ctor kicks in for it.

## Instructions

1. Debugging a core dump.

    * Run the program. It will crash with a segfault. Run it again but this time make sure the core is dumped:

        ```bash
        ulimit -c unlimited
        ./debug_me_04
        ```

    * The core file will be generated. Run `gdb` with the program and the core file:

        ```bash
        gdb ./debug_me_04 core
        ```

        On Ubuntu, the core file can be found at `/var/lib/apport/coredump`

    * Use `bt` and show how the core can be debugged. The bug happens because `deposit` is null in the `Pot::is_contributor` function. This is because the `deposit` variable is not checked for null when returned from the `Pot::find_deposit` function.

2. Print and debug print demo

    * Run the program again. The sums won't match. 

    * Put a breakpoint in the `Pot::total_for` or something similar and show how printing of arrays works. `p *deposits_@5` will print the first 5 elements of the `deposits_` array.

    * Show how printing of arrays works with `*array@size`.

    * Show the listing of `Pot::add_deposit` function with `l` but briefly.
    * 
    * Demonstrate debug print with `dprintf`.

    * Like this: 

        `dprintf add_deposit,  "BEFORE size: %d, capacity: %d, deposits: %V\n", deposits_size_, deposits_capacity_,  *deposits_@5`
        `dprintf pot.cpp:86,  "AFTER size: %d, capacity: %d, deposits: %V\n", deposits_size_, deposits_capacity_,  *deposits_@'deposits_size_'`

    * Explain `%V` format specifier and printing array elements.

    * Run the program and observe the debug print. No breakpoints are needed.

    * Fix the bug by changing the `deposits_size` increment to post-increment in the `add_deposit` function.


3. Demonstrate `disp` and `call` commands.

    * Run the program. The totals are still off. Put a breakpoint on the `Pot::total_for` function. Now we will do it step-by-step using the `next` command. Use `disp name` `disp deposits_[i]` `disp total` to display the variables on each step. Run the program and observe.

    * Once we are relatively sure it's about `to_lower` function `undisplay` all displays (`info disp` and `undis 1-3`).

    * Time to test if it's really about the `to_lower` function. We are going to call it!

    * Demonstrate `call to_lower(name)` on a name that makes sense. Show how the `name` variable changes.

    * Try calling `to_lower` with a string literal. It won't work. Explain why.

    * Follow with the good solution (slides break):

        ```bash
        set $psv = (std::string_view*)malloc(sizeof(std::string_view))
        call $psv->basic_string_view("HeLlO, wOrLd!")
        set $sv= *$psv
        p $sv
        call to_lower($sv)
        ```

    * Inspect `to_lower` and fix it.
    

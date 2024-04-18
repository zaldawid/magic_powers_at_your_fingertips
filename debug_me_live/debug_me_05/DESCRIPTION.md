# DEBUG_ME_05

> ***Warning: the description contains bug spoilers!***

## Description

This program is used for learning advanced debugging techniques. Passing arguments to the program, but also reverse debugging is show with this demo.

## Instructions

The following commands can be demonstrated using this program:

* Passing arguments to the program.
* Creating catchpoints with `catch throw`.
* Reverse debugging with `record`, `reverse-step`, `reverse-continue`, `reverse-f`, `rs`, `rn`, `rc`.
* Using `rr` for reverse debugging.


## Bugs (SPOILERS)

(Scroll down.)


































The following bugs are included:

1. No check if there are arguments passed to the program.
2. No check if file exists before loading it.
3. In `Pot::goal` the following line cases a nasty bug:

    ```cpp
    return goal_.empty() ? "No goal" : goal_;
    ```

    The return type is `std::string_view` and an ugly conversion kicks in. "No goal" is converted to a temporary `std::string` and the reference is returned. The temporary is destroyed and the reference is invalid. Surprisingly, the same happens for `goal_`. This can be corrected by e.g.:

    ```cpp
    return goal_.empty() ? "No goal"sv : goal_;
    ```

## Instructions

1. Passing arguments to the program.

    * Run the program. It will crash with a SIGABRT. Cool, it looks like it crashed in a library function. `bt` and then do 

        ```bash
        catch throw std::logic_error
        r
        bt
        f 2
        l .
        l -
        f 3
        l .
        p *argv@3
        ```

    * Fix the bug by adding a check for no file.

    * Explain how to pass arguments with `run <args>` or `start <args>` or `set args <args>` and checking them with `info args`. Oh and there is also `gdb --args <program> <args>`.

    * Pass a file that doesn't exist. The program will crash with a SIGSEGV. We could debug it step-by-step. Instead we'll do reverse debugging. `reverse-step` and `reverse-continue` to find the bug!

2. Reverse debugging.

    * Pass a file that doesn't exist. The program will crash with a SIGSEGV. We could debug it step-by-step. Instead we'll do reverse debugging. `reverse-step` and `reverse-continue` to find the bug!
  
    * Do

        ```bash
        start data.txt
        record full
        c
        ```


    * There will be recording errors telling that recording does not support specific instructions. Oops. We need to run `gdb` disabling certain tunables.

        ```bash
        GLIBC_TUNABLES=glibc.cpu.hwcaps=-AVX,-AVX2,-AVX512BW,-AVX512DQ,-AVX512F,-AVX512VL,-BMI1,-BMI2,-LZCNT,-MOVBE,-RTM,-SSE4_1,-SSE4_2,-SSSE3 gdb dbm_05

        (gdb) start
        (gdb) record full
        (gdb) c
        ```

   * We can use `rs`, `rn`, `rc`, and `reverse-f` to debug.

    * `rn` until you see `auto& pot = pm.pot();` as the next line to execute.

    * `info locals` to see the pot manager with a null pot in it.
    
    * `rs` now, we need to get into the loading function.
    
    * `reverse-f`, `reverse-f` to get out of the string functions. Now we are in the `PotManager::load` function.
    
    * A couple of `rs` will get us to the check of `if (std::ifstream in{file_name})`. Examine the source code at this point.
    
    * The bug is obvious. The `pot` is not created if the file does not exist. 
  
3. Demo `rr`

    * First:

        ```bash
        sudo sysctl kernel.perf_event_paranoid=1
        ```

    * Then:

        ```bash
        rr dbm_05 info.txt
        (rr) b main
        (rr) c
        ```

    * And rinse and repeat the steps from the previous point.

# DEBUG_ME_03

> ***Warning: the description contains bug spoilers!***

## Description

This program is used for learning basic debugging techniques. `gdb` commands like: `break`, `backtrace`, `frame`, `info locals`, `info args` and `catch` are used to debug it. Demonstrating debug print (`dprintf`) is also possible.

## Instructions

The following commands can be demonstrated using this program:

* `start`
* `break`
* `bt`
* `frame`
* `info locals`
* `info args`
* `catch`

## Bugs (SPOILERS)

(Scroll down.)

































The following bugs are included:

1. In the `main` function the `n` value is not checked before passing it to the `generate` function. This causes an exception when calling `std::vector::reserve` if n is negative.

2. The `generate` has `char` as the argument type. This causes an overflow when the `n` value is greater than 127.

3. The `generate` function doesn't use `push_back`, it directly writes to the allocated cache's storage, breaking the vector's invariant.

## Instructions

1. SEGFAULT demo
   
    * Run the program and enter `-1` when asked for a number. 
    * The program will segfault because of dereferencing a null pointer. This is cause the vector not being initialized properly (there is a call to `reserve(n + 1)`, which does nothing for n=-1). The dereference happens in the `get_cached` function when -1 index is requested from the `cache` vector.

    * Examine with `bt`, `frame`, `info locals`, `info args`.
    * Fix the bug by checking the `n` value before calling `generate`.
  
        ```cpp
        if (n < 0) {
            return 0;
        }
        ```

2. Exception demonstration

    * Run the program and enter `130` when asked for a number. 
    * The program will crash because of the overflow in the `generate` function. The `char` type is used for the `n` argument, which causes the overflow. Consequently, resizing the vector with a negative value causes an exception.
    * It's possible to show `catch throw` in action.
    * Examine with `bt`, `frame`, `info locals`, `info args`.
    * Fix the bug by changing the `char` type to `int` in the `generate` function. Or better yet, `size_t`.

3. Frame functionality

    * Run the program again. All should function correctly now. 
    * When using `frame` notice that the `cache` size is inconsistent with the `n` value. This is caused by not using `push_back` in the `generate` function. 
    * Fix this bug by using `push_back` in the `generate` function.


4. Alternatively show how to use `dprintf` to debug here.

    * Demonstrate debug print with `dprintf`.
    * Like this: `dprintf <line> "Cache size is: %d, capacity is: %d, data is: %p, first elements are %V\n", cache.size(), cache.capacity(), cache._M_impl._M_start, *cache._M_impl._M_start@10`
    * Explain `%V` format specifier and printing array elements.
    * Fix the bug by using `push_back` in the `generate` function.

#include <vector>
#include <iostream>
#include <optional>

class FibonacciGenerator 
{
public:
  using value_type = unsigned long long;

  struct result_type
  {
    value_type value;
    bool cached;
    friend std::ostream& operator<<(std::ostream& os, const result_type& r)
    {
      return os << r.value << (r.cached ? " (cached)" : "");
    }
  };

  static FibonacciGenerator& getInstance()
  {
    static FibonacciGenerator instance{};
    return instance;
  }

  FibonacciGenerator(FibonacciGenerator const&) = delete;
  void operator=(FibonacciGenerator const&) = delete;

  result_type generate(char n)
  {
    if (auto cached_value = get_cached(n))
    {
      return {.value=cached_value.value().value, .cached=true};
    }

    cache.reserve(n + 1);

    for (int i = cache.size(); i <= n; i++)
    {
      if (i == 0) cache[0] = 0;
      else if (i == 1) cache[1] = 1;
      else cache[i] = cache[i - 1] + cache[i - 2];
    }

    return { .value=cache[n], .cached=false};
  }

private:

  std::optional<result_type> get_cached(std::size_t n)
  {
    if (n < cache.size())
    {
      return result_type{cache[n], true};
    }
    return std::nullopt;
  }

  std::vector<value_type> cache{};

  FibonacciGenerator() {}
};

int main() 
{
  std::cout << "Enter a number n to compute the n-th Fibonacci number (negative number to quit):";
  auto& fib_gen = FibonacciGenerator::getInstance();
  auto  n{0};
  do
  {
    std::cin >> n;
    auto Fn = fib_gen.generate(n);
    std::cout << "The fibonacci number F_[" << n << "] = " <<  Fn << '\n';
    std::cout << "Enter a new number: ";
  } while (n >= 0);
}


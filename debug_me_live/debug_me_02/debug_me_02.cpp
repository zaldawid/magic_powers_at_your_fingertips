#include <vector>
#include <numeric>
#include <cstdlib>


auto sum(const auto& range)
{
  auto sum = std::accumulate(range.begin(), range.end(), 0);
  return sum;
}

auto make_fib(int n)
{
  std::vector fib = {0, 1};
  for (int i = 2; i <= n; ++i)
  {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  return fib;
}

int main()
{
  auto fib = make_fib(10);
  
  auto sum_fib = sum(fib);

  return (sum_fib == 88) ? EXIT_SUCCESS : EXIT_FAILURE;
}
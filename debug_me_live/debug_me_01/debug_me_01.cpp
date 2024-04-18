#include <array>
#include <iostream>

constexpr auto ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING = 42;

int main()
{
  std::array numbers{ 0017,
                      0025,
                      1764 };


  std::cout << "Result: " << (numbers[2] / (numbers[0] + numbers[1])) << '\n';
  
  if (ANSWER_TO_THE_ULTIMATE_QUESTION_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING ==
      numbers[2] / (numbers[0] + numbers[1]))
  {
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;  
}
#include <range/v3/all.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

using namespace ranges;

std::vector<std::string> split(const std::string& str) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, ' ')) {
    tokens.push_back(token);
  }
  return tokens;
}

std::map<std::string, size_t> count_words(std::vector<std::string> const& words)
{
    auto wordCount = std::map<std::string, size_t>{};
    for (auto const& word : words) {
        ++wordCount[word];
    }
    return wordCount;
}

std::map<std::string, size_t> process(const std::string& str) {
  return count_words(split(str));
}

std::map<std::string, size_t> process_with_ranges(const std::string& str) {
  return count_words(str | view::split(' ') | to<std::vector<std::string>>);
}

int main(int argc, char* argv[]) {
  std::string str = "hello world hello";
  // generate random string of 1000 words
  for (int i = 0; i < 100000; ++i) {
    str += " " + std::to_string(rand() % 1000);
  }


  std::cout << "DEFAULT =====================" << std::endl;
  // count initial time for the default algorithm
  auto time = std::chrono::high_resolution_clock::now();
  auto result = process(str);
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
  // for (auto& p : result) {
  //   std::cout << p.first << " " << p.second << std::endl;
  // }
  std::cout << "Duration: " << duration.count() << " microseconds" << std::endl;

  std::cout << "RANGES =====================" << std::endl;
  // count initial time for the ranges algorithm
  time = std::chrono::high_resolution_clock::now();
  auto result2 = process_with_ranges(str);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time);
  // for (auto& p : result2) {
  //   std::cout << p.first << " " << p.second << std::endl;
  // }
  std::cout << "Duration: " << duration.count() << " microseconds" << std::endl;

  std::cout << "============================" << std::endl;

  // DEFAULT =====================
  // Duration: 26049780 microseconds
  // RANGES =====================
  // Duration: 27588901 microseconds

  return 0;
}
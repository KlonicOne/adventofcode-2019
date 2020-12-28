/**
 * @file day14.cpp
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "day14.h"
#include "show_container.h"

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <time.h>
#include <vector>

using namespace std;

#define DEBUG_OUT false

/**
 * @brief constructor
 *
 */
day14::day14(/* args */) { this->m_sum_mem = 0; }

/**
 * @brief Destroy the day14::day14
 *
 */
day14::~day14() {}

/**
 * @brief Solve part 1
 *
 */
void day14::solver_part1(void) {
  unsigned long long answer = 0;

  // Loop through format input and apply the masks to store value
  for (auto iter : this->m_format_input) {
    // Take input value from mem input
    for (auto iter_mem : iter.mem_entry) {
      unsigned long address = iter_mem.first;
      unsigned long value = iter_mem.second;
      // Apply set mask
      value = value | iter.set_mask;
      // Apply reset mask
      value = value & iter.reset_mask;
      // Saturate to 36 bit
      value = value & SAT_MASK;
      // Store in mem
      this->m_mem[address] = value;
    }
  }

  answer = this->calc_sum_mem();

  if (DEBUG_OUT) {
    std::cout << "Memory content: " << std::endl;
    for (auto iter : this->m_mem) {
      std::cout << "[" << std::dec << iter.first << "]: " << iter.second
                << std::endl;
    }
  }

  // Out result
  std::cout << "Result Part1: " << std::dec << answer << std::endl;
}

/**
 * @brief Solve part 2
 *
 */
void day14::solver_part2(void) {
  long answer = 0;

  // Out result
  std::cout << "Result Part2: " << answer << std::endl;
}

/************************************************************/
/************************************************************/
/************************************************************/

/**
 * @brief Split the intput string and store in class code list
 *
 * @param inTable
 */
void day14::format_input(std::vector<std::string> inTable) {
  int line_num = 0;
  bool first_found = false;
  std::string string_line = "";
  t_input_element temp_input_element;

  for (std::vector<std::string>::const_iterator i = inTable.begin();
       i != inTable.end(); ++i, ++line_num) {
    std::size_t found;
    std::size_t found_enclosing;

    // Get single line as string_line
    string_line = (*i);

    // Skip empty line
    if (string_line == "") {
      continue;
    }

    // Check if new input element is found starting with mask
    found = string_line.find("mask");
    if (found != std::string::npos) {
      // Add last content if not very first element
      if (first_found) {
        // Add element because we found first one
        this->m_format_input.push_back(temp_input_element);
      }

      // Clear last content
      temp_input_element.set_mask = 0;
      temp_input_element.reset_mask = 1;
      temp_input_element.mem_entry.clear();

      // Get the masks mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
      std::string mask = string_line.substr(found + 7, 36);

      // Store masks in temp element
      temp_input_element.set_mask = get_set_mask(mask);
      temp_input_element.reset_mask = get_reset_mask(mask);

      // We found first one
      first_found = true;
    } else {
      // Memory to be added on the input element
      found = string_line.find("mem[");
      found_enclosing = string_line.find("]");

      // Extract address mem[7] = 101
      unsigned long adr =
          stoi(string_line.substr(found + 4, found_enclosing - (found + 4)));
      found = string_line.find("=");
      // Extract value for address
      unsigned long val =
          stoi(string_line.substr(found + 1, std::string::npos - (found + 1)));
      // Now add to mem
      temp_input_element.mem_entry[adr] = val;
    }
  }

  // Add last element to format input
  this->m_format_input.push_back(temp_input_element);

  // Debug out the formatted input
  if (DEBUG_OUT) {
    std::cout << "Format input: " << std::endl;
    for (auto iter_input : this->m_format_input) {
      std::cout << "set: " << std::hex << iter_input.set_mask;
      std::cout << ", reset: " << std::hex << iter_input.reset_mask
                << std::endl;
      for (auto iter : iter_input.mem_entry) {
        std::cout << "[" << std::dec << iter.first << "]: " << iter.second
                  << std::endl;
      }
    }
  }
}

/**
 * @brief Get the mask as integer value from string
 *
 * @param str input as string
 * @return unsigned long mask to set bits
 */
unsigned long day14::get_set_mask(std::string str) {
  unsigned long ret_val = 0;

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '1') {
        ret_val = ret_val | (1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Get the mask as integer from string value
 *
 * @param str input as string
 * @return unsigned long reset mask
 */
unsigned long day14::get_reset_mask(std::string str) {
  unsigned long ret_val = SAT_MASK; // Set all lower 36 bit

  if (str != "") {
    for (int i = 0; i < str.size(); ++i) {
      if (str.at(str.size() - 1 - i) == '0') {
        ret_val = ret_val & ~(1ULL << i);
      }
    }
  }

  return (ret_val);
}

/**
 * @brief Calculate the sum over the memory and return it
 *
 * @return unsigned long
 */
unsigned long long day14::calc_sum_mem(void) {
  unsigned long long ret_val = 0;

  for (auto iter : this->m_mem) {
    ret_val += iter.second;
  }

  this->m_sum_mem = ret_val;
  return (ret_val);
}
/**
 * @file day03.h
 * @author klonicone
 * @version 0.1
 * @date 2020-12-01
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef _DAY03_H_
#define _DAY03_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> map_element_t;

#define XDIM (1024)
#define YDIM (512)
#define ZDIM (2) 

class day03 {
 private:
  /* data */
  // max positiond in dimensions
  int m_ydim;
  int m_xdim;
  int m_zdim;

  map_element_t current_pos;               // position of mower
  std::vector<map_element_t> m_path;       // path trhough map with value
  int m_tree_map[XDIM][YDIM][ZDIM];  // Map with tree info on z dim !!! seg fault ???
  int m_map_multiplier;  // how often is the map repeated to right
  int slope_right;       // input from puzzle
  int slope_down;        // intput from puzzle

  int found_trees;  // result with found trees on path

 public:
  day03(/* args */);
  ~day03();

  void solver_part1(void);
  void solver_part2(void);

  // part 1
  void create_map(std::vector<std::string> inTable);
  void calc_path(void);
  void calc_trees_on_path(void);
};

#endif  // _DAY03_H_
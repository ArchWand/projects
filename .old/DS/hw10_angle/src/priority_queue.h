#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>

#include "image.h"

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
    //
    // ASSIGNMENT: Implement this function
    //
    m_heap = values;
    for (unsigned int i = m_heap.size() / 2 - 1; i >= 0; i--) {
      percolate_down(i);
    }
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(int i) { return (2*i)+1 < size(); }
  bool has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }

  // adds location to vector of red pixels
  void add_to_red(int x, int y) {
    red_marks.push_back(std::make_pair(x, y));
  }

  // adds location to vector of black pixels
  void add_to_black(int x, int y) {
    black_marks.push_back(std::make_pair(x, y));
  }

  // removes location from vector of red pixel locations
  void remove_red(int x, int y) {
    std::vector<std::pair<int, int> >::iterator it = red_marks.begin();
    for ( ; it != red_marks.end(); it++) {
      if ((*it).first == x && (*it).second == y) {
        red_marks.erase(it);
        break;
      }
    }
  }

  // checks if the pixel is red
  bool is_red(int x, int y) {
    int vec_size = red_marks.size();
    for (int i = 0; i < vec_size; i++) {
      if (x == red_marks[i].first && y == red_marks[i].second) {
        return true;
      }
    } 
    return false;
  }

  // checks if the pixel is black
  bool is_black(int x, int y) {
    int vec_size = black_marks.size();
    for (int i = 0; i < vec_size; i++) {
      if (x == black_marks[i].first && y == black_marks[i].second) {
        return true;
      }
    }
    return false;
  }
  
 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;
  // vectors of marks
  std::vector<std::pair<int, int> > red_marks;
  std::vector<std::pair<int, int> > black_marks;

  // private helper functions
  void percolate_up(int i) {
    while (i > 0 && *m_heap[i] < *m_heap[get_parent(i)]) {
      // swap the element with its parent
      DistancePixel* tmp = m_heap[i];
      m_heap[i] = m_heap[get_parent(i)];
      m_heap[get_parent(i)] = tmp;
      // update backpointers for the swapped elements
      backpointers[m_heap[i]] = i;
      backpointers[m_heap[get_parent(i)]] = get_parent(i);
      i = get_parent(i);
    }
  }
  
  void percolate_down(int i) {
    while (has_left_child(i)) {
      int smallest_child_index = get_left_child(i);
      if (has_right_child(i) && *m_heap[get_right_child(i)] < *m_heap[smallest_child_index]) {
        smallest_child_index = get_right_child(i);
      }
      if (*m_heap[i] < *m_heap[smallest_child_index]) {
        break;
      } else {
        // swap the element with its smallest child
        DistancePixel* tmp = m_heap[i];
        m_heap[i] = m_heap[smallest_child_index];
        m_heap[smallest_child_index] = tmp;
        // update backpointers for the swapped elements
        backpointers[m_heap[i]] = i;
        backpointers[m_heap[smallest_child_index]] = smallest_child_index;
        i = smallest_child_index;
      }
    }
  }
};

#endif

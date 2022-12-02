#include <cmath>
#include <list>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

enum SortingMethod { unsorted, length, value };

bool stringLessValue(string a, string b) {
  for (int i = 0; i < a.length() && i < b.length(); i++) {
    if (a.at(i) == b.at(i)) {
      continue;
    }
    if (a.at(i) < b.at(i)) {
      return true;
    }
    return false;
  }

  return false;
}

bool stringLessLength(string a, string b) { return a.length() < b.length(); }

class SortedList {
private:
  SortingMethod sortingMethod;
  list<string> values;

public:
  SortingMethod getSortingMethod() const { return sortingMethod; }

  void addSorted(string string) {
    values.push_back(string);
    sort();
  }

  void remove(string string) {
    values.remove(string);
  }

  void removeAll() {
    values.clear();
  }

  bool sortedByLength() const {
    return getSortingMethod() == SortingMethod::length;
  }

  bool sortedByValue() const {
    return getSortingMethod() == SortingMethod::value;
  }

  int length() const {
    return values.size();
  }

  vector<string> string_values() const {
    vector<string> result;

    for (string value : values) {
        result.push_back(value);
    }

    return result;
  }

  string at(int i) const {
    return string_values().at(i);
  }

  void sortByLength() {
    sortingMethod = SortingMethod::length;
    sort();
  }

  void sortByValue() {
    sortingMethod = SortingMethod::value;
    sort();
  }

  void sort() {
    if (sortingMethod == SortingMethod::unsorted) {
      sortingMethod = SortingMethod::length; // Sort by length by default
    }

    if (sortingMethod == SortingMethod::value) {
      values.sort(stringLessValue);
    }
    
    if (sortingMethod == SortingMethod::length) {
        values.sort(stringLessLength);
    }
  }

  SortedList() : sortingMethod(SortingMethod::unsorted) {}
  SortedList(const SortedList &original) {
    sortingMethod = original.getSortingMethod();
    values = original.values;
  }
  SortedList(SortingMethod sortingMethod) : sortingMethod(sortingMethod) {}
};
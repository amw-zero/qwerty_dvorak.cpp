#include <iostream>
#include <fstream>
#include <vector>
#include <map>

inline std::string to_dvorak(std::string& qwerty, std::map<char, char>& map) {    
    std::string ret;
    for (auto c : qwerty) {
      ret += map[c];
    }

    return ret;
}

int main() {

  std::map<char, char> q_to_d = {
    {'a', 'a'},
    {'b', 'x'},
    {'c', 'j'},
    {'d', 'e'},
    {'f', 'u'},
    {'g', 'i'},
    {'h', 'd'},
    {'i', 'c'},
    {'j', 'h'},
    {'k', 't'},
    {'l', 'n'},
    {'m', 'm'},
    {'n', 'b'},
    {'o', 'r'},
    {'p', 'l'},
    {'r', 'p'},
    {'s', 'o'},
    {'t', 'y'},
    {'u', 'g'},
    {'v', 'k'},
    {'x', 'q'},
    {'y', 'f'}
  };

  std::ifstream dict("/usr/share/dict/words");
  std::string line;
  std::string converted;
  std::vector<std::string> lines;

  while(std::getline(dict, line)) {
    std::size_t e = line.find("e");
    std::size_t q = line.find("q");
    std::size_t w = line.find("w");
    std::size_t z = line.find("z");

    std::size_t E = line.find("E");
    std::size_t Q = line.find("Q");
    std::size_t W = line.find("W");
    std::size_t Z = line.find("Z");

    if ( e == std::string::npos && q == std::string::npos && w == std::string::npos && z == std::string::npos
        && E == std::string::npos && Q == std::string::npos && W == std::string::npos && Z == std::string::npos) {
          lines.push_back(line);
    }
  }

  std::map<std::string, bool> index;
  for (auto line : lines) {
    index[line] = true;
  }

  for (auto line : lines) {
    converted = to_dvorak(line, q_to_d);
    if (index[converted] == true) {
      std::cout << line << "  |  " << converted << std::endl;
    }
  }
}

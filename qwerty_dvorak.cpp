#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include <vector>

typedef std::vector<std::string>::iterator words_iter;

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
    std::vector<std::string> valid_dict;
    std::vector<std::string> full_dict;
    
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
            valid_dict.push_back(line);
        }
        full_dict.push_back(line);
    }
    
    
    // Create Index
    std::map<std::string, bool> index;
    for (auto line : full_dict) {
        index[line] = true;
    }
    
    // Divide
    // |--- | ---- |--- | --- |
    const int NUM_THREADS = 4;
    const unsigned long size = full_dict.size();
    const unsigned long chunk = size / NUM_THREADS;
    std::cout << "Chunk size: " << chunk << std::endl;
    
    std::vector<std::thread> workers;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        words_iter start = full_dict.begin() + i * chunk;
        words_iter end = full_dict.begin() + ((i + 1) * chunk) - 1;
        
        if (i == NUM_THREADS - 1) {
            end = full_dict.end();
        }
        
        // Conquer
        
        workers.push_back(std::thread([&q_to_d, &index, start, end, i]() {
            for (words_iter i = start; i != end; i++) {
                std::string converted = to_dvorak(*i, q_to_d);
                if (index[converted] == true) {
                    std::cout << *i << "  |  " << converted << std::endl;
                }
            }
        }));
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        workers[i].join();
    }
}

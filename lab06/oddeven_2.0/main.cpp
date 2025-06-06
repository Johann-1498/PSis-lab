#include "OddEvenSort.h"
#include <iostream>
#include <string>

void Usage(const std::string& prog_name) {
    std::cerr << "usage: " << prog_name << " <n> <g|i|f> [filename]\n";
    std::cerr << "   n:       number of elements in list\n";
    std::cerr << "  'g':      generate list using a random number generator\n";
    std::cerr << "  'i':      user input list\n";
    std::cerr << "  'f':      read list from a text file\n";
    std::cerr << "  filename: required only if using 'f'\n";
}

int main(int argc, char* argv[]) {
    if ((argc != 3 && argc != 4) || (argv[2][0] == 'f' && argc != 4)) {
        Usage(argv[0]);
        return 1;
    }

    int n = std::stoi(argv[1]);
    char mode = argv[2][0];

    if (n <= 0 || (mode != 'g' && mode != 'i' && mode != 'f')) {
        Usage(argv[0]);
        return 1;
    }

    OddEvenSorter sorter(n);

    if (mode == 'g') {
        sorter.generateList();
        sorter.printList("Before sort");
    } else if (mode == 'i') {
        sorter.readList();
    } else if (mode == 'f') {
        std::string filename = argv[3];
        if (!sorter.readFromFile(filename)) {
            std::cerr << "Error: Unable to read from file '" << filename << "'\n";
            return 1;
        }
    }

    sorter.sort();
    sorter.printList("After sort");

    return 0;
}

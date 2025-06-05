#include "OddEvenSort.h"
#include <iostream>
#include <string>

void Usage(const std::string& prog_name) {
    std::cerr << "usage: " << prog_name << " <n> <g|i>\n";
    std::cerr << "   n:   number of elements in list\n";
    std::cerr << "  'g':  generate list using a random number generator\n";
    std::cerr << "  'i':  user input list\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        Usage(argv[0]);
        return 1;
    }

    int n = std::stoi(argv[1]);
    char mode = argv[2][0];

    if (n <= 0 || (mode != 'g' && mode != 'i')) {
        Usage(argv[0]);
        return 1;
    }

    OddEvenSorter sorter(n);

    if (mode == 'g') {
        sorter.generateList();
        sorter.printList("Before sort");
    } else {
        sorter.readList();
    }

    sorter.sort();
    sorter.printList("After sort");

    return 0;
}

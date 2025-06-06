#ifndef ODD_EVEN_SORTER_HPP
#define ODD_EVEN_SORTER_HPP

#include <vector>
#include <string>
#include <mutex>

class OddEvenSorter {
private:
    std::vector<int> list;
    std::mutex mtx;
    const int RMAX = 100;

public:
    OddEvenSorter(int n);
    void generateList();
    void readList();
    void printList(const std::string& title) const;
    void sort();
    void printCurrentStep(int phase) const;

    bool readFromFile(const std::string& filename); // lectura de archivos

};

#endif

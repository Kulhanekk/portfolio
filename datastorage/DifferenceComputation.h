//
// Created by ASUS on 30.09.2026.
//

#ifndef DATASTORAGEHOMEWORK_DIFFERENCECOMPUTATION_H
#define DATASTORAGEHOMEWORK_DIFFERENCECOMPUTATION_H
#include <vector>

void computeDifference(const std::vector<std::vector<int> > &records,
                       std::vector<std::vector<int> > &differences);

void printDifferences(const std::vector<std::vector<int> > &differences);

void computeDifferenceSeq(const std::vector<std::vector<int> > &records,
                       std::vector<std::vector<int> > &differences);


#endif //DATASTORAGEHOMEWORK_DIFFERENCECOMPUTATION_H

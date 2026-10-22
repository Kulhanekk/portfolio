#include <vector>

#include "DifferenceComputation.h"
#include "primsAlg.h"
#include "Utils.h"

using namespace std;

void printInput(vector<vector<int>> input) {
    for (auto record : input) {
        for (auto i : record) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    auto programArguments = ProgramArguments::Parse(argc, argv);

    // The input records, e.g., records[0] is the first record in the input file.
    vector<vector<int>> records = readRecords(programArguments.mInputFilePath);
    // printInput(records);

    vector<vector<int>> differences;
    computeDifference(records, differences);
    // printDifferences(differences);
    int treeCost = calculateMstValue(differences);

    cout << treeCost << endl;
    writeCost(treeCost, programArguments.mOutputFilePath);
}

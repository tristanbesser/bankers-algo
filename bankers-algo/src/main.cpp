#include <iostream>
#include <fstream>
#include <string>

const int P = 5; // number of processes
const int R = 3; // number of resource types

bool safeState(int avail[], int max[][R], int alloc[][R], int *safeSeq);

int main() {

    std::ifstream input("input.txt"); // The stream for input
    // Make sure the file opens correctly
    if (!input.is_open()) {
        std::cerr << "Could not open input file, exiting." << std::endl;
        exit(1);
    }

    int avail_[R];
    int alloc_[P][R];
    int max_[P][R];

    // get input for available resources
    for (int r = 0; r < R; ++r) {
        input >> avail_[r];
    }

    // Output available vector
    std::cout << "Available:" << std::endl;
    for (int r = 0; r < R; ++r) {
        std::cout << avail_[r] << ' ';
    }
    std::cout << std::endl << std::endl;

    // get input for allocated vector
    for (int p = 0; p < P; ++p) {
        for (int r = 0; r < R; ++r) {
            input >> alloc_[p][r];
        }
    }

    // Output Allocated Matrix
    std::cout << "Allocated:" << std::endl;
    for (int p = 0; p < P; ++p) {
        for (int r = 0; r < R; ++r) {
            std::cout << alloc_[p][r] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // get input for max
    for (int p = 0; p < P; ++p) {
        for (int r = 0; r < R; ++r) {
            input >> max_[p][r];
        }
    }

    // Output Max Matrix
    std::cout << "Max:" << std::endl;
    for (int p = 0; p < P; ++p) {
        for (int r = 0; r < R; ++r) {
            std::cout << max_[p][r] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    input.close();

    int *safeSeq = new int[P]; // safe sequence

    bool safe = safeState(avail_, max_, alloc_, safeSeq);

    // if the system is in safe state, output safe sequence
    if (safe) {

        std::cout << "The system is in a safe state!" << std::endl;
        std::cout << "The safe sequence is: ";
        for (int p = 0; p < P; ++p) {
            if (p < P - 1)
                std::cout << 'P' << safeSeq[p] << " ~ ";
            else std::cout << 'P' << safeSeq[p] << std::endl;
        }
    }
    else {
        std::cout << "The system is not in a safe state!" << std::endl;
    }
}

bool safeState(int avail[], int max[][R], int alloc[][R], int *safeSeq) {

    // Calculate the need matrix
    int need[P][R];
    for (int p = 0; p < P; ++p) {
        for (int r = 0; r < R; ++r) {

            // Need = Max - Allocated
            need[p][r] = max[p][r] - alloc[p][r];
        }
    }

    // work = available
    int work[R];
    for (int r = 0; r < R; ++r) {
        work[r] = avail[r];
    }

    // finish[i] = false for i = 0, 1, ..., P - 1
    bool finish[P] = {false};

    int count = 0;
    while (count < P) {

        // Find an i such that both:
        // (a) Finished[i] = false
        // (b) Need[i] <= Work
        bool found = true;
        for (int p = 0; p < P; ++p) {
            // Check if Finished[i] is false
            if (finish[p] == false) {

                // check if need[i] <= work for all of the current process
                int r;
                for (r = 0; r < R; ++r) {
                    if (need[p][r] > work[r]) break;
                }

                if (r == R) {
                    // Work = Work + Allocation
                    for (int k = 0; k < R; ++k) {
                        work[k] += alloc[p][k];
                    }

                    safeSeq[count] = p; // store safe sequence
                    ++count;

                    // Finish[i] = true
                    finish[p] = true;
                }
                else found = false;
            }
        }
    }

    // If Finish [i] == true for all i, then the system is in a safe state
    bool safe = true;
    for (int p = 0; p < P; ++p) {
        safe = finish[p];
    }
    return safe;
}
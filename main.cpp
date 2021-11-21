#include <array>
#include <algorithm>
#include <cmath>
#include <random>
#include <cstdlib>
#include <iostream>


int main() {

    int Q = 4; //Q value; differs from 0 to 15
    int Num = 10e4; //num of experiments; from 0 up to infinity

    int N = 100; //num of users

    int S = 0; //success counter
    int E = 0; //empty counter
    int C = 0; //conflict counter

    uint64_t counter = 0; //counter of successful frames

    double out = 0.00;

    int r = 0; //randomizing tags window in frame
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, RAND_MAX);
    //4 is 2^Q param, this array stores nums of windows in frame, need's to change after changing Q
    std::array<int,16> a;
    for (int j = 1; j <= Num; ++j) {
        N=100;
        while ( N > 0) {
            std::fill(a.begin(), a.end(), 0);

            S = 0;
            C = 0;
            E = 0;
            //generating random window for every tag
            for (int l = 0; l < N; ++l) {
                r = distribution(generator) % (int) pow(2, Q);
                a[r]++;
            }

            //calculating nums of tags in frame windows
            for (int k = 0; k < pow(2, Q); ++k) {
                if (a[k] > 1)C++;
                if (a[k] == 1) {
                    S++;
                    --N;
                }
                if (a[k] == 0) E++;
            }
            counter++;
        }
        if(j%100==0) {std::cout << "Num is: " << j << "\n";}
    }
    out = (double)counter/Num;
    std::cout  << " " << Q << " " << counter << " " << out << "\n";
    return 0;
}
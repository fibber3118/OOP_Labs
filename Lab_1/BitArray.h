#ifndef LAB_1_BITARRAY_H
#define LAB_1_BITARRAY_H

#include <iostream>
#include <cmath>
#include <vector>

namespace bitarray {
    class BitArray {
    public:
        explicit BitArray(int num_bits, unsigned long value = 0);
        void swap(BitArray& b);
        BitArray& operator=(const BitArray& b);
        void resize(int num_bits, bool value = false);


    private:
        std::vector<unsigned long> array;
        int num_bits_used;
        int num_bits_free;
        static const int BITS_IN_WORD = sizeof(unsigned long);

    };
} // bitarray

#endif //LAB_1_BITARRAY_H
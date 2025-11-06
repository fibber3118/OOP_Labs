#include "BitArray.h"


namespace bitarray {
    BitArray::BitArray(int num_bits, unsigned long value) {
        if (num_bits <= 0) {
            throw std::invalid_argument("invalid num_bits");
        }
        int count_word = ceil(static_cast<double>(num_bits) / BITS_IN_WORD);
        num_bits_used = num_bits;
        num_bits_free = count_word * BITS_IN_WORD - num_bits;
        array.resize(count_word);
        array[0] = value;
        size_t unused_bits = BITS_IN_WORD - (count_word % BITS_IN_WORD);
        if (unused_bits != BITS_IN_WORD) {
            unsigned long mask = ~0UL >> unused_bits;
            array[count_word - 1] &= mask;
        }
    }

    void BitArray::swap(BitArray &b) {
        std::swap(array, b.array);
        std::swap(num_bits_free, b.num_bits_free);
        std::swap(num_bits_used, b.num_bits_used);
    }

    BitArray &BitArray::operator=(const BitArray &b) {
        if (this == &b) {
            return *this;
        }
        BitArray tmp(b);
        swap(tmp);
        return *this;
    }

    void BitArray::resize(int num_bits, bool value) {
        if (num_bits < 0) {
            throw std::invalid_argument("num_bits < 0");
        }
        if (num_bits == num_bits_used) {
            return;
        }
        if (num_bits < num_bits_used) {
            int old_num_words = (num_bits_used + BITS_IN_WORD - 1) / BITS_IN_WORD;
            int new_num_words = (num_bits + BITS_IN_WORD - 1) / BITS_IN_WORD;
            int unused_bits_in_last_word = BITS_IN_WORD - (num_bits % BITS_IN_WORD);
            if (unused_bits_in_last_word != BITS_IN_WORD) {
                unsigned long mask = ~0UL >> unused_bits_in_last_word;
                array[new_num_words - 1] &= mask;
            }
            if (new_num_words < old_num_words) {
                array.resize(new_num_words);
            }
            num_bits_used = num_bits;
            num_bits_free = new_num_words * BITS_IN_WORD - num_bits_used;
            return;
        }
        int old_num_words = (num_bits_used + BITS_IN_WORD - 1) / BITS_IN_WORD;
        int new_num_words = (num_bits + BITS_IN_WORD - 1) / BITS_IN_WORD;
        int num_new_bits = num_bits - num_bits_used;
        if (new_num_words > old_num_words) {
            array.resize(new_num_words);
        }
        int current_word_idx = old_num_words - 1;
        int first_new_bit_pos = num_bits_used % BITS_IN_WORD;
        if (first_new_bit_pos != 0 || num_bits_used == 0) {
            if (value) {
                int bits_to_set_in_current_word = BITS_IN_WORD - first_new_bit_pos;
                unsigned long set_mask = (~0UL << first_new_bit_pos);
                if (current_word_idx == new_num_words - 1) {
                    int unused_bits_in_last_word = BITS_IN_WORD - (num_bits % BITS_IN_WORD);
                    if (num_bits % BITS_IN_WORD != 0) {
                        unsigned long clear_mask = ~0UL >> unused_bits_in_last_word;
                        set_mask &= clear_mask;
                    }
                }
                array[current_word_idx] |= set_mask;
            }
            current_word_idx++;
        }
        if (value) {
            for (int i = current_word_idx; i < new_num_words - 1; ++i) {
                array[i] = ~0UL;
            }
            if (current_word_idx <= new_num_words - 1) {
                int unused_bits = new_num_words * BITS_IN_WORD - num_bits;
                unsigned long mask = ~0UL;
                if (unused_bits > 0) {
                    mask = ~0UL >> unused_bits;
                }
                array[new_num_words - 1] = mask;
            }
        }
        num_bits_used = num_bits;
        num_bits_free = new_num_words * BITS_IN_WORD - num_bits_used;
    }
} // bitarray

#include <gtest/gtest.h>
#include "BitArray.h"
using namespace bitarray;


TEST(BitArrayTest, Test1) {
    BitArray a(1, 1);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.size(), 1);
    ASSERT_EQ(a[0], 1);
}

TEST(BitArray_Resize_Test, inc_test) {
    BitArray a(1, 1);
    a.resize(40);
    ASSERT_EQ(a.size(), 40);
    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[2], 0);
}

TEST(BitArray_Resize_Test, dec_test) {
    BitArray a(50, true);
    a.resize(10);
    ASSERT_EQ(a.size(), 10);
}

TEST(BitArray_Push_Test, PushBack) {
    BitArray a(3, 0b101);
    a.push_back(false);
    ASSERT_EQ(a[3], 0);
    a.push_back(true);
    ASSERT_EQ(a[4], 1);
}

TEST(BitArray_Swap_Test, swap) {
    BitArray a(2, 0b10);
    BitArray b(3, 0b110);
    a.swap(b);
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(b.size(), 2);
    ASSERT_EQ(b[1], 0);
    ASSERT_EQ(a[2], 0);
}

TEST(BitArray_OperatorEQ_Test, EQ) {
    BitArray a(2, 0b10);
    BitArray b(2, 0b10);
    ASSERT_EQ(a==b, 1);
    BitArray c(3, 0b111);
    ASSERT_EQ(a==c, 0);
}

TEST(BitArray_OperatorAssingment_Test, EQ) {
    BitArray a(2, 0b10);
    BitArray b = a;
    ASSERT_EQ(a==b, 1);
}

TEST(BitArray_Clear_Test, clear) {
    BitArray a(3, 0b10);
    a.clear();
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.to_string(), "");
}

TEST(BitArray_Shift_Test, left_shift) {
    BitArray a(2, 0b01);
    BitArray b = a << 1;
    ASSERT_EQ(b[0], 1);
}

TEST(BitArray_Shift_Test, right_shift) {
    BitArray a(2, 0b10);
    BitArray b = a >> 1;
    ASSERT_EQ(b[1], 1);
}

TEST(BitArray_Set_Test, set) {
    BitArray a(2, 0b11);
    a.set(1, 0);
    ASSERT_EQ(a[1], 0);
    ASSERT_EQ(a[0], 1);
}

TEST(BitArray_Set_Test, set_all) {
    BitArray a(70);
    a.set();
    for (int i = 0; i < 70; i++) {
        ASSERT_EQ(a[i], 1);
    }
}

TEST(BitArray_Count_Test, count) {
    BitArray a(10, 0b111110101);
    ASSERT_EQ(a.count(), 7);
}

TEST(BitArray_to_String_Test, to_string) {
    BitArray a(9, 0b111110101);
    std::string s = "111110101";
    std::string b = a.to_string();
    ASSERT_EQ(b, s);
}

TEST(BitArray_Operator_Not_Test, op_not) {
    BitArray a(3, 10);
    BitArray b = ~a;
    ASSERT_EQ(b.to_string(), "101");
}

TEST(BitArray_Any_Test, any) {
    BitArray a(3, 10);
    ASSERT_EQ(a.any(), 1);
    BitArray b(3);
    ASSERT_EQ(b.any(), 0);
}

TEST(BitArray_Reset_Test, reset) {
    BitArray a(3, 10);
    BitArray b = a.reset();
    ASSERT_EQ(b.to_string(), "000");
}

TEST(BitArray_Operator_And_Test, op_and) {
    BitArray a(3, 101);
    BitArray b(3, 0b110);
    BitArray c = a & b;
    ASSERT_EQ(c.to_string(), "100");
}

TEST(BitArray_Operator_Or_Test, op_or) {
    BitArray a(3, 101);
    BitArray b(3, 0b110);
    BitArray c = a | b;
    ASSERT_EQ(c.to_string(), "111");
}

TEST(BitArray_Operator_XOR_Test, op_xor) {
    BitArray a(3, 101);
    BitArray b(3, 0b110);
    BitArray c = a ^ b;
    ASSERT_EQ(c.to_string(), "011");
}

TEST(BitArray_Operator_Assignment_Test, op_assignment) {
    BitArray a(3, 101);
    BitArray b(10);
    b = a;
    ASSERT_EQ(b.to_string(), "101");
    ASSERT_EQ(b.size(), a.size());
}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

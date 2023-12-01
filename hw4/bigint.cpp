#include "bigint.h"
#include <iostream>

// Write your implementation below
BigInt::BigInt(std::string s) {
    for (int i = s.size() - 1; i >= 0; --i) {
        digits.push_back(s[i] - '0');
    }
}

std::string BigInt::to_string() const {
    std::string res = "";
    for (int i = digits.size() - 1; i >= 0; --i) {
        res += std::to_string(digits[i]);
    }
    return res;
}

void BigInt::add(BigInt b) {
    int carry = 0;
    int len = std::max(digits.size(), b.digits.size());
    int i = 0;
    while (i < len || carry != 0) {
        int res = 0;
        if (i < b.digits.size())
            res += b.digits[i];
        if (i < digits.size())
            res += digits[i];
        res += carry;
        carry = res / 10;
        if (i < digits.size()) {
            digits[i] = res % 10;
        } else {
            digits.push_back(res % 10);
        }
        i++;
    }
}
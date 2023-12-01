#include "str.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

// Add your implementations here.

Str::Str() {
    data_ = new char[1];
    data_[0] = '\0';
    size_ = 0;
}

Str::Str(const char *s) {
    if (s == NULL) {
        data_ = new char[1];
        data_[0] = '\0';
        size_ = 0;
    } else {
        data_ = new char[strlen(s) + 1];
        strcpy(data_, s);
        size_ = strlen(s);
    }
}

Str::Str(const Str &str) {
    data_ = new char[strlen(str.data_) + 1];
    strcpy(data_, str.data_);
    size_ = str.size_;
}

Str::~Str() { delete[] data_; }

size_t Str::size() const { return size_; }

Str &Str::operator=(const Str &s) {
    char *d = new char[strlen(s.data_) + 1];
    strcpy(d, s.data_);
    delete[] data_;
    data_ = d;
    size_ = s.size_;
    return *this;
}

Str &Str::operator=(const char *s) {
    char *d = new char[strlen(s) + 1];
    strcpy(d, s);
    delete[] data_;
    data_ = d;
    size_ = strlen(s);
    return *this;
}

Str &Str::operator+=(const Str &s) {
    char *d = new char[strlen(data_) + strlen(s.data_) + 1];
    strcpy(d, data_);
    strcat(d, s.data_);
    delete[] data_;
    data_ = d;
    size_ += s.size_;
    return *this;
}

Str &Str::operator+=(const char *s) {
    if (s == NULL)
        return *this;
    char *d = new char[strlen(data_) + strlen(s) + 1];
    strcpy(d, data_);
    strcat(d, s);
    delete[] data_;
    data_ = d;
    size_ += strlen(s);
    return *this;
}

Str Str::operator+(const Str &rhs) const {
    Str st(data_);
    st += rhs;
    return st;
}

Str Str::operator+(const char *rhs) const {
    Str st(data_);
    st += rhs;
    return st;
}

std::ostream &operator<<(std::ostream &ostr, const Str &s) {
    ostr << s.data_;
    return ostr;
}

bool Str::operator==(const Str &rhs) {
    if (size_ != rhs.size_)
        return false;
    if (strcmp(data_, rhs.data_) != 0)
        return false;
    return true;
}

bool Str::operator==(const char *rhs) {
    if (size_ != strlen(rhs))
        return false;
    if (strcmp(data_, rhs) != 0)
        return false;
    return true;
}

bool Str::operator!=(const Str &rhs) {
    if (strcmp(data_, rhs.data_) == 0)
        return false;
    return true;
}

bool Str::operator!=(const char *rhs) {
    if (strcmp(data_, rhs) == 0)
        return false;
    return true;
}

// Given implementations - DO NOT ALTER
const char *Str::data() const { return data_; }

char &Str::operator[](unsigned int i) {
    if (i >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    return data_[i];
}

char const &Str::operator[](unsigned int i) const {
    if (i >= size_) {
        throw std::out_of_range("Index is out of range");
    }
    return data_[i];
}

bool Str::operator<(const Str &rhs) const {
    return (strcmp(data_, rhs.data_) < 0);
}

bool Str::operator>(const Str &rhs) const {
    return (strcmp(data_, rhs.data_) > 0);
}

std::istream &operator>>(std::istream &istr, Str &s) {
    std::string stemp;
    istr >> stemp;
    s = stemp.c_str();
    return istr;
}

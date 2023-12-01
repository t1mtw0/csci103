#ifndef STR_H
#define STR_H
#include <iostream>

//-----------------------------------------------
// This file is not complete. You will need to
// add prototypes for the needed member functions
// based on the usage of str-test.cpp.
//-----------------------------------------------
class Str {
  public:
    /**
     * Default constructor should create a string
     * equal to ""
     */
    Str();
    /**
     * Character array constructor
     *  If s is NULL create a string that contains
     *  only the null character (i.e. "")
     */
    Str(const char *s);

    // Other needed functions may be appropriate to prototype here

    Str(const Str &str);

    ~Str();

    /**
     * Accessor for testing - Do not alter
     */
    const char *data() const;

    /**
     * Return the size of the string (e.g. "Hello" => 5)
     */
    size_t size() const;

    /**
     * Assignment operator
     */
    Str &operator=(const Str &s);

    /**
     * Assignment operator
     * If s is NULL, set this to a blank string ("")
     */
    Str &operator=(const char *s);

    /**
     * Str concatenation-assignment operator
     *  E.g. s += t
     */
    Str &operator+=(const Str &s);

    /**
     * Char. array concatenation-assignment operator
     *  E.g. s += " more"
     *  If s is NULL simply return this Str
     */
    Str &operator+=(const char *s);

    /**
     * String concatenation operator
     *  E.g. str s1("a"), s2("b"); cout << s1 + s2 << endl;
     */
    Str operator+(const Str &rhs) const;

    /**
     * String concatenation operator
     *  E.g. str s1; cout << s1 + " world" << endl;
     *  If rhs is NULL, simply return a copy of this Str
     */
    Str operator+(const char *rhs) const;

    /**
     * Non-const index operator - Complete
     *  E.g.  str s1("103");  s1[2] = '4';
     * Should throw std::out_of_range if invalid index is passed
     */
    char &operator[](unsigned int i);
    /**
     * Const index operator - Complete
     *  E.g. str s1("104");  char c = s1[2];
     * Should throw std::out_of_range if invalid index is passed
     */
    char const &operator[](unsigned int i) const;

    /**
     * Less-than check operator - Complete do not alter
     *  Should use strcmp() in underlying implementation
     */
    bool operator<(const Str &rhs) const;
    /**
     * Greater-than check operator - Complete do not alter
     *  Should use strcmp() in underlying implementation
     */
    bool operator>(const Str &rhs) const;

    /**
     * istream (>>) operator - Complete do not alter
     */
    friend std::istream &operator>>(std::istream &istr, Str &s);

    // Add any other necessary member functions

    friend std::ostream &operator<<(std::ostream &ostr, const Str &s);

    bool operator==(const Str &rhs);

    bool operator==(const char *rhs);

    bool operator!=(const Str &rhs);

    bool operator!=(const char *rhs);

  private:
    // You must use this data member
    char *data_;
    // You may add another member or two if needed
    // (e.g. think about whether it may save time to store
    //  the size in a separate member)
    unsigned int size_;
};
#endif

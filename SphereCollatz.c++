// --------------------------
// robby35us/cs378-collatz/SphereCollatz.c++
// Copyright (C) 2011
// Glenn P. Downing and Robert Reed
// --------------------------


// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostream, cin, cout, ios_base


// ------------
// collatz_read
// ------------

/**
* reads two ints into i and j
* @param r a std::istream
* @param i an int by reference
* @param j an int by reference
* @return true if that succeeds, false otherwise
*/
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ----------
// _getCycLen
// ----------

/**
* computes the cycle-length for a single value
* @param n a positive integer
* @return the cycle length of n
**/
int _getCycLen(int num) {
   assert(num > 0);
   int len = 1;
   while(num > 1) {
      if(num % 2 == 0)
         num = num / 2;
      else
         num = 3 * num + 1;
      ++len;}
   assert(num > 0);
   return len;}



// ------------
// collatz_eval
// ------------

/**
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @return the max cycle length in the range [i, j]
*/
int collatz_eval (int beg, int end) {
    assert(beg > 0);
    assert(end > 0);
    int max = 1;
    if(beg >= end){
       beg ^= end;
       end ^= beg;
       beg ^= end;}
    int index = beg;
    for(index = beg; index <= end; ++index) {
       int cycLen = _getCycLen(index);
       if(cycLen > max)
          max = cycLen;}
    assert(max > 0);
    return max;}

// -------------
// collatz_print
// -------------

/**
* prints the values of i, j, and v
* @param w a std::ostream
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @param v the max cycle length
*/
void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    collatz_solve(cin, cout);
    return 0;}

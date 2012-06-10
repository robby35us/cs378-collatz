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
#include <iostream> // endl, istream, ostream

//global varible for use throught program
const int cacheLen = 1000000;
int _cache[cacheLen];

// -----------------
// _initialize_cache
// -----------------

void _initialize_cache() {
    for(int i = 1; i < cacheLen; ++i)
        _cache[i] = 0;}

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
bool collatz_read (std::istream& r, long int& i, long int& j) {
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
* @param num a positive integer
* @return the cycle length of num
**/
int _getCycLen(long int num) {
   assert(num > 0);
   if(num < cacheLen && _cache[num] > 0)
      return _cache[num];
   long int index = num;
   int cycLen = 1;
   while(index > 1) {
      if(index < cacheLen && _cache[index] > 0) {
         cycLen += _cache[index] - 1;
         break;}
      else if(index % 2 == 0)
         index = index / 2;
      else
         index = 3 * index + 1;
      ++cycLen;
      assert(index > 0);}
   if(num < cacheLen && _cache[num] == 0)
      _cache[num] = cycLen;
   assert(num > 0);
   return cycLen;}



// ------------
// collatz_eval
// ------------

/**
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @return the max cycle length in the range [i, j]
*/
int collatz_eval (long beg, long end) {
    assert(beg > 0);
    assert(end > 0);
    int max = 1;
    if(beg >= end){
       beg ^= end;
       end ^= beg;
       beg ^= end;}
    for(long int index = beg; index <= end; ++index) {
       int cycLen = _getCycLen(index);
       assert(cycLen > 0);
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
void collatz_print (std::ostream& w, long int i, long int j, int v) {
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
    long int i;
    long int j;
    _initialize_cache();
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);
    collatz_solve(cin, cout);
    return 0; }

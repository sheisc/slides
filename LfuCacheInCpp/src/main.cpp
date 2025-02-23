#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "LfuCache.h"
using namespace std;

typedef int KeyTy;
typedef long ValueTy;

int main(void) {
    long n = 4;
    LfuCache<KeyTy, ValueTy> cache(n);

    for (KeyTy i = 1; i <= n; i++) {
        //cache.Put(i, std::to_string(i * 10));
        cache.Put(i, i * 10);
        cache.Print(cout, "Put", i);
    }

    //
    for (KeyTy i = 1; i <= n; i++) {
        ValueTy value;
        bool found = cache.Get(i, value);
        cache.Print(cout, "Get", i);
        if (found) {
            cout << "\t" << i << " --> " << value << endl;
        }
    }

    for (KeyTy i = n + 1; i <= 2 * n; i++) {
        cache.Put(i, i * 10);
        //cache.Put(i, std::to_string(i * 10));
        cache.Print(cout, "Put", i);
    }

    return 0;
}

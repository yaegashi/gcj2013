#define __STDC_FORMAT_MACROS
#include <cstdint>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <cmath>

#include <iostream>
#include <sstream>
#include <string>


using namespace std;


bool
fair(uint64_t x)
{
        char s[32];
        snprintf(s, sizeof(s), "%" PRIu64, x);
        int a = 0;
        int b = strlen(s) - 1;
        while (a < b) {
                if (s[a] != s[b])
                        return false;
                a++;
                b--;
        }
        return true;
}


int
scan(uint64_t a, uint64_t b)
{
        int c = 0;
        uint64_t smin = sqrt(a);
        uint64_t smax = sqrt(b);
        for (uint64_t s = smin; s <= smax; s++) {
                if (!fair(s))
                        continue;
                uint64_t ss = s * s;
                if (ss < a)
                        continue;
                if (fair(ss))
                        c++;
        }
        return c;
}


int
main(int argc, char **argv)
{
        int T;
        string  lineT;
        getline(cin, lineT);
        stringstream ssT(lineT);
        ssT >> T;

        for (int i = 0; i < T; i++) {
                string lineAB;
                getline(cin, lineAB);
                stringstream ssAB(lineAB);
                uint64_t a, b;
                ssAB >> a >> b;
                cout << "Case #" << i+1 << ": " << scan(a, b) << endl;
        }

        return 0;
}

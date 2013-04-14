#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAXK = 200;

typedef std::vector<bool> opens_t;
typedef std::vector<uint16_t> keys_t;
typedef std::vector<uint16_t> hist_t;


bool
cmp(const hist_t &r, hist_t &s)
{
        int rsize = r.size(), ssize = s.size();
        for (int i = 0; i < rsize && i < ssize; i++)
                if (r[i] < s[i])
                        return true;
        return false;
}


const hist_t
rec(const keys_t &okeys, const keys_t *akeys, const opens_t &opens, const keys_t &ikeys, const hist_t &hist)
{
        if (opens.size() == hist.size()) {
                return hist;
        }
        else {
                hist_t r;
                for (int i = 0; i < opens.size(); i++) {
                        if (opens[i])
                                continue;
                        int o = okeys[i];
                        if (ikeys[o] > 0)
                                continue;
                        bool as = true;
                        for (int j = 0; j < opens.size(); j++) {
                                if (j == i)
                                        continue;
                                if (akeys[j][o] > 0)
                                        as = false;
                        }
                        if (as)
                                return r;
                }
                for (int i = 0; i < opens.size(); i++) {
                        if (opens[i])
                                continue;
                        int q = okeys[i];
                        if (!ikeys[q])
                                continue;
                        hist_t hist2(hist);
                        hist2.push_back(i);
                        if (cmp(r, hist2))
                                continue;
                        opens_t opens2(opens);
                        keys_t ikeys2(ikeys);
                        opens2[i] = true;
                        ikeys2[q]--;
                        for (int j = 0; j < akeys[i].size(); j++)
                                ikeys2[j] += akeys[i][j];
                        hist_t s = rec(okeys, akeys, opens2, ikeys2, hist2);
                        if (s.size() == 0)
                                continue;
                        r = s;
                }
                if (false && r.size() == 0) {
                        cerr << "abort:";
                        for (int i = 0; i < hist.size(); i++)
                                cerr << " " << hist[i];
                        cerr << endl;
                }
                return r;
        }
}


int
main(int argc, char **argv)
{
        string line;
        int T;
        getline(cin, line);
        stringstream ssT(line);
        ssT >> T;

        for (int i = 0; i < T; i++) {
                int K, N;
                getline(cin, line);
                stringstream ssKN(line);
                ssKN >> K >> N;

                keys_t okeys(N, 0), akeys[N];
                keys_t ikeys(MAXK, 0), osum(MAXK, 0), asum(MAXK, 0);

                getline(cin, line);
                stringstream ssIKEYS(line);
                for (int j = 0; j < K; j++) {
                        int n;
                        ssIKEYS >> n;
                        ikeys[n]++;
                        asum[n]++;
                }

                for (int j = 0; j < N; j++) {
                        int m, n;
                        getline(cin, line);
                        stringstream ssAKEYS(line);
                        ssAKEYS >> n;
                        okeys[j] = n;
                        osum[n]++;
                        ssAKEYS >> n;
                        akeys[j].assign(MAXK, 0);
                        for (int k = 0; k < n; k++) {
                                ssAKEYS >> m;
                                akeys[j][m]++;
                                asum[m]++;
                        }
                }

                cerr << "ikeys:";
                for (int j = 1; j <= 10; j++)
                        cerr << " " << j << ":" << ikeys[j];
                cerr << endl;

                for (int j = 0; j < N; j++) {
                        cerr << "[" << j << "] " << okeys[j];
                        for (int k = 1; k <= 10; k++)
                                cerr << " " << k << ":" << akeys[j][k];
                        cerr << endl;
                }

                cerr << "osum:";
                for (int j = 1; j <= 10; j++)
                        cerr << " " << j << ":" << osum[j];
                cerr << endl;

                cerr << "asum:";
                for (int j = 1; j <= 10; j++)
                        cerr << " " << j << ":" << asum[j];
                cerr << endl;

                hist_t r;
                bool s = true;
                for (int j = 0; j < osum.size(); j++)
                        if (osum[j] > asum[j])
                                s = false;
                if (s) {
                        hist_t hist;
                        opens_t opens(N, false);
                        r = rec(okeys, akeys, opens, ikeys, hist);
                }

                cout << "Case #" << i+1 << ":";
                if (r.size() == 0)
                        cout << " IMPOSSIBLE";
                else
                        for (int i = 0; i < r.size(); i++)
                                cout << " " << r[i]+1;
                cout << endl;
        }
        return 0;
}

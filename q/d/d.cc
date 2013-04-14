#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int MAXK = 201;

typedef vector<bool> opens_t;
typedef vector<int> keys_t;
typedef vector<int> hist_t;


bool
reachable(const int *okeys, const keys_t *akeys,
                opens_t opens, keys_t ikeys, hist_t hist) {
        while (hist.size() < opens.size()) {
                hist_t openable;
                for (int i = 0; i < ikeys.size(); i++) {
                        if (ikeys[i] == 0)
                                continue;
                        for (int j = 0; j < opens.size(); j++)
                                if (!opens[j] && okeys[j] == i)
                                        openable.push_back(j);
                }
                if (openable.empty())
                        return false;
                for (int i = 0; i < openable.size(); i++) {
                        int n = openable[i];
                        opens[n] = true;
                        hist.push_back(n);
                        for (int j = 0; j < akeys[n].size(); j++)
                                ikeys[j] += akeys[n][j];
                }
        }
        return true;
}


const hist_t
rec(const int *okeys, const keys_t *akeys,
                const opens_t &opens, const keys_t &ikeys, const hist_t &hist)
{
        if (opens.size() == hist.size()) {
                return hist;
        }
        else {
                if (!reachable(okeys, akeys, opens, ikeys, hist))
                        return hist_t();
                for (int i = 0; i < opens.size(); i++) {
                        if (opens[i])
                                continue;
                        int o = okeys[i];
                        if (ikeys[o] == 0)
                                continue;
                        opens_t opens2(opens);
                        keys_t ikeys2(ikeys);
                        hist_t hist2(hist);
                        opens2[i] = true;
                        ikeys2[o]--;
                        hist2.push_back(i);
                        for (int j = 0; j < akeys[i].size(); j++)
                                ikeys2[j] += akeys[i][j];
                        hist_t s = rec(okeys, akeys, opens2, ikeys2, hist2);
                        if (s.size() > 0)
                                return s;
                }
                return hist_t();
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

                int okeys[N];
                keys_t akeys[N];
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

#if 0
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
#endif

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

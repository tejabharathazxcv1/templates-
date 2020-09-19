const int Z = 1e9 + 9;

// backward hash , for checking palindrome
string valid(string& s, int len)
{

    int n = s.size();
    ll hf1 = 0;
    ll hr1 = 0;

    ll hf2 = 0;
    ll hr2 = 0;

    ll p = 257;

    ll plast1 = 1;

    ll plast2 = 1;

    ll psize1 = 1;
    ll psize2 = 1;

    ll pstart1 = 1;
    ll pstart2 = 1;

    string res = "";
    for (int i = 0; i < n; ++i) {

        if (i <= len - 1) {
            hf1 = ((hf1)*p + s[i]) % M;
            hf2 = ((hf2)*p + s[i]) % Z;

            hr1 = ((hr1) + plast1 * s[i]) % M;
            hr2 = ((hr2) + plast2 * s[i]) % Z;

            if (i == len - 1) {

                if (hf1 == hr1 && hf2 == hr2) {
                    res = s.substr(i - len + 1, len);
                    return res;
                }
                psize1 = plast1;
                psize2 = plast2;
            }

            plast1 *= p;
            plast1 %= M;
            plast2 *= p;
            plast2 %= Z;

            continue;
        }

        hf1 = (((hf1 - s[i - len] * psize1) % M + M) * p + s[i] + M) % M;

        hf2 = (((hf2 - s[i - len] * psize2) % Z + Z) * p + s[i] + Z) % Z;

        hr1 = (((hr1 - s[i - len] * pstart1) % M + M) + s[i] * plast1 + M) % M;

        hr2 = (((hr2 - s[i - len] * pstart2) % Z + Z) + s[i] * plast2 + Z) % Z;

        pstart1 = (pstart1 * p) % M;

        pstart2 = (pstart2 * p) % Z;

        plast1 = (plast1 * p) % M;
        plast2 = (plast2 * p) % Z;

        if (((hf1 * pstart1) % M == hr1) && ((hf2 * pstart2) % Z == hr2)) {
            res = s.substr(i - len + 1, len);
            return res;
        }
    }

    return res;
}


const int psz = 1e5;

vector<ll> P1(psz + 10);

vector<ll> P2(psz + 10);

const int p = 257;

void preprocess()
{

    P1[0] = 1, P2[0] = 1;

    for (int i = 1; i < psz; ++i) {
        P1[i] = (P1[i - 1] * p) % M;
        P2[i] = (P2[i - 1] * p) % Z;
    }
}

class RollHash {
public:
    string s;
    int n;

    vector<ll> h1, h2;

    pair<ll,ll> h ; 

    RollHash(string& _s)
    {
        s = _s;
        n = s.size();
        h1 = vector<ll>(n + 10);
        h2 = vector<ll>(n + 10);
        computeHash();
    }

    void computeHash()
    {

        for (int i = 0; i < n; ++i) {

            if (i == 0) {
                h1[i] = s[i];
                h2[i] = s[i];
                continue;
            }

            h1[i] = (h1[i - 1] + s[i] * P1[i]) % M;
            h2[i] = (h2[i - 1] + s[i] * P2[i]) % Z;
        }

        h = {h1[n-1],h2[n-1]}; 

    }

    pair<ll, ll> getHash(int l, int r)
    {

        ll t1, t2;
        t1 = h1[r], t2 = h2[r];

        if (l - 1 >= 0) {
            t1 = (t1 - h1[l - 1]) % M;
            t2 = (t2 - h2[l - 1]) % Z;
        }
        t1 = (t1 + M) % M;
        t2 = (t2 + Z) % Z;

        return { t1, t2 };
    }

    bool compareHash(ll l1, ll r1, pair<ll, ll> t2, int l2, int r2)
    {

        pair<ll, ll> t1 = getHash(l1, r1);
        if (l2 >= l1) {
            t1.first = (t1.first * P1[l2 - l1]) % M;
            t1.second = (t1.second * P2[l2 - l1]) % Z;
        } else {
            t2.first = (t2.first * P1[l1 - l2]) % M;
            t2.second = (t2.second * P2[l1 - l2]) % Z;
        }

        return (t1 == t2);
    }

    bool compareHash(ll l1 , pair<ll,ll>& t2 , int l2 )
    {


        pair<ll,ll> t1 = h;
        if (l2 >= l1) {
            t1.first = (t1.first * P1[l2 - l1]) % M;
            t1.second = (t1.second * P2[l2 - l1]) % Z;
        } else {
            t2.first = (t2.first * P1[l1 - l2]) % M;
            t2.second = (t2.second * P2[l1 - l2]) % Z;
        }

        return (t1 == t2);
    }
};
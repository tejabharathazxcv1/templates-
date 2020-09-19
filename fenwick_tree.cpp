class bittree {

public:
    int n_;
    int n;

    vector<ll> bit; //  stores sum of vals for all ind
    vector<ll> bit2; //  stores cnt of ind

    int L;

    bittree(int n_)
    {
        this->n_ = n_;
        n = n_ + 10;
        bit = vector<ll>(n);
        bit2 = vector<ll>(n);
        L = f_lg(n);
    }

    void update(int i, ll x)
    {

        if (i < 0) {
            return;
        }

        ++i;
        while (i < (int)bit.size()) {
            bit[i] += x;

            bit2[i] += (x > 0 ? 1 : -1);

            i += i & -i;
        }
    }

    ll pre(int i)
    {

        if (i < 0) {
            return 0LL;
        }

        ++i;
        ll tot = 0;
        while (i > 0) {
            tot += bit[i];
            i -= i & -i;
        }
        return tot;
    }

    ll range(int i, int j)
    {

        if (j < i) {
            return 0LL;
        }

        return pre(j) - pre(i - 1);
    }

    ll getval(int i)
    {

        return range(i, i);
    }

    // ############################   for finding  nth element in bit    #######################################################

    //using bit

    int find(int tar)
    {

        ++tar;

        if (tar == 0) {
            // return -1;
            assert(false);
        }

        int pos = 0;

        int rem = tar;
        for (int i = L; i >= 0; --i) {

            if ((pos + (1 << i) < (n)) && bit[pos + (1 << i)] < rem) {
                rem -= bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }

        if (pos >= n_) {
            assert(false);
        }

        return pos;
    }

    int find2(int tar)
    {

        ++tar;

        dbg(tar);

        if (tar == 0) {
            // return -1;
            assert(false);
        }

        int pos = 0;

        int rem = tar;
        for (int i = L; i >= 0; --i) {

            if ((pos + (1 << i) < (n)) && bit2[pos + (1 << i)] < rem) {
                rem -= bit2[pos + (1 << i)];
                pos += (1 << i);
            }
        }

        if (pos >= n_) {
            assert(false);
        }

        return pos;
    }

    // ####################  for range updates and point queries #######################################
    // nth element will not work now

    void update_r(int i, int j, ll x)
    {

        update(i, x);
        update(j + 1, -x);
    }

    ll getval_r(int i)
    {

        return pre(i);
    }
};

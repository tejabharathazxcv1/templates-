
template <typename T, class F = function<T(const T&, const T&)>>
class SPT {
public:
    int n;
    vector<vector<T>> A;
    F func;

    SPT(const vector<T>& a, const F& f)
        : func(f)
    {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        A.resize(max_log);
        A[0] = a;
        for (int j = 1; j < max_log; j++) {
            A[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                A[j][i] = func(A[j - 1][i], A[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int lt, int rt) const
    {
        assert(0 <= lt && lt <= rt && rt <= n - 1);
        int lg = 32 - __builtin_clz(rt - lt + 1) - 1;
        return func(A[lg][lt], A[lg][rt - (1 << lg) + 1]);
    }
};

// SparseTable<int> st(a, [&](int i, int j) { return max(i, j); });


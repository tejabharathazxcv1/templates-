// refer errichto gym contest
// https://codeforces.com/gym/102644

struct Mat {

    // int a[2][2] = { { 0, 0 }, { 0, 0 } };

    // int a[100][100] = {};

    vector<vector<ll>> a = vector<vector<ll>>  (100,  vector<ll> (100 , INF));


    Mat operator*(const Mat& other)
    {
        Mat prod;
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                for (int k = 0; k < 100; ++k) {
                    // no of ways
                    // prod.a[i][j] = add(prod.a[i][j], mul(a[i][k], other.a[k][j]));
                    prod.a[i][j] = min(prod.a[i][j],  a[i][k] + other.a[k][j]); 
                }
            }
        }

        return prod;
    }
};

Mat matpow(Mat a, ll b)
{

    Mat res;

    // be very careful when choosing initial value for res,
    // different kinds of initial values it can take based on problems  <Eg>:  identitiy matrix in some cases
    for (int i = 0; i < 100; ++i) {
        res.a[i][i] = 0; 
    }

    while (b > 0) {

        if (b & 1) {
            res = res * a;
        }

        a = a * a;

        b >>= 1;
    }

    return res;
}
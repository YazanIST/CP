// Dependency: modular_arithmetic.cpp
struct Matrix {
    int n, m;
    vector<vector<int>> mat;

    Matrix(int n, int m): n(n), m(m), mat(vector<vector<int>> (n, vector<int>(m))) {}

    Matrix(vector<vector<int>> mat): n(mat.size()), m(mat[0].size()), mat(mat) {}

    Matrix(const Matrix &other): n(other.n), m(other.m), mat(other.mat) {}

    Matrix operator*(Matrix other) {
        assert(m == other.n);
        Matrix ret(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < other.n; k++) {
                for (int j = 0; j < other.m; j++) {
                    ret.mat[i][j] = add(ret.mat[i][j], mul(mat[i][k], other.mat[k][j]));
                }
            }
        }
        return ret;
    }

    Matrix power(ll p) {
        Matrix ret(n, m), base(mat);
        for (int i = 0; i < n; i++) {
            ret.mat[i][i] = 1;
        }
        while (p > 0) {
            if (p % 2 == 1) {
                ret = ret * base;
            }
            base = base * base;
            p /= 2;
        }
        return ret;
    }

    void printMatrix() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

/* ===== DU LIEU CHUNG ===== */
const int MAX = 12; // Dung chi so tu 1 -> 11

string tenTinh[] = {
    "", "Ha Noi", "Hai Duong", "Hai Phong", "Hung Yen", "Bac Giang",
    "Bac Ninh", "Thai Nguyen", "Son Tay", "Hoa Binh", "Phu Ly", "Uong Bi"
};

/* ===== HAM IN DINH ===== */
void inTinh(int u) {
    cout << tenTinh[u] << " (" << u << ") -> ";
}

/* =====================================================
   ========== MA TRAN KE ==========
   ===================================================== */
int maTranKe[MAX][MAX];
bool daTham_MT[MAX];

void themCanh_MaTran(int u, int v) {
    maTranKe[u][v] = 1;
    maTranKe[v][u] = 1; // Do thi vo huong
}

void bfs_MaTran(int batDau) {
    cout << "\n--- BFS SU DUNG MA TRAN KE ---\n";
    memset(daTham_MT, false, sizeof(daTham_MT));

    queue<int> q;
    q.push(batDau);
    daTham_MT[batDau] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inTinh(u);

        // Uu tien dinh co so thu tu LON -> BE
        for (int v = 11; v >= 1; v--) {
            if (maTranKe[u][v] == 1 && !daTham_MT[v]) {
                daTham_MT[v] = true;
                q.push(v);
            }
        }
    }
    cout << "KET THUC\n";
}

/* =====================================================
   ========== DANH SACH KE ==========
   ===================================================== */
vector<int> danhSachKe[MAX];
bool daTham_DS[MAX];

void themCanh_DanhSach(int u, int v) {
    danhSachKe[u].push_back(v);
    danhSachKe[v].push_back(u);
}

void bfs_DanhSach(int batDau) {
    cout << "\n--- BFS SU DUNG DANH SACH KE ---\n";
    memset(daTham_DS, false, sizeof(daTham_DS));

    // Sap xep danh sach ke giam dan
    for (int i = 1; i <= 11; i++) {
        sort(danhSachKe[i].begin(), danhSachKe[i].end(), greater<int>());
    }

    queue<int> q;
    q.push(batDau);
    daTham_DS[batDau] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inTinh(u);

        for (int v : danhSachKe[u]) {
            if (!daTham_DS[v]) {
                daTham_DS[v] = true;
                q.push(v);
            }
        }
    }
    cout << "KET THUC\n";
}

/* =====================================================
   ========== HAM MAIN ==========
   ===================================================== */
int main() {
    memset(maTranKe, 0, sizeof(maTranKe));

    vector<pair<int, int>> canh = {
        {1,10}, {1,9}, {1,8}, {1,7}, {1,6}, {1,2},
        {10,4}, {4,2}, {2,3},
        {6,5}, {6,11}, {5,11}
    };

    for (auto c : canh) {
        themCanh_MaTran(c.first, c.second);
        themCanh_DanhSach(c.first, c.second);
    }

    bfs_MaTran(1);
    bfs_DanhSach(1);

    return 0;
}


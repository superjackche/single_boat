#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 判断是否可以在相邻距离至少为 d 的情况下放置 M 棵树苗
bool canPlace(const vector<int>& positions, int n, int m, int d) {
    int count = 1; // 已放置的树苗数量（第一个位置必放）
    int last_position = positions[0]; // 上一次放置树苗的位置

    for (int i = 1; i < n; ++i) {
        // 如果当前位置与上一次放置的位置的距离 >= d，则放置树苗
        if (positions[i] - last_position >= d) {
            count++;
            last_position = positions[i];
            // 如果已经放置了 M 棵树苗，返回 true
            if (count >= m) {
                return true;
            }
        }
    }
    return false;
}

// 主函数：计算最大最近距离
int maxMinDistance(int n, int m, vector<int>& positions) {
    // 对位置数组进行排序
    sort(positions.begin(), positions.end());

    // 二分查找范围
    int left = 1; // 最小可能的距离
    int right = positions[n - 1] - positions[0]; // 最大可能的距离
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2; // 当前尝试的最小距离
        if (canPlace(positions, n, m, mid)) {
            result = mid; // 更新结果
            left = mid + 1; // 尝试更大的最小距离
        } else {
            right = mid - 1; // 尝试更小的最小距离
        }
    }

    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> positions(n);
    for (int i = 0; i < n; i++) cin >> positions[i];

    // 输出结果
    cout << maxMinDistance(n, m, positions) << endl;

    return 0;
}
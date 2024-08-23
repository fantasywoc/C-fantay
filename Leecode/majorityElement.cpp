// 169. 多数元素

// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 示例 1：

// 输入：nums = [3,2,3]
// 输出：3

// 示例 2：

// 输入：nums = [2,2,1,1,1,2,2]
// 输出：2

// 提示：
//     n == nums.length
//     1 <= n <= 5 * 104
//     -109 <= nums[i] <= 109

// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。

#include<iostream>
#include<vector>
#include <chrono>
#include<unordered_map>
using namespace std;

void printv(vector<int>& vec) {
    for (auto& it : vec) {
        cout << it << ";";
    }
    cout << endl;
}

// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         unordered_map<int,int> counts;
//     }
// };

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        int majority = 0, cnt = 0;
        for (int num: nums) {
            ++counts[num];
            if (counts[num] > cnt) {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};


int main() {

    int m = 2;
    vector<int> nums1 = {0, 0, 1, 1, 1, 1, 2, 3, 3};

    auto start = chrono::high_resolution_clock::now();

    Solution solution;
    cout << (solution.majorityElement(nums1)) << endl;

    auto end = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
    printv(nums1);

}
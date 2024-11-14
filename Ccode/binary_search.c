#include <stdio.h>

int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;  // 避免溢位

        if (arr[mid] == target) {
            return mid;  // 找到目標值，返回索引
        } else if (arr[mid] < target) {
            left = mid + 1;  // 目標值在右半部
        } else {
            right = mid - 1;  // 目標值在左半部
        }
    }

    return -1;  // 未找到目標值
}

int main() {
    int arr[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    int result = binary_search(arr, size, target);

    if (result != -1) {
        printf("Found %d at index %d\n", target, result);
    } else {
        printf("%d not found in the array.\n", target);
    }

    return 0;
}

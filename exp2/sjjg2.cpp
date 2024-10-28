#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>

int largestRectangleArea(std::vector<int>& heights) {
    int n = heights.size();
    std::vector<int> left(n), right(n);
    std::stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        if (st.empty())
            left[i] = 0;
        else
            left[i] = st.top() + 1;
        st.push(i);
    }

    while (!st.empty())
        st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        if (st.empty())
            right[i] = n - 1;
        else
            right[i] = st.top() - 1;
        st.push(i);
    }

    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int area = heights[i] * (right[i] - left[i] + 1);
        maxArea = std::max(maxArea, area);
    }

    return maxArea;
}

void testLargestRectangleArea() {
    std::srand(std::time(nullptr));
    for (int i = 0; i < 10; i++) {
        int n = std::rand() % 100 + 1;
        std::vector<int> heights;
        for (int j = 0; j < n; j++) {
            heights.push_back(std::rand() % 10000);
        }
        int area = largestRectangleArea(heights);
        std::cout << "Test " << i + 1 << ", heights: ";
        for (int h : heights) {
            std::cout << h << " ";
        }
        std::cout << ", Max area: " << area << std::endl;
    }
}

int main() {
    testLargestRectangleArea();
    return 0;
}

#include <iostream>
#include <vector>
#include <cctype>

// 栈数据结构
class Stack {
private:
    std::vector<int> items;
public:
    void push(int item) {
        items.push_back(item);
    }

    int pop() {
        if (!is_empty()) {
            int top = items.back();
            items.pop_back();
            return top;
        }
        return -1;
    }

    int peek() {
        if (!is_empty()) {
            return items.back();
        }
        return -1;
    }

    bool is_empty() {
        return items.empty();
    }
};

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int performOperation(char op, int num1, int num2) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2!= 0)
                return num1 / num2;
            else
                return -1;
    }
    return -1;
}

int evaluateExpression(const std::string& expression) {
    Stack numStack;
    Stack opStack;

    for (char c : expression) {
        if (isdigit(c)) {
            numStack.push(c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!opStack.is_empty() && precedence(opStack.peek()) >= precedence(c)) {
                int num2 = numStack.pop();
                int num1 = numStack.pop();
                char op = opStack.pop();
                int result = performOperation(op, num1, num2);
                numStack.push(result);
            }
            opStack.push(c);
        }
    }

    while (!opStack.is_empty()) {
        int num2 = numStack.pop();
        int num1 = numStack.pop();
        char op = opStack.pop();
        int result = performOperation(op, num1, num2);
        numStack.push(result);
    }

    return numStack.peek();
}
//测试 
int main() {
    std::string expression = "3+4*2-6/3";
    int result = evaluateExpression(expression);
    std::cout << "Result of expression '" << expression << "' is: " << result << std::endl;
    return 0;
}

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

class Stack {
private:
    struct node {
        int value;
        node* prev;
    };
    node* head;
    int size;

public:
    Stack() : head(nullptr), size(0) {}

    void push(int value) {
        node* newNode = new node{value, head};
        head = newNode;
        ++size;
    }

    int pop() {
        int result = head->value;
        node* oldHead = head;
        head = head->prev;
        delete oldHead;
        --size;
        return result;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int top() const {
        return head->value;
    }
};

int symb(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string CreateString(const std::string& exp) {
    Stack stack;
    std::string post;
    
    for (size_t i = 0; i < exp.length(); ++i) {
        char ch = exp[i];

        if (std::isdigit(ch)) {
            int num = 0;
            while (i < exp.length() && std::isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                ++i;
            }
            --i;
            post += std::to_string(num) + " ";
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                post += static_cast<char>(stack.pop());
                post += ' ';
            }
            stack.pop();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() && symb(stack.top()) >= symb(ch)) {
                post += static_cast<char>(stack.pop());
                post += ' ';
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        post += stack.pop();
        post += ' ';
    }
    return post;
}

int Postf(const std::string& post) {
    Stack stack;
    for (size_t i = 0; i < post.length(); ++i) {
        char ch = post[i];

        if (std::isdigit(ch)) {
            int num = 0;
            while (i < post.length() && std::isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            --i;
            stack.push(num);
        } else if (ch == ' ') {
            continue;
        } else {
            int ch2 = stack.pop();
            int ch1 = stack.pop();

            if (ch == '+') {
                stack.push(ch1 + ch2);
            } else if (ch == '-') {
                stack.push(ch1 - ch2);
            } else if (ch == '*') {
                stack.push(ch1 * ch2);
            } else if (ch == '/') {
                stack.push(ch1 / ch2);
            }
        }
    }
    return stack.pop();
}

int main() {
    std::string exp;
    std::getline(std::cin, exp);

    std::string post = CreateString(exp);
    int result = Postf(post);

    std::cout << "Expression:" << std::endl << exp << std::endl;
    std::cout << "Reverse Polish Notation:" << std::endl << post << std::endl;
    std::cout << "Result:" << std::endl << result << std::endl;

    return 0;
}
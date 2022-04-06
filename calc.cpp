#include <iostream>
#include <string>
#include <vector>
#include "list.h"

int math(int x, std::string oper, int y)
{
    switch (oper[0])
    {
    case '+':
        return x + y;
        break;
    case '-':
        return x - y;
        break;
    case '*':
        return x * y;
        break;
    case '/':
        return x / y;
        break;
    }
    return 0;
}

int main()
{
    std::string exp;
    std::string num;
    list<int> nums;
    list<std::string> oper;
    std::vector<int> queue;

    std::cin >> exp;
    for (int i = 0; exp.length(); ++i)
    {
        nums.push_back(0);
        while (exp.front() > 47)
        {
            num.push_back(exp[0]);
            exp.erase(exp.begin());
        }
        nums[i] = std::stoi(num);
        if (exp.length())
        {
            oper.push_back("");
            oper[i].push_back(exp[0]);
            if (oper[i] == "/" || oper[i] == "*")
                queue.push_back(i);
            exp.erase(exp.begin());
        }
        num.clear();
    }

    for (int i = queue[0], l = 0; queue.size(); i = queue[0], ++l)
    {
        nums[i - l] = math(nums[i - l], oper[i - l], nums[i + 1 - l]);
        nums.removeAt(i + 1 - l);
        oper.removeAt(i - l);
        queue.erase(queue.begin());
        while (!queue.size() && oper.getSize())
        {
            nums[0] = math(nums[0], oper[0], nums[1]);
            nums.removeAt(1);
            oper.removeAt(0);
        }
    }
    std::cout << nums[0];
}
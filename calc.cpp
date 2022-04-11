#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <math.h>

class calc
{
public:
    std::stack<double> nums;
    std::stack<char> oper;

    int getRang(char ch)
    {
        if (ch == '^')
            return 3;
        if (ch == '+' || ch == '-')
            return 1;
        if (ch == '*' || ch == '/')
            return 2;
        else
            return 0;
    }

    bool math()
    {
        double a, b, c;
        a = nums.top();
        nums.pop();

        switch (oper.top())
        {
        case '+':
            b = nums.top();
            nums.pop();
            c = a + b;
            nums.push(c);
            oper.pop();
            break;

        case '-':
            b = nums.top();
            nums.pop();
            c = b - a;
            nums.push(c);
            oper.pop();
            break;

        case '^':
            b = nums.top();
            nums.pop();
            c = pow(b, a);
            nums.push(c);
            oper.pop();
            break;

        case '*':
            b = nums.top();
            nums.pop();
            c = a * b;
            nums.push(c);
            oper.pop();
            break;

        case '/':
            b = nums.top();
            if (a == 0)
            {
                std::cerr << "Error";
                return false;
            }
            else
            {
                nums.pop();
                c = (b / a);
                nums.push(c);
                oper.pop();
                break;
            }
        }
        return true;
    }

    int sort()
    {
        std::string str;
        getline(std::cin, str);
        std::stringstream sstr{str};

        char ch;
        double value;
        bool flag = true;

        while (true)
        {
            ch = sstr.peek();
            if (ch == '\377')
                break;
            if (ch == ' ')
            {
                std::cin.ignore();
                continue;
            }
            if (ch >= '0' && ch <= '9' || ch == '-' && flag == 1)
            {
                sstr >> value;
                nums.push(value);
                flag = 0;
                continue;
            }
            if (ch == '+' || ch == '-' && flag == 0 || ch == '*' || ch == '/' || ch == '^')
            {
                if (oper.size() == 0)
                {
                    oper.push(ch);
                    sstr.ignore();
                    continue;
                }
                else if (getRang(ch) > getRang(oper.top()))
                {
                    oper.push(ch);
                    sstr.ignore();
                    continue;
                }
                else if (getRang(ch) <= getRang(oper.top()))
                {
                    if (math() == false)
                    {
                        system("pause");
                        return 0;
                    }
                    continue;
                }
            }

            if (ch == '(')
            {
                oper.push(ch);
                sstr.ignore();
                continue;
            }
            if (ch == ')')
            {
                while (oper.top() != '(')
                {
                    if (math() == false)
                    {
                        system("pause");
                        return 0;
                    }
                    else
                        continue; 
                }
                oper.pop();
                sstr.ignore();
                continue;
            }
            // else
            // {
            //     cout << "\nError Enter\n";
            //     system("pause");
            //     return 0;
            // }
        }
        while (oper.size() != 0)
        {
            if (math() == false)
            {
                system("pause");
                return 0;
            }
            else
                continue;
        }
        std::cout << "result: " << nums.top() << std::endl;
        system("pause");
        return 0;
    }

    calc()
    {
        sort();
    }
};

int main()
{
    calc c;
}

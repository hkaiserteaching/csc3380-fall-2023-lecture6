
#include <iostream>
#include <stdexcept>
#include <string>

// Token stuff (explained in the next lecture)

// declaration so that primary() can call expression()
double expression();

// exactly like expression(), but for * and /
double term()
{
    double left = primary();    // get the Primary
    while (true)
    {
        token t = get_token();    // get the next Token ...
        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0)
                throw std::runtime_error("divide by zero");
            left /= d;
            break;
        }
        default:
            return left;    // return the value
        }
    }
}

double primary()    // Number or ‘(‘ Expression ‘)’
{
    token t = get_token();
    switch (t.kind)
    {
    case '(':    // handle ‘(’expression ‘)’
    {
        double d = expression();
        t = get_token();
        if (t.kind != ')')
            throw std::runtime_error("')' expected");
        return d;
    }
    case '8':    // we use ‘8’ to represent the “kind” of a number
        return t.value;    // return the number’s value
    default:
        throw std::runtime_error("primary expected");
    }
}

// read and evaluate: 1   1+2.5   1+2+3.14  etc.
// 	 return the sum (or difference)
double expression()
{
    double left = term();    // get the Term
    while (true)
    {
        token t = get_token();    // get the next token…
        switch (t.kind)
        {                         // ... and do the right thing with it
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            return left;    // return the value of the expression
        }
    }
}

int main()
try
{
    while (std::cin)
        std::cout << expression() << '\n';
    return 0;
}
catch (std::runtime_error& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "exception \n";
    return 2;
}

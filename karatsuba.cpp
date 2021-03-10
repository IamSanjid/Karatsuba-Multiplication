#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#define print(x) std::cout << x << std::endl
#define print_l(x) for (int i = x.size() - 1; i >= 0; i--) std::cout << x[i] << std::endl

std::vector<int> add_from(std::vector<int> l, int start, int end)
{
    std::vector<int> n_l;
    for (int i = start, s = l.size(); i <= end && i < s; i++)
    {
        n_l.push_back(l[i]);
    }
    return n_l;
}

long long get_number(std::vector<int> digits)
{
    long long number = 0;
    long long tens = 1;
    for (int i = 0, s = digits.size(); i < s; i++)
    {
        number += tens * digits[i];
        tens *= 10;
    }
    return number;
}

std::vector<int> get_digits(long long number)
{
    std::vector<int> digits;
    while(number > 10)
    {
        int x = number % 10;
        digits.push_back(x);
        number = (number - x) / 10;
    }
    digits.push_back(number);
    //std::reverse(digits.begin(), digits.end());
    return digits;
}

long long mul_one_digit(std::vector<int> n1_digits, std::vector<int> n2_digits)
{
    /*
                25
                x5
                5*5 = 25 | ans+=5 | carry=2
                5*2 = 10 | 10+carry | ans+=12*10^1 | carry=0
    */
    int carry = 0;
    long long ans = 0;
    long long tens = 1;
    std::vector<int> list = n1_digits;
    int m = n2_digits[0];
    
    if (n1_digits.size() == 1)
    {
        list = n2_digits;
        m = n1_digits[0];
    }

    for (int i = 0, n = list.size(); i < n; i++)
    {
        int s = list[i] * m + carry;
        carry = 0;
        if (i < n - 1)
        {
            int k = s % 10;
            ans += k * tens;
            if (s > 10)
                carry = (s - k) / 10;
            tens *= 10;
        }
        else
        {
            ans += s * tens;
        }
    }
    return ans;
}

long long multiply(std::vector<int> n1_digits, std::vector<int> n2_digits)
{
    if (n1_digits.size() == 1 || n2_digits.size() == 1)
    {
        return mul_one_digit(n1_digits, n2_digits);
    }

    int m = n1_digits.size() - 1;
    if (n1_digits.size() > n2_digits.size())
    {
        m = n2_digits.size() - 1;
    }

    auto high1 = add_from(n1_digits, m, n1_digits.size());
    auto low1 = add_from(n1_digits, 0, m - 1);

    auto high2 = add_from(n2_digits, m, n2_digits.size());
    auto low2 = add_from(n2_digits, 0, m - 1);

    auto z0 = multiply(low1, low2);
    auto z1 = multiply(
        get_digits(get_number(low1) + get_number(high1)),
        get_digits(get_number(low2) + get_number(high2))
    );
    auto z2 = multiply(high1, high2);

    /* (z2 × 10 ^ (m × 2)) + ((z1 - z2 - z0) × 10 ^ m) + z0 */
    long long ans = z2;
    
    long long t1 = 1;
    /* 10^m×2 */
    for (int i = 1; i <= m * 2; i++)
    {
        t1 *= 10;
    }
    /* z2 × 10 ^ (m × 2) */
    ans *= t1;
    
    long long t2 = 1;
    
    for (int i = 1; i <= m; i++)
    {
        t2 *= 10;
    }
    /* (z1 - z2 - z0) × 10 ^ m) */
    z1 = z1 - z2 - z0;
    z1 *= t2;
    
    /* + z0 */
    ans += z1 + z0;

    return ans;
}


int main()
{
    std::cout << multiply(get_digits(12345), get_digits(6789)) << std::endl;   
	return 0;
}

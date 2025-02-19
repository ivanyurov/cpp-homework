#include <iostream>
#include <cmath>
#include <vector>

std::vector<double> SolveQuadrEq(std::vector<double> coeffs)
{
    if (coeffs[0] == 0)
    {
        std::cout << "Введены неверные данные\n";
        return std::vector<double>(0);
    }
    else
    {
        double discriminant = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];
        if (discriminant < 0)
        {
            std::cout << "Уравнение не имеет вещественных корней\n";
            return std::vector<double>(0);
        }
        else if (discriminant == 0)
        {
            std::cout << "Уравнение имеет единственный корень:\n";
            return std::vector<double>(1, -coeffs[1] / (2 * coeffs[0]));
        }
        else
        {
            std::cout << "Уравнение имеет два различных корня:\n";
            std::vector<double> res(2);
            res[0] = (-coeffs[1] - sqrt(discriminant)) / (2 * coeffs[0]);
            res[1] = (-coeffs[1] + sqrt(discriminant)) / (2 * coeffs[0]);
            return res;
        }
    }
}

int main()
{
    std::vector<double> coeffs(3, 0);

    std::cout << "Введите коэффициенты a, b и c:\n";
    std::cin >> coeffs[0] >> coeffs[1] >> coeffs[2];

    std::vector<double> roots = SolveQuadrEq(coeffs);

    if (!roots.empty())
    {
        if (roots.size() == 1)
        {
            std::cout << roots[0] << std::endl;
        }
        else
        {
            std::cout << roots[0] << ", " << roots[1] << std::endl;
        }
    }

    return 0;
}
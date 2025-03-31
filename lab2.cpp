#include <iostream>
#include <fstream>
#include <sstream> //для считывания строки с файла
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib> //для функции rand() для средних студентов
#include <ctime>   //для генерации случайных чисед в функции main

std::vector<double> SolveQuadrEq(double a, double b, double c)
{
    if (a == 0)
    {
        return std::vector<double>(0);
    }
    else
    {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return std::vector<double>(0);
        }
        else if (discriminant == 0)
        {
            return std::vector<double>(1, -b / (2 * a));
        }
        else
        {
            std::vector<double> res(2);
            res[0] = (-b - sqrt(discriminant)) / (2 * a);
            res[1] = (-b + sqrt(discriminant)) / (2 * a);
            return res;
        }
    }
}

class Student
{
public:
    std::string name;
    Student(const std::string &name) : name(name) {}
    virtual std::vector<double> Solve(double a, double b, double c) = 0;
    virtual ~Student() = default;
};

class GoodStudent : public Student // всегда правильный ответ
{
public:
    GoodStudent(const std::string &name) : Student(name) {}
    std::vector<double> Solve(double a, double b, double c) override
    {
        return SolveQuadrEq(a, b, c);
    }
};

class AverageStudent : public Student // имеет вероятность правильно решить уравнение (реализовано через переменную accuracy)
{
    double accuracy;

public:
    AverageStudent(const std::string &name, double acc = 0.5)
        : Student(name), accuracy(acc) {}

    std::vector<double> Solve(double a, double b, double c) override
    {
        if ((double)(rand()) / RAND_MAX < accuracy)
        {
            return SolveQuadrEq(a, b, c);
        }
        else
        {
            return {0.0};
        }
    }
};

class BadStudent : public Student // всегда 0
{
public:
    BadStudent(const std::string &name) : Student(name) {}
    std::vector<double> Solve(double a, double b, double c) override
    {
        return {0.0};
    }
};

class Teacher   // проверяет ответы и сохраняет в таблицу
{

    std::vector<std::pair<std::string, int>> results;

public:

    bool CheckAnswer(double a, double b, double c,
                     const std::vector<double> &studentSolution) const
    {
        std::vector<double> correct = SolveQuadrEq(a, b, c);
        if (correct.size() != studentSolution.size())
            return false;

        for (unsigned int i = 0; i < correct.size(); ++i)
        {
            if (std::abs(correct[i] - studentSolution[i]) > 1e-6)
                return false;
        }
        return true;
    }

    void processSolution(const std::string &studentName,
                         double a, double b, double c,
                         const std::vector<double> &studentSolution)
    {

        bool isCorrect = CheckAnswer(a, b, c, studentSolution);

        for (auto &entry : results)
        {
            if (entry.first == studentName)
            {
                if (isCorrect)
                    entry.second++;
                return;
            }
        }
        results.push_back({studentName, (int)isCorrect});
    }

    void publishResults() const
    {
        std::cout << "\nРезультаты зачета:\n\n";
        for (const auto &res : results)
        {
            std::cout << res.first << ": " << res.second << " правильных\n";
        }
    }
};

std::vector<std::vector<double>> ReadEqFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::vector<double>> equations;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double a, b, c;
        if (iss >> a >> b >> c)
        {
            equations.push_back({a, b, c});
        }
    }
    return equations;
}

int main()
{
    srand(time(0));

    Teacher teacher;
    GoodStudent ivan("Иван");
    AverageStudent artem("Артем", 0.8);
    BadStudent victor("Виктор");

    auto equations = ReadEqFromFile("equations.txt");

    for (const auto &eq : equations)
    {
        double a = eq[0], b = eq[1], c = eq[2];

        teacher.processSolution(ivan.name, a, b, c, ivan.Solve(a, b, c));
        teacher.processSolution(artem.name, a, b, c, artem.Solve(a, b, c));
        teacher.processSolution(victor.name, a, b, c, victor.Solve(a, b, c));
    }

    teacher.publishResults();

    return 0;
}
#include "../include/Wrapper.hpp"
#include "../include/Engine.hpp"
#include <iostream>

// Класс с разными методами для тестов
class Subject
{
public:
    int f3(int arg1, int arg2) // Метод для базового теста: сумма двух int.
    {
        return arg1 + arg2;
    }

    double f_double(double arg1, double arg2) // Метод для теста с double: умножение.
    {
        return arg1 * arg2;
    }

    void f_void(int arg) // Метод void: просто вывод (для теста void-return).
    {
        std::cout << "Void method called with: " << arg << std::endl;
    }

    int f_no_args() // Метод без аргументов: возвращает константу.
    {
        return 42;
    }

    std::string f_string(const std::string &arg) // Метод с string: конкатенация.
    {
        return "Hello, " + arg;
    }

    int f_const(int arg) const // Const-метод: удвоение.
    {
        return arg * 2;
    }

    int f_mismatch(int arg) // Для теста ошибки: просто возвращает.
    {
        return arg;
    }

    int f_multiple(int a, double b, std::string c) // Метод с разными типами.
    {
        std::cout << c << ": " << a << " + " << b << std::endl;
        return static_cast<int>(a + b);
    }
};

int main()
{
    try
    {
        Subject subj;
        Engine engine;

        // Тест 1: Базовый - int метод с двумя аргументами.
        Wrapper wrapper1(&subj, &Subject::f3, {{"arg1", 0}, {"arg2", 0}});
        engine.register_command(&wrapper1, "test1");
        std::cout << "Test 1: " << std::any_cast<int>(engine.execute("test1", {{"arg1", 4}, {"arg2", 5}})) << std::endl; // Ожидаемо: 9

        // Тест 2: Использование дефолта - missing arg2.
        std::cout << "Test 2: " << std::any_cast<int>(engine.execute("test1", {{"arg1", 10}})) << std::endl; // Ожидаемо: 10 (arg2=0)

        // Тест 3: Метод с double - умножение.
        Wrapper wrapper3(&subj, &Subject::f_double, {{"arg1", 0.0}, {"arg2", 1.0}});
        engine.register_command(&wrapper3, "test3");
        std::cout << "Test 3: " << std::any_cast<double>(engine.execute("test3", {{"arg1", 2.5}, {"arg2", 3.0}})) << std::endl; // Ожидаемо: 7.5

        // Тест 4: Void-метод - без возврата, только вызов.
        Wrapper wrapper4(&subj, &Subject::f_void, {{"arg", 0}});
        engine.register_command(&wrapper4, "test4");
        engine.execute("test4", {{"arg", 100}}); // Ожидаемо: Вывод "Void method called with: 100", any пустой

        // Тест 5: Метод без аргументов.
        Wrapper wrapper5(&subj, &Subject::f_no_args, {});
        engine.register_command(&wrapper5, "test5");
        std::cout << "Test 5: " << std::any_cast<int>(engine.execute("test5", {})) << std::endl; // Ожидаемо: 42

        // Тест 6: Метод с string.
        Wrapper wrapper6(&subj, &Subject::f_string, {{"arg", std::string("")}});
        engine.register_command(&wrapper6, "test6");
        std::cout << "Test 6: " << std::any_cast<std::string>(engine.execute("test6", {{"arg", std::string("World")}})) << std::endl; // Ожидаемо: "Hello, World"

        // Тест 7: Const-метод.
        const Subject const_subj; // Const объект для теста.
        Wrapper wrapper7(&const_subj, &Subject::f_const, {{"arg", 0}});
        engine.register_command(&wrapper7, "test7");
        std::cout << "Test 7: " << std::any_cast<int>(engine.execute("test7", {{"arg", 5}})) << std::endl; // Ожидаемо: 10

        // Тест 8: Метод с mixed types и ошибка type mismatch .
        Wrapper wrapper8(&subj, &Subject::f_multiple, {{"a", 0}, {"b", 0.0}, {"c", std::string("")}});
        engine.register_command(&wrapper8, "test8");
        std::cout << "Test 8 success: " << std::any_cast<int>(engine.execute("test8", {{"a", 1}, {"b", 2.5}, {"c", std::string("Sum")}})) << std::endl; // Ожидаемо: 3, вывод "Sum: 1 + 2.5"
        // Для ошибки: передаем string вместо int для "a" - должно бросить exception.
        try
        {
            engine.execute("test8", {{"a", std::string("wrong")}, {"b", 2.5}, {"c", std::string("Sum")}});
        }
        catch (const std::exception &e)
        {
            std::cout << "Test 8 error: " << e.what() << std::endl; // Ожидаемо: Type mismatch...
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
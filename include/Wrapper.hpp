#ifndef WRAPPER_H
#define WRAPPER_H

#include <any>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <tuple> // для хранения распакованных элементов
#include <utility>
#include <stdexcept>
#include <initializer_list>
#include <typeinfo>
#include <type_traits> // для std::decay_t - удаления ссылок и const для унификации типов аргументов
#include <typeindex>   // для сравнения типов в check_types
#include <sstream>

// Распаковывает аргументы из мапы в кортеж.
template <typename... Args, size_t... I>
void unpack_helper(std::tuple<std::decay_t<Args>...> &t, const std::unordered_map<std::string, std::any> &args,
                   const std::vector<std::string> &arg_names, const std::vector<std::any> &defaults,
                   std::index_sequence<I...>)
{
    (..., (void)([&]
                 {
            const std::string& name = arg_names[I];
            auto it = args.find(name);
            if (it != args.end()) {
                try {
                    std::get<I>(t) = std::any_cast<std::decay_t<Args>>(it->second);
                } catch (const std::bad_any_cast&) {
                    std::ostringstream oss;
                    oss << "Type mismatch for argument: " << name
                        << " (expected: " << typeid(std::decay_t<Args>).name()
                        << ", got: " << it->second.type().name() << ")";
                    throw std::invalid_argument(oss.str());
                }
            } else {
                // использует дефолтные значения
                if (defaults.size() > I && defaults[I].has_value()) {
                    try {
                        std::get<I>(t) = std::any_cast<std::decay_t<Args>>(defaults[I]);
                    } catch (const std::bad_any_cast&) {
                        std::ostringstream oss;
                        oss << "Type mismatch in default for: " << name
                            << " (expected: " << typeid(std::decay_t<Args>).name()
                            << ", got: " << defaults[I].type().name() << ")";
                        throw std::invalid_argument(oss.str());
                    }
                } else {
                    throw std::invalid_argument("Missing argument: " + name);
                }
            } }()));
}

// Инкапсулирует метод класса произвольной сигнатуры.
class Wrapper
{
private:
    std::vector<std::string> arg_names;                                                // Упорядоченные имена аргументов
    std::vector<std::any> defaults;                                                    // Дефолтные значения (если не хватает аргументов)
    std::function<std::any(const std::unordered_map<std::string, std::any> &)> caller; // Хоанит логику распаковки и вызова.
    // Проверяет типы дефолтных значений на соответствие аргументам.
    template <typename... Args>
    void check_types(const std::vector<std::pair<std::string, std::any>> &def_pairs)
    {
        std::vector<std::type_index> expected{std::type_index(typeid(std::decay_t<Args>))...};
        for (size_t i = 0; i < def_pairs.size(); ++i)
        {
            if (std::type_index(def_pairs[i].second.type()) != expected[i])
            {
                std::ostringstream oss;
                oss << "Type mismatch in default value for " << def_pairs[i].first
                    << " at position " << i << " (expected: " << expected[i].name()
                    << ", got: " << def_pairs[i].second.type().name() << ")";
                throw std::invalid_argument(oss.str());
            }
        }
    }

public:
    // шаблонный конструктор для неконстантных
    template <typename T, typename R, typename... Args>
    Wrapper(T *o, R (T::*f)(Args...), std::initializer_list<std::pair<std::string, std::any>> d)
    {
        std::vector<std::pair<std::string, std::any>> def_pairs(d);
        if (def_pairs.size() != sizeof...(Args))
        {
            throw std::invalid_argument("Number of defaults does not match number of arguments");
        }

        arg_names.reserve(def_pairs.size());
        defaults.reserve(def_pairs.size());
        for (const auto &p : def_pairs)
        {
            arg_names.push_back(p.first);
            defaults.push_back(p.second);
        }

        check_types<Args...>(def_pairs);

        auto func = [o, f](std::decay_t<Args>... a) -> std::any
        {
            if constexpr (std::is_void_v<R>)
            {
                (o->*f)(a...);
                return {};
            }
            else
            {
                return (o->*f)(a...);
            }
        };

        //  Распаковывает элементы и применяет func
        caller = [this, func](const std::unordered_map<std::string, std::any> &args) -> std::any
        {
            std::tuple<std::decay_t<Args>...> arguments;
            unpack_helper<Args...>(arguments, args, arg_names, defaults, std::make_index_sequence<sizeof...(Args)>{});
            return std::apply(func, arguments);
        };
    }

    // конструктор для константных
    template <typename T, typename R, typename... Args>
    Wrapper(const T *o, R (T::*f)(Args...) const, std::initializer_list<std::pair<std::string, std::any>> d)
    {
        std::vector<std::pair<std::string, std::any>> def_pairs(d);
        if (def_pairs.size() != sizeof...(Args))
        {
            throw std::invalid_argument("Number of defaults does not match number of arguments");
        }

        arg_names.reserve(def_pairs.size());
        defaults.reserve(def_pairs.size());
        for (const auto &p : def_pairs)
        {
            arg_names.push_back(p.first);
            defaults.push_back(p.second);
        }

        check_types<Args...>(def_pairs);

        auto func = [o, f](std::decay_t<Args>... a) -> std::any
        {
            if constexpr (std::is_void_v<R>)
            {
                (o->*f)(a...);
                return {};
            }
            else
            {
                return (o->*f)(a...);
            }
        };

        caller = [this, func](const std::unordered_map<std::string, std::any> &args) -> std::any
        {
            std::tuple<std::decay_t<Args>...> arguments;
            unpack_helper<Args...>(arguments, args, arg_names, defaults, std::make_index_sequence<sizeof...(Args)>{});
            return std::apply(func, arguments);
        };
    }

    // проверяет есть ли caller и вызывает
    std::any execute(const std::unordered_map<std::string, std::any> &args);
};

#endif // WRAPPER_H
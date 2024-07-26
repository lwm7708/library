#pragma once

#include <array>
#include <bitset>
#include <cstddef>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Debug {

    namespace Traits {

        template <typename>
        auto testFormat(unsigned) -> std::false_type;

        template <typename T>
        auto testFormat(int) -> decltype(void(std::declval<T>()._format()), std::true_type());

        template <typename T>
        class HasFormat : public decltype(testFormat<T>(0)) {};

        template <typename>
        class IsMap : public std::false_type {};

        template <typename... Types>
        class IsMap<std::map<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsMap<std::multimap<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsMap<std::unordered_map<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsMap<std::unordered_multimap<Types...>> : public std::true_type {};

        template <typename>
        class IsSequence : public std::false_type {};

        template <typename T, std::size_t N>
        class IsSequence<std::array<T, N>> : public std::true_type {};

        template <typename... Types>
        class IsSequence<std::deque<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSequence<std::forward_list<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSequence<std::list<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSequence<std::vector<Types...>> : public std::true_type {};

        template <typename>
        class IsSet : public std::false_type {};

        template <typename... Types>
        class IsSet<std::multiset<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSet<std::set<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSet<std::unordered_multiset<Types...>> : public std::true_type {};

        template <typename... Types>
        class IsSet<std::unordered_set<Types...>> : public std::true_type {};

        template <typename T>
        constexpr auto has_format_v = HasFormat<T>::value;

        template <typename T>
        constexpr auto is_map_v = IsMap<T>::value;

        template <typename T>
        constexpr auto is_sequence_v = IsSequence<T>::value;

        template <typename T>
        constexpr auto is_set_v = IsSet<T>::value;

    }

    template <typename T>
    auto format(T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr);

    template <typename T>
    auto format(T, std::enable_if_t<std::is_integral_v<T>>* = nullptr);

    template <typename T>
    auto format(const T&, std::enable_if_t<Traits::is_map_v<T>>* = nullptr);

    template <typename T>
    auto format(const T&, std::enable_if_t<Traits::is_sequence_v<T>>* = nullptr);

    template <typename T>
    auto format(const T&, std::enable_if_t<Traits::is_set_v<T>>* = nullptr);

    template <std::size_t N>
    auto format(const std::bitset<N>&);

    template <typename T1, typename T2>
    auto format(const std::pair<T1, T2>&);

    template <typename... Types>
    auto format(const std::priority_queue<Types...>&);

    template <typename... Types>
    auto format(const std::queue<Types...>&);

    template <typename... Types>
    auto format(const std::stack<Types...>&);

    auto format(bool);

    auto format(char);

    auto format(const char*);

    auto format(const std::string&);

    template <typename T>
    auto format(T, std::enable_if_t<Traits::has_format_v<T>>* = nullptr);

    template <typename T, typename F>
    auto formatAdaptor(T, F);

    template <typename It>
    auto formatIt(It, It);

    template <typename T>
    auto combine(const T& value) {

        return format(value);

    }

    template <typename T, typename... Ts>
    auto combine(const T& value, const Ts&... rest) {

        return format(value) + ", " + combine(rest...);

    }

    template <typename T>
    auto format(T value, std::enable_if_t<std::is_floating_point_v<T>>*) {

        auto str_stream = std::ostringstream();

        str_stream << std::fixed << std::setprecision(8) << value;

        return std::string(str_stream.str());

    }

    template <typename T>
    auto format(T value, std::enable_if_t<std::is_integral_v<T>>*) {

        return std::to_string(value);

    }

    template <typename T>
    auto format(const T& value, std::enable_if_t<Traits::is_map_v<T>>*) {

        auto str = std::string("{");

        for (auto it = value.begin(); it != value.end(); ++it) {
            str.append(format(it->first) + ": " + format(it->second));
            if (std::next(it) != value.end()) {
                str.append(", ");
            }
        }

        str.push_back('}');

        return str;

    }

    template <typename T>
    auto format(const T& value, std::enable_if_t<Traits::is_sequence_v<T>>*) {

        return '[' + formatIt(value.begin(), value.end()) + ']';

    }

    template <typename T>
    auto format(const T& value, std::enable_if_t<Traits::is_set_v<T>>*) {

        return '{' + formatIt(value.begin(), value.end()) + '}';

    }

    template <std::size_t N>
    auto format(const std::bitset<N>& value) {

        return value.to_string();

    }

    template <typename T1, typename T2>
    auto format(const std::pair<T1, T2>& value) {

        return '(' + format(value.first) + ", " + format(value.second) + ')';

    }

    template <typename... Types>
    auto format(const std::priority_queue<Types...>& value) {

        return formatAdaptor(
            value,
            [](const std::priority_queue<Types...>& container) {
                return container.top();
            }
        );

    }

    template <typename... Types>
    auto format(const std::queue<Types...>& value) {

        return formatAdaptor(
            value,
            [](const std::queue<Types...>& container) {
                return container.front();
            }
        );

    }

    template <typename... Types>
    auto format(const std::stack<Types...>& value) {

        return formatAdaptor(
            value,
            [](const std::stack<Types...>& container) {
                return container.top();
            }
        );

    }

    auto format(bool value) {

        return std::string(value ? "true" : "false");

    }

    auto format(char value) {

        return std::string({value});

    }

    auto format(const char* value) {

        return std::string(value);

    }

    auto format(const std::string& value) {

        return value;

    }

    template <typename T>
    auto format(T value, std::enable_if_t<Traits::has_format_v<T>>*) {

        return value._format();

    }

    template <typename T, typename F>
    auto formatAdaptor(T value, F f) {

        auto str = std::string("[");

        while (!value.empty()) {
            str.append(format(f(value)));
            value.pop();
            if (!value.empty()) {
                str.append(", ");
            }
        }

        str.push_back(']');

        return str;

    }

    template <typename It>
    auto formatIt(It first, It last) {

        auto str = std::string();

        while (first != last) {
            str.append(format(*first));
            if (std::next(first) != last) {
                str.append(", ");
            }
            ++first;
        }

        return str;

    }

}

auto debug() {

    std::clog << '\n' << std::flush;

}

template <typename T>
auto debug(const T& value) {

    std::clog << Debug::format(value) << '\n' << std::flush;

}

template <typename T, typename... Ts>
auto debug(const T& value, const Ts&... rest) {

    std::clog << Debug::format(value) << ' ';

    debug(rest...);

}

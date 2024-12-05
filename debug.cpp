#include <array>
#include <bitset>
#include <complex>
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

namespace debug {

    namespace traits {

        template <typename, typename = void>
        class has_fmt : public std::false_type {};

        template <typename T>
        class has_fmt<
            T, std::void_t<decltype(std::declval<T>()._fmt())>
        > : public std::true_type {};

        template <typename>
        class is_map : public std::false_type {};

        template <typename... Types>
        class is_map<std::map<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_map<std::multimap<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_map<std::unordered_map<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_map<std::unordered_multimap<Types...>> : public std::true_type {};

        template <typename>
        class is_seq : public std::false_type {};

        template <typename T, std::size_t N>
        class is_seq<std::array<T, N>> : public std::true_type {};

        template <typename... Types>
        class is_seq<std::deque<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_seq<std::forward_list<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_seq<std::list<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_seq<std::vector<Types...>> : public std::true_type {};

        template <typename>
        class is_set : public std::false_type {};

        template <typename... Types>
        class is_set<std::multiset<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_set<std::set<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_set<std::unordered_multiset<Types...>> : public std::true_type {};

        template <typename... Types>
        class is_set<std::unordered_set<Types...>> : public std::true_type {};

        template <typename T>
        constexpr bool has_fmt_v = has_fmt<T>::value;

        template <typename T>
        constexpr bool is_map_v = is_map<T>::value;

        template <typename T>
        constexpr bool is_seq_v = is_seq<T>::value;

        template <typename T>
        constexpr bool is_set_v = is_set<T>::value;

    }

    template <typename T>
    std::string fmt(T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr);

    template <typename T>
    std::string fmt(T, std::enable_if_t<std::is_integral_v<T>>* = nullptr);

    template <typename T>
    std::string fmt(const T&, std::enable_if_t<traits::is_map_v<T>>* = nullptr);

    template <typename T>
    std::string fmt(const T&, std::enable_if_t<traits::is_seq_v<T>>* = nullptr);

    template <typename T>
    std::string fmt(const T&, std::enable_if_t<traits::is_set_v<T>>* = nullptr);

    template <std::size_t N>
    std::string fmt(const std::bitset<N>&);

    template <typename T>
    std::string fmt(const std::complex<T>&);

    template <typename T1, typename T2>
    std::string fmt(const std::pair<T1, T2>&);

    template <typename... Types>
    std::string fmt(const std::priority_queue<Types...>&);

    template <typename... Types>
    std::string fmt(const std::queue<Types...>&);

    template <typename... Types>
    std::string fmt(const std::stack<Types...>&);

    std::string fmt(bool);

    std::string fmt(char);

    std::string fmt(const char*);

    std::string fmt(const std::string&);

    template <typename T>
    std::string fmt(T, std::enable_if_t<traits::has_fmt_v<T>>* = nullptr);

    template <typename T, typename F>
    std::string fmt_adptr(T val, F f) {

        std::string str("[");

        while (!std::empty(val)) {
            str.append(fmt(f(val)));
            val.pop();
            if (!std::empty(val)) {
                str.append(", ");
            }
        }

        str.push_back(']');

        return str;

    }

    template <typename It>
    std::string fmt_it(It it_l, It it_r) {

        std::string str;

        while (it_l != it_r) {
            str.append(fmt(*it_l));
            if (std::next(it_l) != it_r) {
                str.append(", ");
            }
            ++it_l;
        }

        return str;

    }

    template <typename T>
    std::string cmb(const T& val) {

        return fmt(val);

    }

    template <typename T, typename... Ts>
    std::string cmb(const T& val, const Ts&... rest) {

        return fmt(val) + ", " + cmb(rest...);

    }

    template <typename T>
    std::string fmt(T val, std::enable_if_t<std::is_floating_point_v<T>>*) {

        std::ostringstream strm;

        strm << std::fixed << std::setprecision(8) << val;

        return std::string(strm.str());

    }

    template <typename T>
    std::string fmt(T val, std::enable_if_t<std::is_integral_v<T>>*) {

        return std::to_string(val);

    }

    template <typename T>
    std::string fmt(const T& val, std::enable_if_t<traits::is_map_v<T>>*) {

        std::string str("{");

        for (auto it = std::begin(val); it != std::end(val); ++it) {
            str.append(fmt(it->first) + ": " + fmt(it->second));
            if (std::next(it) != std::end(val)) {
                str.append(", ");
            }
        }

        str.push_back('}');

        return str;

    }

    template <typename T>
    std::string fmt(const T& val, std::enable_if_t<traits::is_seq_v<T>>*) {

        return '[' + fmt_it(std::begin(val), std::end(val)) + ']';

    }

    template <typename T>
    std::string fmt(const T& val, std::enable_if_t<traits::is_set_v<T>>*) {

        return '{' + fmt_it(std::begin(val), std::end(val)) + '}';

    }

    template <std::size_t N>
    std::string fmt(const std::bitset<N>& val) {

        return val.to_string();

    }

    template <typename T>
    std::string fmt(const std::complex<T>& val) {

        const T imag = std::imag(val);

        return fmt(
            std::real(val)
        ) + ' ' + (imag >= 0 ? '+' : '-') + ' ' + fmt(std::abs(imag)) + 'i';

    }

    template <typename T1, typename T2>
    std::string fmt(const std::pair<T1, T2>& val) {

        return '(' + cmb(val.first, val.second) + ')';

    }

    template <typename... Types>
    std::string fmt(const std::priority_queue<Types...>& val) {

        return fmt_adptr(
            val,
            [](const std::priority_queue<Types...>& cont) {
                return cont.top();
            }
        );

    }

    template <typename... Types>
    std::string fmt(const std::queue<Types...>& val) {

        return fmt_adptr(
            val,
            [](const std::queue<Types...>& cont) {
                return cont.front();
            }
        );

    }

    template <typename... Types>
    std::string fmt(const std::stack<Types...>& val) {

        return fmt_adptr(
            val,
            [](const std::stack<Types...>& cont) {
                return cont.top();
            }
        );

    }

    std::string fmt(bool val) {

        return std::string(!val ? "false" : "true");

    }

    std::string fmt(char val) {

        return std::string({val});

    }

    std::string fmt(const char* val) {

        return std::string(val);

    }

    std::string fmt(const std::string& val) {

        return val;

    }

    template <typename T>
    std::string fmt(T val, std::enable_if_t<traits::has_fmt_v<T>>*) {

        return val._fmt();

    }

}

void dbg() {

    std::clog << '\n' << std::flush;

}

template <typename T>
void dbg(const T& val) {

    std::clog << debug::fmt(val) << '\n' << std::flush;

}

template <typename T, typename... Ts>
void dbg(const T& val, const Ts&... rest) {

    std::clog << debug::fmt(val) << ' ';

    dbg(rest...);

}

template <typename... Ts>
void dbg_if(bool cond, const Ts&... rest) {

    if (cond) {
        dbg(rest...);
    }

}

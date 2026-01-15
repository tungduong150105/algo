#include <iostream>

template<typename A, typename B> std::ostream& operator<<(std::ostream &os, const std::pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename... Args> std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& t) { os << '('; apply([&os](const Args&... args) { size_t n = 0; ((os << args << (++n != sizeof...(Args) ? ", " : "")), ...); }, t); return os << ')'; }
template<typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type> std::ostream& operator<<(std::ostream &os, const T_container &v) { os << '{'; std::string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
const std::string COLOR_RESET = "\033[0m", BRIGHT_GREEN = "\033[1;32m", BRIGHT_RED = "\033[1;31m", BRIGHT_CYAN = "\033[1;36m";
void dbg_out() { std::cerr << std::endl << COLOR_RESET; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { std::cerr << ' ' << H; dbg_out(T...); }
#ifndef DEBUG
#define dbg(...) std::cerr << "[LINE: " << BRIGHT_GREEN << __LINE__ << COLOR_RESET << "] " << BRIGHT_CYAN << "(" << #__VA_ARGS__ << "):" << COLOR_RESET, dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

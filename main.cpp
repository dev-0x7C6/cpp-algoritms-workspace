#include <algorithm>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

using namespace std::literals;

namespace examples {

namespace data {
namespace match {
constexpr auto set_1 = {4, 5};
}

namespace same {
constexpr auto set_1 = {4, 4, 4};
}

constexpr auto set_1 = {1, 3, 4, 5, 6, 7, 8, 9, 1};
constexpr auto set_2 = {1, 3, 9, 4, 5, 6, 7, 8, 1};
} // namespace data

template <typename type>
using container = std::vector<type>;

template <typename type = int>
constexpr auto all_of(const container<type> &v, const type value) -> bool {
    return std::all_of(
        v.cbegin(), v.cend(),
        [match{value}](auto &&value) -> bool { return value == match; });
}

template <typename type = int>
constexpr auto none_of(const container<type> &v, const type value) -> bool {
    return std::none_of(
        v.cbegin(), v.cend(),
        [match{value}](auto &&value) -> bool { return value == match; });
}

template <typename type = int>
constexpr auto any_of(const container<type> &v, const type value) -> bool {
    return std::any_of(
        v.cbegin(), v.cend(),
        [match{value}](auto &&value) -> bool { return value == match; });
}

template <typename type = int>
constexpr auto for_each(const container<type> &v) -> void {
    std::cout << "for_each print: ";
    std::for_each(v.cbegin(), v.cend(),
        [](auto &&value) { std::cout << value << " "; });
    std::cout << std::endl;
}

template <typename type = int>
constexpr auto for_each_n(const container<type> &v) -> void {
    std::cout << "for_each print: ";
    std::for_each(v.begin(), v.begin() + v.size() / 2,
        [](auto &&value) { std::cout << value << " "; });
    std::cout << std::endl;
}

template <typename type = int>
constexpr auto count(const container<type> &v, const type value) -> bool {
    return std::count(v.cbegin(), v.cend(), value);
}

template <typename type = int>
constexpr auto count_if(const container<type> &v, const type value) -> bool {
    return std::count_if(
        v.cbegin(), v.cend(),
        [match{value}](auto &&value) -> bool { return value == match; });
}

template <typename type = int>
constexpr auto mismatch(const container<type> &v1, const container<type> &v2) {
    auto iterator_pair =
        std::mismatch(v1.begin(), v1.end(), v2.begin(), v2.end());
    // todo
}

template <typename type = int>
constexpr auto find(const container<type> &v, const type value) -> bool {
    return std::find(v.cbegin(), v.cend(), value) != v.cend();
}

template <typename type = int>
constexpr auto find_if(const container<type> &v, const type value) -> bool {
    return std::find_if(v.cbegin(), v.cend(),
               [match{value}](auto &&value) -> bool {
                   return value == match;
               }) != v.cend();
}

template <typename type = int>
constexpr auto find_if_not(const container<type> &v, const type value) -> bool {
    return !examples::find_if(v, value);
}

template <typename type = int>
constexpr auto find_end(const container<type> &v1, const container<type> &match)
    -> bool {
    return std::find_end(v1.cbegin(), v1.cend(), match.cbegin(), match.cend()) !=
        v1.end();
}

template <typename type = int>
constexpr auto find_first_of(const container<type> &v1,
    const container<type> &match) -> bool {
    return std::find_first_of(v1.cbegin(), v1.cend(), match.cbegin(),
               match.cend()) != v1.end();
}

namespace ranges {
template <typename type = int>
constexpr auto all_of(const container<type> &v, const type value) -> bool {
    return std::ranges::all_of(
        v, [match{value}](auto &&value) -> bool { return value == match; });
}
} // namespace ranges

} // namespace examples

auto print_title(std::string_view sv) {
    std::cout << std::endl
              << "=== " << sv << " ===" << std::endl
              << std::endl;
}

template <typename result_type>
auto print_result(std::string_view name, result_type &&result) {
    std::cout << name << ": " << std::forward<result_type>(result) << std::endl;
}

auto main(int argc, char *argv[]) -> int {
    print_title("standard algorithms"sv);

    using namespace examples::data;

    print_result("examples::all_of()"sv, examples::all_of({same::set_1}, 4));
    print_result("examples::any_of()"sv, examples::any_of({set_1}, 4));
    print_result("examples::count()"sv, examples::count({set_1}, 4));
    print_result("examples::count_if()"sv, examples::count_if({set_1}, 4));
    print_result("examples::find()"sv, examples::find({set_1}, 4));
    print_result("examples::find_if()"sv, examples::find_if({set_1}, 4));
    print_result("examples::find_if_not()"sv,
        examples::find_if_not({set_1}, 420));
    print_result("examples::find_end()"sv,
        examples::find_end({set_1}, {match::set_1}));
    print_result("examples::none_of(100)"sv, examples::none_of({set_1}, 100));

    examples::for_each({100, 200, 300});
    examples::for_each_n({set_1});

    print_title("ranges algorithms"sv);
    std::cout << "examples::ranges::all_of(): "
              << examples::ranges::all_of({set_1}, 4) << std::endl;

    return 0;
}

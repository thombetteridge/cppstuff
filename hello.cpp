#include <iostream>
#include <vector>

auto main() -> int
{
    std::cout << "hello world\n";

    std::vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    for (auto& i : v) {
        std::cout << i << "\n";
    }

    return 0;
}

#include <vector>

namespace Sieve {

    auto facts = std::vector<int>();
    auto primes = std::vector<int>();

    auto reserve(int size) {

        facts.resize(size + 1);

        for (auto i = 2; i <= size; ++i) {
            if (facts[i] == 0) {
                facts[i] = i;
                primes.push_back(i);
            }
            for (auto x : primes) {
                if (i * x > size) {
                    break;
                }
                facts[i * x] = x;
                if (x == facts[i]) {
                    break;
                }
            }
        }

    }

}

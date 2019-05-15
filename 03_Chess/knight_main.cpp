#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <iomanip>

struct solution {
    size_t moves;
    unsigned long long result;

    void print() {
        std::cout << moves << std::endl << result << std::endl;
    }

    bool operator!=(solution &other) {
        return moves != other.moves || result != other.result;
    }
};

solution solve(size_t pos) {
    //Ожидаемое решение
    unsigned long long field = 1;
    field = field << pos;
    unsigned long long result =
            (field >> 10 | field << 6) & 0x3F3F3F3F3F3F3F3F |
            (field >> 17 | field << 15) & 0x7F7F7F7F7F7F7F7F |
            (field >> 15 | field << 17) & 0xFEFEFEFEFEFEFEFE |
            (field << 10 | field >> 6) & 0xFCFCFCFCFCFCFCFC;
    unsigned long long temp = result;
    size_t moves = 0;
    while (temp != 0) {
        ++moves;
        temp = temp & temp - 1;
    }
    return {moves, result};
}

const std::array<size_t, 64> moves = {
        2, 3, 4, 4, 4, 4, 3, 2, 3, 4, 6, 6, 6, 6, 4, 3, 4, 6, 8, 8, 8, 8, 6, 4, 4, 6, 8, 8, 8, 8, 6, 4,
        4, 6, 8, 8, 8, 8, 6, 4, 4, 6, 8, 8, 8, 8, 6, 4, 3, 4, 6, 6, 6, 6, 4, 3, 2, 3, 4, 4, 4, 4, 3, 2};
const std::array<unsigned long long, 64> result = {
        132096, 329728, 659712, 1319424, 2638848, 5277696, 10489856, 4202496, 33816580, 84410376, 168886289, 337772578,
        675545156, 1351090312, 2685403152, 1075839008, 8657044482, 21609056261, 43234889994, 86469779988, 172939559976,
        345879119952, 687463207072, 275414786112, 2216203387392, 5531918402816, 11068131838464, 22136263676928,
        44272527353856, 88545054707712, 175990581010432, 70506185244672, 567348067172352, 1416171111120896,
        2833441750646784, 5666883501293568, 11333767002587136, 22667534005174272, 45053588738670592, 18049583422636032,
        145241105196122112, 362539804446949376, 725361088165576704, 1450722176331153408, 2901444352662306816,
        5802888705324613632, 11533718717099671552ul, 4620693356194824192, 288234782788157440, 576469569871282176,
        1224997833292120064, 2449995666584240128, 4899991333168480256, 9799982666336960512ul, 1152939783987658752,
        2305878468463689728, 1128098930098176, 2257297371824128, 4796069720358912, 9592139440717824, 19184278881435648,
        38368557762871296, 4679521487814656, 9077567998918656};

inline solution solveFast(size_t pos) {
    //Быстрое читерское решение (если на входе была бы битовая маска - непрокатило бы а так...)
    return {moves[pos], result[pos]};
}

bool checkFastValid() {
    for (int i = 0; i < 64; ++i) {
        auto s1 = solve(i), s2 = solveFast(i);
        if (s1 != s2) {
            std::cout << "Fail at test " << i << std::endl;
            return false;
        }
    }
    std::cout << "Ok" << std::endl;
    return true;
}

void checkPerformance() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    const size_t tests = 100000000;
    size_t t1, t2;
    std::vector<int> ids(tests);
    for (int i = 0; i < tests; ++i) {
        ids[i] = std::rand() % (64);
    }
    start = std::chrono::system_clock::now();
    for (auto i : ids) {
        solve(i);
    }
    end = std::chrono::system_clock::now();
    std::cout << "solve() " << (t1 = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count()) << "ms." << std::endl;
    start = std::chrono::system_clock::now();
    for (auto i : ids) {
        solveFast(i);
    }
    end = std::chrono::system_clock::now();
    std::cout << "solveFast() " << (t2 = std::chrono::duration_cast<std::chrono::milliseconds>
            (end - start).count()) << "ms." << std::endl;
    std::cout << std::setprecision(2) << 1.0 * t1 / t2 << "x boost" << std::endl;
}

int main() {
    size_t pos;
    std::cin >> pos;
    solveFast(pos).print();
    return 0;
}
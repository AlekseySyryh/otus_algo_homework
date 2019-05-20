#include <iostream>
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

const std::vector<solution> solutions = {
        {2, 132096}, {3, 329728}, {4, 659712}, {4, 1319424}, {4, 2638848}, {4, 5277696}, {3, 10489856}, {2, 4202496},
        {3, 33816580}, {4, 84410376}, {6, 168886289}, {6, 337772578}, {6, 675545156}, {6, 1351090312}, {4, 2685403152},
        {3, 1075839008}, {4, 8657044482}, {6, 21609056261}, {8, 43234889994}, {8, 86469779988}, {8, 172939559976},
        {8, 345879119952}, {6, 687463207072}, {4, 275414786112}, {4, 2216203387392}, {6, 5531918402816},
        {8, 11068131838464}, {8, 22136263676928}, {8, 44272527353856}, {8, 88545054707712}, {6, 175990581010432},
        {4, 70506185244672}, {4, 567348067172352}, {6, 1416171111120896}, {8, 2833441750646784}, {8, 5666883501293568},
        {8, 11333767002587136}, {8, 22667534005174272}, {6, 45053588738670592}, {4, 18049583422636032},
        {4, 145241105196122112}, {6, 362539804446949376}, {8, 725361088165576704}, {8, 1450722176331153408},
        {8, 2901444352662306816}, {8, 5802888705324613632}, {6, 11533718717099671552ul}, {4, 4620693356194824192},
        {3, 288234782788157440}, {4, 576469569871282176}, {6, 1224997833292120064}, {6, 2449995666584240128},
        {6, 4899991333168480256}, {6, 9799982666336960512ul}, {4, 1152939783987658752}, {3, 2305878468463689728},
        {2, 1128098930098176}, {3, 2257297371824128}, {4, 4796069720358912}, {4, 9592139440717824},
        {4, 19184278881435648}, {4, 38368557762871296}, {3, 4679521487814656}, {2, 9077567998918656}};

inline solution solveFast(size_t pos) {
    //Быстрое читерское решение (если на входе была бы битовая маска - непрокатило бы а так...)
    return solutions[pos];
}

bool checkFastValid() {
    for (int i = 0; i < 64; ++i) {
        auto s1 = solve(i), s2 = solveFast(i);
        if (s1 != s2) {
            std::cout << "Fail at test " << i << ":" << std::endl;
            s1.print();
            s2.print();
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
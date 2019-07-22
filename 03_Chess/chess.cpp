#include <iostream>
#include "state.h"
#include <algorithm>
#include <memory>
#include <iomanip>
#include "tests.h"

int main() {
    std::unique_ptr<state> st;
    bool done = false;
    while (!done) {
        std::cout << "q: quit\nt: run tests\nn: new state\n";
        if (st.get() != nullptr) {
            std::cout << "m: move\n" << st->show() <<
                      std::endl << "Is check?:" << std::boolalpha << st->isCheck() <<
                      std::endl << "Is checkmate?:" << st->isCheckmate() <<
                      std::endl << "Is stalemate?:" << st->isStalemate() <<
                      std::endl << "Is draw?:" << st->isDraw() << std::endl << "Possible moves:" << std::endl;

            auto moves = st->getAllNonCheckMoves();
            auto grouped = st->sortAndGroup(moves);
            for (auto fig : grouped) {
                for (auto move:fig) {
                    std::cout << move.name << " ";
                }
                std::cout << std::endl;
            }
        }
        char c;
        std::cin >> c;
        switch (c) {
            case 'q':
                done = true;
                break;
            case 't':
                allTests();
                break;
            case 'm':
                if (st.get() != nullptr) {
                    std::string move;
                    std::cout << "Move?";
                    std::cin >> move;
                    auto moves = st->getAllNonCheckMoves();
                    if (std::count(moves.begin(), moves.end(), move) == 0) {
                        std::cout << "\nImpossible move\n";
                    } else {
                        st->makeMove(move);
                        std::cout << std::endl;
                    }

                }
                break;
            case 'n':
                std::cout << "FEN?";
                std::string fen;
                while (fen.length() == 0)
                    getline(std::cin, fen);
                st = std::make_unique<state>(fen);
                break;

        }
    }
    return EXIT_SUCCESS;
}
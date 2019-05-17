#include <iostream>
#include "state.h"
#include <algorithm>

void parseFEN() {
    std::cout << "Parse FEN:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::string excepted = "  +-----------------+\n"
                           "8 | r n b q k b n r |\n"
                           "7 | p p p p p p p p |\n"
                           "6 | . . . . . . . . |\n"
                           "5 | . . . . . . . . |\n"
                           "4 | . . . . . . . . |\n"
                           "3 | . . . . . . . . |\n"
                           "2 | P P P P P P P P |\n"
                           "1 | R N B Q K B N R |\n"
                           "  +-----------------+\n"
                           "    a b c d e f g h";
    std::string actual = a.show();
    if (excepted == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail" << std::endl;
}

void buildFEN() {
    std::cout << "Build FEN:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KqkQ - 0 1");
    std::string excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string actual = a.build();
    if (excepted == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail" << std::endl;
}


int main() {
    parseFEN();
    buildFEN();
    return EXIT_SUCCESS;
}
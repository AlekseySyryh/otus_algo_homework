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
void moveNoChange() {
    std::cout << "Move number change:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    a.move("e2e2");
    std::string excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    a.move("e7e7");
    excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 2";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail" << std::endl;
    } else {
        std::cout << "OK" << std::endl;

    }
}
void halfMoveNoChange() {
    std::cout << "Half move number change:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    a.move("b1f3");
    char excepted = '1';
    std::string answer = a.build();
    char actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    a.move("e2e4");
    excepted = '0';
    answer = a.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    state b("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    b.move("e5g4");
    excepted = '0';
    answer = b.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 3 fail" << std::endl;
        return;
    }
    state c("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    c.move("b1f3");
    excepted = '5';
    answer = c.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 4 fail" << std::endl;
        return;
    }
    std::cout << "Ok" << std::endl;
}

void noTakeMove() {
    std::cout << "No take move:";
    state a("k7/r7/b7/q7/N7/B7/R7/K7 w - - 15 48");
    a.move("a2h2");
    std::string excepted = "k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    a.move("a5e1");
    excepted = "k7/r7/b7/8/N7/B7/7R/K3q3 w - - 17 49";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

int main() {
    parseFEN();
    buildFEN();
    moveNoChange();
    halfMoveNoChange();
    noTakeMove();
    return EXIT_SUCCESS;
}
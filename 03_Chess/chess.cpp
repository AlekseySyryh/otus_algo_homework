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
        std::cout << "Ok" << std::endl;

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
int main() {
    parseFEN();
    buildFEN();
    moveNoChange();
    halfMoveNoChange();
    return EXIT_SUCCESS;
}
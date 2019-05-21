#pragma once


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
        std::cout << "Fail " << std::endl << actual << std::endl << excepted << std::endl;
}

void buildFEN() {
    std::cout << "Build FEN:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KqkQ - 0 1");
    std::string excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string actual = a.build();
    if (excepted == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail " << std::endl << actual << std::endl << excepted << std::endl;
}

void moveNoChange() {
    std::cout << "Move number change:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    a.makeMove("e2e2");
    std::string excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    a.makeMove("e7e7");
    excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 2";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
    } else {
        std::cout << "OK" << std::endl;

    }
}

void halfMoveNoChange() {
    std::cout << "Half move number change:";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    a.makeMove("b1f3");
    char excepted = '1';
    std::string answer = a.build();
    char actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    a.makeMove("e2e4");
    excepted = '0';
    answer = a.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    state b("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    b.makeMove("e5g4");
    excepted = '0';
    answer = b.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    state c("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    c.makeMove("b1f3");
    excepted = '5';
    answer = c.build();
    actual = answer[answer.length() - 3];
    if (excepted != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    std::cout << "Ok" << std::endl;
}

void noTakeMove() {
    std::cout << "No take move:";
    state a("k7/r7/b7/q7/N7/B7/R7/K7 w - - 15 48");
    a.makeMove("a2h2");
    std::string excepted = "k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    a.makeMove("a5e1");
    excepted = "k7/r7/b7/8/N7/B7/7R/K3q3 w - - 17 49";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void takeMove() {
    std::cout << "Take move:";
    state a("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
    a.makeMove("e4d5");
    std::string excepted = "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    a.makeMove("d8d5");
    excepted = "rnb1kbnr/ppp1pppp/8/3q4/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void pawnConvert() {
    std::cout << "Pawn convert:";
    state a("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5");
    a.makeMove("b2a1q");
    std::string excepted = "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    state b("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5");
    b.makeMove("b2a1b");
    excepted = "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/bNBQKBNR w Kkq - 0 6";
    actual = b.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    state c("rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w K - 0 6");
    c.makeMove("d7c8R");
    excepted = "rnRq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6";
    actual = c.build();
    if (excepted != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    state d("rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w K - 0 6");
    d.makeMove("d7c8N");
    excepted = "rnNq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6";
    actual = d.build();
    if (excepted != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void enPassantFix() {
    std::cout << "En passant fix:";
    state a("rnbqkbnr/ppp1pppp/8/4P3/3p4/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3");
    a.makeMove("c2c4");
    std::string excepted = "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3";
    std::string actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
    a.makeMove("f7f5");
    excepted = "rnbqkbnr/ppp1p1pp/8/4Pp2/2Pp4/8/PP1P1PPP/RNBQKBNR w KQkq f6 0 4";
    actual = a.build();
    if (excepted != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
#ifndef noattackcheck
    state b("rnbqkbnr/ppp1pppp/8/8/3p4/N6N/PPPPPPPP/R1BQKB1R w KQkq - 0 3");
    b.move("b2b4");
    excepted = "rnbqkbnr/ppp1pppp/8/8/1P1p4/N6N/P1PPPPPP/R1BQKB1R b KQkq - 0 3";
    actual = b.build();
    if (excepted!=actual){
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << excepted << std::endl;
        return;
    }
#endif
    std::cout << "OK" << std::endl;
}


void allTests() {
    parseFEN();
    buildFEN();
    moveNoChange();
    halfMoveNoChange();
    noTakeMove();
    takeMove();
    pawnConvert();
    enPassantFix();
}
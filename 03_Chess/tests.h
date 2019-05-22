#pragma once


void parseFEN() {
    std::cout << "Parse FEN:\t\t\t";
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
    std::cout << "Build FEN:\t\t\t";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KqkQ - 0 1");
    std::string excepted = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string actual = a.build();
    if (excepted == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail " << std::endl << actual << std::endl << excepted << std::endl;
}

void moveNoChange() {
    std::cout << "Move number change:\t\t";
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
    std::cout << "Half move number change:\t";
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
    std::cout << "OK" << std::endl;
}

void noTakeMove() {
    std::cout << "No take move:\t\t\t";
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
    std::cout << "Take move:\t\t\t";
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
    std::cout << "Pawn convert:\t\t\t";
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
    std::cout << "En passant fix:\t\t\t";
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

void sortAndGroupMoves() {
    std::cout << "Sort and group moves:\t\t";
    state a("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<move> moves{{"a2a3"},
                            {"b2b3"},
                            {"c2c3"},
                            {"d2d3"},
                            {"e2e3"},
                            {"f2f3"},
                            {"g2g3"},
                            {"h2h3"},
                            {"a2a4"},
                            {"b2b4"},
                            {"c2c4"},
                            {"d2d4"},
                            {"e2e4"},
                            {"f2f4"},
                            {"g2g4"},
                            {"h2h4"},
                            {"b1c3"},
                            {"b1a3"},
                            {"g1h3"},
                            {"g1f3"}};
    std::vector<std::vector<move>> excepted = {
            {{"b1a3"}, {"b1c3"}},
            {{"g1f3"}, {"g1h3"}},
            {{"a2a3"}, {"a2a4"}},
            {{"b2b3"}, {"b2b4"}},
            {{"c2c3"}, {"c2c4"}},
            {{"d2d3"}, {"d2d4"}},
            {{"e2e3"}, {"e2e4"}},
            {{"f2f3"}, {"f2f4"}},
            {{"g2g3"}, {"g2g4"}},
            {{"h2h3"}, {"h2h4"}}};
    std::vector<std::vector<move>> actual = a.sortAndGroup(moves);

    if (excepted == actual) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }
}

void knightMoves() {
    std::cout << "Knight Moves:\t\t\t";
    state a("2k5/8/8/4N3/8/8/P7/2K5 w - - 6 19");
    std::vector<move> possibleMoves = a.getPossibleKnightMoves();
    if (possibleMoves.size() != 8 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5g4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5c6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5g6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5d7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5f7")) != 1) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    a = state("8/1k6/8/8/3K4/8/8/n1n1n2n b - -");
    possibleMoves = a.getPossibleKnightMoves();
    if (possibleMoves.size() != 12 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("a1b3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("a1c2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("c1a2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("c1e2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("c1b3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("c1d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e1c2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e1g2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e1d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e1f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("h1f2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("h1g3")) != 1) {
        std::cout << "Multiple test fail" << std::endl;
        return;
    }

    a = state("2k5/3p1b2/2p3p1/4N3/2q3p1/3r1n2/P7/K7 w - -");
    possibleMoves = a.getPossibleKnightMoves();
    if (possibleMoves.size() != 8 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5g4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5c6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5g6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5d7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e5f7")) != 1) {
        std::cout << "Can take test fail" << std::endl;
        return;
    }

    a = state("8/3R1R2/2R3R1/k3N3/2R3R1/3R1R2/P7/K7 w - -");
    possibleMoves = a.getPossibleKnightMoves();
    if (possibleMoves.size() != 0) {
        std::cout << "Block test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void rockMoves() {
    std::cout << "Rock Moves:\t\t\t";
    state a("2k5/8/8/8/4R3/8/8/K7 w - -");
    std::vector<move> possibleMoves = a.getPossibleRockMoves();
    if (possibleMoves.size() != 14 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4a4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4b4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4g4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4h4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e1")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e8")) != 1) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }
    a = state("2k5/4p3/8/8/1p2R1p1/4p3/8/K7 w - -");
    possibleMoves = a.getPossibleRockMoves();
    if (possibleMoves.size() != 9 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4b4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4g4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e7")) != 1) {
        std::cout << "Take test fail" << std::endl;
        return;
    }
    a = state("2k5/4p3/8/8/1p2r1p1/4p3/8/K7 b - -");
    possibleMoves = a.getPossibleRockMoves();
    if (possibleMoves.size() != 5 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4e6")) != 1) {
        std::cout << "Block test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void bishopMoves() {
    std::cout << "Bishop Moves:\t\t\t";
    state a("4k3/8/8/8/4B3/8/8/4K3 w - - 5 7");
    std::vector<move> possibleMoves = a.getPossibleBishopMoves();
    if (possibleMoves.size() != 13 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4a8")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4b7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4g2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4h1")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4b1")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4g6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4h7")) != 1) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }
    a = state("4k3/8/2R5/5R2/4b3/8/6R1/1R2K3 b - - 5 7");
    possibleMoves = a.getPossibleBishopMoves();
    if (possibleMoves.size() != 8 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4g2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4b1")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f5")) != 1) {
        std::cout << "Take test fail" << std::endl;
        return;
    }
    a = state("4k3/8/2R5/5R2/4B3/8/6R1/1R2K3 w - - 5 7");
    possibleMoves = a.getPossibleBishopMoves();
    if (possibleMoves.size() != 4 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4c2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("e4d3")) != 1) {
        std::cout << "Block test fail" << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void queenMoves() {
    std::cout << "Queen Moves:\t\t\t";
    state a("4k3/8/8/3Q4/8/8/8/4K3 w - - 5 7");
    std::vector<move> possibleMoves = a.getPossibleQueenMoves();
    if (possibleMoves.size() != 27 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5a8")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d8")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5g8")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5b7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5f7")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5c6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5e6")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5a5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5b5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5c5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5e5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5f5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5g5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5h5")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5c4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5e4")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5b3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5f3")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5a2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5g2")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5d1")) != 1 ||
        std::count(possibleMoves.begin(), possibleMoves.end(), move("d5h1")) != 1) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    a = state("4k3/8/2PPP3/2PqP3/8/1P1P4/6P1/4K3 b - - 5 9");
    possibleMoves = a.getPossibleQueenMoves();
    std::vector<move> excepted = {{"d5c6"},
                                  {"d5d6"},
                                  {"d5e6"},
                                  {"d5c5"},
                                  {"d5e5"},
                                  {"d5c4"},
                                  {"d5d4"},
                                  {"d5e4"},
                                  {"d5b3"},
                                  {"d5d3"},
                                  {"d5f3"},
                                  {"d5g2"}};
    if (a.sortAndGroup(possibleMoves) != a.sortAndGroup(excepted)) {
        std::cout << "Take test fail" << std::endl;
        return;
    }
    a = state("4k3/8/2PPP3/2PQP3/8/1P1P4/6P1/4K3 w - -5 9");
    possibleMoves = a.getPossibleQueenMoves();
    excepted = {{"d5c4"},
                {"d5d4"},
                {"d5e4"},
                {"d5f3"}};
    if (a.sortAndGroup(possibleMoves) != a.sortAndGroup(excepted)) {
        std::cout << "Block test fail" << std::endl;
        return;
    }

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


    sortAndGroupMoves();
    knightMoves();
    rockMoves();
    bishopMoves();
    queenMoves();
}
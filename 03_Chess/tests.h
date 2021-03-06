#pragma once


void parseFEN() {
    std::cout << "Parse FEN:\t\t\t";
    state board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::string expected = "  +-----------------+\n"
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
    std::string actual = board.show();
    if (expected == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail " << std::endl << actual << std::endl << expected << std::endl;
}

void buildFEN() {
    std::cout << "Build FEN:\t\t\t";
    state board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KqkQ - 0 1");
    std::string expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string actual = board.build();
    if (expected == actual)
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail " << std::endl << actual << std::endl << expected << std::endl;
}

void moveNoChange() {
    std::cout << "Move number change:\t\t";
    state board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.makeMove("e2e2");
    std::string expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("e7e7");
    expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 2";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
    } else {
        std::cout << "OK" << std::endl;

    }
}

void halfMoveNoChange() {
    std::cout << "Half move number change:\t";
    state board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.makeMove("b1f3");
    char expected = '1';
    std::string answer = board.build();
    char actual = answer[answer.length() - 3];
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("e2e4");
    expected = '0';
    answer = board.build();
    actual = answer[answer.length() - 3];
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = state("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    board.makeMove("e5g4");
    expected = '0';
    answer = board.build();
    actual = answer[answer.length() - 3];
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = state("rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3");
    board.makeMove("b1f3");
    expected = '5';
    answer = board.build();
    actual = answer[answer.length() - 3];
    if (expected != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void noTakeMove() {
    std::cout << "No take move:\t\t\t";
    state board("k7/r7/b7/q7/N7/B7/R7/K7 w - - 15 48");
    board.makeMove("a2h2");
    std::string expected = "k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("a5e1");
    expected = "k7/r7/b7/8/N7/B7/7R/K3q3 w - - 17 49";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void takeMove() {
    std::cout << "Take move:\t\t\t";
    state board("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2");
    board.makeMove("e4d5");
    std::string expected = "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("d8d5");
    expected = "rnb1kbnr/ppp1pppp/8/3q4/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void pawnConvert() {
    std::cout << "Pawn convert:\t\t\t";
    state board("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5");
    board.makeMove("b2a1q");
    std::string expected = "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = state("rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5");
    board.makeMove("b2a1b");
    expected = "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/bNBQKBNR w Kkq - 0 6";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = state("rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w K - 0 6");
    board.makeMove("d7c8R");
    expected = "rnRq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = state("rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w K - 0 6");
    board.makeMove("d7c8N");
    expected = "rnNq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void enPassantFix() {
    std::cout << "En passant fix:\t\t\t";
    state board("rnbqkbnr/ppp1pppp/8/4P3/3p4/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3");
    board.makeMove("c2c4");
    std::string expected = "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("f7f5");
    expected = "rnbqkbnr/ppp1p1pp/8/4Pp2/2Pp4/8/PP1P1PPP/RNBQKBNR w KQkq f6 0 4";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    board = state("rnbqkbnr/ppp1pppp/8/8/3p4/N6N/PPPPPPPP/R1BQKB1R w KQkq - 0 3");
    board.makeMove("b2b4");
    expected = "rnbqkbnr/ppp1pppp/8/8/1P1p4/N6N/P1PPPPPP/R1BQKB1R b KQkq - 0 3";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void enPassantTake() {
    std::cout << "En passant take:\t\t\t";
    state board("rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3");
    board.makeMove("d4c3");
    std::string expected = "rnbqkbnr/ppp1pppp/8/4P3/8/2p5/PP1P1PPP/RNBQKBNR w KQkq - 0 4";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    board = state("r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6");
    board.makeMove("g5f6");
    expected = "r1bqkbnr/ppp1p1pp/2n2P2/4P3/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    board = state("r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6");
    board.makeMove("e5f6");
    expected = "r1bqkbnr/ppp1p1pp/2n2P2/6P1/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    board = state("r2qkbnr/pppbp2p/2n2p2/4PpP1/8/2p2N2/PP1P1P1P/RNBQK2R w KQkq - 0 9");
    board.makeMove("e5f6");
    expected = "r2qkbnr/pppbp2p/2n2P2/5pP1/8/2p2N2/PP1P1P1P/RNBQK2R b KQkq - 0 9";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void kingResetCastling() {
    std::cout << "King reset castling:\t\t\t";
    state board("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16");
    board.makeMove("e8d8");
    std::string expected = "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("e1d1");
    expected = "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R2K3R b - - 2 17";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board = {"r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R3K2R w KQkq - 4 16"};
    board.makeMove("e1d1");
    expected = "r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R2K3R b kq - 5 16";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void rockResetCastling() {
    std::cout << "Rock reset castling:\t\t\t";
    state board("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16");
    board.makeMove("a8b8");
    std::string expected = "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQk - 1 17";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("h1g1");
    expected = "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 b Qk - 2 17";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("h8g8");
    expected = "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 w Q - 3 18";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 3 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("a1c1");
    expected = "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/2R1K1R1 b - - 4 18";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 4 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }


    std::cout << "OK" << std::endl;
}

void shortCastling() {
    std::cout << "Short castling:\t\t\t";
    state board("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16");
    board.makeMove("e8g8");
    std::string expected = "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("e1g1");
    expected = "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R4RK1 b - - 2 17";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void longCastling() {
    std::cout << "Short castling:\t\t\t";
    state board("r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16");
    board.makeMove("e8c8");
    std::string expected = "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17";
    std::string actual = board.build();
    if (expected != actual) {
        std::cout << "Test 1 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }
    board.makeMove("e1c1");
    expected = "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/2KR3R b - - 2 17";
    actual = board.build();
    if (expected != actual) {
        std::cout << "Test 2 fail " << std::endl << actual << std::endl << expected << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void sortAndGroupMoves() {
    std::cout << "Sort and group moves:\t\t";
    state board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
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
    std::vector<std::vector<move>> expected = {
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
    std::vector<std::vector<move>> actual = board.sortAndGroup(moves);

    if (expected == actual) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "Fail" << std::endl;
    }
}

void knightMoves() {
    std::cout << "Knight moves:\t\t\t";
    state board("2k5/8/8/4N3/8/8/P7/2K5 w - - 6 19");
    std::vector<move> expected = {{"e5d3"},
                                  {"e5f3"},
                                  {"e5c4"},
                                  {"e5g4"},
                                  {"e5c6"},
                                  {"e5g6"},
                                  {"e5d7"},
                                  {"e5f7"}};
    std::vector<move> actual = board.getPossibleKnightMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    board = state("8/1k6/8/8/3K4/8/8/n1n1n2n b - - 5 45");
    expected = {{"a1b3"},
                {"a1c2"},
                {"c1a2"},
                {"c1e2"},
                {"c1b3"},
                {"c1d3"},
                {"e1c2"},
                {"e1g2"},
                {"e1d3"},
                {"e1f3"},
                {"h1f2"},
                {"h1g3"}};
    actual = board.getPossibleKnightMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Multiple test fail" << std::endl;
        return;
    }

    board = state("2k5/3p1b2/2p3p1/4N3/2q3p1/3r1n2/P7/K7 w - - 4 32");
    expected = {{"e5d3"},
                {"e5f3"},
                {"e5c4"},
                {"e5g4"},
                {"e5c6"},
                {"e5g6"},
                {"e5d7"},
                {"e5f7"}};
    actual = board.getPossibleKnightMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Can take test fail" << std::endl;
        return;
    }

    board = state("8/3R1R2/2R3R1/k3N3/2R3R1/3R1R2/P7/K7 w - -");
    expected = {};
    actual = board.getPossibleKnightMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Block test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void rockMoves() {
    std::cout << "Rock moves:\t\t\t";
    state board("2k5/8/8/8/4R3/8/8/K7 w - - 6 19");
    std::vector<move> expected = {{"e4a4"},
                                  {"e4b4"},
                                  {"e4c4"},
                                  {"e4d4"},
                                  {"e4f4"},
                                  {"e4g4"},
                                  {"e4h4"},
                                  {"e4e1"},
                                  {"e4e2"},
                                  {"e4e3"},
                                  {"e4e5"},
                                  {"e4e6"},
                                  {"e4e7"},
                                  {"e4e8"}};
    std::vector<move> actual = board.getPossibleRockMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    board = state("2k5/4p3/8/8/1p2R1p1/4p3/8/K7 w - - 6 19");
    expected = {{"e4b4"},
                {"e4c4"},
                {"e4d4"},
                {"e4f4"},
                {"e4g4"},
                {"e4e3"},
                {"e4e5"},
                {"e4e6"},
                {"e4e7"}};
    actual = board.getPossibleRockMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Take test fail" << std::endl;
        return;
    }

    board = state("2k5/4p3/8/8/1p2r1p1/4p3/8/K7 b - - 6 19");
    expected = {{"e4c4"},
                {"e4d4"},
                {"e4f4"},
                {"e4e5"},
                {"e4e6"}};
    actual = board.getPossibleRockMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Block test fail" << std::endl;
        return;
    }

    board = state("2k5/4p3/8/2p5/p1r1r1p1/2p1p3/8/K7 b - - 6 19");
    expected = {{"c4b4"},
                {"c4d4"},
                {"e4d4"},
                {"e4f4"},
                {"e4e5"},
                {"e4e6"}};
    actual = board.getPossibleRockMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Multiple test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void bishopMoves() {
    std::cout << "Bishop moves:\t\t\t";
    state board("4k3/8/8/8/4B3/8/8/4K3 w - - 5 7");
    std::vector<move> expected{{"e4a8"},
                               {"e4b7"},
                               {"e4c6"},
                               {"e4d5"},
                               {"e4f3"},
                               {"e4g2"},
                               {"e4h1"},
                               {"e4b1"},
                               {"e4c2"},
                               {"e4d3"},
                               {"e4f5"},
                               {"e4g6"},
                               {"e4h7"}};
    std::vector<move> actual = board.getPossibleBishopMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2R5/5R2/4b3/8/6R1/1R2K3 b - - 5 7");
    expected = {{"e4c6"},
                {"e4d5"},
                {"e4f3"},
                {"e4g2"},
                {"e4b1"},
                {"e4c2"},
                {"e4d3"},
                {"e4f5"}};
    actual = board.getPossibleBishopMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Take test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2R5/5R2/4B3/8/6R1/1R2K3 w - - 5 7");
    expected = {{"e4d5"},
                {"e4f3"},
                {"e4c2"},
                {"e4d3"}};
    actual = board.getPossibleBishopMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Block test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2R5/5R2/4B3/4R3/6R1/1R2K1B1 w - - 5 7");
    expected = {{"e4d5"},
                {"e4f3"},
                {"e4c2"},
                {"e4d3"},
                {"g1f2"},
                {"g1h2"}};
    actual = board.getPossibleBishopMoves();
    if (board.sortAndGroup(expected) != board.sortAndGroup(actual)) {
        std::cout << "Multiple test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void queenMoves() {
    std::cout << "Queen moves:\t\t\t";
    state board("4k3/8/8/3Q4/8/8/8/4K3 w - - 5 7");
    std::vector<move> actual = board.getPossibleQueenMoves();
    std::vector<move> expected = {{"d5a8"},
                                  {"d5d8"},
                                  {"d5g8"},
                                  {"d5b7"},
                                  {"d5d7"},
                                  {"d5f7"},
                                  {"d5c6"},
                                  {"d5d6"},
                                  {"d5e6"},
                                  {"d5a5"},
                                  {"d5b5"},
                                  {"d5c5"},
                                  {"d5e5"},
                                  {"d5f5"},
                                  {"d5g5"},
                                  {"d5h5"},
                                  {"d5c4"},
                                  {"d5d4"},
                                  {"d5e4"},
                                  {"d5b3"},
                                  {"d5d3"},
                                  {"d5f3"},
                                  {"d5a2"},
                                  {"d5d2"},
                                  {"d5g2"},
                                  {"d5d1"},
                                  {"d5h1"}};
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2PPP3/2PqP3/8/1P1P4/6P1/4K3 b - - 5 9");
    expected = {{"d5c6"},
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
    actual = board.getPossibleQueenMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Take test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2PPP3/2PQP3/8/1P1P4/6P1/4K3 w - - 5 9");
    expected = {{"d5c4"},
                {"d5d4"},
                {"d5e4"},
                {"d5f3"}};
    actual = board.getPossibleQueenMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Block test fail" << std::endl;
        return;
    }

    board = state("4k3/8/2PPP3/2PQP3/1P1Q1P2/1P1P4/1P3PP1/4K3 w - - 5 9");
    expected = {{"d5c4"},
                {"d5e4"},
                {"d5f3"},
                {"d4c4"},
                {"d4e4"},
                {"d4c3"},
                {"d4e3"}};
    actual = board.getPossibleQueenMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Multiple test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void kingMoves() {
    std::cout << "King moves:\t\t\t";
    state board("8/8/8/8/7k/4K3/8/8 w - - 5 43");
    std::vector<move> expected = {{"e3d4"},
                                  {"e3e4"},
                                  {"e3f4"},
                                  {"e3d3"},
                                  {"e3f3"},
                                  {"e3d2"},
                                  {"e3e2"},
                                  {"e3f2"}};
    std::vector<move> actual = board.getPossibleKingMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Middle test fail" << std::endl;
        return;
    }

    board = {"8/8/8/6NN/6Nk/4K1nn/8/8 b - - w - - 3 45"};
    expected = {{"h4g5"},
                {"h4h5"},
                {"h4g4"}};
    actual = board.getPossibleKingMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Block/take test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void pawnMoves() {
    std::cout << "Pawn moves:\t\t\t";
    state board("4k3/8/6p1/8/8/1P6/8/4K3 w - - 1 3");
    std::vector<move> expected = {{"b3b4"}};
    std::vector<move> actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "One step white test fail" << std::endl;
        return;
    }

    board = {"4k3/8/6p1/8/8/1P6/8/4K3 b - - 1 3"};
    expected = {{"g6g5"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "One step black test fail" << std::endl;
        return;
    }

    board = {"4k3/5p2/8/8/8/8/3P4/4K3 w - - 1 3"};
    expected = {{"d2d3"},
                {"d2d4"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Two step white test fail" << std::endl;
        return;
    }

    board = {"4k3/5p2/8/8/8/8/3P4/4K3 b - - 1 3"};
    expected = {{"f7f6"},
                {"f7f5"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Two step black test fail" << std::endl;
        return;
    }

    board = {"3k4/3p4/2R1R3/8/2r1r3/3P4/8/3K4 w - - 1 3"};
    expected = {{"d3d4"},
                {"d3c4"},
                {"d3e4"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Take white test fail" << std::endl;
        return;
    }

    board = {"3k4/8/3p4/2R1R3/2r1r3/3P4/8/3K4 b - - 1 3"};
    expected = {{"d6d5"},
                {"d6c5"},
                {"d6e5"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Take black test fail" << std::endl;
        return;
    }

    board = {"3k4/8/8/5Pp1/8/8/8/1K6 w g6 - 1 3"};
    expected = {{"f5f6"},
                {"f5g6"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "En passant white test fail" << std::endl;
        return;
    }

    board = {"3k4/8/8/8/5Pp1/8/8/1K6 b f3 - 1 3"};
    expected = {{"g4g3"},
                {"g4f3"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "En passant test fail" << std::endl;
        return;
    }

    board = {"3k4/6P1/8/8/8/8/8/1K6 w - - 1 3"};
    expected = {{"g7g8Q"},
                {"g7g8R"},
                {"g7g8B"},
                {"g7g8N"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Convert white test fail" << std::endl;
        return;
    }

    board = {"3k4/8/8/8/8/8/7p/1K6 b - - 1 3"};
    expected = {{"h2h1q"},
                {"h2h1r"},
                {"h2h1b"},
                {"h2h1n"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Convert black test fail" << std::endl;
        return;
    }

    board = {"3k4/8/3r2R1/3P2PP/2r2R2/r3R3/P1PPPP2/1K6 w - - 1 3"};
    expected = {{"c2c3"},
                {"d2d3"},
                {"d2d4"},
                {"f2f3"},
                {"h5h6"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Multiple white test fail" << std::endl;
        return;
    }

    board = {"3k4/p1pp2pp/R1r5/3r3R/1p6/8/4pp2/1K3r2 b - - 1 3"};
    expected = {{"b4b3"},
                {"d7d6"},
                {"e2e1q"},
                {"e2e1b"},
                {"e2e1r"},
                {"e2e1n"},
                {"g7g6"},
                {"g7g5"},
                {"h7h6"}};
    actual = board.getPossiblePawnMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Multiple black test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void allMoves() {
    std::cout << "All moves:\t\t\t";
    state board("N6k/2P5/8/B7/8/RPP5/1P6/QK6 w - - 1 3");
    std::vector<move> expected = {{"a1a2"},
                                  {"a3a2"},
                                  {"a3a4"},
                                  {"a5b4"},
                                  {"a5b6"},
                                  {"a8b6"},
                                  {"b1a2"},
                                  {"b1c1"},
                                  {"b1c2"},
                                  {"b3b4"},
                                  {"c3c4"},
                                  {"c7c8Q"},
                                  {"c7c8R"},
                                  {"c7c8B"},
                                  {"c7c8N"}};
    std::vector<move> actual = board.getAllMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void isCheck() {
    std::cout << "Is check:\t\t\t";
    state board("4k3/3r4/8/8/8/8/8/4K3 w - - 5 10");
    if (board.isCheck()) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    board = {"4k3/4r3/8/8/8/8/8/4K3 w - - 5 10"};
    if (!board.isCheck()) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    board = {"4k3/1B6/8/8/8/8/8/4K3 b - - 5 10"};
    if (board.isCheck()) {
        std::cout << "Test 3 fail" << std::endl;
        return;
    }
    board = {"4k3/8/2B5/8/8/8/8/4K3 b - - 5 10"};
    if (!board.isCheck()) {
        std::cout << "Test 4 fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void noCheckMoves() {
    std::cout << "No check moves:\t\t\t";
    state board("4k3/4r3/8/8/8/8/8/4K3 w - - 5 10");
    std::vector<move> expected = {{"e1d1"},
                                  {"e1d2"},
                                  {"e1f1"},
                                  {"e1f2"}};
    std::vector<move> actual = board.getAllNonCheckMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "White test fail" << std::endl;
        return;
    }

    board = {"4k3/8/2B5/8/8/8/8/4K3 b - - 5 10"};
    expected = {{"e8d8"},
                {"e8f8"},
                {"e8e7"},
                {"e8f7"}};
    actual = board.getAllNonCheckMoves();
    if (board.sortAndGroup(actual) != board.sortAndGroup(expected)) {
        std::cout << "Black test fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void goodCastlingMoves() {
    std::cout << "Good castling moves:\t\t\t";
    state board("r3k2r/8/8/8/8/8/8/R3K2R w K - 5 10");
    std::vector<move> actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 1) {
        std::cout << "White short test fail" << std::endl;
        return;
    }
    board = {"r3k2r/8/8/8/8/8/8/R3K2R w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 1) {
        std::cout << "White long test fail" << std::endl;
        return;
    }
    board = {"r3k2r/8/8/8/8/8/8/R3K2R b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move("e8g8")) != 1) {
        std::cout << "Black short test fail" << std::endl;
        return;
    }
    board = {"r3k2r/8/8/8/8/8/8/R3K2R b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 1) {
        std::cout << "Black long test fail" << std::endl;
        return;
    }

    std::cout << "OK" << std::endl;
}

void badCastlingMoves() {
    std::cout << "Bad castling moves:\t\t\t";
    state board("4k3/8/8/8/8/8/8/4KB1R w K - 5 10");
    std::vector<move> actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 0) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    board = {"4k3/8/8/8/8/8/8/4K1NR w K - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 0) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }

    board = {"4k3/4r3/8/8/8/8/8/4K2R w K - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 0) {
        std::cout << "Test 3 fail" << std::endl;
        return;
    }
    board = {"4k3/5r2/8/8/8/8/8/4K2R w K - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 0) {
        std::cout << "Test 4 fail" << std::endl;
        return;
    }
    board = {"4k3/6r1/8/8/8/8/8/4K2R w K - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1g1"}) != 0) {
        std::cout << "Test 5 fail" << std::endl;
        return;
    }
    board = {"4k3/8/8/8/8/8/8/R2QK3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 6 fail" << std::endl;
        return;
    }
    board = {"4k3/8/8/8/8/8/8/R1B1K3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 7 fail" << std::endl;
        return;
    }
    board = {"4k3/8/8/8/8/8/8/RN2K3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 8 fail" << std::endl;
        return;
    }
    board = {"4k3/4r3/8/8/8/8/8/R3K3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 9 fail" << std::endl;
        return;
    }
    board = {"4k3/3r4/8/8/8/8/8/R3K3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 10 fail" << std::endl;
        return;
    }
    board = {"4k3/2r5/8/8/8/8/8/R3K3 w Q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e1c1"}) != 0) {
        std::cout << "Test 11 fail" << std::endl;
        return;
    }

    board = {"4kb1r/8/8/8/8/8/8/4K3 b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8g8"}) != 0) {
        std::cout << "Test 12 fail" << std::endl;
        return;
    }
    board = {"4k1nr/8/8/8/8/8/8/4K3 b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8g8"}) != 0) {
        std::cout << "Test 13 fail" << std::endl;
        return;
    }
    board = {"4k2r/8/8/8/8/8/4R3/4K3 b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8g8"}) != 0) {
        std::cout << "Test 14 fail" << std::endl;
        return;
    }
    board = {"4k2r/8/8/8/8/8/5R2/4K3 b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8g8"}) != 0) {
        std::cout << "Test 15 fail" << std::endl;
        return;
    }
    board = {"4k2r/8/8/8/8/8/6R1/4K3 b k - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8g8"}) != 0) {
        std::cout << "Test 16 fail" << std::endl;
        return;
    }
    board = {"r2qk3/8/8/8/8/8/8/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 17 fail" << std::endl;
        return;
    }
    board = {"r1b1k3/8/8/8/8/8/8/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 18 fail" << std::endl;
        return;
    }
    board = {"rn2k3/8/8/8/8/8/8/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 19 fail" << std::endl;
        return;
    }
    board = {"r3k3/8/8/8/8/8/4R3/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 20 fail" << std::endl;
        return;
    }
    board = {"r3k3/8/8/8/8/8/3R4/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 21 fail" << std::endl;
        return;
    }
    board = {"r3k3/8/8/8/8/8/2R5/4K3 b q - 5 10"};
    actual = board.getPossibleKingMoves();
    if (std::count(
            actual.begin(),
            actual.end(),
            move{"e8c8"}) != 0) {
        std::cout << "Test 22 fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void checkmate() {
    std::cout << "Is checkmate:\t\t\t";
    state board("k7/8/8/8/8/8/8/7K w - - 5 7");
    if (board.isCheckmate()) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    board = {"k6r/8/8/8/8/8/8/7K w - - 5 8"};
    if (board.isCheckmate()) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    board = {"k5rr/8/8/8/8/8/8/7K w - - 5 8"};
    if (!board.isCheckmate()) {
        std::cout << "Test 3 fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void stalemate() {
    std::cout << "Is stalemate:\t\t\t";
    state board("k7/8/8/8/8/8/8/7K w - - 5 7");
    if (board.isStalemate()) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    board = {"k6r/8/8/8/8/8/8/7K w - - 5 8"};
    if (board.isStalemate()) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    board = {"k5rr/8/8/8/8/8/8/7K w - - 5 8"};
    if (board.isStalemate()) {
        std::cout << "Test 3 fail" << std::endl;
        return;
    }
    board = {"k5r1/8/8/8/8/8/r7/7K w - - 5 8"};
    if (!board.isStalemate()) {
        std::cout << "Test 4 fail" << std::endl;
        return;
    }
    std::cout << "OK" << std::endl;
}

void draw() {
    std::cout << "Is draw:\t\t\t";
    state board("k7/8/8/8/8/8/8/7K w - - 5 7");
    if (board.isDraw()) {
        std::cout << "Test 1 fail" << std::endl;
        return;
    }
    board = {"k7/8/8/8/8/8/8/7K w - - 100 200"};
    if (!board.isDraw()) {
        std::cout << "Test 2 fail" << std::endl;
        return;
    }
    board = {"k5r1/8/8/8/8/8/r7/7K w - - 5 8"};
    if (!board.isDraw()) {
        std::cout << "Test 3 fail" << std::endl;
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
    enPassantTake();
    kingResetCastling();
    rockResetCastling();
    shortCastling();
    longCastling();
    sortAndGroupMoves();
    knightMoves();
    rockMoves();
    bishopMoves();
    queenMoves();
    kingMoves();
    pawnMoves();
    allMoves();
    isCheck();
    noCheckMoves();
    goodCastlingMoves();
    badCastlingMoves();
    checkmate();
    stalemate();
    draw();
}
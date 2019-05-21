#pragma once

class move {
public:
    move(std::string move) : from(move.substr(0, 2)), to(move.substr(2, 2)) {
        valid = (from != to);
        if (move.length() == 5) {
            pawnConvert = true;
            newFigure = move[4];
        } else {
            pawnConvert = false;
        }
    }

    pos from, to;
    bool valid, pawnConvert;
    char newFigure;
};
#pragma once
#include "include.hpp"

class Flashcard {
public:
    Flashcard();
    Flashcard(string q, string a) : question(q), answer(a) {}
    string getQuestion();
    string getAnswer();
    void mistake();
    void mistakeCorrected();
    bool wasMistaken();
    bool cardCompare(Flashcard card);
private:
    string question;
    string answer;
    bool wrongAnswer = false;
};

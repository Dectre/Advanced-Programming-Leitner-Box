#include "flashcard.hpp"

string Flashcard::getQuestion() { return question; }
string Flashcard::getAnswer() { return answer; }
void Flashcard::mistake() { wrongAnswer = true; }
void Flashcard::mistakeCorrected() { wrongAnswer = false; }
bool Flashcard::wasMistaken() { return wrongAnswer; }
bool Flashcard::cardCompare(Flashcard card) {
    if (card.question == question)
        return true;
    return false;
}
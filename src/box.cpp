#include "box.hpp"

Box::Box() {}
vector<Flashcard> &Box::getFlashcards() { return flashcards; }
void Box::addFlashcard(Flashcard card) { flashcards.push_back(card); }
void Box::removeFlashcard(size_t index) { flashcards.erase(flashcards.begin() + index); }
int Box::findFlashcardinBox(Flashcard card)
{
    for (int i = 0; i < flashcards.size(); i++)
    {
        if (flashcards[i].cardCompare(card))
            return i;
    }
    return -1;
}
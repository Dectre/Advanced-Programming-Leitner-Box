#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string CMD_STREAK = "streak";
const string CMD_ADD_FLASHCARD = "add_flashcard";
const string CMD_REVIEW_TODAY = "review_today";
const string CMD_GET_REPORT = "get_report";
const string CMD_GET_PROGRESS_REPORT = "get_progress_report";
const string CMD_NEXT_DAY = "next_day";

class Flashcard {
public:
    string getQuestion() { return question; }
    string getAnswer() { return answer; }
    bool wasMistaken() { return wrongAnswer; }
private:
    string question;
    string answer;
    bool wrongAnswer = false;
};

class Box {
public:
    vector<Flashcard>& getFlashcards() { return flashcards; }
    void addFlashcard(Flashcard card) { flashcards.push_back(card); }
    void removeFlashcard(size_t index) { flashcards.erase(flashcards.begin() + index);
    }

private:
    vector<Flashcard> flashcards;
};

class LeitnerBox {
public:
    LeitnerBox() : streak(0), day(1) {
        for (int i = 1; i<= 4; i++) {
            boxes[i] = Box();
        }
    }
    void reportStreak();
private:
    vector<Box> boxes;
    int streak;
    int day;
};

int main() {
    cout << "Test" << endl;
    return 0;
}

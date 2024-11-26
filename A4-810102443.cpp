#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const string CMD_STREAK = "streak";
const string CMD_ADD_FLASHCARD = "add_flashcard";
const string CMD_REVIEW_TODAY = "review_today";
const string CMD_GET_REPORT = "get_report";
const string CMD_GET_PROGRESS_REPORT = "get_progress_report";
const string CMD_NEXT_DAY = "next_day";

const int level1 = 1;
const int level2 = 3;
const int level3 = 7;
const int level4 = 30;

const int NUM_OF_BOXES = 4;

const int DAILY = 0;
const int THREEDAYS = 0;
const int WEEKLY = 0;
const int MONTHLY = 0;

const string MSG_FLASHCARD_ADDED_SUCCESSFULLY = "flashcards added to the daily box";

class Flashcard {
public:
    Flashcard(string q, string a) : question(q), answer(a) {}
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
    Box() = default;
    vector<Flashcard>& getFlashcards() { return flashcards; }
    void addFlashcard(Flashcard card) { flashcards.push_back(card); }
    void removeFlashcard(size_t index) { flashcards.erase(flashcards.begin() + index); }
    void printFlashcards() { displayFlashcards(); }
private:
    vector<Flashcard> flashcards;
    void displayFlashcards() {
        for (auto flashcard : flashcards) {
            cout << "Question: " << flashcard.getQuestion() << endl;
            cout << "Answer: " << flashcard.getAnswer() << endl;
        }
        return;
    }
};

class Day {
public:
    int getCorrectAnswers() { return correctAnswers; }
    int getWrongAnswers() { return wrongAnswers; }
    int getTotalAnswers() {return totalAnswers; }
private:
    int correctAnswers;
    int wrongAnswers;
    int totalAnswers;
};

class LeitnerBox {
public:
    LeitnerBox() : streak(0), day(1), boxes(NUM_OF_BOXES) {}

    void reportStreak();

    Box& getBox(int boxLevel) { return boxes[boxLevel]; }

private:
    vector<Box> boxes;
    int streak;
    int day;
};

vector<string> splitStringBy(const string& sentence, char delimiter) {
    vector<string> words;
    istringstream stream(sentence);
    string word;

    while(getline(stream, word, delimiter)) {
        words.push_back(word);
    }

    return words;
}

void addFlashcard(LeitnerBox& leitnerBox, vector<string> argument) {
    int numOfQuestions = stoi(argument[1]);
    for (int i = 0; i < numOfQuestions; i++) {
        string question;
        string answer;
        getline(cin, question);
        getline(cin, answer);
        Flashcard newCard(question, answer);
        leitnerBox.getBox(DAILY).addFlashcard(newCard);
    }
    cout << MSG_FLASHCARD_ADDED_SUCCESSFULLY << endl;
    return;
}

void reviewFlashcards(LeitnerBox& leitnerBox, vector<Day>& days, vector<string> argument) {
}
void nextDay(LeitnerBox& leitnerBox, vector<Day>& days) {
}
void handleInput(LeitnerBox& leitnerBox, vector<Day>& days) {
    string input;
    while (getline(cin, input)) {
        vector<string> argument = splitStringBy(input, ' ');
        string command = argument[0];
        if (command == CMD_ADD_FLASHCARD) {
            addFlashcard(leitnerBox, argument);
            leitnerBox.getBox(DAILY).printFlashcards();
        }
        if (command == CMD_REVIEW_TODAY) {
            reviewFlashcards(leitnerBox, days, argument);
        }
        if (command == CMD_NEXT_DAY) {
            nextDay(leitnerBox, days);
        }

        if (command == CMD_STREAK) { }
        if (command == CMD_GET_REPORT)
        if (command == CMD_GET_PROGRESS_REPORT) { }
    }
}

int main() {
    LeitnerBox leitnerBox;
    vector<Day> days;
    handleInput(leitnerBox, days);
}

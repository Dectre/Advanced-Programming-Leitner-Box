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

const vector<int> LEVELS = {1, 3, 7, 10};

const int NUM_OF_BOXES = 4;

const int DAILY = 0;
const int THREEDAYS = 1;
const int WEEKLY = 2;
const int MONTHLY = 3;

const string MSG_FLASHCARD_ADDED_SUCCESSFULLY = "flashcards added to the daily box";
const vector<string> MSG_NEXT_DAY = {"Good morning! Today is day ", " of our journey.\nYour current streak is: "
                                    , "\nStart reviewing to keep your streak!"};
const string MSG_CORRECT_ANSWER = "Your answer was correct! Well done, keep it up!";
const vector<string> MSG_WRONG_ANSWER = {"Your answer was incorrect. Don't worry! The correct answer is: ",
                                         ". Keep practicing!"};
const string MSG_FLASHCARD_QUESTION = "Flashcard: ";
const string MSG_YOUR_ANSWER = "Your Answer: ";

class Flashcard {
public:
    Flashcard();
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
    Day() : correctAnswers(0), wrongAnswers(0), totalAnswers(0) {}
    int getCorrectAnswers() { return correctAnswers; }
    int getWrongAnswers() { return wrongAnswers; }
    int getTotalAnswers() {return totalAnswers; }
    void incCorrectAnswers() { correctAnswers+= 1; }
    void incWrongAnswers() { wrongAnswers+= 1; }
    void incTotalAnswers() { totalAnswers+= 1; }
private:
    int correctAnswers;
    int wrongAnswers;
    int totalAnswers;
};

class LeitnerBox {
public:
    LeitnerBox() : streak(0), day(1), boxes(NUM_OF_BOXES) {}
    int getStreak() { return streak; };
    int getDay() { return day; };
    void getTodayFlashcards(vector<Flashcard>& todayFlashcards) {
        for (int i = 3 ; i > -1; i--) {
            if (day % LEVELS[i] == 0) {
                for (auto flashcard: getBox(i).getFlashcards()) {
                    todayFlashcards.push_back(flashcard);
                }
            }
        }
    }
    void incStreak() { streak+= 1; }
    void resetStreak() {streak = 0; }
    Box& getBox(int boxLevel) { return boxes[boxLevel]; }
    void incDay() { day+= 1; }


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
}

bool getAnswer(string answer) {
    string userAnswer;
    getline(cin, userAnswer);

    if (userAnswer.compare(answer) == 0) {
        cout << MSG_CORRECT_ANSWER << endl;
        return true;
    }
    cout << MSG_WRONG_ANSWER[0] << answer << MSG_WRONG_ANSWER[1] << endl;
    return false;
}

void grading(Day& day, bool result) {
    if (result)
        day.incCorrectAnswers();
    else
        day.incWrongAnswers();
    day.incTotalAnswers();
}

void reviewFlashcards(vector<Flashcard>& todayFlashcards, vector<Day>& days, vector<string> argument) {
    int cardsNum = stoi(argument[1]);
    Day today;
    for (int i = 0; i < cardsNum ; i++) {
        Flashcard flashcard = todayFlashcards[i];
        cout << MSG_FLASHCARD_QUESTION << flashcard.getQuestion() << endl;
        cout << MSG_YOUR_ANSWER;
        string correctAnswer = flashcard.getAnswer();
        grading(today, getAnswer(correctAnswer));
    }
    days.push_back(today);
}

void nextDay(LeitnerBox& leitnerBox, vector<Day>& days) {
    Day temp;
    days.push_back(temp);
    //checkStreak();
    leitnerBox.incDay();
    cout << MSG_NEXT_DAY[0] << leitnerBox.getDay() << MSG_NEXT_DAY [1] << 0 << MSG_NEXT_DAY[2] << endl;
}

bool checkRemainingFlashcards(vector<Flashcard>& todayFlashcards){
    if (todayFlashcards.size() == 0)
        return true;
    return false;
}

void checkStreak(LeitnerBox& leitnerBox, vector<Flashcard>& todayFlashcards) {
    if (checkRemainingFlashcards(todayFlashcards)){
        leitnerBox.incStreak();
        return;
    }
    leitnerBox.resetStreak();
    return;
}

void handleInput(LeitnerBox& leitnerBox, vector<Day>& days) {
    string input;
    while (getline(cin, input)) {
        vector<string> argument = splitStringBy(input, ' ');
        string command = argument[0];

        vector<Flashcard> todayFlashcards;
        leitnerBox.getTodayFlashcards(todayFlashcards);

        if (command == CMD_ADD_FLASHCARD) {
            addFlashcard(leitnerBox, argument);
        }
        if (command == CMD_REVIEW_TODAY) {
            reviewFlashcards(todayFlashcards, days, argument);
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

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

const vector<int> LEVELS = {1, 3, 7, 30};

const int NUM_OF_BOXES = 4;

const int DAILY = 0;
const int THREEDAYS = 1;
const int WEEKLY = 2;
const int MONTHLY = 3;

const string MSG_FLASHCARD_ADDED_SUCCESSFULLY = "flashcards added to the daily box";
const vector<string> MSG_NEXT_DAY = {"Good morning! Today is day ", " of our journey.\nYour current streak is: "
        , "\nStart reviewing to keep your streak!"};
const string MSG_CORRECT_ANSWER = "\nYour answer was correct! Well done, keep it up!";
const vector<string> MSG_WRONG_ANSWER = {"\nYour answer was incorrect. Don't worry! The correct answer is: ",
                                         ". Keep practicing!"};
const string MSG_FLASHCARD_QUESTION = "Flashcard: ";
const string MSG_YOUR_ANSWER = "Your answer: ";
const string MSG_TODAYS_REVIEW = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!";
const vector<string> MSG_STREAK = {"Your current streak is: ",
                                   "\nKeep going!"};
const vector<string> MSG_REPORT = {"Day: ",  "Correct Answers: ", "Incorrect Answers: ", "Total: ", " to "};
const vector<string> MSG_PROGRESS_REPORT = {"Challenge Progress Report:\n", "Day of the Challenge: ",
                                            "Streak: ", "Total Days Participated: ", "Mastered Flashcards: ",
                                            "\nKeep up the great work! You're making steady progress toward mastering your flashcards."};

#include <iostream>
#include <vector>
#include <string>
#include <cctype>


#define MAX_PIN    10
#define MAX_FRAME  10

// check for valid input
bool isNumber(const std::string& s)
{
    if (s.empty()) return false;
    for (char ch : s)
        if (!std::isdigit(static_cast<unsigned char>(ch)))
            return false;
    return true;
}

int readRoll(int frame, int rollNo, int remainingPins)
{
    while (true)
    {
        std::string token;
        std::cout << "Frame " << frame << ", roll " << rollNo
                  << " (0‑" << remainingPins << "): ";
        std::cin  >> token;

        if (!isNumber(token))
        {
            std::cout << "Please enter only number"<< std::endl;
            continue;
        }

        int pins = std::stoi(token);
        if (pins < 0 || pins > remainingPins)
        {
            std::cout << "Enter a value between 0 and "
                      << remainingPins << ".\n";
            continue;
        }
        return pins;
    }
}

class BowlingGame
{
public:
    explicit BowlingGame(const std::vector<int>& rolls) : mRolls(rolls) {}

    int calculateScore() const
    {
        int score = 0;
        std::size_t rollIdx = 0;

        for (int frame = 0; frame < MAX_FRAME; ++frame)
        {
            if (mRolls[rollIdx] == MAX_PIN)
            {
                score += MAX_PIN + mRolls[rollIdx + 1] + mRolls[rollIdx + 2];
                ++rollIdx;
            }
            else if (mRolls[rollIdx] + mRolls[rollIdx + 1] == MAX_PIN)
            {
                score += MAX_PIN + mRolls[rollIdx + 2];
                rollIdx += 2;
            }
            else
            {
                score += mRolls[rollIdx] + mRolls[rollIdx + 1];
                rollIdx += 2;
            }
        }
        return score;
    }

private:
    std::vector<int> mRolls;
};

int main()
{
    std::vector<int> rolls;

    for (int frame = 1; frame <= MAX_FRAME; ++frame)
    {
        int first = readRoll(frame, 1, MAX_PIN);
        rolls.push_back(first);

        if (frame < MAX_FRAME)
        {
            // strike
            if (first == MAX_PIN) continue;

            int second = readRoll(frame, 2, MAX_PIN - first);
            rolls.push_back(second);
        }
        else
        {
            int second = readRoll(frame, 2,
                                   (first == MAX_PIN) ? MAX_PIN
                                                      : MAX_PIN - first);
            rolls.push_back(second);

            bool strikeOrSpare = (first == MAX_PIN) ||
                                 (first + second == MAX_PIN);

            // Extra ball handling
            if (strikeOrSpare)
            {
                int third = readRoll(frame, 3, MAX_PIN);
                rolls.push_back(third);
            }
        }
    }

    BowlingGame game(rolls);
    std::cout << "\nFinal score: " << game.calculateScore() << "\n";
    return 0;
}

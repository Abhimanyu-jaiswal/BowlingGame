#include <iostream>
#include <vector>

class BowlingGame {
public:
    BowlingGame(const std::vector<int>& rolls) : mRolls(rolls) {}
    
    int calculateScore() {
        int score = 0;
        int rollIndex = 0;
        
        // for 1 to 9 frames
        for (int frame = 0; frame < 9; ++frame) {
            if (isStrike(rollIndex)) {
                score += 10 + strikeBonus(rollIndex);
                rollIndex += 1;
            } else if (isSpare(rollIndex)) {
                score += 10 + spareBonus(rollIndex);
                rollIndex += 2;
            } else {
                score += frameScore(rollIndex);
                rollIndex += 2;
            }
        }
        
        // for 10th frame
        score += calculate10thFrame(rollIndex);
        
        return score;
    }

private:
    std::vector<int> mRolls;
    
    bool isStrike(int index) {
        return index < mRolls.size() && mRolls[index] == 10;
    }
    
    bool isSpare(int index) {
        return index + 1 < mRolls.size() && mRolls[index] + mRolls[index + 1] == 10;
    }
    
    int strikeBonus(int index) {
        if (index + 2 >= mRolls.size()) return 0;
        return mRolls[index + 1] + mRolls[index + 2];
    }
    
    int spareBonus(int index) {
        if (index + 2 >= mRolls.size()) return 0;
        return mRolls[index + 2];
    }
    
    int frameScore(int index) {
        if (index + 1 >= mRolls.size()) return 0;
        return mRolls[index] + mRolls[index + 1];
    }
    
    int calculate10thFrame(int rollIndex) {
        if (rollIndex >= mRolls.size()) return 0;
        
        // Case 1: Strike in first roll of 10th frame
        if (mRolls[rollIndex] == 10) {
            return mRolls[rollIndex] + mRolls[rollIndex + 1] ;
        }
        
        // Case 2: Spare in 10th frame
        if (rollIndex + 1 < mRolls.size() && mRolls[rollIndex] + mRolls[rollIndex + 1] == 10) {
            return mRolls[rollIndex] + mRolls[rollIndex + 1] + mRolls[rollIndex + 2];
        }
        
        // Case 3: Normal case
        return mRolls[rollIndex] + mRolls[rollIndex + 1];
    }
};

int main() {
    
    std::vector<int> rollsInput1 = {
        1, 4, 4, 5, 6 ,4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 8, 6
    };

    std::vector<int> rollsInput2 = {
        4, 5, 4, 5, 6, 4, 10, 9, 0, 10, 10, 7, 2, 10, 10, 2, 6
    };
    
    BowlingGame game1(rollsInput1);
    BowlingGame game2(rollsInput2);
    std::cout << "Total Score: " << game1.calculateScore() << std::endl;
    std::cout << "Total Score: " << game2.calculateScore() << std::endl;
    
    return 0;
}


// 1. strike on the first try
// 2. sum of two try should not be greater than 10(MACRO) max pin, max_frame;
// 3. no character is allowed


// UMBC - CMSC 341 - Fall 2024 - Proj0
#include "solitaire.h"
using namespace std;

class Tester{
    public:
    //This function will test the error case for the constructor
    //If it creates an empty object with all the attributes set to zero
    bool errorConstructorTest(Solitaire frenchBoard);
    //This function tests a normal case for the constructor
    //If it creates the correct object, all the attributes will be set to ENGLISH or ENGLISHSIZE
    bool normalConstructorTest(Solitaire englishBoard);
    //This function tests whether newBoard works for error cases
    //the newBoard function is supposed to detect the object is empty and return false
    bool errorNewBoardTest(Solitaire frenchBoard);
    //This function tests newBoard for normal cases
    //newBoard should check if there is a board, then re-intialize the board into the new shape
    //this test performs a move to change the board, then sees if the board is re-intialized
    bool normalNewBoardTest(Solitaire englishBoard);
    //This function tests changeBoard when given the same board
    //the function should discover its the same board and re-intialize
    //this test performs a move to change then board from it's default values
    //then it runs the newBoard function to see if it re-intializes
    bool sameBoardChangeBoardTest(Solitaire englishBoard);
    //This function tests changeBoard when given a different board
    //the function is expected to create a new Solitaire object
    //the test is changing a board from an english board to a diamond board, then back to english
    bool difBoardChangeBoardTest(Solitaire englishBoard);
    //This function tests change board by changing the board to an unsupported board
    //then changing it back to an english back
    bool changeBoardToUnsupportedBoard(Solitaire englishBoard);
    //This function tests normal cases for the function play
    //The test tries multiple cases that should move
    //The test returns true if the board removes a marble with each move
    bool normalCasesPlayTest(Solitaire englishBoard);
    //This function tests error cases for the function play
    bool errorCasesPlayTest(Solitaire englishBoard);
    //This function tests the copy constructor when trying to use an empty board
    bool errorCaseCopyConstructorTest(Solitaire frenchBoard);
    //This function tests the copy constructor for normal cases
    //tests to see if the board has the same attributes, but at a different location
    bool normalCaseCopyConstructorTest(Solitaire englishBoard);
    //This functions tests whether the clear function deallocates the memory of the board
    bool clearTest(Solitaire englishBoard);
};
    

int main(){
    //counts the amounts of tests passed
    int testsPassed = 0;
    const int totalTests = 12;
    //the two test boards.
    Solitaire frenchBoard(FRENCH);
    Solitaire englishBoard(ENGLISH);
    //tester object
    Tester tester;
    if(tester.errorConstructorTest(frenchBoard) == true){
        testsPassed++;
    }
    if(tester.normalConstructorTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.errorNewBoardTest(frenchBoard) == true){
        testsPassed++;
    }
    if(tester.normalNewBoardTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.sameBoardChangeBoardTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.difBoardChangeBoardTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.changeBoardToUnsupportedBoard(englishBoard) == true){
        testsPassed++;
    }
    if(tester.normalCasesPlayTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.errorCasesPlayTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.errorCaseCopyConstructorTest(frenchBoard) == true){
        testsPassed++;
    }
    if(tester.normalCaseCopyConstructorTest(englishBoard) == true){
        testsPassed++;
    }
    if(tester.clearTest(englishBoard) == true){
        testsPassed++;
    }
    //if all the tests passed, these will be equal
    if(testsPassed == totalTests){
        cout << "** ALL TESTS PASSED **" << endl;
    }else{
        cout << "Not all tests were passed." << endl;
    }
    return 0;
}

bool Tester::errorConstructorTest(Solitaire frenchBoard){
        //all the french board attributes should be set to zero
        if(frenchBoard.m_numMarbles == NONE
        && frenchBoard.m_numRows == NONE 
        && frenchBoard.m_numColumns == NONE 
        && frenchBoard.m_shape == NONE){
            cout <<"Error case for the constructor has passed!" << endl;
            return true;
        }else{
            cout << "Error case for the constructor has failed" << endl;
        }
        return false;
    }
    bool Tester::normalConstructorTest(Solitaire englishBoard){
        //checks the english board attributes and checks if the middle of the board is a hole
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_numRows == ENGLISHSIZE
        && englishBoard.m_numColumns == ENGLISHSIZE 
        && englishBoard.m_shape == ENGLISH
        &&englishBoard.m_board[3][3] == HOLE){
            cout <<"Normal case for the constructor has passed!" << endl;
            return true;
        }else{
            cout << "Normal case for the constructor has failed" << endl;
        }
        return false;
    }
    bool Tester::errorNewBoardTest(Solitaire frenchBoard){
        //if someone tries to create a new unsupported board, the function will return false
        if(frenchBoard.newBoard() == false){
            cout << "Error case for newBoard has passed!" << endl;
            return true;
        }else{
            cout << "Error case for newBoard has failed" << endl;
        }
        return false;

    }

    bool Tester::normalNewBoardTest(Solitaire englishBoard){
        bool moveTest = false;
        bool newBoardTest = false;
        bool newBoardReturn = false;
        //after this move, there should be 31 marbles
        //and the middle coordinate should be a marble
        englishBoard.play(pair<int,int>(5,3), pair<int,int>(3,3));
        if(englishBoard.m_numMarbles == 31 
        && englishBoard.m_board[3][3] == MARBLE){
            moveTest = true;
        }
        //newBoard should return true if it re-intialized the board
        newBoardReturn = englishBoard.newBoard();
        //after using newBoard, there should be 32 marbles again
        //,the middle coordinate should be a hole and the function should return true
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_board[3][3] == HOLE){
            newBoardTest = true;
        }
        if(newBoardTest == true && moveTest == true && newBoardReturn == true){
            cout << "The boardTest for normal cases has passed!" << endl;
            return true;
        }else{
            cout << "normalBoardTest has failed." << endl;
        }
        return false;
    }
    bool Tester::sameBoardChangeBoardTest(Solitaire englishBoard){
        bool moveTest = false;
        bool changeBoardTest = false;
        englishBoard.play(pair<int,int>(1,3), pair<int,int>(3,3));
        //Does a move, to show the board is actually re-intializing instead of just staying the same
        if(englishBoard.m_numMarbles == 31
        && englishBoard.m_board[3][3] != HOLE){
            moveTest = true;
        }
        englishBoard.changeBoard(ENGLISH);
        //shows the board re-initializes to the same shape
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_board[3][3] == HOLE){
            changeBoardTest = true;
        }
        if(changeBoardTest == true && moveTest == true){
            cout << "The changeBoard when given the same type passed!"<< endl;
            return true;
        }else{
            cout << "The changeBoard test didn't pass when given the same board type" << endl;
        }
        return false;
    }
    bool Tester::difBoardChangeBoardTest(Solitaire englishBoard){
        bool correctEnglishCount = false;
        bool correctDiamondCount = false;
        //checks if the board is english to begin with
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_numColumns == ENGLISHSIZE
        && englishBoard.m_numRows == ENGLISHSIZE 
        && englishBoard.m_shape == ENGLISH){
            correctEnglishCount = true;
        }
        //changes the board to diamond
        englishBoard.changeBoard(DIAMOND);
        //checks to see if the board is diamond by counting the marbles
        if(englishBoard.m_numMarbles == NUMDIAMONDMARBLES
        && englishBoard.m_numColumns == DIAMONDSIZE
        && englishBoard.m_numRows == DIAMONDSIZE
        && englishBoard.m_shape == DIAMOND){
            correctDiamondCount = true;
        }
        //change back to english
        englishBoard.changeBoard(ENGLISH);
        //if the board didn't change back to english, the test fails
        if(englishBoard.m_numMarbles != NUMENGLISHMARBLES
        && englishBoard.m_numColumns != ENGLISHSIZE
        && englishBoard.m_numRows != ENGLISH
        && englishBoard.m_shape != ENGLISH){
            correctEnglishCount = false;
        }
        if(correctEnglishCount == true && correctDiamondCount == true){
            cout << "changeBoard when changing to a different board passed!" << endl;
            return true;
        }else{
            cout << "changeBoard when changing to a different board failed" << endl;
        }
        return false;
    }
    bool Tester::changeBoardToUnsupportedBoard(Solitaire englishBoard){
        bool correctEnglishCount = false;
        bool correctFrenchCount = false;
        //checks if the board is english
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_numColumns == ENGLISHSIZE
        && englishBoard.m_numRows == ENGLISHSIZE 
        && englishBoard.m_shape == ENGLISH){
            correctEnglishCount = true;
        }
        englishBoard.changeBoard(FRENCH);
        //checks if the board is empty
        if(englishBoard.m_numMarbles == 0
        && englishBoard.m_numColumns == 0
        && englishBoard.m_numRows == 0 ){
            correctFrenchCount = true;
        }
        englishBoard.changeBoard(ENGLISH);
        //checks if the board is switched back to english
        if(englishBoard.m_numMarbles != NUMENGLISHMARBLES
        && englishBoard.m_numColumns != ENGLISHSIZE
        && englishBoard.m_numRows != ENGLISH
        && englishBoard.m_shape != ENGLISH){
            correctEnglishCount = false;
        }
        if(correctEnglishCount == true && correctFrenchCount == true){
            cout << "change board works when changing to an unsupported board!" << endl;
            return true;
        }else{
            cout << "change board didn't work when changing to an unsupported board" << endl;
        }
        return false;
    }
    bool Tester::normalCasesPlayTest(Solitaire englishBoard){
        int validMoveCounter = 0;
        bool rightCount = false;
        int marbleCount = NUMENGLISHMARBLES;
        //making sure the board is unused before testing
        if(englishBoard.m_numMarbles == marbleCount && englishBoard.m_board[3][3] == HOLE){
            rightCount = true;
        }
        //valid move
        englishBoard.play(pair<int,int>(3,5), pair<int,int>(3,3));
        marbleCount--;
        //checks the move
        if(englishBoard.m_board[3][3] == MARBLE 
        && englishBoard.m_board[3][5] == HOLE){
            validMoveCounter++;
        }
        if(englishBoard.m_numMarbles != marbleCount){
            rightCount = false;
        }
        //valid move
        englishBoard.play(pair<int,int>(5,4), pair<int,int>(3,4));
        marbleCount--;
        if(englishBoard.m_board[3][4] == MARBLE 
        && englishBoard.m_board[5][4] == HOLE){
            validMoveCounter++;
        }
        if(englishBoard.m_numMarbles != marbleCount){
            rightCount = false;
        }
        //valid move
        englishBoard.play(pair<int,int>(3,3), pair<int,int>(3,5));
        marbleCount--;
        if(englishBoard.m_board[3][5] == MARBLE 
        && englishBoard.m_board[3][3] == HOLE){
            validMoveCounter++;
        }
        if(englishBoard.m_numMarbles != marbleCount){
            rightCount = false;
        }
        //valid move
        englishBoard.play(pair<int,int>(3,6), pair<int,int>(3,4));
        marbleCount--;
        if(englishBoard.m_board[3][4] == MARBLE 
        && englishBoard.m_board[3][6] == HOLE){
            validMoveCounter++;
        }
        if(englishBoard.m_numMarbles != marbleCount){
            rightCount = false;
        }
        if(rightCount == true && validMoveCounter == 4){
            cout <<"The test for normal cases on play has passed!" << endl;
            return true;
        }else{
            cout <<"The test for normal cases on play has failed" << endl;
        }
        return false;
    }
    bool Tester::errorCasesPlayTest(Solitaire englishBoard){
        bool correctCount = false;
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES){
            correctCount = true;
        }
        //all these cases are out of bounds and shouldn't make a move
        englishBoard.play(pair<int,int>(20,4), pair<int,int>(3,4));
        englishBoard.play(pair<int,int>(-20,7), pair<int,int>(3,4));
        englishBoard.play(pair<int,int>(3,6), pair<int,int>(20,4));
        englishBoard.play(pair<int,int>(3,6), pair<int,int>(3,7));
        //tries moving a hole into a marble
        englishBoard.play(pair<int,int>(3,3), pair<int,int>(3,7));
        //tries moving marble to marble
        englishBoard.play(pair<int,int>(3,6), pair<int,int>(3,5));
        // if the number of marbles hasn't change and the middle is still a hole
        if(englishBoard.m_numMarbles != NUMENGLISHMARBLES
        && englishBoard.m_board[3][3] == HOLE){
            correctCount = false;
        }
        if(correctCount == true){
            cout <<"The test for error cases on play has passed!" << endl;
            return true;
        }else{
             cout <<"The test for error cases on play has failed" << endl;
        }
        return false;
    }
    bool Tester::errorCaseCopyConstructorTest(Solitaire frenchBoard){
        Solitaire copiedBoard(frenchBoard);
        //the copied board attributes should all be set to zero
        if(copiedBoard.m_numMarbles == 0 
        && copiedBoard.m_shape == 0
        && copiedBoard.m_numColumns == 0
        && copiedBoard.m_numRows == 0){
            cout <<"Test for error case in the copy constructor has passed!" << endl;
            return true;
        }else{
            cout <<"Test for error case in the copy constructor has failed." << endl;
        }
        return false;
    }
    bool Tester::normalCaseCopyConstructorTest(Solitaire englishBoard){
        bool equalBoards = true;
        bool equalAttributes = false;
        bool checkPointers = true;
        Solitaire copiedBoard(englishBoard);
        //checks if the copied board has the attributes but the pointer points to a different location
        if(copiedBoard.m_numMarbles == NUMENGLISHMARBLES &&
        copiedBoard.m_board != englishBoard.m_board &&
        copiedBoard.m_shape == englishBoard.m_shape &&
        copiedBoard.m_numColumns == englishBoard.m_numColumns){
            equalAttributes = true;
            //checks each of the board pegs
            for(int i = 0; i < englishBoard.m_numRows; i++){
                for(int j = 0; j < englishBoard.m_numColumns; j++){
                    if(englishBoard.m_board[i][j] != copiedBoard.m_board[i][j]){
                        equalBoards = false;
                    }
                    if(i != j){
                        //checks that the row pointer are different 
                        if(englishBoard.m_board[i] == copiedBoard.m_board[j]){
                            checkPointers = false;
                        }
                    }

                }
            }
        }
            if(equalBoards == true && equalAttributes == true){
            cout <<"Test for normal case in the copy constructor has passed!" << endl;
            return true;
        }else{
            cout <<"Test for normal case in the copy constructor has failed." << endl;
        }
        return false;

    }

    bool Tester::clearTest(Solitaire englishBoard){
        bool correctAttributesBefore = false;
        bool deallocatedMemory = false;
        //checks if the board is correct beforehand
        if(englishBoard.m_numMarbles == NUMENGLISHMARBLES
        && englishBoard.m_numRows == ENGLISHSIZE
        && englishBoard.m_numColumns == ENGLISHSIZE 
        && englishBoard.m_shape == ENGLISH
        && englishBoard.m_board != nullptr){
            correctAttributesBefore = true;
        }
        //clears the board
        englishBoard.clear();
        //checks if the board attributes are reset and m_board is deallocated
        if(englishBoard.m_numMarbles == 0
        && englishBoard.m_numRows == 0 
        && englishBoard.m_numColumns == 0 
        && englishBoard.m_shape == 0 
        && englishBoard.m_board == nullptr){
            deallocatedMemory = true;
        }
        if(deallocatedMemory == true && correctAttributesBefore == true){
            cout << "Clear test has passed!" << endl;
            return true;
        }else{
            cout << "Clear test failed." << endl;
        }
        return false;
    }
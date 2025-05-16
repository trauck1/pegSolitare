// UMBC - CMSC 341 - Fall 2024 - Proj0
#include "solitaire.h"
Solitaire::Solitaire(){
    m_numColumns = OUT;
    m_numMarbles = OUT;
    m_numRows = OUT;
    m_shape = NONE;
    m_board = nullptr;
    
} 
Solitaire::Solitaire(BOARDSHAPE board){
    m_shape = board;
    //initializes the diamond board
    if(board == DIAMOND){
        m_numColumns = DIAMONDSIZE;
        m_numRows = DIAMONDSIZE;
        m_numMarbles = NUMDIAMONDMARBLES;    
        m_board = new int*[m_numRows];
    for(int i = 0; i < m_numRows; i++){
        m_board[i] = new int[m_numColumns];
    }
    for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){
            if((i == 0 || i ==8) && j != 4){
                m_board[i][j] = OUT;
            }else if((i == 0 || i ==8) && j == 4){
                m_board[i][j] = MARBLE;
            }else if((i == 1 || i == 7) && (j > 5 || j < 3)){
                m_board[i][j] = OUT;
            }else if((i == 1 || i == 7) && (j <= 5 && j >= 3)){
                m_board[i][j] = MARBLE;
            }else if((i == 2 || i == 6) && j > 6 && j < 2){
                m_board[i][j] = OUT;
            }else if((i == 2 || i == 6) && j <= 6 && j >= 2){
                m_board[i][j] = MARBLE;
            }else if((i == 3 || i == 5) && j > 7 && j < 1){
                m_board[i][j] = OUT;
            }else if((i == 3 || i == 5) && j < 8 && j > 0){
                m_board[i][j] = MARBLE;
            }else if(i == 4 && j != 4){
                m_board[i][j] = MARBLE;
            }else if(i ==4 && j == 4){
                m_board[i][j] = HOLE;
            }
        }
    }
     //initializes the english board    
    }else if(board == ENGLISH){
        m_numColumns = ENGLISHSIZE;
        m_numRows = ENGLISHSIZE;
        m_numMarbles = NUMENGLISHMARBLES;
        m_board = new int*[m_numRows];
    for(int i = 0; i < m_numRows; i++){
        m_board[i] = new int[m_numColumns];
    }
     for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){
            if(i < 2 || i > 4){
                if(j > 1 && j < 5){
                    m_board[i][j] = MARBLE;
                }else{
                    m_board[i][j] = OUT;
                }
            }else if( i == 2 || i == 4){
                m_board[i][j] = MARBLE;
            }else if(i == 3){
                if(j == 3){//center of english board
                    m_board[i][j] = HOLE;
                }else{
                    m_board[i][j] = MARBLE;
                }
            }
        }
    }
    //if the user tries to use a non-supported board type
    }else{
        m_numColumns = OUT;
        m_numRows = OUT;
        m_numMarbles = OUT;
        m_shape = NONE;
        m_board = nullptr;
    }
    
    }


Solitaire::Solitaire(const Solitaire & rhs){
    //copies the attributes
    m_numColumns = rhs.m_numColumns;
    m_numRows = rhs.m_numRows;
    m_numMarbles = rhs.m_numMarbles;
    m_shape = rhs.m_shape;
    //sets m_board
    m_board = new int*[m_numRows];
    for(int i = 0; i < m_numRows; i++){
        m_board[i] = new int[m_numColumns];
    }
    //sets each individual peg on the board
    for(int i = 0; i < m_numRows; i++){
        for(int j = 0; j < m_numColumns; j++){
            m_board[i][j] = rhs.m_board[i][j];
            }
        }
    
}
Solitaire::~Solitaire(){
    clear();
}
void Solitaire::clear(){
    //deallocates m_board
    for(int i = 0; i < m_numRows; i++){    
        delete [] m_board[i];
    }
    delete [] m_board;
    m_board = nullptr;
    //sets all the attributes to default values
    m_numMarbles = OUT;
    m_numColumns = OUT;
    m_numRows = OUT;
    m_shape = NONE;
}

bool Solitaire::play(pair<int,int> origin, pair<int,int> destination){ 
    //origin coordinates 
    int originRow = origin.first;
    int originCol = origin.second;
    //destination coordinates 
    int destRow = destination.first;
    int destCol = destination.second;
    int jumpedRow = OUT;
    int jumpedCol = OUT;
    int difference;
    bool validOrigin = false;
    bool validDestination = false;
    bool validJump = false;
    //checks to see if the pegs selected are on the board
    if(m_shape == DIAMOND){
        if(destRow > 8 || destCol > 8 || originRow > 8 || originCol > 8){
            return false;
        }else if(destRow < 0 || destCol < 0 || originRow < 0 || originCol < 0){
            return false;
        }
    }else if(m_shape == ENGLISH){
        if(destRow > 6 || destCol > 6 || originRow > 6 || originCol > 6){
            return false;
        }else if(destRow < 0 || destCol < 0 || originRow < 0 || originCol < 0){
            return false;
        }
    }
    //the origin of the move has to be a marble
    if(m_board[originRow][originCol] == MARBLE){
        validOrigin = true;
    }
    //destination has to be a hole, along with other requirements
    if(m_board[destRow][destCol] == HOLE){
        if(originRow == destRow || originCol == destCol){
            if(originRow == destRow){
                if(originCol > destCol){
                    difference = originCol - destCol;
                    //the destination coordinate has be exactly 2 spaces away from the origin
                    if(difference == 2){
                        validDestination = true;
                        jumpedRow = originRow;
                        jumpedCol = originCol -1;
                    }
                }else if(originCol < destCol){
                    difference = destCol - originCol;
                    if(difference == 2){
                        validDestination = true;
                        jumpedRow = originRow;
                        jumpedCol = destCol -1;
                    }
                }
            }else if(originCol == destCol){
                if(originRow > destRow){
                    difference = originRow - destRow;
                    if(difference == 2){
                        validDestination = true;
                        jumpedRow = originRow - 1;
                        jumpedCol = originCol;
                    }
                }if(originRow < destRow){
                    difference = destRow - originRow;
                    if(difference == 2){
                        validDestination = true;
                        jumpedRow = destRow - 1;
                        jumpedCol = originCol;
                    }
                }
            }
        }
        }
        //the origin marble has to jump over a marble for a valid move
        if(m_board[jumpedRow][jumpedCol] == MARBLE){
            validJump = true;
            }
        //if all positions involved are valid, move the pieces
        if(validOrigin == true && validDestination == true && validJump == true){
            m_board[originRow][originCol] = HOLE;
            m_board[jumpedRow][jumpedCol] = HOLE;
            m_board[destRow][destCol] = MARBLE;
            m_numMarbles--;
            return true;
        }
        return false;
    }


void Solitaire::changeBoard(BOARDSHAPE board){
    bool boardChange;
    if(m_shape != board){
        //deallocatess the board
        clear();
        m_shape = board;
        if(m_shape == DIAMOND){
            //reallocates new memory for diamond boards
            m_numColumns = DIAMONDSIZE;
            m_numRows = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            m_board = new int*[m_numRows];
            for(int i = 0; i < m_numRows; i++){
                m_board[i] = new int[m_numColumns];
                }
            for(int i = 0; i < m_numRows; i++){
                for(int j = 0; j < m_numColumns; j++){
                    if((i == 0 || i ==8) && j != 4){
                        m_board[i][j] = OUT;
                    }else if((i == 0 || i ==8) && j == 4){
                        m_board[i][j] = MARBLE;
                    }else if((i == 1 || i == 7) && (j > 5 || j < 3)){
                        m_board[i][j] = OUT;
                    }else if((i == 1 || i == 7) && (j <= 5 && j >= 3)){
                        m_board[i][j] = MARBLE;
                    }else if((i == 2 || i == 6) && j > 6 && j < 2){
                        m_board[i][j] = OUT;
                    }else if((i == 2 || i == 6) && j <= 6 && j >= 2){
                        m_board[i][j] = MARBLE;
                    }else if((i == 3 || i == 5) && j > 7 && j < 1){
                        m_board[i][j] = OUT;
                    }else if((i == 3 || i == 5) && j < 8 && j > 0){
                        m_board[i][j] = MARBLE;
                    }else if(i == 4 && j != 4){
                        m_board[i][j] = MARBLE;
                    }else if(i ==4 && j == 4){ //center of diamond board
                        m_board[i][j] = HOLE;
                    }
                }
            }
        }else if(m_shape == ENGLISH){
            //reallocates new memory for english boards
            m_numColumns = ENGLISHSIZE;
            m_numRows = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            m_board = new int*[m_numRows];
            for(int i = 0; i < m_numRows; i++){
                m_board[i] = new int[m_numColumns];
                }
            for(int i = 0; i < m_numRows; i++){
                for(int j = 0; j < m_numColumns; j++){
                    if(i < 2 || i > 4){
                        if(j > 1 && j < 5){
                            m_board[i][j] = MARBLE;
                        }else{
                            m_board[i][j] = OUT;
                        }
                    }else if( i == 2 || i == 4){
                        m_board[i][j] = MARBLE;
                    }else if(i == 3){
                        if(j == 3){//center of english board
                            m_board[i][j] = HOLE;
                        }else{
                            m_board[i][j] = MARBLE;
                        }
                    }
                }
            }
            }
    }else{
        //if the user tries to change to the same board, re-initialize the board
        boardChange = newBoard();
        }
    }

bool Solitaire::newBoard(){
        //re-intializes diamond boards
        if(m_shape == DIAMOND){
            m_numColumns = DIAMONDSIZE;
            m_numRows = DIAMONDSIZE;
            m_numMarbles = NUMDIAMONDMARBLES;
            for(int i = 0; i < m_numRows; i++){
                for(int j = 0; j < m_numColumns; j++){
            if((i == 0 || i ==8) && j != 4){
                m_board[i][j] = OUT;
            }else if((i == 0 || i ==8) && j == 4){
                m_board[i][j] = MARBLE;
            }else if((i == 1 || i == 7) && (j > 5 || j < 3)){
                m_board[i][j] = OUT;
            }else if((i == 1 || i == 7) && (j <= 5 && j >= 3)){
                m_board[i][j] = MARBLE;
            }else if((i == 2 || i == 6) && j > 6 && j < 2){
                m_board[i][j] = OUT;
            }else if((i == 2 || i == 6) && j <= 6 && j >= 2){
                m_board[i][j] = MARBLE;
            }else if((i == 3 || i == 5) && j > 7 && j < 1){
                m_board[i][j] = OUT;
            }else if((i == 3 || i == 5) && j < 8 && j > 0){
                m_board[i][j] = MARBLE;
            }else if(i == 4 && j != 4){
                m_board[i][j] = MARBLE;
            }else if(i == 4 && j == 4){
                m_board[i][j] = HOLE;
            }
        }
    }
        return true;
        //re-intializes english boards
        }else if(m_shape == ENGLISH){
            m_numColumns = ENGLISHSIZE;
            m_numRows = ENGLISHSIZE;
            m_numMarbles = NUMENGLISHMARBLES;
            for(int i = 0; i < m_numRows; i++){
                for(int j = 0; j < m_numColumns; j++){
            if(i < 2 || i > 4){
                if(j > 1 && j < 5){
                    m_board[i][j] = MARBLE;
                }else{
                    m_board[i][j] = OUT;
                }
            }else if( i == 2 || i == 4){
                m_board[i][j] = MARBLE;
            }else if(i == 3){
                if(j == 3){//center of english board
                    m_board[i][j] = HOLE;
                }else{
                    m_board[i][j] = MARBLE;
                    }
                }
            }
        }
        return true;
        //if the board is empty
        }else{
            return false;
        }
        return true;
    }

void Solitaire::dumpBoard(){
    // this is to facilitate debugging 
    cout << "  ";
    for (int k=0;k<m_numColumns;k++){
        cout << k << " ";
    }
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        cout << i-1 << " ";
        for (int j=1;j<=m_numColumns;j++){
            if (m_board[i-1][j-1] == OUT)
                cout << "  ";
            else if (m_board[i-1][j-1] == HOLE)
                cout << BLACKSTAR;
            else
                cout << REDSTAR;
        }
        cout << endl;
    }
    cout << endl;
}
int Solitaire::reportNumMarbles(){
    // this is to facilitate debugging 
    cout << "You have " << m_numMarbles << " marbles to remove!" << endl;
    return m_numMarbles;
}

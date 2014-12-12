#include <iostream>
#include <list>
#include <vector>

using namespace std;


vector<vector<int> > initSudoku();
void printSudoku(vector<vector<int> > &sudoku);
void printVector(vector<int> &toPrint);
void printTwoDimenVector(vector<vector<int> > &toPrint);
vector<int> horizontalNumbers(vector<vector<int> > &sudoku, int pos_y);
vector<int> verticalNumbers(vector<vector<int> > &sudoku, int pos_x);
vector<int> blockNumbers(vector<vector<int> > &sudoku, int pos_x, int pos_y);
vector<int> getLackNumbers(vector<int> existNumbers);
vector<int> getEmptyPointPossibleNumbers(vector<vector<int> > &sudoku, int pos_x, int pos_y);
vector<vector<int> > getOneRowPossibleNumbers(vector<vector<int> > &sudoku, int pos_y);
vector<vector<int> > getPossibleArrangement(vector<vector<int> > &sudoku, vector<vector<int> > &possibleNumbers, int pos_y);
vector<vector<int> > possibleNumbersRecursion(vector<vector<int> > &lastResult, vector<int> &toDeal);
vector<vector<vector<int> > > possibleArrangementRecursion(vector<vector<vector<int> > > &lastResult, vector<vector<int> > &toDeal);
bool isHorizontalHasSameNumber(vector<vector<int> > &sudoku, int pos_y);
bool isVerticalHasSameNumber(vector<vector<int> > &sudoku, int pos_x);
bool isBlockHasSameNumber(vector<vector<int> > &sudoku, int pos_x, int pos_y);
bool validateSudoku(vector<vector<int> > &sudoku);
vector<vector<int> > generateSudoku(vector<vector<int> > &sudoku);


int main() {
    vector<vector<int> > sudoku = initSudoku();
    printSudoku(sudoku);
    cout << "==============================\n" ;
    vector<vector<int> > result = generateSudoku(sudoku);
    printSudoku(result);
}

vector<vector<int> > initSudoku() {
    /*
    vector<vector<int> > sudoku(9, vector<int>(9, 0));
    sudoku[0][0] = 5;
    sudoku[0][1] = 3;
    sudoku[0][4] = 7;

    sudoku[1][0] = 6;
    sudoku[1][3] = 1;
    sudoku[1][4] = 9;
    sudoku[1][5] = 5;

    sudoku[2][1] = 9;
    sudoku[2][2] = 8;
    sudoku[2][7] = 6;

    sudoku[3][0] = 8;
    sudoku[3][4] = 6;
    sudoku[3][8] = 3;

    sudoku[4][0] = 4;
    sudoku[4][3] = 8;
    sudoku[4][5] = 3;
    sudoku[4][8] = 1;

    sudoku[5][0] = 7;
    sudoku[5][4] = 2;
    sudoku[5][8] = 6;

    sudoku[6][1] = 6;
    sudoku[6][6] = 2;
    sudoku[6][7] = 8;

    sudoku[7][3] = 4;
    sudoku[7][4] = 1;
    sudoku[7][5] = 9;
    sudoku[7][8] = 5;

    sudoku[8][4] = 8;
    sudoku[8][7] = 7;
    sudoku[8][8] = 9;
    return sudoku;
    */
    vector<vector<int> > sudoku(9, vector<int>(9, 0));
    sudoku[0][0] = 4;
    sudoku[0][3] = 1;
    sudoku[0][8] = 3;

    sudoku[1][1] = 1;
    sudoku[1][3] = 8;
    sudoku[1][7] = 6;

    sudoku[2][1] = 3;
    sudoku[2][4] = 7;
    sudoku[2][7] = 9;

    sudoku[3][7] = 4;
    sudoku[3][8] = 1;

    sudoku[4][2] = 8;
    sudoku[4][6] = 7;

    sudoku[5][0] = 5;
    sudoku[5][1] = 2;

    sudoku[6][1] = 4;
    sudoku[6][4] = 3;
    sudoku[6][7] = 8;

    sudoku[7][1] = 6;
    sudoku[7][5] = 2;
    sudoku[7][7] = 1;

    sudoku[8][0] = 2;
    sudoku[8][5] = 9;
    sudoku[8][8] = 5;
    return sudoku;
}

void printSudoku(vector<vector<int> > &sudoku) {
    vector<vector<int> >::const_iterator ii;
    vector<int>::const_iterator jj;
    for (ii = sudoku.begin(); ii != sudoku.end(); ii++) {
        for (jj = (*ii).begin(); jj != (*ii).end(); jj++) {
            cout << *jj << ",";
        }
        cout << endl;
    }
}

void printVector(vector<int> &toPrint) {
    vector<int>::const_iterator ii;
    for (ii = toPrint.begin(); ii != toPrint.end(); ii++) {
        cout << *ii << endl;
    }
}

void printTwoDimenVector(vector<vector<int> > &toPrint) {
    vector<vector<int> >::const_iterator ii;
    vector<int>::const_iterator jj;

    for (ii = toPrint.begin(); ii != toPrint.end(); ii++) {
        for (jj = (*ii).begin(); jj != (*ii).end(); jj++) {
            cout << *jj << ",";
        }
        cout << endl;
    }
}

vector<int> horizontalNumbers(vector<vector<int> > &sudoku, int pos_y) {
    vector<int> numbers;
    int i;
    for (i = 0; i < 9; i++) {
        if (sudoku[pos_y][i] != 0) {
            numbers.push_back(sudoku[pos_y][i]);
        }
    }
    return numbers;
}

vector<int> verticalNumbers(vector<vector<int> > &sudoku, int pos_x) {
    vector<int> numbers;
    int i;
    for (i = 0; i < 9; i++) {
        if (sudoku[i][pos_x] != 0) {
            numbers.push_back(sudoku[i][pos_x]);
        }
    }
    return numbers;
}

vector<int> blockNumbers(vector<vector<int> > &sudoku, int pos_x, int pos_y) {
    vector<int> numbers;
    int x = pos_x % 3;
    int y = pos_y % 3;
    int i, j;
    for (i = pos_x - x; i < pos_x + 3 - x; i++) {
        for (j = pos_y - y; j < pos_y + 3 - y; j++) {
            if (sudoku[j][i] != 0) {
                numbers.push_back(sudoku[j][i]);
            }
        }
    }
    return numbers;
}

vector<int> getLackNumbers(vector<int> existNumbers) {
    vector<int> numbers;
    vector<int>::const_iterator ii;
    for (int i = 1; i <= 9; i++) {
        bool isExist = false;
        for (ii = existNumbers.begin(); ii != existNumbers.end(); ii++) {
            if (*ii == i) {
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            numbers.push_back(i);
        }
    }
    return numbers;
}

vector<int> getEmptyPointPossibleNumbers(vector<vector<int> > &sudoku, int pos_x, int pos_y) {
    vector<int> b_numbers = blockNumbers(sudoku, pos_x, pos_y);
    vector<int> v_numbers = verticalNumbers(sudoku, pos_x);
    vector<int> h_numbers = horizontalNumbers(sudoku, pos_y);

    vector<int> numbers;
    vector<int>::const_iterator ii;
    for (int i = 1; i <= 9; i++) {
        bool isExist = false;
        for (ii = b_numbers.begin(); ii != b_numbers.end(); ii++) {
            if (*ii == i) {
                isExist = true;
                break;
            }
        }
        if (isExist) continue;
        for (ii = v_numbers.begin(); ii != v_numbers.end(); ii++) {
            if (*ii == i) {
                isExist = true;
                break;
            }
        }
        if (isExist) continue;
        for (ii = h_numbers.begin(); ii != h_numbers.end(); ii++) {
            if (*ii == i) {
                isExist = true;
                break;
            }
        }
        if (!isExist) {
            numbers.push_back(i);
        }
    }
    return numbers;
}

vector<vector<int> > getOneRowPossibleNumbers(vector<vector<int> > &sudoku, int pos_y) {
    vector<vector<int> > oneRowPossibleNumbers;
    vector<int> onePointNumbers;
    for (int i = 0; i < 9; i++) {
        if (sudoku[pos_y][i] == 0) {
            onePointNumbers = getEmptyPointPossibleNumbers(sudoku, i, pos_y);
            oneRowPossibleNumbers.push_back(onePointNumbers);
        }
    }
    return oneRowPossibleNumbers;
}

vector<vector<int> > getPossibleArrangement(vector<vector<int> > &sudoku, vector<vector<int> > &possibleNumbers, int pos_y) {
    vector<vector<int> > result, lastResult;
    vector<vector<int> >:: const_iterator ii;
    for (ii = possibleNumbers.begin(); ii != possibleNumbers.end(); ii++) {
        vector<int> a = *ii;
        lastResult = possibleNumbersRecursion(lastResult, a);
    }

    for (ii = lastResult.begin(); ii != lastResult.end(); ii++) {
        int jj = 0;
        vector<int> temp;
        vector<int> aa = (*ii);
        for (int i = 0; i < 9; i++) {
            if (sudoku[pos_y][i] == 0) {
                temp.push_back(aa[jj]);
                jj++;
            } else {
                temp.push_back(sudoku[pos_y][i]);
            }
        }
        result.push_back(temp);
    }
    return result;
}

vector<vector<int> > possibleNumbersRecursion(vector<vector<int> > &lastResult, vector<int> &toDeal) {

    vector<vector<int> > result;

    vector<vector<int> >::const_iterator ii;
    vector<int>::const_iterator jj, kk;
    int i, j;
    if (lastResult.size() == 0) {
        for (jj = toDeal.begin(); jj != toDeal.end(); jj++) {
            vector<int> a;
            int temp = *jj;
            a.push_back(temp);
            result.push_back(a);
        }
    } else {
        for (ii = lastResult.begin(); ii != lastResult.end(); ii++) {
            for (jj = toDeal.begin(); jj != toDeal.end(); jj++) {
                bool isExist = false;
                for (kk = (*ii).begin(); kk != (*ii).end(); kk++) {
                    if (*jj == *kk) {
                        isExist = true;
                        break;
                    }
                }

                if (!isExist) {
                    vector<int> a = (*ii);
                    int temp = (*jj);
                    a.push_back(temp);
                    result.push_back(a);
                }
            }
        }

    }

    return result;
}

vector<vector<vector<int> > > possibleArrangementRecursion(vector<vector<vector<int> > > &lastResult, vector<vector<int> > &toDeal) {
    vector<vector<vector<int> > > result;
    vector<vector<int> >::const_iterator ii1, ii2;
    vector<vector<vector<int> > >::const_iterator iii;
    vector<int>::const_iterator jj, kk;
    if (lastResult.size() == 0) {
        for (ii1 = toDeal.begin(); ii1 != toDeal.end(); ii1++) {
            vector<int> aa = *ii1;
            vector<vector<int> > aaa;
            aaa.push_back(aa);
            result.push_back(aaa);
        }
    } else {
        for (iii = lastResult.begin(); iii != lastResult.end(); iii++) {
            for (ii1 = toDeal.begin(); ii1 != toDeal.end(); ii1++) {
                bool hasSameNumber = false;
                for (ii2 = (*iii).begin(); ii2 != (*iii).end(); ii2++) {
                    vector<int> temp1 = *ii1;
                    vector<int> temp2 = *ii2;
                    for (int i = 0; i < temp1.size(); i++) {
                        if (temp1[i] == temp2[i]) {
                            hasSameNumber = true;
                            break;
                        }
                    }
                    if (hasSameNumber) break;
                }
                if (!hasSameNumber) {
                    vector<vector<int> > aaa = *iii;
                    vector<int> aa = *ii1;
                    aaa.push_back(aa);
                    result.push_back(aaa);
                }
            }
        }
    }
    return result;
}


bool isHorizontalHasSameNumber(vector<vector<int> > &sudoku, int pos_y) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
            if (sudoku[pos_y][i] == sudoku[pos_y][j]) return true;
        }
    }
    return false;
}

bool isVerticalHasSameNumber(vector<vector<int> > &sudoku, int pos_x) {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
            if (sudoku[i][pos_x] == sudoku[j][pos_x]) return true;
        }
    }
    return false;
}

bool isBlockHasSameNumber(vector<vector<int> > &sudoku, int pos_x, int pos_y) {
    vector<int> numbers;
    int x = pos_x % 3;
    int y = pos_y % 3;
    int i, j, k;
    for (i = pos_x - x; i < pos_x + 3 - x; i++) {
        for (j = pos_y - y; j < pos_y + 3 - y; j++) {
            for (k = 0; k < numbers.size(); k++) {
                if (sudoku[j][i] == numbers[k]) return true;
            }
            numbers.push_back(sudoku[j][i]);
        }
    }
    return false;
}

bool validateSudoku(vector<vector<int> > &sudoku) {
    for (int i = 0; i < 9; i++) {
        if (isHorizontalHasSameNumber(sudoku, i) || isVerticalHasSameNumber(sudoku, i)) return false;
    }

    for (int j = 0; j < 9; j = j + 3) {
        for (int k = 0; k < 9; k = k + 3) {
            if (isBlockHasSameNumber(sudoku, j, k)) return false;
        }
    }
    return true;
}

vector<vector<int> > generateSudoku(vector<vector<int> > &sudoku) {
    vector<vector<int> > row;
    vector<vector<int> > rowNum;
    vector<vector<int> > newSudoku;
    vector<vector<vector<int> > > result;

    for (int i = 0; i < 9; i++) {
        rowNum = getOneRowPossibleNumbers(sudoku, i);
        row = getPossibleArrangement(sudoku, rowNum, i);
        result = possibleArrangementRecursion(result, row);
    }
    cout << "result : " << result.size() << endl;
    vector<vector<vector<int> > >::const_iterator iii;
    for (iii = result.begin(); iii != result.end(); iii++) {
        vector<vector<int> > nnnnSudoku = *iii;
        if (validateSudoku(nnnnSudoku)) {
            cout << "The answer is right!!!!\n" << endl;
            newSudoku = nnnnSudoku;
            break;
        }
    }

    return newSudoku;
}

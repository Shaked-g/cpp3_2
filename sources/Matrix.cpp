#include "Matrix.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace zich;
using namespace std;

Matrix::Matrix(vector<double> &matrix, int row, int col){
    if(row < 0 || col < 0 ){
        throw ("Matrix cant be with negative shape");
    }
    if (matrix.size() != row * col) {
        throw ("Matrix shape does not align with row and col");
    }
    this->row = row;
    this->col = col;
    this->matrix = matrix;
}

Matrix::~Matrix(){
}


//-------------------------------------
// Arithmetic Operators
//-------------------------------------

//Matrix * Matrix
Matrix Matrix::operator * (const Matrix &otherMat) const {
    if (this->getCol() != otherMat.getRow()) {
        throw("Matrices dont follow multiplication dimensions rules, matrix1 rows must be equal to matrix2 cols");
    };

    double tempVal = 0;
    unsigned long vectorSize = (unsigned int)(this->getRow() * otherMat.getCol());
    vector <double> newVec(vectorSize);
    unsigned int index = 0;
    for(int i = 0; i < this->getRow(); ++i)
	{
		for(int j = 0; j < otherMat.getCol(); ++j)
		{
			for(int k = 0; k < this->getCol(); ++k)
			{
                unsigned int thisIndex = (unsigned int)((i * this->getCol()) + k);
                unsigned int otherIndex = (unsigned int)((k * otherMat.getCol()) + j);
                tempVal += this->getMatrix().at(thisIndex) * otherMat.getMatrix().at(otherIndex);
			}
            newVec.at(index++) = tempVal;
            // (unsigned int)(i * otherMat.getCol() + j)
            tempVal = 0;
		}
	}
    Matrix answer (newVec, this->getRow(), otherMat.getCol());
    return answer;
}

//Matrix * double
Matrix Matrix:: operator * (double num){
    Matrix answer (this->matrix, this->getRow(), this->getCol());
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        answer.matrix.at(i) = this->getMatrix().at(i) * num;
    }
    return answer;
}

//Matrix + Matrix
Matrix Matrix::operator + (const Matrix &otherMat){
    checkSameSize(*this, otherMat);
    Matrix answer (this->matrix, this->getRow(), this->getCol());
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        answer.matrix.at(i) = this->getMatrix().at(i) + otherMat.getMatrix().at(i);
    }
    return answer;
}

//Matrix - Matrix
Matrix Matrix::operator - (const Matrix &otherMat){
    checkSameSize(*this, otherMat);
    Matrix answer (this->matrix, this->getRow(), this->getCol());
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        answer.matrix.at(i) = this->getMatrix().at(i) - otherMat.getMatrix().at(i);
    }
    return answer;
}

//Matrix--
Matrix Matrix::operator-- (int num){
    Matrix res = *this;
    --(*this);
    return res;
}

//Matrix++ the original matrix is returned and than incresed by 1
Matrix Matrix::operator++ (int num){
    Matrix res = *this;
    ++(*this);
    return res;
}

//int * Matrix
Matrix zich::operator * (const int num, Matrix& mat){
    Matrix answer (mat.matrix, mat.getRow(), mat.getCol());
    for (size_t i = 0; i < mat.getMatrix().size(); i++) {
        answer.matrix.at(i) = mat.matrix.at(i) * num;
    }
    return answer;
}


//-------------------------------------
// Relational Operators
//-------------------------------------

bool Matrix::operator > (const Matrix &otherMat) const{
    checkSameSize(*this, otherMat);
    const double thisSum = getMatrixSum(*this);
    const double otherSum = getMatrixSum(otherMat);
    // if (thisSum > otherSum) {
    //     return true;
    // }
    return (thisSum > otherSum);
}

bool Matrix::operator < (const Matrix &otherMat) const{
    checkSameSize(*this, otherMat);
    const double thisSum = getMatrixSum(*this);
    const double otherSum = getMatrixSum(otherMat);
    // if (thisSum < otherSum) {
    //     return true;
    // }
    return (thisSum < otherSum) ;
}

bool Matrix::operator >= (const Matrix &otherMat) const{
    checkSameSize(*this, otherMat);
    const double thisSum = getMatrixSum(*this);
    const double otherSum = getMatrixSum(otherMat);
    // if (thisSum >= otherSum) {
    //     return true;
    // }
    return (thisSum >= otherSum);
}

bool Matrix::operator <= (const Matrix &otherMat) const{
    checkSameSize(*this, otherMat);
    const double thisSum = getMatrixSum(*this);
    const double otherSum = getMatrixSum(otherMat);
    // if (thisSum <= otherSum) {
    //     return true;
    // }
    return (thisSum <= otherSum);
}

bool Matrix::operator == (const Matrix &otherMat) const{
    checkSameSize(*this, otherMat);
    // compare the vectors elements
    return (this->getMatrix() == otherMat.getMatrix());
}

bool Matrix::operator != (const Matrix &otherMat) const{
    return !(*this == otherMat);
}

//-------------------------------------
// Assignment Operators
//-------------------------------------

//Matrix += Matrix
Matrix Matrix::operator += (const Matrix &otherMat){
    checkSameSize(*this, otherMat);
    *this = *this + otherMat;
    return *this;
}

//Matrix -= Matrix
Matrix Matrix::operator -= (const Matrix &otherMat){
    checkSameSize(*this, otherMat);
    *this = *this - otherMat;
    return *this;
}

//Matrix *= double
Matrix Matrix::operator *= (double number){
    *this = *this * number;
    return *this;
}

//Matrix *= Matrix
Matrix Matrix::operator *= (const Matrix &otherMat){
    *this = *this * otherMat;
    return *this;
}


//-------------------------------------
// Unary Operation
//-------------------------------------

//--Matrix
Matrix Matrix::operator -- (){
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        this->matrix.at(i) -= 1;
    }
    return *this;
}

//++Matrix
Matrix Matrix::operator ++ (){
    for (size_t i = 0; i < this->getMatrix().size(); i++) {
        this->matrix.at(i) += 1;
    }
    return *this;
}

//-Matrix
Matrix Matrix::operator - () const{
    std::vector<double> negativeVec;
    for(double element : this->getMatrix()){
        negativeVec.push_back(element *(-1));
    }
    Matrix ans (negativeVec, this->row, this->col);
    return ans;
}

//+Matrix
Matrix Matrix::operator + () const{
    return *this;
}

//-------------------------------------
// Friend global IO operators - Input and Output
//-------------------------------------

ostream& zich::operator << (ostream& output , const Matrix& matrix){
    for (int row = 0; row < matrix.getRow(); row++)
    {
        output << "[";
        for (int col = 0; col < matrix.getCol(); col++)
        {
            if (col < matrix.getCol() - 1)
            {
                output << matrix.getMatrix().at((unsigned int)(row * matrix.getCol() + col)) << " ";
            }
            // last number in line
            else
            {
                output << matrix.getMatrix().at((unsigned int)(row * matrix.getCol() + col));
            }
        }

        if (row < matrix.getRow() - 1)
        {
            output << "]" << '\n';
        }
        // last row
        else {
            output << "]";
        }
    }
    return output;
}

istream &zich::operator >> (std::istream &input, Matrix &matrix){
    string str;
    vector <double> recivedVector;
    int numberOfRows = 0;
    int numberOfClosers = 0;
    int numberOfNum = 0; // will save length of numbers in last row, number of cols
    int numberOfPsik = 0;
    getline(input, str);

    if(str[0] != '[') {
        throw("unValid string input");
    }

    for(std::string::size_type i = 0; i < str.size(); ++i) {
        // new Row
        if (str[i] == '[') {
            // push number after opening a row
            recivedVector.push_back(str[i+1]);
            i++;
            numberOfRows +=1;
            numberOfNum = 1;
        }

        // new Colser
        else if (str[i] == ']') {
            // means new row, skips ", "
            if (str[i+1] == ','){
                numberOfPsik +=1;
                i += 2;
            }
            // end of input
            else if (str[i+1] == '\\') {
                numberOfClosers +=1;
                break;
            }
            // else if(str[i+1] == ']'){
            //     throw("only , or \\ after closing bracket  ]");
            //     break;
            // }
            numberOfClosers +=1;
        }

        // take the number after an empty char
        else if (str[i] == ' ')
        {
            if (str[i+1] == ']') {
                 throw("only [ after space ");
                break;
            }
            recivedVector.push_back(str[i+1]);
            i++;
            numberOfNum += 1;
        }
 
    }

    if (numberOfClosers != numberOfRows){
        throw("number of [ and ] are not the same");
    }

    if (((numberOfClosers+numberOfRows)/2)-1 != (numberOfPsik)){
        throw("number of [ ] and , are not the same");
    }

    Matrix answer (recivedVector, numberOfRows, numberOfNum);
    matrix.setMatrix(answer);
    
    return input;
}


//-------------------------------------
// Input Check
//-------------------------------------

void Matrix::checkNegative(const Matrix &mat) {
    if(mat.getCol() < 0 || mat.getRow() < 0){
        throw ("Matrix cant be with negative shape");
    }
}

void Matrix::checkSameSize(const Matrix &matrix1 , const Matrix &matrix2) {
    if (matrix1.getCol() != matrix2.getCol() || matrix1.getRow() != matrix2.getRow()){
        throw ("Matrices have to be from the same shape");
    }
}


//-------------------------------------
// Helper Functions
//-------------------------------------

double Matrix::getMatrixSum(const Matrix& mat) {
    double sum = 0;
    for(double element : mat.getMatrix()){
        sum += element;
    }
    return sum;
}


// void Matrix::setMatrixVal(unsigned int index, double newValue, Matrix& mat){
//     mat.matrix.at(index) = newValue;
// }

void Matrix::setMatrix(Matrix &mat){
    this->matrix = mat.getMatrix();
    this->col = mat.getCol();
    this->row = mat.getRow();
}


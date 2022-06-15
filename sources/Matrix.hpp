#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
namespace zich {
    class Matrix {
        private:
            int row;
            int col;
            vector <double> matrix;

            

        public:
            Matrix(vector<double> &matrix, int row, int col); // Constructor
            ~Matrix(); // Destructor

            //-------------------------------------
	        // Arithmetic Operators
	        //-------------------------------------
            Matrix operator * (const Matrix &mat) const;
            Matrix operator * (double num);
            Matrix operator + (const Matrix &mat);
            Matrix operator - (const Matrix &mat);
            Matrix operator -- (int num);
            Matrix operator ++ (int num);

            friend Matrix operator * (const int num, Matrix &mat); ///


            //-------------------------------------
	        // Relational Operators
	        //-------------------------------------
            bool operator > (const Matrix &otherMat) const;
            bool operator >= (const Matrix &otherMat) const;
            bool operator < (const Matrix &otherMat) const;
            bool operator <= (const Matrix &otherMat) const;
            bool operator != (const Matrix &otherMat) const;
            bool operator == (Matrix const &otherMat) const;


            //-------------------------------------
	        // Assignment Operators
	        //-------------------------------------
            Matrix operator += (const Matrix &otherMat);
            Matrix operator -= (const Matrix &otherMat);
            Matrix operator *= (double number);
            Matrix operator *= (const Matrix &otherMat);
            
            //-------------------------------------
	        // Unary Operation
	        //-------------------------------------
            Matrix operator -- ();
            Matrix operator ++ ();
            Matrix operator + () const;
            Matrix operator - () const;


            //-------------------------------------
	        // Friend global IO operators - Input and Output
	        //-------------------------------------
            friend ostream& operator << (ostream &output, Matrix const &matrix);
            friend istream& operator >> (std::istream &input, Matrix &matrix);


            //-------------------------------------
	        // Getters
	        //-------------------------------------
            int getRow() const {return this->row;}
            int getCol() const {return this->col;}
            vector<double> getMatrix() const {return this->matrix;}
            // void setMatrixVal(unsigned int index, double value);
            void setMatrix(Matrix &mat);


            //-------------------------------------
	        // Input Check
	        //-------------------------------------
            static void checkNegative(const Matrix &mat);
            static void checkSameSize(const Matrix &matrix1, const Matrix &matrix2);

            //-------------------------------------
	        // Helper Functions
	        //-------------------------------------
            static double getMatrixSum(const Matrix& mat);



    };

}
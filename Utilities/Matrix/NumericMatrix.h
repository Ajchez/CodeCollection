#ifndef NUMERICMATRIX_H_INCLUDED
#define NUMERICMATRIX_H_INCLUDED

//User Defined Includes
#include "BaseMatrix.h"

//Standard library includes
#include <type_traits>

namespace Matrix
{
    template <class T>
    class NumericMatrix : public BaseMatrix<T>
    {
        //Require that class T is a numerical type
        static_assert(std::is_arithmetic<T>::value, "Numeric Matrix must be of arithmetic type.");

    public:
        //Allow for using the size type from BaseMatrix
        using size_type = typename BaseMatrix<T>::size_type;

        //Default constructor
        NumericMatrix() : BaseMatrix<T>()
        {
        }

        //Sizing constructor
        NumericMatrix(size_type rows, size_type cols) : BaseMatrix<T>(rows, cols)
        {
        }

        //Initializer list constructor
        NumericMatrix(size_type rows, size_type cols, std::initializer_list<T> vals) : BaseMatrix<T>(rows, cols, vals)
        {
        }

        NumericMatrix& operator+=(const NumericMatrix& obj)
        {
            //Loop over the rows
            for (size_type row=0; row<nRows; ++row)
            {
                for (size_type col=0; col<nCols; ++col)
                {
                    size_type idx = GetDataIndex(row,col);
                    matrix_data[idx] += obj.matrix_data[idx];
                }
            }

            return *this;
        }

        NumericMatrix& operator-=(const NumericMatrix& obj)
        {
            //Loop over the rows
            for (size_type row=0; row<nRows; ++row)
            {
                for (size_type col=0; col<nCols; ++col)
                {
                    size_type idx = GetDataIndex(row,col);
                    matrix_data[idx] -= obj.matrix_data[idx];
                }
            }

            return *this;
        }

        NumericMatrix operator+(const NumericMatrix& obj)
        {

            NumericMatrix retObj{*this};
            retObj += obj;
            return retObj;
        }

        NumericMatrix operator-(const NumericMatrix& obj)
        {
            NumericMatrix retObj{*this};
            retObj -= obj;
            return retObj;
        }

        NumericMatrix operator*(const NumericMatrix& obj)
        {
            //Create a new matrix
            //(m x n) * (n x p) = (m x p)
            NumericMatrix retObj{nRows, obj.nCols};

            //Loop over the rows
            for (size_type row=0; row<nRows; ++row)
            {
                //Loop over the columns
                for (size_type col=0; col<obj.nCols; ++col)
                {

                    //Loop over the common dimension
                    for (size_type k=0; k<nCols; ++k)
                    {
                        size_type idx1 = GetDataIndex(row,k);
                        size_type idx2 = obj.GetDataIndex(k,col);
                        retObj(row,col) += matrix_data[idx1] * obj.matrix_data[idx2];
                    }
                }
            }

            return retObj;
        }

        NumericMatrix Scale(T val)
        {
            //Return a new matrix so we can retain the original
            NumericMatrix retObj{*this};

            //Loop over the rows
            for (T& it : retObj.matrix_data)
            {
                it *= val;
            }
            return retObj;
        }

    protected:
        using BaseMatrix<T>::GetDataIndex;
        using BaseMatrix<T>::matrix_data;
        using BaseMatrix<T>::nCols;
        using BaseMatrix<T>::nRows;

    private:
    };
}



#endif // NUMERICMATRIX_H_INCLUDED

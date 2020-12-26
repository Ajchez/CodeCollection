#ifndef BASEMATRIX_H_INCLUDED
#define BASEMATRIX_H_INCLUDED

//User defined includes

//Standard library includes
#include <iostream>
#include <vector>

namespace Matrix
{
    template <class T>
    class BaseMatrix
    {
    public:
        //Define types from the vector container
        using size_type = typename std::vector<T>::size_type;

        //Rule of Zero: Define default constructor due to custom constructor
        BaseMatrix() : nRows(0),
                       nCols(0),
                       matrix_data()
        {
        }

        //Custom constructor to allow for sizing
        BaseMatrix(size_type rows, size_type cols) : nRows(rows),
                                                     nCols(cols),
                                                     matrix_data(std::vector<T>(rows*cols, T()))
        {
        }

        //Custom constructor to initialize from an initializer list
        BaseMatrix(size_type rows, size_type cols, std::initializer_list<T> vals) : nRows(rows),
                                                                                    nCols(cols),
                                                                                    matrix_data(vals)
        {
        }

        //Operator to get a value from the matrix
        T& operator()(size_type row, size_type col)
        {
            return matrix_data[GetDataIndex(row,col)];
        }

        //Friend function to allow for printing the matrix
        friend std::ostream& operator<<(std::ostream& out, const BaseMatrix& obj)
        {
            for (size_type row=0; row<obj.nRows; ++row)
            {
                for (size_type col=0; col<obj.nCols; ++col)
                {
                    size_type idx = obj.GetDataIndex(row,col);
                    std::cout << obj.matrix_data[idx] << "  ";
                }
                std::cout << std::endl;
            }

            return out;
        }

        //Transpose function
        //Return a new object so we don't destroy the original
        virtual BaseMatrix Transpose()
        {
            BaseMatrix retObj{nCols, nRows};
            for (size_type row=0; row<nCols; ++row)
            {
                for (size_type col=0; col<nRows; ++col)
                {
                    retObj(row,col) = (*this)(col,row);
                }
            }
            return retObj;
        }

    protected:
        size_type nRows;
        size_type nCols;
        std::vector<T> matrix_data;

        size_type GetDataIndex(size_type row, size_type col) const
        {
            //Assumes column major indexing
            return nRows * col + row;
        }

    private:
    };
}

#endif // BASEMATRIX_H_INCLUDED

// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz = 0;
  T* pMem = nullptr;
public:
  TDynamicVector(size_t size = 1) : sz(size)                                        //est' test
  {
    if (sz <= 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)                                        //est' test
  {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v): sz(v.sz)                                        //est' test
  {
      pMem = new T[sz];
      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = v.pMem;
      v.pMem = nullptr;
      sz = v.sz;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v) noexcept                                        //est' test
  {
      delete[] pMem;
      pMem = new T[v.sz];
      sz = v.sz;

      for (int i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      pMem = v.pMem;
      v.pMem = nullptr;
      sz = v.sz;
      v.sz = 0;

      return *this;
  }

  size_t size() const noexcept { return sz; }                                        //est' test

  T* get_pMem() {
      return this->pMem;
  }

  // индексация
  T& operator[](size_t ind)                                        //est' test
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";

      return pMem[ind];
  }
  const T& operator[](size_t ind) const                                        //est' test
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";

      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";

      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";

      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept                                        //est' test
  {
      if (sz != v.sz)
          return false;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept                                        //est' test
  {
      if (sz != v.sz)
          return true;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] == v.pMem[i]) {
              return false;
          }
      }

      return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)                                        //est' test
  {
      TDynamicVector res(sz);

      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + val;
      }

      return res;
  }
  TDynamicVector operator-(double val)                                        //est' test
  {
      TDynamicVector res(sz);

      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - static_cast<T>(val);
      }

      return res;
  }
  TDynamicVector operator*(double val)                                        //est' test
  {
      TDynamicVector res(sz);

      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * static_cast<T>(val);
      }

      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)                                        //est' test
  {
      if (sz != v.sz) {
          throw "sizes are not equel";
      }

      TDynamicVector res(sz);

      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + v[i];
      }

      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)                                        //est' test
  {
      if (sz != v.sz) {
          throw "sizes are not equel";
      }

      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))                                        //est' test
  {
      if (sz != v.sz) {
          throw "sizes are not equel";
      }

      T res = 0;
      for (int i = 0; i < sz; i++) {
          res += this->pMem[i] * v.pMem[i];
      }
      return sqrt(res);
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)                                        //provereno
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};




// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)                                        //est' test
  {
      if (sz <= 0 || sz >= MAX_MATRIX_SIZE)
          throw "wrong vector size";
      
      for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];                                        //est' test

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept                                        //est' test
  {
      if (sz != m.sz)
          return false;

      for (int i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }

      return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val) noexcept                                        //est' test
  {
      TDynamicVector<T> res(sz);

      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              res[i] += pMem[i][j] * val;
          }
      }

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)                                        //est' test
  {
      if (sz != v.size())
          throw "not equal sizes";

      TDynamicVector<T> res(sz);

      for (int i = 0; i < sz; i++) {
          res[i] = 0;
          for (int j = 0; j < sz; j++) {
              res[i] += pMem[i][j] * v[j];
          }
      }

      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)                                        //est' test
  {
      if (sz != m.sz)
          throw "not equal sizes";

      TDynamicMatrix res(sz);

      for (int i = 0; i < sz; i++)
              res.pMem[i] = pMem[i] + m.pMem[i];

      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)                                        //est' test
  {
      if (sz != m.sz)
          throw "not equal sizes";

      TDynamicMatrix res(sz);

      for (int i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - m.pMem[i];

      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)                                        //est' test
  {
      if (sz != m.sz) {
          throw "not equal sizes";
      }

      TDynamicMatrix res(sz);

      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              res.pMem[i][j] = 0;
              for (int h = 0; h < sz; h++)
                  res.pMem[i][j] += pMem[i][h] * m.pMem[h][j];
          }
      }

      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++)
              istr >> v.pMem[i][j];
      }

      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)                                        //provereno
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i][j] << ' ';
      }

      return ostr;
  }

  int get_size() {                                        //est' test
      return this->sz;
  }

};

#endif;
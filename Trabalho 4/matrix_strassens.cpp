#include <bits/stdc++.h>

#include <omp.h>

using namespace std;

int n;

vector<vector<int>> getRandomMatrix()
{
  vector<vector<int>> m(n, vector<int>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      m[i][j] = rand() % 100;
    }
  }

  return m;
}

vector<vector<int>>
add_matrix(vector<vector<int>> matrix_A,
           vector<vector<int>> matrix_B, int split_index,
           int multiplier = 1)
{
  for (auto i = 0; i < split_index; i++)
    for (auto j = 0; j < split_index; j++)
      matrix_A[i][j] = matrix_A[i][j] + (multiplier * matrix_B[i][j]);
  return matrix_A;
}

vector<vector<int>>
multiply_matrix(vector<vector<int>> matrix_A,
                vector<vector<int>> matrix_B)
{
  int col_1 = matrix_A[0].size();
  int row_1 = matrix_A.size();
  int col_2 = matrix_B[0].size();
  int row_2 = matrix_B.size();

  if (col_1 != row_2)
  {
    cout << "\nError: The number of columns in Matrix "
            "A  must be equal to the number of rows in "
            "Matrix B\n";
    return {};
  }

  vector<int> result_matrix_row(col_2, 0);
  vector<vector<int>> result_matrix(row_1, result_matrix_row);
  if (col_1 == 1)
    result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0];
  else
  {
    int split_index = col_1 / 2;

    vector<int> row_vector(split_index, 0);

    vector<vector<int>> a00(split_index, row_vector);
    vector<vector<int>> a01(split_index, row_vector);
    vector<vector<int>> a10(split_index, row_vector);
    vector<vector<int>> a11(split_index, row_vector);
    vector<vector<int>> b00(split_index, row_vector);
    vector<vector<int>> b01(split_index, row_vector);
    vector<vector<int>> b10(split_index, row_vector);
    vector<vector<int>> b11(split_index, row_vector);

    for (auto i = 0; i < split_index; i++)
      for (auto j = 0; j < split_index; j++)
      {
        a00[i][j] = matrix_A[i][j];
        a01[i][j] = matrix_A[i][j + split_index];
        a10[i][j] = matrix_A[split_index + i][j];
        a11[i][j] = matrix_A[i + split_index]
                            [j + split_index];
        b00[i][j] = matrix_B[i][j];
        b01[i][j] = matrix_B[i][j + split_index];
        b10[i][j] = matrix_B[split_index + i][j];
        b11[i][j] = matrix_B[i + split_index]
                            [j + split_index];
      }

    vector<vector<int>> p, q, r, s, t, u, v;
    #pragma omp task shared(p)
    {
      p = multiply_matrix(a00, add_matrix(b01, b11, split_index, -1));
    }

    #pragma omp task shared(q)
    {
      q = (multiply_matrix(add_matrix(a00, a01, split_index), b11));
    }

    #pragma omp task shared(r)
    {
      r = (multiply_matrix(add_matrix(a10, a11, split_index), b00));
    }

    #pragma omp task shared(s)
    {
      s = (multiply_matrix(a11, add_matrix(b10, b00, split_index, -1)));
    }

    #pragma omp task shared(t)
    {
      t = (multiply_matrix(add_matrix(a00, a11, split_index),add_matrix(b00, b11, split_index)));
    }

    #pragma omp task shared(u)
    {
      u = (multiply_matrix(add_matrix(a01, a11, split_index, -1),add_matrix(b10, b11, split_index)));
    }

    #pragma omp task shared(v)
    {
      v = (multiply_matrix(add_matrix(a00, a10, split_index, -1),add_matrix(b00, b01, split_index)));
    }
    //p = (multiply_matrix(a00, add_matrix(b01, b11, split_index, -1)));
    // q = (multiply_matrix(add_matrix(a00, a01, split_index), b11));
    // r = (multiply_matrix(add_matrix(a10, a11, split_index), b00));
    // s = (multiply_matrix(a11, add_matrix(b10, b00, split_index, -1)));
    // t = (multiply_matrix(add_matrix(a00, a11, split_index),add_matrix(b00, b11, split_index)));
    // u = (multiply_matrix(add_matrix(a01, a11, split_index, -1),add_matrix(b10, b11, split_index)));
    // v = (multiply_matrix(add_matrix(a00, a10, split_index, -1),add_matrix(b00, b01, split_index)));

    #pragma omp taskwait

    vector<vector<int>> result_matrix_00(add_matrix(add_matrix(add_matrix(t, s, split_index), u,split_index),q, split_index, -1));
    vector<vector<int>> result_matrix_01(add_matrix(p, q, split_index));
    vector<vector<int>> result_matrix_10(add_matrix(r, s, split_index));
    vector<vector<int>> result_matrix_11(add_matrix(add_matrix(add_matrix(t, p, split_index), r,split_index, -1),v, split_index, -1));

    for (auto i = 0; i < split_index; i++)
      for (auto j = 0; j < split_index; j++)
      {
        result_matrix[i][j] = result_matrix_00[i][j];
        result_matrix[i][j + split_index] = result_matrix_01[i][j];
        result_matrix[split_index + i][j] = result_matrix_10[i][j];
        result_matrix[i + split_index]
                     [j + split_index] = result_matrix_11[i][j];
      }
  }
  return result_matrix;
}

int main(int argc, char const *argv[])
{
  srand(time(NULL));

  n = stoi(argv[1]);

  clock_t start_time, end_time;
  vector<vector<int>> ma = getRandomMatrix(), mb = getRandomMatrix();

  start_time = clock();

#pragma omp parallel 
{
  #pragma omp single
  {
    multiply_matrix(ma, mb);
  }
}

  end_time = clock();
  double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  cout << fixed << setprecision(10) << total_time << endl;
}
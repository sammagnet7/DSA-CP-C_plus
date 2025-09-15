#include <iostream>
#include<algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    int N;
    cout << "Enter the number of rows: ";
    cin >> N;
    cout << endl;

    cout << "\nPattern 1: Rectangular Star Pattern\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }

    cout << "\nPattern 2: Right-Angled Triangle Pattern\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (i + 1); j++)
        {
            cout << "* ";
        }
        cout << endl;
    }

    cout << "\nPattern 3: Right-Angled Number Pyramid\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (i + 1); j++)
        {
            cout << (j + 1) << ' ';
        }
        cout << endl;
    }

    cout << "\nPattern 4: Right-Angled Number Pyramid - II\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (i + 1); j++)
        {
            cout << (i + 1) << ' ';
        }
        cout << endl;
    }

    cout << "\nPattern 5: Inverted Right Pyramid\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (N - i); j++)
        {
            cout << '*' << ' ';
        }
        cout << endl;
    }

    cout << "\nPattern 6: Inverted Numbered Right Pyramid\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < (N - i); j++)
        {
            cout << (j + 1) << ' ';
        }
        cout << endl;
    }

    cout << "\nPattern 7: Star Pyramid\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++)
        {
            cout << "*";
        }
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        cout << endl;
    }

    cout << "\nPattern 8: Inverted Star Pyramid\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        for (int k = 0; k < (2 * (N - i - 1) + 1); k++)
        {
            cout << "*";
        }
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << endl;
    }

    cout << "\nPattern 9: Diamond Star Pattern\n";
    for (int i = 0; i < N; i++)
    { // triangle
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        for (int j = 0; j < 2 * i + 1; j++)
        {
            cout << "*";
        }
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        for (int k = 0; k < (2 * (N - i - 1) + 1); k++)
        {
            cout << "*";
        }
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << endl;
    }

    cout << "\nPattern 10: Half Diamond Star Pattern\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
    for (int p = N - 1; p > 0; p--)
    {
        for (int q = 0; q < p - 1; q++)
        {
            cout << "*";
        }
        cout << endl;
    }

    cout << "\nPattern 11: Binary Number Triangle Pattern\n";
    for (int i = 0; i < N; i++)
    {
        int start;
        if (i % 2 == 0)
            start = 1;
        else
            start = 0;

        for (int j = 0; j <= i; j++)
        {
            cout << start;
            start ^= 1;
        }
        cout << endl;
    }

    cout << "\nPattern 12: Number Crown Pattern\n";
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << j;
        }
        for (int k = 1; k <= 2 * (N - (i - 1) - 1); k++)
        {
            cout << " ";
        }
        for (int l = i; l >= 1; l--)
        {
            cout << l;
        }
        cout << endl;
    }

    cout << "\nPattern 13: Increasing Number Triangle Pattern\n";
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << ++count << " ";
        }
        cout << endl;
    }

    cout << "\nPattern 14: Increasing Letter Triangle Pattern\n";
    for (int i = 0; i < N; i++)
    {
        char c = 'A';
        for (int j = 0; j <= i; j++)
        {
            cout << c++;
        }
        cout << endl;
    }
    cout << "\nPattern 15: Reverse Letter Triangle Pattern\n";
    for (int i = N - 1; i >= 0; i--)
    {
        char ch = 'A';
        for (int j = 0; j <= i; j++)
        {
            cout << ch++;
        }
        cout << endl;
    }

    cout << "\nPattern 16: Alpha-Ramp Pattern\n";
    char ch = 'A';
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            cout << ch;
        }
        cout << endl;
        ch++;
    }

    cout << "\nPattern 17: Alpha-Hill Pattern\n";
    for (int i = 0; i < N; i++)
    {
        char ch = 'A';
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        for (int k = 0; k <= i; k++)
        {
            cout << ch++;
        }
        ch--;
        for (int l = 0; l < i; l++)
        {
            cout << --ch;
        }
        for (int j = 0; j < N - i - 1; j++)
        {
            cout << " ";
        }
        \        
        cout << endl;
    }

    cout << "\nPattern 18: Alpha-Triangle Pattern\n";
    for (int i = 0; i < N; i++)
    {
        char startChar = 'A' + (N - i - 1);
        for (int j = 0; j <= i; j++)
        {
            cout << startChar++ << " ";
        }
        cout << endl;
    }

    cout << "\nPattern 19: Symmetric-Void Pattern\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i; j++)
        {
            cout << "*";
        }
        for (int k = 0; k < 2 * i; k++)
        {
            cout << " ";
        }
        for (int j = 0; j < N - i; j++)
        {
            cout << "*";
        }
        cout << endl;
    }
    for (int i = 0; i < N; i++)
    {
        // Reverse
        for (int l = 0; l <= i; l++)
        {
            cout << "*";
        }
        for (int m = 2 * (N - i - 1); m > 0; m--)
        {
            cout << " ";
        }
        for (int l = 0; l <= i; l++)
        {
            cout << "*";
        }

        // Newline
        cout << endl;
    }

    cout << "\nPattern 20: Symmetric-Butterfly Pattern\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
            cout << "*";
        for (int k = 2 * (N - i - 1); k > 0; k--)
            cout << " ";
        for (int j = 0; j <= i; j++)
            cout << "*";
        cout << endl;
    }
    for (int i = 0; i < N - 1; i++)
    {
        for (int l = N - 1 - i; l > 0; l--)
            cout << "*";

        for (int m = 0; m < 2 * (i + 1); m++)
            cout << " ";
        for (int l = N - 1 - i; l > 0; l--)
            cout << "*";

        cout << endl;
    }

    cout << "\nPattern 21: Hollow Rectangle Pattern\n";
    for (int i = 0; i < N; i++)
    {
        if (i == 0 || i == N - 1)
        {
            for (int j = 0; j < N; j++)
                cout << "*";
        }
        else
        {
            cout << "*";
            for (int j = 0; j < (N - 2); j++)
                cout << " ";
            cout << "*";
        }
        cout << endl
             << endl;
    }

    cout << "\nPattern 22: The Number Pattern\n\n";
    int matrixSize = 2 * N - 1;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            int minDist = min({i, (matrixSize - i - 1), j, (matrixSize - j - 1)}); // minDist ~ min dist from {top, bottom, left, right}
            int val = N - minDist;
            cout << val;
        }
        cout << endl;
    }

    cout << endl
         << endl
         << endl;
    return 0;
}

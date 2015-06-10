#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>

using namespace std;

void readPubKey(largeClass &p, largeClass &g, largeClass &y, string filename)
{
    ifstream ifst(filename.c_str());
    string p_str, g_str, y_str;
    getline(ifst, p_str);
    getline(ifst, g_str);
    getline(ifst, y_str);

    p = largeClass(p_str.c_str());
    g = largeClass(g_str.c_str());
    y = largeClass(y_str.c_str());
}

void readPrivKey(largeClass &p, largeClass &x, string filename)
{
    ifstream ifst(filename.c_str());
    string p_str, x_str;;
    getline(ifst, p_str);
    getline(ifst, x_str);

    p = largeClass(p_str.c_str());
    x = largeClass(x_str.c_str());
}

//Шифрование : Выбирается сессионный ключ — случайное целое число k такое, что 1 < k < p - 1
//Вычисляются числа a = g^k (mod p) и b = y^k * M (mod p)
//Пара чисел (a, b) является шифротекстом.
void encrypt(largeClass m, largeClass p, largeClass g, largeClass y, largeClass &a, largeClass &b)
{
    largeClass pp = p - 2;
    largeClass k = GenRandomByRangeC(pp) + 1;
    a = powModClass(g, k, p);
    b = powModClass(y, k, p);
    b = (b * m) % p;
}

largeClass decrypt(largeClass p, largeClass x, largeClass a, largeClass b)
{
    largeClass tmp = p-1-x;
    return (b * powModClass(a, tmp, p)) % p;
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cerr << "Usage: elgamal <key_name> <infile> <outfile> {e,d}" << endl;
        return 1;
    }
    string key_name = argv[1];
    string infile = argv[2];
    string outfile = argv[3];
    string flag = argv[4];

    if (flag == "e")
    {
        largeClass p, g, y;
        readPubKey(p, g, y, key_name + ".pub");
        largeClass m, a, b;
        m.readFromBinFile(infile.c_str());
        encrypt(m, p, g, y, a, b);

        ofstream ofst(outfile.c_str());
        ofst << a.str() << endl << b.str();
    }
    else
    {
        largeClass p, x, a, b;
        readPrivKey(p, x, key_name + ".priv");
        ifstream ifst(infile.c_str());
        string a_str, b_str;
        getline(ifst, a_str);
        getline(ifst, b_str);

        a = largeClass(a_str.c_str());
        b = largeClass(b_str.c_str());
        largeClass m = decrypt(p, x, a, b);

        m.writeToBinFile(outfile.c_str());
    }
    return 0;
}

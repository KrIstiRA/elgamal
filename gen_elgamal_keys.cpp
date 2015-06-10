#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>

using namespace std;

void gen_elgamal_keys(int bitlen, string key_name)
{
    // Генерируется случайное простое число p длины n битов.
    //Выбирается случайный элемент g поля Zp, Выбирается случайное целое число x такое, что 1 < x < p-1.
    //Вычисляется y = g^x (mod p).
    //Открытым ключом является тройка (p,g,y), закрытым ключом — число x.
    largeClass p = GenPrime(bitlen);
    largeClass g = GenRandomByRangeC(p);
    largeClass x = GenRandomByRangeC(p);
    largeClass y = powModClass(g, x, p);


    ofstream pub((key_name + string(".pub")).c_str());
    ofstream priv((key_name + string(".priv")).c_str());

    pub << p.str() << endl << g.str() << endl << y.str() << endl;
    priv << p.str() << endl << x.str() << endl;
}

int main(int argc, char* argv[])
{
    srand(time(0));
    if (argc != 3)//сколько аргументов?
    {
        cerr << "Generate keys for Elgamal" << endl;
        cerr << "Usage: gen_elgamal_keys <bitlen> <key_name>" << endl;
        return 1;
    }
    gen_elgamal_keys(atoi(argv[1]), argv[2]);// ????
    return 0;
}

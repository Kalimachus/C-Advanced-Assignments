/*
Kyle Gomez
Assignment 2, GNU GCC, Windows 10 64 Bit
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

int fSize(const char *add) {
     ifstream fin;
     fin.open(add, ios_base::binary);
     fin.seekg(0, ios_base::end);
     int size = fin.tellg();
     fin.close();
     return size;
}

unsigned char bcdToDecimal(unsigned char x) {
     return static_cast<char>((((x >> 4) * 10) + (x & 0xF)) + 32);
}

int main()
{
     int length;
     const char* filename = "ass2data.bin";
     int x;

     ifstream fin(filename);
     if (!fin) {
          cerr << "Unable to open input file " << filename << endl;
          exit(1);
     }

     int binSize = fSize(filename);
     length = binSize / 4;
     cout << "The file size is " << binSize << " bytes" << endl;
     cout << "The file contains " << length << " ints\n" << endl;

     int* numArr = new int[length];


     for (int i = 1; i < length + 1; i++)
     {
          fin.read((char*)&x, sizeof(int));
          cout << setw(12) << right << x;
          if (i % 6 == 0)
          {
               cout << endl;
          }
          numArr[i - 1] = x;
     }
     cout << endl;

     cout << showbase;
     for (int i = 1; i < length + 1; i++)
     {
          cout << setw(12) << hex << numArr[i - 1];
          if (i % 6 == 0)
          {
               cout << endl;
          }
     }
     cout << endl;

     for (int i = 1; i < length + 1; i++)
     {
          int x = (numArr[i - 1] >> (1 * 8)) & 0xFF;
          cout << setw(6) << hex << x;

          if (i % 12 == 0)
          {
               cout << endl;
          }
     }
     cout << endl;

     cout << hex;
     unsigned char * ans = new unsigned char[length];
     unsigned short int hByte;
     unsigned short int lByte;
     unsigned short int result;

     for (int i = 1; i < length + 1; i++)
     {
          hByte = numArr[i - 1] & 0xF000;
          lByte = numArr[i - 1] & 0x0F00;
          result = lByte * 0x10;
          hByte /= 0x10;
          result += hByte;
          result = (result >> 8) & 0xFF;

          cout << setw(6) << result;

          ans[i - 1] = static_cast<unsigned char>(result);
          if (i % 12 == 0)
          {
               cout << endl;
          }
     }
     cout << endl;
     for (int i = 1; i < length + 1; i++)
     {

          cout << bcdToDecimal(ans[i - 1]);

     }
     cout << endl;

     delete[] numArr;
     delete[] ans;
     ans = nullptr;
     numArr = nullptr;

     return 0;
}
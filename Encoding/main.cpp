
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int fibArr[30] = { 1, 2, 3, 5, 8, 13, 21, 34
, 55, 89, 144, 233, 377, 610, 987,1597
,2584, 4181,6765,10946,17711,28657,46368
,75025, 121393, 196418, 317811, 514229, 832040, 1346269};

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * Thanks to this table we know how long can we expect the character be
 * or how long in bytes it will be.
 *
 * ############################################################################################
 * ##          ##          ##          ##          ##                    ##                  ##
 * ##  BYTE 1  ##  BYTE 2  ##  BYTE 3  ##  BYTE 4  ##  FIRST CODE POINT  ##  LAST CODE POINT ##
 * ##          ##          ##          ##          ##                    ##                  ##
 * ############################################################################################
 * ## 0xxxxxxx ## -------- ## -------- ## -------- ##       0x0000       ##      0x007F      ##
 * ############################################################################################
 * ## 110xxxxx ## 10xxxxxx ## -------- ## -------- ##       0x0080       ##      0x07FF      ##
 * ############################################################################################
 * ## 1110xxxx ## 10xxxxxx ## 10xxxxxx ## -------- ##       0x0800       ##      0xFFFF      ##
 * ############################################################################################
 * ## 11110xxx ## 10xxxxxx ## 10xxxxxx ## 10xxxxxx ##       0x10000      ##      0x10FFFF    ##
 * ############################################################################################
 * Source: Wikipedia
 *
 * The first bit(s) of first byte tell us how many bytes make up
 * the whole character.
 *
 * As we process the bytes we shift values to make space for another byte
 * if necessary and remove the formatting except for the first byte.
 * When the value is about to be returned, we get rid of the formatting
 * in the first byte and return the value.
 * This way we return the code point of the character.
 *
 * returns value of whole utf-8 character in int
 * if EOF, returns -2
 * if wrong format, returns -1
*/

int getNextChar (ifstream & input)
{
    uint8_t ch = input.get();
    int acc = 0;

    if(input.eof())
    {
        return -2;
    }

    bool check[5] = {((ch >> 7) & 1) == 1, ((ch >> 6) & 1) == 1, ((ch >> 5) & 1) == 1, ((ch >> 4) & 1) == 1, ((ch >> 3) & 1) == 1};

    if(!check[0])
    {
        return ch;
    }

    //######################################
    //##############SECOND BYTE#############
    //######################################
    acc = ch << 6;

    ch = input.get();

    if (!((ch >> 7) & 1) || ((ch >> 6) & 1))
            return -1;

    ch -= 0x80;
    if(check[0] && check[1] && !check[2])
    {
        return (acc - 0x3000) + ch;
    }

    //######################################
    //##############THIRD BYTE##############
    //######################################
    acc = (ch << 6) + (acc << 6);


    ch = input.get();

    if (!((ch >> 7) & 1) || ((ch >> 6) & 1))
            return -1;

    ch -= 0x80;
    if(check[0] && check[1] && check[2] && !check[3])
    {
        return (acc - 0xE0000)+ ch;
    }

    //######################################
    //###############FORTH BYTE#############
    //######################################
    acc = (ch << 6) + (acc << 6);


    ch = input.get();

    if (!((ch >> 7) & 1) || ((ch >> 6) & 1))
            return -1;

    ch -= 0x80;
    if(check[0] && check[1] && check[2] && check[3] && !check[4])
    {
        return (acc - 0x3C00000) + ch;
    }
    else return -1;

}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * Recursive function that returns number that corresponds to x-th index
 */

int getFibonacciNum(int x)
{
    /*if(x == 0)
        return 0;
    if(x == 1)
        return 1;
    else return getFibonacciNum(x - 1) + getFibonacciNum(x - 2);*/
    return fibArr[x-2];
}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * Creates Fibonacci code by subtracting the biggest number in Fibonacci sequence that is smaller than character/remainder
 * in bool array we store what n-th number that was in Fibonacci sequence
 * this repeats until remainder is 0 and this means we extracted all indexes/numbers
 * returns bool array and index of max number in length
 */
void getFibonacciCode(int ch, int & length, bool binary[31])
{
    int check, i, tmp = 0, tmpLength = 0;


    while(ch != 0)
    {
        check = 0;
        i = 1;
        while (check <= ch)
        {
            i++;
            tmp = check;
            check = getFibonacciNum(i);
        }
        if(check == 1)
        {
            tmp = 1;
            i++;
        }


        ch -= tmp;
        binary[i-3] = true;
    }

    for(int j = 0; j < 31; j++)
    {
        if(binary[j])
            tmpLength = j;
    }
    length += tmpLength+1;

    /*for(int j = 0; j <=tmpLength; j++)
    {
        cout << binary[j];
    }
    cout << endl;*/

}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * Rotates byte in array in order to make LSB on right
 */

void rotateByte(bool * binary)
{
    bool tmp;
    for(int j = 0; j <= 3; j++)
    {
        tmp = binary[ 7 - j ];
        binary[  7 - j ] = binary[  + j ];
        binary[ j ] = tmp;
    }
}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * Calculates value of char by powers of two and array of bools, always calculates one char
 */

uint8_t getCharFromByte(const bool * binary, int byte)
{
    return binary[byte * 8] * 128 + binary[byte * 8 + 1] * 64 + binary[byte * 8 + 2] * 32 + binary[byte * 8 + 3] * 16 + binary[byte * 8 + 4] * 8
         + binary[byte * 8 + 5] * 4 + binary[byte * 8 + 6] * 2 + binary[byte * 8 + 7];
}

uint8_t getCharFromByte(const bool * binary)
{
    return binary[0] * 128 + binary[1] * 64 + binary[2] * 32 + binary[3] * 16 + binary[4] * 8
           + binary[5] * 4 + binary[6] * 2 + binary[7];
}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 */

bool               utf8ToFibonacci                         ( const char      * inFile,
                                                             const char      * outFile )
{

    ifstream input(inFile);
    ofstream output(outFile);
    if(input.fail() || output.fail() || input.bad() || output.bad())
        return false;

    int ch = 0, sizeOfBinary = -1;

    bool binary[64];

    // Preemptively null whole array because we would have trouble when reading indexes of Fibonacci sequence
    // as the getFibonacciCode function doesn't care about other bits other than the ones it writes
    // and that would create big problem when reading from this array.
    // Basically at creation, it is filled with random data.
    for(bool & i : binary)
    {
        i = false;
    }

    bool done = false;
    while(true)
    {
        if((ch = getNextChar(input)) == -1 || ch > 0x10ffff) // gets next character in file
            return false;
        if(ch == -2) // this gets returned if we hit EOF
            done = true;
        //cout << "Char value: " << static_cast<int>(ch) << endl;

        if(!done)
        {
            getFibonacciCode(ch+1, sizeOfBinary, binary+sizeOfBinary+1);

            binary[++sizeOfBinary] = true;

            while(sizeOfBinary < 8)
            {
                if((ch = getNextChar(input)) == -1 || ch > 0x10ffff) // gets next character in file
                    return false;
                if(ch == -2)// this gets returned if we hit EOF
                {
                    done = true;
                    break;
                }
                //cout << "Char value: " << static_cast<int>(ch) << endl;


                getFibonacciCode(ch+1, sizeOfBinary, binary+sizeOfBinary+1);
                binary[++sizeOfBinary] = true;
            }
        }

        if(done)
        {
            for(unsigned long i = sizeOfBinary+1; i < 8; i++) // inserts padding
            {
                binary[i] = false;
            }

            rotateByte(binary);
            /*cout << "Rotated: ";
            for(int i = 0; i < sizeOfBinary + (sizeOfBinary % 8); i++)
            {
                if(i % 8 == 0)
                cout << "|";
            cout << binary[i];
            }
            cout << endl;*/

            //cout << "Char value: " << static_cast<int>(getCharFromByte(binary)) << endl;
            output << getCharFromByte(binary); // outputs char into output file
            if(output.fail())
                return false;

            break;

        }


        /*cout << "After loading char: ";
        for(int i = 0; i <= sizeOfBinary; i++)
        {
            if(i % 8 == 0)
            cout << "|";
        cout << binary[i];
        }
        cout << endl;*/

        while(sizeOfBinary > 7)
        {
            rotateByte(binary);

            /*cout << "Rotated: ";
            for (int i = 0; i < sizeOfBinary + (sizeOfBinary % 8); i++) {
                if (i % 8 == 0)
                    cout << "|";
                cout << binary[i];
            }
            cout << endl;*/

            //cout << "Output: " << static_cast<int>(getCharFromByte(binary)) << endl;
            output << getCharFromByte(binary); // outputs char into output file
            if(output.fail())
                return false;

            for (int i = 0; i <= sizeOfBinary - 8; i++) {
                binary[i] = binary[i + 8];
            }
            for (int i = sizeOfBinary - 7; i <= sizeOfBinary; i++)
                binary[i] = false;

            sizeOfBinary -= 8;

            /*cout << "Moved by byte: ";
            for (int i = 0; i <= sizeOfBinary; i++) {
                if (i % 8 == 0)
                    cout << "|";
                cout << binary[i];
            }
            cout << "\n------------------------\n" << endl;*/
        }
    }

    //cout << "###############" << endl;

    input.close();
    output.close();

    return true;
}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 */

bool printUTF8(const bool binary[31], int length, ostream & output)
{
    int ch = 0;


    //cout << "Reprezentace ve Fibonacciho kodu: ";
    for(int j = 0; j < length; j++)
    {
        //cout << binary[j];

        if(binary[j])
        {
            ch += getFibonacciNum(j+2);
        }
    }
    ch--;

    bool resBinary[32], * ptr = nullptr;

    for(int i = 31; i >= 0; i--)
    {
        resBinary[31-i] = ((ch >> i) & 1);
    }

    //uint8_t tmp;
    /*cout << "\nUTF8 code point: ";
    for(int i = 0; i < 32; i++)
    {
        if(i % 8 == 0)
            cout << "|";
        cout << resBinary[i];
    }
    cout << endl;*/

    if( ch <= 0x007F )
    {
        ptr = &resBinary[24];

        bool utf[8];
        utf[0] = false;

        for(int i = 1; i < 8; i++)
        {
            utf[i] = ptr[i];
        }

        /*for(int i = 0; i < 8; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << utf[i];
        }
        cout << endl;*/

        //cout << (int)getCharFromByte(utf) << "\n" << (int)ch << "\n" << endl;
        output << getCharFromByte(utf);
        //cout << (int)tmp << "\n" << (int)ch << "\n" << endl;

        return true;
    }

    //######################################
    //##############SECOND BYTE#############
    //######################################

    if( ch <= 0x07FF )
    {
        ptr = &resBinary[16];

        /*cout << "---------DVA BYTY----------\nOsekany codepoint: ";
        for(int i = 0; i < 16; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << ptr[i];
        }
        cout << endl;*/


        bool utf[16];

        // Writing format
        utf[0] = utf[1] = utf[8] = true;
        utf[2] = utf[9] = false;


        //cout << "Prvni byte: ";
        for(int i = 3; i < 8; i++) // Writing first byte
        {
            //cout << ptr[ i+2 ];
            utf[i] = ptr[ i+2 ];
        }
        //cout << endl << "Druhy byte: ";
        for(int i = 10; i < 16; i++) // Writing second byte
        {
            //cout << ptr[ i ];
            utf[i] = ptr[ i ];
        }

        //########## TEST ##########

        /*cout << "\nSestavena UTF8 binarka: ";
        for(int i = 0; i < 16; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << utf[i];
        }
        cout << "\n------------------------------------" << endl;*/

        for(int i = 0; i <=1 ; i++) // Writing to file
        {
            //cout << "Reprezentace bytu " << i << " v int: " << (int)getCharFromByte(utf, i) << endl;
            output << getCharFromByte(utf, i);
        }
        //cout << "#####################################################\n" << endl;

        return true;
    }

    //######################################
    //##############THIRD BYTE##############
    //######################################

    if(ch <= 0xFFFF)
    {
        ptr = &resBinary[8];
        /*cout << "---------TRI BYTY----------\nOsekany codepoint: ";
        for(int i = 0; i < 24; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << ptr[i];
        }
        cout << endl;*/

        bool utf[24];

        utf[0] = utf[1] = utf[2] = utf[8] = utf[16] = true;
        utf[3] = utf[9] = utf[17] = false;

        //cout << "Prvni byte: ";
        for(int i = 4; i < 8; i++) // Writing first byte
        {
            //cout << ptr[i + 4];
            utf[i] = ptr[i + 4];
        }
        //cout << endl << "Druhy byte: ";
        for(int i = 10; i < 16; i++) // Writing second byte
        {
            //cout << ptr[i + 2];
            utf[i] = ptr[i + 2];
        }
        //cout << endl << "Treti byte: ";
        for(int i = 18; i < 24; i++) // Writing third byte
        {
            //cout << ptr[i];
            utf[i] = ptr[i];
        }
        /*cout << "\nSestavena UTF8 binarka: ";
        for(int i = 0; i < 24; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << utf[i];
        }
        cout << "\n------------------------------------" << endl;*/

        for(int i = 0; i <= 2; i++) // Writing to file
        {
            //cout << "Reprezentace bytu " << i << " v int: " << (int)getCharFromByte(utf, i) << endl;
            output << getCharFromByte(utf, i);
        }
        //cout << "#####################################################\n" << endl;

        return true;
    }

    //######################################
    //###############FORTH BYTE#############
    //######################################

    if(ch <= 0x10FFFF)
    {
        //cout << "---------CTYRI BYTY----------" << endl;

        bool utf[32];

        utf[0] = utf[1] = utf[2] = utf[3] = utf[8] = utf[16] = utf[24] = true;
        utf[4] = utf[9] = utf[17] = utf[25] = false;

        //cout << "Prvni byte: ";
        for(int i = 4; i < 8; i++) // Writing first byte
        {
            //cout << resBinary[i + 6];
            utf[i] = resBinary[i + 6];
        }
        //cout << endl << "Druhy byte: ";
        for(int i = 10; i < 16; i++) // Writing second byte
        {
            //cout << resBinary[i + 4];
            utf[i] = resBinary[i + 4];
        }
        //cout << endl << "Treti byte: ";
        for(int i = 18; i < 24; i++) // Writing third byte
        {
            //cout << resBinary[i + 2];
            utf[i] = resBinary[i + 2];
        }
        //cout << endl << "Ctvrty byte: ";
        for(int i = 26; i < 32; i++) // Writing forth byte
        {
            //cout << resBinary[i];
            utf[i] = resBinary[i];
        }

        /*cout << "\nSestavena UTF8 binarka: ";
        for(int i = 0; i < 32; i++)
        {
            if(i % 8 == 0)
                cout << "|";
            cout << utf[i];
        }
        cout << "\n------------------------------------" << endl;*/

        for(int i = 0; i < 4; i++) // Writing to file
        {
            //cout << "Reprezentace bytu " << i << " v int: " << (int)getCharFromByte(utf, i) << endl;
            output << getCharFromByte(utf, i);
        }
        //cout << "#####################################################\n" << endl;

        return true;
    }
    else
        return false;
}

bool               fibonacciToUtf8                         ( const char      * inFile,
                                                             const char      * outFile )
{
    ifstream input(inFile);
    ofstream output(outFile);
    if(input.fail() || output.fail() || input.bad() || output.bad())
        return false;


    bool binary[40], prev = false, now;
    int binaryIndex = 0, sizeOfBuffer = 0;
    uint8_t ch;

    if((ch = input.get()) == 255)
        return false;

    for(int j = 7; j >= 0; j--)
        binary[j] = ((ch >> j) & 1);

    sizeOfBuffer = 8;

    /*for(int i = 0; i < sizeOfBuffer; i++)
    {
        if(i % 8 == 0)
            cout << "|";
        cout << binary[i];
    }
    cout << endl;*/


    while(true)
    {

        if(binaryIndex == sizeOfBuffer)
        {
            if((ch = input.get()) == 255)
            {
                for (int i = 0; i < sizeOfBuffer; i++) {
                    if (binary[i])
                        return false;
                }

                break;
            }

            //cout << "Addition to buffer: ";
            for(int j = 7; j >= 0; j--)
            {
                binary[j + sizeOfBuffer] = ((ch >> j) & 1);
                //cout << binary[j + sizeOfBuffer];
            }
            //cout << endl;

            sizeOfBuffer += 8;

            /*cout << "New buffer: ";
            for (int i = 0; i < sizeOfBuffer; i++) {
                if (i % 8 == 0)
                    cout << "|";
                cout << binary[i];
            }
            cout << "\n--------------------------------" << endl;*/
        }


        now = binary[binaryIndex];
        if(now && prev)
        {
            if(!printUTF8(binary, binaryIndex, output))
                return false;
            if(output.fail())
                return false;

            now = prev = false;
            for (int i = 0; i <= sizeOfBuffer - binaryIndex; i++)
            {
                binary[i] = binary[i + binaryIndex+1];
            }

            sizeOfBuffer -= binaryIndex+1;
            /*cout << "Moved by binaryIndex: ";
            for (int i = 0; i < sizeOfBuffer; i++) {
                if (i % 8 == 0)
                    cout << "|";
                cout << binary[i];
            }
            cout << "\nBuffer size: " << sizeOfBuffer << endl;
            cout << "\n------------------------\n" << endl;*/
            binaryIndex = 0;

        }
        else
        {
            prev = now;
            if(binaryIndex == 33)
                return false;
            binaryIndex++;
        }


    }


    //cout << "############################" << endl;


    input.close();
    output.close();



    return true;

}

/*
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 * #####################################################################################################################
 */

bool               identicalFiles                          ( const char      * file1,
                                                             const char      * file2 )
{
    ifstream f1(file1), f2(file2);

    uint8_t a, b;
    while(!f2.eof())
    {
        a = f1.get();
        b = f2.get();

        //cout << "output: " << (int)a << "\nreference: " << (int)b << "\n\n" << endl;
        if(a != b || (a == 255 && b != 255) || (a != 255 && b == 255))
            return false;
        if(a == 255 && b == 255)
            break;

    }
    //cout << "\n\n" << endl;
    return true;
}

int main ( int argc, char * argv [] ) {

    if ( argc != 4 || strcmp(argv[1], "-h") == 0  ) {
        cout << "Usage: fibEncode <mode> <input file> <output file>" << endl;
        cout << "Modes: -e (encode), -d (decode), -c (compare)" << endl;
        cout << "Example: fibEncode -e input.txt output.txt" << endl;
        cout << "Written by: David Houdek, 2023" << endl;
        return 1;
    }

    // separate arguments
    string mode = argv[1];
    const char *inputFile = argv[2];
    const char *outputFile = argv[3];

    if(mode == "-e")
    {
        if(!utf8ToFibonacci(inputFile, outputFile))
        {
            cerr << "Error while encoding" << endl;
            return 1;
        }
    }
    else if(mode == "-d")
    {
        if(!fibonacciToUtf8(inputFile, outputFile))
        {
            cerr << "Error while decoding" << endl;
            return 1;
        }
    }
    else if(mode == "-c")
    {
        if(!identicalFiles(inputFile, outputFile))
        {
            cerr << "Files are not identical" << endl;
            return 1;
        }
    }
    else
    {
        cerr << "Unknown mode" << endl;
        return 1;
    }

    cout << "Success" << endl;


    return 0;
}

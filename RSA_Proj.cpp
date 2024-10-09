#include <iostream>
#include <vector>
using namespace std;
bool is_prime(unsigned int num)  // This algorithm is faster than the other one because it breaks when it descovers there is another factor rather than 1 and num
{
    int factor = 0;                       // This algorithm starts to discover factors of num starting with "1"  tell "num-1"
    for (int i = 1; i < num; i++)
    {
        if (num % i == 0)
            factor += i;   // sum of all factors of num
        if (factor > 1)       //while working on getting factors if it founds that the sum of factors it will return false
            return false;
    }
    return true;
}
vector <int> factoring(int num)            //this algorithm gives you all factors of any number in an arra
{
    vector <int> factors;
    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
            factors.push_back(i);
    }
    return factors;
}
bool IsPrime2(int num)                            //this algorithm checks if a number is prime or not by checking the number of factor
{                                                                     // if the num has only 2 factors then it is a prime number
    if (factoring(num).size() == 2)
        return true;
    return false;
}
bool IsPrime(int num)                            //this algorithm checks if a number is prime or not by checking the number of factor
{                                                                     // if the num has only 2 factors then it is a prime number
    if (num<=1)
        return true;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}
int GCD_calc(int num1, int num2)      // This algorithm calculates the Greastest Common Divisor for two numbers
{
    int GCD_Num;
    if (num1 > num2)         // assigning the lower integer to the GCD_Num
        GCD_Num = num2;
    else
        GCD_Num = num1;

    while (GCD_Num > 0) // checking evey smaller integer
    {
        if (num1 % GCD_Num == 0 && num2 % GCD_Num == 0)  // Finding Number is divisable by num1 and num2
            break;                          //if the number is divisble by num1 and num2 then the loop breaks and this is the GCD
        GCD_Num--;                    // if Not  .. check the lower integer than the current number
    }
    return GCD_Num;
}
long long int ModularExponentiation(long long int base, long long int power, int modulus)  // (7 ^ 99) % 5
{                        // This algorithm calculates numbers with large power by Modular Exponentiation
    long long int result = 1;
    while (power > 0)
    {
        if (power % 2 != 0)    //if exponention is odd
            result = (result * base) % modulus;  //storing this value till Exponent becomes 1 
        power /= 2;
        base = (base * base) % modulus;
    }
    return result;
}
vector <int> to_ascii(string str)   // converting any statment to array of ASCII value
{
    vector <int> result;
    for (char i : str)  
    {
        result.push_back(int(i));  // adding every charcter's ASCII value to the array
    }
    return result;
}
string to_str(vector <int> temp)   //converting any array of ASCII values to statment
{ // Saif  =  { s ,a , i ,f } = { 75 ,65 , 70 ,80 }
    string str = "";
    for (int i = 0; i < temp.size(); i++)
    {
        str += char(temp[i]);         // adding every charcter to the string after converting from  ASCII value to charcter
    }
    return str;
}
vector<int> RSA_full_prog(int r, int q)
// Here is The main algorithm of my RSA Encryption and Decryption programe
{
    if (is_prime(r) == 0 || is_prime(q) == 0)  //  1 ==> checking if r and q are prime numbers or not
    {
        system("color 4F");
        return { 0 };
    }
    int n = r * q;                                //  2 ==>  intiallizing  n
    int m = (r - 1) * (q - 1);                //  3 ==>  intiallizing  m
    int e;
    for (int i = 2; i < m; i++)         // i starts with 2 and i < m because we will assign  "i" value's to "e" because     1 < e < m
    {
        e = i;
        if (GCD_calc(m, e) == 1 && GCD_calc(n, e) == 1)     // 4 ==> checking if e is coprime for n and m or not
            break;
    }  
    int d;
    float temp;
    for (int k = 1; ; k++)               // 5 ==>  checking the integer value of k that makes d integer
    {
        temp = ((m * k) + 1) / float(e);
        if (trunc(temp) == temp)         // if the real value = the value after removing the decimal point  ... then  d is integer number  .. then we will assign that value to d
        {  
            //cout <<"k : " << k << endl;
            d = ((m * k) + 1) / e;
            break;
        }
    }
    cout << "\nn : " << n << endl << "m : " << m << endl << "e : " << e << endl << "d : " << d << endl;
    vector <int> keys = { n,e,d };
    // Now We Have finished Key Generation


    cout << "==========Wellcome in PHI's  Team RSA Programe===========\n";
    for (int o = 0; ; o++)
    {
        cout << "==========================================================\n ";
        char ans;

        string P, C, P2;
        vector <int> ascii_statment;
        vector <int> edited_ascii_statment;

        cout << "\nWhat You Want to do : \n    -Encyption ==> enter ( e )\n    -Decyption ==> enter ( d )\n"
            << "\nEnter Your Choise here : ";
        cin >> ans;
        if (ans == 'e' || ans == 'E')      // Encryption
        {
            cout << "\nEnter The plain Message : ";
            cin >> P;
            ascii_statment = to_ascii(P);      // Converting the Message from charcters to array ASCII values
            cout << "\n---Your ASCII Values for plain statment  : ";
            for (int i : ascii_statment)
                cout << i << "  ";
            for (int i = 0; i < P.length(); i++)
            {
                // C = int(pow(P,e)) % n;                  // This method is Not efficient in case of large power
                edited_ascii_statment.push_back(ModularExponentiation(ascii_statment[i], e, n));       // this method is efficient
            }                                                                                                                                                                    // Making Encryption For the ASCII values
            C = to_str(edited_ascii_statment);              // Converting The array of ASCII values to Statement of Charcters
            cout << "\n---Your ASCII Values for cipher statment : ";
            for (int i : edited_ascii_statment)
                cout << i << "  ";
            cout << "\n\n---Your Cipher Message after Encryption is : " << C;
            system("color 2F");
            vector <int> encrypted;
            vector <int> decrypted;
            encrypted = edited_ascii_statment;
            //  encrypted = to_ascii(C);



             // Auto Decryption for the Cipher Message
            for (int i = 0; i < P.length(); i++)
            {
                decrypted.push_back(ModularExponentiation(encrypted[i], d, n));
            }
            P2 = to_str(decrypted);
            cout << "\n---Your Plain Message after Decryption is : " << P2;
        }


        else if (ans == 'd' || ans == 'D')    // Decryption
        {
            cout << "\nEnter The Cipher Message : ";
            cin >> C;
            ascii_statment = to_ascii(C);
            for (int i = 0; i < C.length(); i++)
            {
                edited_ascii_statment.push_back(ModularExponentiation(ascii_statment[i], d, n));
            }
            P = to_str(edited_ascii_statment);
            cout << "\nYour Plain Message is : " << P;
            system("color 2F");
        }
        else
        {
            cout << "\nInvalid Choise \n";
            system("color 4F");
            return { 0 };
        }

        char ans2;
        cout << "\nDo You Want To Make another operation ? [y/n] : ";
        cin >> ans2;
        cout << "\n";
        if (ans2 == 'n' || ans2 == 'N')
        {
            cout << "==========Thanks For Using My App:)============= \n";
            system("color 4F");
            break;
        }
        if (ans2 == 'y' || ans2 == 'Y')
        {
            system("color 8F");
            continue;
        }
        else
        {
            cout << "\nInvalid Choise \n";
            system("color 4F");
            return { 0 };
        }
    }
    return keys;
}
vector<int> RSA_part_prog(int r, int q)
// Here is The main algorithm of my RSA Encryption and Decryption programe
{
    if (is_prime(r) == 0 || is_prime(q) == 0)  //  1 ==> checking if r and q are prime numbers or not
        return { 0 };
    int n = r * q;                                //  2 ==>  intiallizing  n
    int m = (r - 1) * (q - 1);                //  3 ==>  intiallizing  m
    int e;
    for (int i = 2; i < m; i++)         // i starts with 1 and i < m because we will assign  "i" value's to "e" because     0 < e < m
    {
        e = i;
        if (GCD_calc(m, e) == 1 && GCD_calc(n, e) == 1)     // 4 ==> checking if e is coprime for n and m or not
            break;
    }
    int d;
    float temp;
    for (int k = 2; ; k++)               // 5 ==>  checking the integer value of k that makes d integer
    {
        temp = ((m * k) + 1) / float(e);
        if (trunc(temp) == temp)         // if the real value = the value after removing the decimal point  ... then  d is integer number  .. then we will assign that value to d
        {
            //cout <<"k : " << k << endl;
            d = ((m * k) + 1) / e;
            break;
        }
    }
    cout << "\nn : " << n << endl << "m : " << m << endl << "e : " << e << endl << "d : " << d << endl;
    vector <int> keys = { n,e,d };
    // Now We Have finished Key Generation


    cout << "==========Wellcome in Yusuf's RSA Programe===========\n";
    for (int o = 0; ; o++)
    {
        cout << "=====================================================\n ";
        char ans;

        long long int P, C;

        cout << "\nWhat You Want to do : \n    -Encyption ==> enter ( e )\n    -Decyption ==> enter ( d )\n"
            << "\nEnter Your Choise here : ";
        cin >> ans;
        if (ans == 'e' || ans == 'E')      // Encryption
        {
            cout << "\nEnter The plain Message : ";
            cin >> P;
            // C = int(pow(P,e)) % n;                  // This method is Not efficient in case of large power
            C = ModularExponentiation(P, e, n);    // this method is efficient
            cout << "\nYour Cipher Message after Encryption is : " << C;
            system("color 2F");
        }


        else if (ans == 'd' || ans == 'D')    // Decryption
        {
            cout << "\nEnter The Cipher Message : ";
            cin >> C;
            P = ModularExponentiation(C, d, n);
            cout << "\nYour Plain Message is : " << P;
            system("color 2F");
        }

        char ans2;
        cout << "\nDo You Want To Make another operation ? [y/n] : ";
        cin >> ans2;
        cout << "\n";
        if (ans2 == 'n' || ans2 == 'N')
        {
            cout << "==========Thanks For Using My App:)============= \n";
            system("color 4F");
            break;
        }
    }
    return keys;
}
int main()
{
    RSA_full_prog(19,17);
    return 0;
}

#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>

int first_exercise();
int second_exercise();

class Polynomial
{
public:
    explicit Polynomial(std::string code_seq)
    {
        this->code_seq = code_seq;
    }

    std::string code_seq;


    void setCode(std::string code_seq){
        this->code_seq = code_seq;
    }

    Polynomial() = default;
    ~Polynomial() = default;
};

//EVERYTHING IN GF(2)
bool operator>(std::string p_first, std::string p_second)
{
    int it = 0;
    if (p_first.length() == p_second.length())
    {
        while (it++ != p_first.length() && p_first[it] == p_second[it]);
        if (it == p_first.length() - 1)
            return false;
        else if (p_first[it] == '1')
            return true;
        else
            return false;
    } else if (p_first.length() > p_second.length() && p_first[0] == '1')
        return true;
    else if (p_first.length() < p_second.length() && p_second[0] == '1')
        return false;
    return false;
}

bool operator<(std::string p_first, std::string p_second)
{
    int it = 0;
    if (p_first.length() == p_second.length())
    {
        while (it++ != p_first.length() && p_first[it] == p_second[it]);
        if (it != p_first.length())
            return false;
        else if (p_first[it] == '0')
            return true;
        else
            return false;
    } else if (p_first.length() > p_second.length() && p_first[0] == '1')
        return false;
    else if (p_first.length() < p_second.length() && p_second[0] == '1')
        return true;
    return false;
}


std::string operator/(Polynomial polynomial_first, Polynomial polynomial_second) // xor instead of diff
{
    Polynomial quotient("");
    std::string str1 = polynomial_first.code_seq, str2 = polynomial_second.code_seq;
    while (str1.length() >= str2.length())   //main cycle of division1
    {
        int curr_index = 0;
        std::string curr_divider;      // giving zero-value for making a new divider every time from curr_index pos
        if (curr_divider.length() || str1[curr_index] != '0')
        {
            curr_divider += str1[curr_index];
            curr_index += 1;
        } else
        { str1.erase(0, 1); }
        while (curr_divider < str2)
        {
            quotient.code_seq += '0';
            if (curr_divider.length() || str1[curr_index] != '0')
            {
                curr_divider += str1[curr_index];
                curr_index += 1;
            } else
            { str1.erase(0, 1); }
        }
        while (curr_index-- > 0)
        {
            if (curr_divider[curr_index] == '1' && str2[curr_index] == '1')
            {
                str1.replace(curr_index, 1, "0");
            } else if (curr_divider[curr_index] == '0' && str2[curr_index] == '1')
            {
                str1.replace(curr_index, 1, "1");
            }
        }
    }
    return str1;
}


int main()
{
    first_exercise();
    second_exercise();
    return 0;
}

int first_exercise(){
    std::string code_sequence, answer, generator_polynomial = "100000010010000000010000001001";     // g(x) = p(x)* (x^(2n - 1) - 1)
    std::cout
            << "Do you want to enter code sequence from console by yourself or form it with random() function by program?(C|R)";
    getline(std::cin, answer);
    bool flag_of_error = true;
    while (flag_of_error)
    {
        if (answer == "R")
        {
            code_sequence.append("1");
            srand(time(nullptr));
            for (int i = 0; i < 19408; i++)
            {
                code_sequence.append(std::to_string(std::rand() % 2));
            }
            flag_of_error = false;
        } else if (answer == "C")
        {
            std::cout << "Enter your code sequence of 19408 size below please: ";
            getline(std::cin, code_sequence);
            flag_of_error = false;
        } else
            std::cout << "I cannot understand the answer, please enter C or R";
    }
    std::cout << "\nFile is ready";
    for (int i = 0; i < 29; ++i)
        code_sequence += '0';
    std::string syndrome;
    Polynomial code(code_sequence), forming_poly(generator_polynomial);
    syndrome = code / forming_poly;
    std::cout << "\nSyndrome is ready";
    code.code_seq.erase(code.code_seq.length() - 30);
    std::cout << "\nLength of code.code_seq now is: " << code.code_seq.length();
    int temp_len = syndrome.length();
    while (temp_len++ < 29) code.code_seq.append("0");
    code.code_seq.append(syndrome);
    //file processing
    std::ofstream out_stream;
    out_stream.open("file_with_code.txt");
    out_stream << "Program implementing Fire's codes for correcting transfer mistakes" << std::endl
               << "Made by Danil Kizeev\nSPbU, math-mechanic faculty\n";
    out_stream << "2019 \nYour encoded polynomial of 19408 length:" << std::endl;
    out_stream << "Your syndrome is :" << syndrome << std::endl;
    out_stream << code.code_seq << std::endl << "Your polynomial length: " << code.code_seq.length();
    out_stream << "\nFile has encoded!";
    out_stream.close();
}


int second_exercise()
{
    std::string result, generator_polynomial_j_4 = "1000000000000000100000000000100000001000000000001";     //g(x^4)
                // g(x) = x^48 + x^32 + x^20 + x^12 + 1
    std::vector<std::string> array_of_Polynomials;
    for (int i = 0; i < 4; ++i)
    {
        std::string temp_code;
        temp_code.append("1");
        srand(time(nullptr));
        for (int i = 0; i < 256; i++)       // making code for size of 499 - 243 = 256 for decreasing time wasting
        {
            temp_code.append(std::to_string(std::rand() % 2));
        }
        array_of_Polynomials.push_back(temp_code);
    }
    std::cout << "Array of shorted codes has made";
    //interleaving now:
    for(int i = 0; i < 256; ++i)
    {
        result.push_back(array_of_Polynomials[0][i]);
        result.push_back(array_of_Polynomials[1][i]);
        result.push_back(array_of_Polynomials[2][i]);
        result.push_back(array_of_Polynomials[3][i]);
    }
    std::cout << "Interleaved code is ready";
    for (int i = 0; i < 48; ++i)        //adding checking-errors bites
        result += '0';
    Polynomial code_first(result), forming_polynomial(generator_polynomial_j_4);
    std::string syndrome = code_first / forming_polynomial;
    std::cout << "\nSyndrome is ready";
    code_first.code_seq.erase(code_first.code_seq.length() - 49);       // deleting checking zeros for replacing it with the syndrome
    int temp_len = syndrome.length();
    while (temp_len++ < 48) code_first.code_seq.append("0");      //if syndrome.length() != n - k = 48
    code_first.code_seq.append(syndrome);
    std::cout << "\nLength of code_first.code_seq now is: " << code_first.code_seq.length();
    std::cout << "\nFirst code sequence is ready now";
    //first is ready now

    array_of_Polynomials.clear(); result = ""
            , generator_polynomial_j_4 = "100000000000100000001000000000000000100000000000100000001";
                //g(x) = x^56 + x^44 + x^36 + x^20 + x^8 + 1
    for (int i = 0; i < 4; ++i)
    {
        std::string temp_code;
        temp_code.append("1");
        srand(time(nullptr));
        for (int i = 0; i < 256; i++)       // making code for size of 265 - 9 = 256 for decreasing time wasting
        {
            temp_code.append(std::to_string(std::rand() % 2));
        }
        array_of_Polynomials.push_back(temp_code);
    }
    std::cout << "Array of shorted codes has made";
    //interleaving now:
    for(int i = 0; i < 256; ++i)
    {
        result.push_back(array_of_Polynomials[0][i]);
        result.push_back(array_of_Polynomials[1][i]);
        result.push_back(array_of_Polynomials[2][i]);
        result.push_back(array_of_Polynomials[3][i]);
    }
    std::cout << "Interleaved code is ready";
    for (int i = 0; i < 48; ++i)        //adding checking-errors bites
        result += '0';
    Polynomial code_second(result);
    forming_polynomial.setCode(generator_polynomial_j_4);
    syndrome = code_second / forming_polynomial;
    std::cout << "\nSyndrome is ready";
    code_second.code_seq.erase(code_second.code_seq.length() - 49);       // deleting checking zeros for replacing it with the syndrome
    temp_len = syndrome.length();
    while (temp_len++ < 48) code_second.code_seq.append("0");      //if syndrome.length() != n - k = 48
    code_second.code_seq.append(syndrome);
    std::cout << "\nLength of code_first.code_seq now is: " << code_second.code_seq.length();
    std::cout << "\nFirst code sequence is ready now";

    //working with file now
    std::ofstream out_stream;
    out_stream.open("Exercise_2.txt");
    out_stream << "Program implementing interleaving and shorting code for correcting transfer mistakes" << std::endl
               << "Made by Danil Kizeev\nSPbU, math-mechanic faculty\n";
    out_stream << "2019 \n\nYour encoded polynomial of 1076 length:\n" << std::endl;
    out_stream << code_first.code_seq;
    out_stream << "\n\nYour encoded polynomial of 1080 length:\n" << std::endl;
    out_stream << code_second.code_seq;
    std::cout << "\n\nFile is ready!";
    out_stream.close();
}


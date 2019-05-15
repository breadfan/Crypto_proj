#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>


class Polynomial{
public:
    explicit Polynomial(std::string code_seq)
    {
        this->code_seq = code_seq;
    }
    std::string code_seq;
};

//EVERYTHING IN GF(2)
bool operator >(std::string p_first, std::string p_second){
    int it = 0;
    if(p_first.length() == p_second.length()){
        while(it++ != p_first.length() && p_first[it] == p_second[it]);
        if(it == p_first.length() - 1)
            return false;
        else if(p_first[it] == '1')
            return true;
        else
            return false;
    }
    else if(p_first.length() > p_second.length() && p_first[0] == '1')
        return true;
    else if(p_first.length() < p_second.length() && p_second[0] == '1')
        return false;
    return false;
}

bool operator <(std::string p_first, std::string p_second){
    int it = 0;
    if(p_first.length() == p_second.length()){
        while(it++ != p_first.length() && p_first[it] == p_second[it]);
        if(it != p_first.length())
            return false;
        else if(p_first[it] == '0')
            return true;
        else
            return false;
    }
    else if(p_first.length() > p_second.length() && p_first[0] == '1')
        return false;
    else if(p_first.length() < p_second.length() && p_second[0] == '1')
        return true;
    return false;
}


std::string operator /(Polynomial polynomial_first, Polynomial polynomial_second) // xor instead of diff
{
    Polynomial quotient("");
    std::string str1 = polynomial_first.code_seq, str2 = polynomial_second.code_seq;
    while(str1.length() >= str2.length())   //main cycle of division1
    {
        int curr_index = 0;
        std::string curr_divider;      // giving zero-value for making a new divider every time from curr_index pos
        if(curr_divider.length() || str1[curr_index] != '0')
        {
                curr_divider += str1[curr_index];
                curr_index += 1;
        } else {str1.erase(0, 1);}
        while(curr_divider < str2)
        {
            quotient.code_seq += '0';
            if(curr_divider.length() || str1[curr_index] != '0')
            {
                curr_divider += str1[curr_index];
                curr_index += 1;
            } else {str1.erase(0, 1);}
        }
        while(curr_index-- > 0)
        {
            if(curr_divider[curr_index] == '1' && str2[curr_index] == '1')
            {
                str1.replace(curr_index , 1, "0");
            }
            else if(curr_divider[curr_index] == '0' && str2[curr_index] == '1')
            {
                str1.replace(curr_index, 1, "1");
            }
        }
    }
    return str1;
}



int main()
{
    std::string code_sequence, generator_polynomial = "100000010010000000010000001001";     // g(x) = p(x)* (x^(2n - 1) - 1)
    code_sequence.append("1");
    srand(time(nullptr));
    for(int i = 0; i < 19408; i++){
        code_sequence.append(std::to_string(std::rand() % 2));
    }
    std::cout << "\nFile is ready";
    for(int i = 0; i < 29; ++i)
        code_sequence += '0';
    std::string syndrome;
    Polynomial code(code_sequence), forming_poly(generator_polynomial);
    syndrome = code / forming_poly;
    std::cout << "\nSyndrome is ready";
    code.code_seq.erase(code.code_seq.length() - 30);
    std::cout << "\nLength of code.code_seq now is: " << code.code_seq.length();
    int temp_len = syndrome.length();
    while(temp_len++ < 29) code.code_seq.append("0");
    code.code_seq.append(syndrome);
            //file processing
    std::ofstream out_stream;
    out_stream.open("file_with_code.txt");
    out_stream << "Program implementing Fire's codes for correcting transfer mistakes" << std::endl << "Made by Danil Kizeev\nSPbU, Math-mechanic faculty\n";
    out_stream << "2019 \nYour encoded polynomial of 19408 length:" << std::endl;
    out_stream << "Your syndrome is :" << syndrome <<std::endl;
    out_stream << code.code_seq << std::endl << "Your polynomial length: " << code.code_seq.length();
    out_stream << "\nFile encoded!";
    out_stream.close();
    return 0;
}


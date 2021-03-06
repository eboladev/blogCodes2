#include <clocale>
#include <cmath>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

void find_chinese()
{
    try{
        std::wstring ws_str = L"性 \t\r\n`~!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?爱";
        std::wregex wrx(L"性[(\\W|_]*爱", std::regex_constants::extended);
        std::wstring wfmt(L"革命");
        std::locale::global(std::locale("en_US.UTF-8"));
        std::wstring ws_res = std::regex_replace(ws_str, wrx, wfmt);
        std::wcout<<ws_res<<std::endl;
    }catch(std::exception const &ex){
        std::cout<<ex.what()<<std::endl;
    }
}

void find_multiple_words()
{
    std::string const strs("This is a book 123, a pen 321, a human 345");
    std::regex reg("\\d+");

    std::vector<int> nums;
    for(std::sregex_iterator begin(std::begin(strs), std::end(strs), reg), end; begin != end; ++begin){
        nums.emplace_back(std::stoi(begin->str()));
        std::cout<<nums.back()<<std::endl;
    }
}

void find_multiple_words_two()
{
    std::string strs("one,two,three,four,five,six,seven,eight,nine,ten,eleven,NNNN");
    std::regex reg(R"(([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),(NNNN)\n?)");
    //std::regex reg(R"(([a-z]*,){11}(NNNN)[\n]?)");
    std::cout<<std::regex_replace(strs, reg, "$1-$2-$3-$4-$5-$6-$7-$8-$9-$10-$11")<<std::endl;

    /*std::smatch match;
    std::regex_search(strs, match, reg);
    std::cout<<match.size()<<std::endl;
    for(size_t i = 0; i != match.size(); ++i){
        std::cout<<match[i]<<std::endl;
    }*/
}

void find_multiple_words_three()
{
    std::string const strs("one,two,three,four,five,six,seven,eight,nine,ten,eleven,NNNN");
    std::regex reg_extract(R"(([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),([a-z]*),(NNNN)\n?)");
    std::smatch match;
    std::regex_search(strs, match, reg_extract);
    for(size_t i = 1; i != match.size() - 1; ++i){
        std::cout<<match[i]<<std::endl;
    }

    std::regex reg_replace_comma(",");
    std::cout<<std::regex_replace(strs, reg_replace_comma, "-")<<std::endl;

    std::regex reg_replace_newline(R"(\n|\r)");
    std::cout<<std::regex_replace(strs, reg_replace_newline, " ")<<std::endl;
}

void find_patterns_one()
{
    try{
        std::string const strs("00004400  00 00 04 02 00 00 18 04  01 30 01 14 33 A2 44 41   ........ .0..3.DA\n"
                               "00004410  0C E4 BB A4 E7 8B 90 E5  A4 A9 E5 86 B0 00 00 00   ........ ........\n"
                               "00004460  00 00 00 00 00 00 00 00  00 00 00 01 30 01 14 85   ........ ....0...\n"
                               "00004470  A3 44 41 09 E5 B2 B3 E9  9C 87 E5 A4 A9 00 00 00   .DA..... ........ ");

        std::regex pattern_0("30[ ]+01[ ]+14[ ]+.{2}[ ]+.{2}[ ]+(44[ ]+41)|"
                             "30.{29}  01 14 .{2} .{2} (44 41)|"
                             "30 01.{29}  14 .{2} .{2} (44 41)|"
                             "30 01 14.{29}  .{2} .{2} (44 41)|"
                             "30 01 14 .{2}.{29}  .{2} (44 41)|"
                             "30 01 14 .{2} .{2}.{29}  (44 41)|"
                             "30 01 14 .{2} .{2} (44.{29}  41)",
                             std::regex_constants::optimize
                             );

        /*std::regex pattern_1("30 01 14 .{2}.{20}\\n.{8}  .{2} (44 41)");

        std::smatch match;
        std::regex_search(strs, match, pattern_0);

        for(size_t i = 0; i != match.size(); ++i){
            std::cout<<"match string "<<i<<" : "<<match[i]<<std::endl;
            std::cout<<"match position "<<i<<" : "<<match.position(i)<<std::endl<<std::endl;
        }

        std::regex_search(strs.substr(match.position(1), strs.size() - match.position(1)), match, pattern_0);
        for(size_t i = 0; i != match.size(); ++i){
            std::cout<<"match string "<<i<<" : "<<match[i]<<std::endl;
            std::cout<<"match position "<<i<<" : "<<match.position(i)<<std::endl<<std::endl;
        }*/

        size_t loop = 0;
        for(std::sregex_iterator begin(std::begin(strs), std::end(strs), pattern_0), end; begin != end; ++begin){
            std::cout<<"match "<<loop++<<std::endl;
            for(size_t i = 0; i != begin->size(); ++i){
                if(begin->position(i) >= 0){
                    std::cout<<"match string "<<i<<" : "<<begin->str(i)<<std::endl;
                    std::cout<<"match position "<<i<<" : "<<begin->position(i)<<std::endl<<std::endl;
                }
            }
        }
    }catch(std::exception const &ex){
        std::cout<<ex.what()<<std::endl;
    }
}

void regex_replace_one()
{
    std::string s ("there is a subsequence in the string\n");
    std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

    // using string/c-string (3) version:
    std::cout << std::regex_replace (s,e,"sub-$2");

    // using range/c-string (6) version:
    std::string result;
    std::regex_replace (std::back_inserter(result), s.begin(), s.end(), e, "$2");
    std::cout << result;

    // with flags:
    std::cout << std::regex_replace (s,e,"$1 and $2",std::regex_constants::format_no_copy);
    std::cout << std::endl;
}

void regex_replace_two()
{
    char str[] = "i like this dog,what a pretty dog";
    std::regex e("\\b(dog)");

    std::string const result = std::regex_replace(str, e, "cat");
    std::cout<<result<<std::endl;
}

void regex_replace_three()
{
    std::string strs{"0.5\">If you are a premiere member of the lynda.com online training library, or if you\n\n"
                     "5.19\">are watching this tutorial on a DVD, you have access to the exercise files used throughout the title.\n\n"};

    std::regex pattern(R"delimeter(([0-9.]+)[^\n]+\n+)delimeter"
                       R"delimeter(([0-9.]+)[^\n]+\n+)delimeter");
    std::smatch match;
    std::regex_search(strs, match, pattern);

    size_t loop = 0;
    //std::string result;
    //std::string new_line;
    for(std::sregex_iterator begin(std::begin(strs), std::end(strs), pattern), end; begin != end; ++begin){
        std::cout<<"loop "<<loop++<<std::endl;
        size_t const Size = begin->size();
        for(size_t i = Size > 1 ? 1 : 0; i != Size; ++i){
            std::cout<<"match string "<<i<<" : "<<begin->str(i)<<std::endl<<std::endl;
        }

        if(Size == 3){
            //size_t string_position = strs.find_first_of("\"");
            float const first_num = std::stof(begin->str(1));
            //float const second_num = std::stof(begin->str(2));
            std::cout<< (int)(first_num / 3600) <<", "<< ((int)(first_num / 60) % 60) <<", " <<
                        ((int)first_num % 60)<<", "<<(int)((first_num - std::floor(first_num)) * 1000)
                        <<std::endl;
        }
        //std::cout<<strs<<std::endl;
    }
}

int main()
{
    //find_chinese();
    //find_multiple_words();
    //find_multiple_words_two();
    //find_multiple_words_three();
    //find_patterns_one();
    //regex_replace_one();
    //regex_replace_two();
    regex_replace_three();

    return 0;
}


#pragma once

#include <string>
#include <vector>
#include <regex>

inline std::vector<std::string> splitWhitespace(std::string str){
    std::vector<std::string> split;

    std::string word = "";

    for (int i = 0; i < str.length(); i++)
    {
       char c = str.at(i);
       if (c == ' '){
        split.push_back(word);
        word = "";
       }
       else
       {
        word += c;
       }
    }

    if (word.length() > 0){
        split.push_back(word);
    }

    return split;
}

inline bool isLineComment(std::string str){
    return str.length() > 1 && str.substr(0, 2) == "//";
}
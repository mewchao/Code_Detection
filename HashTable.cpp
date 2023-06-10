#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include "HashTable.h"


string key_word[32]={
        //其中，存储类型包括：
        "auto", "static", "register", "extern",
        //数据类型包括：
        "int", "short", "long", "char", "float", "double", "signed", "unsigned", "struct", "enum", "union", "void",
        //控制语句包括：
        "if", "else", "switch", "case", "default", "break", "for", "while", "do", "goto", "continue",
        //其他关键字包括：
        "const", "sizeof", "typedef", "volatile", "return",
};

//    这是一个读取文件并过滤注释的函数。
//    它使用了正则表达式和字符串操作来去除空行、单行注释、多行注释和行内注释，只保留代码行。其中，isNotes变量用于记录是否处于多行注释中。
//    函数首先尝试打开指定路径的文件，如果无法打开则返回空的字符串向量。
//    然后逐行读取文件内容，去除行首和行末的空格，并过滤掉空行和注释行。
//    如果当前行处于多行注释中，则继续读取直到遇到结束符号"/"。如果当前行以"/"开头，则表示进入了多行注释，将isNotes标记为真。
//    如果当前行中存在注释符号"//"或"/*"，则截取注释符号之前的内容。最后将过滤后的代码行存入字符串向量中并返回。
vector<string> readFile(const string &path) {
    vector<string> file;
    bool isNotes=false;
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr<<"Error opening file: "<<path<<std::endl;
        return file;
    }
    string line;
    while (std::getline(ifs, line)) {
        line=std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");
        // 过滤C语言文件中的空行、单行注释、多行注释和行内注释
        if (isNotes&&line.find("*/")!=string::npos) {
            isNotes=false;
            continue;
        }
        if (line.empty()||line.find("//")==0||(line.find("/*")==0&&line.find("*/")!=string::npos)||isNotes) {
            continue;
        }
        if (!isNotes&&line.find("/*")==0) {
            isNotes=true;
            continue;
        }
        size_t noteIndex=(line.find("/*")==string::npos) ? line.find("//") : line.find("/*");
        if (noteIndex!=string::npos) {
            line=line.substr(0, noteIndex);
        }

        file.push_back(line);
    }
    ifs.close();
//    cout<<"test";
    return file;
}


//该函数返回一个元组(tuple)，包含三个不同的字符串向量(vector
tuple<vector<string>, vector<string>, vector<string>> readFiles() {
//  使用了花括号列表初始化的方式
    return {readFile("../test1.c"), readFile("../test2.c"), readFile("../test3.c")};
}


//接受两个参数：一个vector<string>类型的文件和一个HashTable<string, int>类型的哈希表。该函数的作用是将文件中每个单词在哈希表中进行计数，即统计单词出现的次数。
//然后，函数遍历words中的每个单词，并检查它是否已经在哈希表中出现过。如果是，则在哈希表中增加该单词的计数值；否则忽略该单词。
void processFile(const vector<string> &file, HashTable &table) {

    std::regex pattern("[\\s,.?;!:\"']+");

    for (const auto &line: file) {

//        sregex_token_iterator其中第一个参数为待查找的字符串，第二个参数为正则表达式，第三个参数为指定查找方式的标志位
        vector<string> words(std::sregex_token_iterator(line.begin(), line.end(), pattern, -1),
                             std::sregex_token_iterator());

        for (const auto &word: words) {
            int flag=0;
            for(int i=0;i<32;i++){
                if(word==key_word[i]){
                    flag=1;
                }
            }
            if(flag)
//              判断哈希表中是否存在该单词
//              table.get(word)获取该单词对应的值（即出现次数），table.put(word, table.get(word)+1)将该单词的值加1并更新到哈希表中。
                table.put(word, table.get(word)+1);
//cout<<word<<":  put test"<<"  "<<endl;
        }
    }
}


//计算两个一维数组之间欧几里得距离。其中，输入参数array1和array2分别表示待计算的两个一维数组，distance用于记录计算结果，i表示当前正在计算的元素下标。
//具体来说，该函数会首先将distance初始化为0，然后对于数组中每个元素，计算它们之间差的平方，并将结果累加到distance中。最后，使用sqrt函数计算distance的平方根并返回结果。
double computeEuclideanDistance(const vector<int> &array1, const vector<int> &array2) {
    double distance=0;
    for (size_t i=0; i<array1.size(); ++i) {
        distance+=pow(array1[i]-array2[i], 2);
    }
    return sqrt(distance);
}


// 两个向量之间余弦相似度的函数。余弦相似度是通过比较两个向量在空间中的夹角来衡量它们的相似程度的一种方法。
// 创建一个与输入向量相同大小的全零向量 zeroList，并检查 x 和 y 是否等于全零向量。
// 如果其中任何一个向量是全零向量，则返回 0 或 1（取决于它们是否相等）。否则，函数将计算两个向量的点积和平方和，并根据公式计算余弦相似度。
// 函数返回余弦相似度的值加上 0.5 的结果，以确保输出范围在 [0, 1] 内。
// 假定输入向量已经被规范化为单位向量，即其长度为 1。如果输入向量未被规范化，则应该先将它们规范化为单位向量，再调用此函数进行相似度计算
double computeCosineSimilarity(const vector<int> &x, const vector<int> &y) {
    vector<int> zeroList(x.size(), 0);
    if (x==zeroList||y==zeroList) {
        return (x==y) ? 1.0 : 0.0;
    }

    double dotProduct=0, squareSumX=0, squareSumY=0;
    for (size_t i=0; i<x.size(); ++i) {
        dotProduct+=x[i]*y[i];
        squareSumX+=x[i]*x[i];
        squareSumY+=y[i]*y[i];
    }
    double cos=dotProduct/(sqrt(squareSumX)*sqrt(squareSumY));

    return 0.5*cos+0.5;
}



int main() {

    cout<<endl<<endl<<"Copyright <c++> 2023-2023 22220231_游竣超. All Right Reserved"<<endl<<endl;

    //======================================
    cout<<endl<<"test1.c词频如下:"<<endl<<endl;
    HashTable hashtable1(32);

    for ( auto word: key_word) {
        hashtable1.put(word, 1);
    }

    vector <string > v1=std::get<1>(readFiles());

    processFile(v1,hashtable1);

    hashtable1.displayHashTable(hashtable1);
    //======================================
    cout<<endl<<"test2.c词频如下:"<<endl<<endl;
    HashTable hashtable2(32);

    for ( auto word: key_word) {
        hashtable2.put(word, 1);
    }

    vector <string > v2=std::get<2>(readFiles());

    processFile(v2,hashtable2);

    hashtable2.displayHashTable(hashtable2);
    //======================================
    cout<<endl<<"test3.c词频如下:"<<endl<<endl;
    HashTable hashtable3(32);

    for ( auto word: key_word) {
        hashtable3.put(word, 1);
    }

    vector <string > v3=std::get<2>(readFiles());

    processFile(v3,hashtable3);

    hashtable3.displayHashTable(hashtable3);
    //======================================
    system("pause");

}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>
#include "HashTable.h"


string key_word[32]={
        //���У��洢���Ͱ�����
        "auto", "static", "register", "extern",
        //�������Ͱ�����
        "int", "short", "long", "char", "float", "double", "signed", "unsigned", "struct", "enum", "union", "void",
        //������������
        "if", "else", "switch", "case", "default", "break", "for", "while", "do", "goto", "continue",
        //�����ؼ��ְ�����
        "const", "sizeof", "typedef", "volatile", "return",
};

//    ����һ����ȡ�ļ�������ע�͵ĺ�����
//    ��ʹ����������ʽ���ַ���������ȥ�����С�����ע�͡�����ע�ͺ�����ע�ͣ�ֻ���������С����У�isNotes�������ڼ�¼�Ƿ��ڶ���ע���С�
//    �������ȳ��Դ�ָ��·�����ļ�������޷����򷵻ؿյ��ַ���������
//    Ȼ�����ж�ȡ�ļ����ݣ�ȥ�����׺���ĩ�Ŀո񣬲����˵����к�ע���С�
//    �����ǰ�д��ڶ���ע���У��������ȡֱ��������������"/"�������ǰ����"/"��ͷ�����ʾ�����˶���ע�ͣ���isNotes���Ϊ�档
//    �����ǰ���д���ע�ͷ���"//"��"/*"�����ȡע�ͷ���֮ǰ�����ݡ���󽫹��˺�Ĵ����д����ַ��������в����ء�
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
        // ����C�����ļ��еĿ��С�����ע�͡�����ע�ͺ�����ע��
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


//�ú�������һ��Ԫ��(tuple)������������ͬ���ַ�������(vector
tuple<vector<string>, vector<string>, vector<string>> readFiles() {
//  ʹ���˻������б��ʼ���ķ�ʽ
    return {readFile("../test1.c"), readFile("../test2.c"), readFile("../test3.c")};
}


//��������������һ��vector<string>���͵��ļ���һ��HashTable<string, int>���͵Ĺ�ϣ���ú����������ǽ��ļ���ÿ�������ڹ�ϣ���н��м�������ͳ�Ƶ��ʳ��ֵĴ�����
//Ȼ�󣬺�������words�е�ÿ�����ʣ���������Ƿ��Ѿ��ڹ�ϣ���г��ֹ�������ǣ����ڹ�ϣ�������Ӹõ��ʵļ���ֵ��������Ըõ��ʡ�
void processFile(const vector<string> &file, HashTable &table) {

    std::regex pattern("[\\s,.?;!:\"']+");

    for (const auto &line: file) {

//        sregex_token_iterator���е�һ������Ϊ�����ҵ��ַ������ڶ�������Ϊ������ʽ������������Ϊָ�����ҷ�ʽ�ı�־λ
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
//              �жϹ�ϣ�����Ƿ���ڸõ���
//              table.get(word)��ȡ�õ��ʶ�Ӧ��ֵ�������ִ�������table.put(word, table.get(word)+1)���õ��ʵ�ֵ��1�����µ���ϣ���С�
                table.put(word, table.get(word)+1);
//cout<<word<<":  put test"<<"  "<<endl;
        }
    }
}


//��������һά����֮��ŷ����þ��롣���У��������array1��array2�ֱ��ʾ�����������һά���飬distance���ڼ�¼��������i��ʾ��ǰ���ڼ����Ԫ���±ꡣ
//������˵���ú��������Ƚ�distance��ʼ��Ϊ0��Ȼ�����������ÿ��Ԫ�أ���������֮����ƽ������������ۼӵ�distance�С����ʹ��sqrt��������distance��ƽ���������ؽ����
double computeEuclideanDistance(const vector<int> &array1, const vector<int> &array2) {
    double distance=0;
    for (size_t i=0; i<array1.size(); ++i) {
        distance+=pow(array1[i]-array2[i], 2);
    }
    return sqrt(distance);
}


// ��������֮���������ƶȵĺ������������ƶ���ͨ���Ƚ����������ڿռ��еļн����������ǵ����Ƴ̶ȵ�һ�ַ�����
// ����һ��������������ͬ��С��ȫ������ zeroList������� x �� y �Ƿ����ȫ��������
// ��������κ�һ��������ȫ���������򷵻� 0 �� 1��ȡ���������Ƿ���ȣ������򣬺������������������ĵ����ƽ���ͣ������ݹ�ʽ�����������ƶȡ�
// ���������������ƶȵ�ֵ���� 0.5 �Ľ������ȷ�������Χ�� [0, 1] �ڡ�
// �ٶ����������Ѿ����淶��Ϊ��λ���������䳤��Ϊ 1�������������δ���淶������Ӧ���Ƚ����ǹ淶��Ϊ��λ�������ٵ��ô˺����������ƶȼ���
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

    cout<<endl<<endl<<"Copyright <c++> 2023-2023 22220231_�ο���. All Right Reserved"<<endl<<endl;

    //======================================
    cout<<endl<<"test1.c��Ƶ����:"<<endl<<endl;
    HashTable hashtable1(32);

    for ( auto word: key_word) {
        hashtable1.put(word, 1);
    }

    vector <string > v1=std::get<1>(readFiles());

    processFile(v1,hashtable1);

    hashtable1.displayHashTable(hashtable1);
    //======================================
    cout<<endl<<"test2.c��Ƶ����:"<<endl<<endl;
    HashTable hashtable2(32);

    for ( auto word: key_word) {
        hashtable2.put(word, 1);
    }

    vector <string > v2=std::get<2>(readFiles());

    processFile(v2,hashtable2);

    hashtable2.displayHashTable(hashtable2);
    //======================================
    cout<<endl<<"test3.c��Ƶ����:"<<endl<<endl;
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
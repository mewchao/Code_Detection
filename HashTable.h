#ifndef CHECK_HASHTABLE_H
#define CHECK_HASHTABLE_H

#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::tuple;
using std::cout;
using std::endl;

//哈希表->数据结构
class HashTable {
private:
    //哈希表的大小
    int size;
    //存放key
    vector<string> slot;
    //存放value
    vector<int> data;

public:
    HashTable(int size) {
//      散列表（哈希表）的大小
        this->size=size;
        this->slot.resize(size);
        this->data.resize(size);
    }

//    哈希表::插入操作，接收键值和数据作为参数，并将它们存储在哈希表中。
//    该函数首先调用哈希函数来计算键的哈希值，然后使用该值作为索引来访问哈希表。
//    如果该索引为空，则直接将键和数据存储在该位置上。如果该索引不为空，那么需要检查该位置上的键是否与要插入的键相同。
//    如果相同，则只需覆盖该位置上的数据。否则，需要使用再哈希法计算新的索引，并继续搜索空的位置，直到找到一个空的位置为止。
//    这个插入操作考虑了冲突的情况，通过使用再哈希法来解决冲突，并将键和数据存储在可用的空位置上。
    void put(string key, int data) {
//      根据键值返回索引
        int hashValue=hashFunction(key, this->slot.size());

        if (this->slot[hashValue].empty()) {
//          此索引hashValue为空时
//          直接放入Entry
            this->slot[hashValue]=key;
            this->data[hashValue]=data;
        } else {
//          此索引hashValue不为空  键值相等，覆盖
            if (this->slot[hashValue]==key) {
                this->data[hashValue]=data;
            } else {
//              键值不相等  再哈希法得到新的下标
                int nextSlot=rehash(hashValue, this->slot.size());
                while (!this->slot[nextSlot].empty()&&this->slot[nextSlot]!=key) {
//                  循环找到一个空的下标
                    nextSlot=rehash(nextSlot, this->slot.size());
                }
//              直到找到一个空的位置存放Entry
                if (this->slot[nextSlot].empty()) {
                    this->slot[nextSlot]=key;
                    this->data[nextSlot]=data;
                } else {
                    this->data[nextSlot]=data;
                }
            }
        }
    }


//    它接受一个字符串键值和哈希表的大小作为输入，
//    并返回一个整数值作为存储该键值对应的值的数组的索引。
//    该函数的工作原理是遍历字符串中的每个字符，并将其ASCII值添加到一个累加器中。
//    最后，将总和除以哈希表的大小（可用插槽数量），并将余数作为索引返回。
    static int hashFunction(string key, int size) {
        int sum=0;
        for (char ch: key) {
            sum+=(int) ch;
        }
        return sum%size;
    }

//    再哈希法”（rehashing）。它接收旧哈希值和表大小作为参数，并返回新的哈希值。
    static int rehash(int oldHash, int size) {
        return (oldHash+3)%size;
    }


//    查询函数::根据key得到value
    int get(string key) {
//        计算出下标
        int startSlot=hashFunction(key, this->slot.size());
        int data=0;
        bool found=false;
        bool stop=false;
        int position=startSlot;

        while (!this->slot[position].empty()&&!found&&!stop) {
            if (this->slot[position]==key) {
                found=true;
                data=this->data[position];
            } else {
                position=rehash(position, this->slot.size());
                if (position==startSlot) {
                    stop=true;
                }
            }
        }
        return data;
    }

//   重载下标运算符， 根据key值得到value
    int operator[](string key) {
        return this->data[hashFunction(key, this->slot.size())];

    }

    //输出hashtable
    void displayHashTable(const HashTable &table) {
        for (int i=0; i<table.size; ++i) {
            std::cout<<"slot "<<i<<": ";
            if (!table.slot[i].empty()) {
                std::cout<<table.slot[i]<<" -> "<<table.data[i];
            }
            std::cout<<std::endl;
        }
    }

//    bool contains( string key) const {
//        // 计算key的哈希值
//        int index = hashFunction(key,this->size);
//
//        // 遍历对应的链表
//        for (const auto& node : data[index]) {
//            if (node.first == key) { // 找到了匹配的键
//                return true;
//            }
//        }
//
//        // 在该位置上没有找到匹配的键
//        return false;
//    }
};

////#ifndef SHOW_COPYRIGHT
////#define SHOW_COPYRIGHT
//void show_copyright() {
//    cout<<endl<<endl<<
//        "Copyright <c++> 2023-2023 22220231_游竣超. All Right Reserved"<<endl<<endl;
//}
////#endif SHOW_COPYRIGHT

#endif //CHECK_HASHTABLE_H

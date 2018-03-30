/** @Copyright   保卫萝卜
*   @author      陈建彰
*   @date        2018/2/28
*   @brief       CSV表格文件处理头文件
*/
#pragma once
#ifndef CSV_UTIL_H
#define CSV_UTIL_H

#include<vector>
#include<map>
#include<string>

typedef std::vector<std::string> StrVec;
typedef std::vector<StrVec> StrDict;
typedef std::map<std::string, StrDict> CsvMap;

class CsvUtil
{
public:
    /*
    @brief   获取单实例
    @return  一个实例指针
    */
    static CsvUtil* getInstance();

    /*
    @brief   销毁当前实例
    */
    static void destroyInstance();

    /*
    @brief             载入一个文件到字典中
    @param FilePath    文件路径
    */
    virtual void addFileData(const std::string& FilePath);

    /*
    @brief              释放文件，在字典中删除该文件对应的数据
    @param FilePath     文件路径
    */
    virtual void releaseFile(const std::string& FilePath);

    /*
    @brief           在某个csv文件中读取某一行某一列的数据

    @param rRow      目标行数
    @param rCol      目标列数
    @param FilePath  文件路径

    @return          可返回字符串std::string，整型数据和浮点型数据
    */
    virtual std::string getStr(const int& rRow, const int& rCol, const std::string &FilePath);
    virtual int getInt(const int& rRow, const int& rCol, const std::string &FilePath);
    virtual double getDouble(const int& rRow, const int& rCol, const std::string &FilePath);

    /*
    @brief           获取一整行的数据
    @param rRow      目标行数
    @param FilePath  文件路径
    */
    virtual StrVec getRowData(const int& rRow, const std::string& FilePath);

    /*
    @brief            获取该文件的行数和列数
    @param FilePath   文件路径
    @return           一个元组，第一个数是行数，第二个数是列数
    */
    virtual std::tuple<int, int> getFileRowColNum(const std::string &FilePath);

    /*
    @brief               在某个csv文件的某一列中寻找一个值，若寻找成功，返回对应的行数
    @param targetValue   目标值
    @param col           查找范围
    @param FilePath      文件路径
    @return              该值对应的行数
    */
    virtual int findVal(const std::string &targetValue, const int &col, const std::string &FilePath);

protected:
    /*
    @brief            获取某csv文件对应的StrDict
    @param FilePath   文件路径
    @return           文件对应的StrDict
    */
    virtual StrDict &getFileDict(const std::string &FilePath);
    virtual ~CsvUtil();

private:
    CsvUtil();  //不允许在类外部使用构造函数进行实例化
    CsvUtil(const CsvUtil &) = delete; //不允许复制构造
    CsvUtil &operator=(const CsvUtil&) = delete; //不允许赋值


    static CsvUtil* _gInstance;
    CsvMap* _pCsvMap;
};

#endif //CSV_UTIL_H
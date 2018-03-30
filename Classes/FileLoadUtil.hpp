/** @Copyright   保卫萝卜
*   @author      陈建彰
*   @date        2018/2/28
*   @brief       文件加载辅助工具头文件
*/

#pragma once
#ifndef FILE_LOAD_UTIL_HPP
#define FILE_LOAD_UTIL_HPP

#include "cocos2d.h"
#include "StringUtil.h"

/** @brief 文件加载辅助工具头文件，用于加载csv文件，然后将其按行分割，读取里面每一行的数据并返回每一行对应的字符串。
*   @author 陈建彰
*/

class FileLoadUtil
{
public:
    /**
    @brief   该函数用于读取一个文件，并分别将该文件每一行的数据以std::vector<std::string>的形式保存并返回。
    @param   FilePath 文件路径
    @return  分割后的字符串向量(StrVec, 即std::vector<std::string>)
    *
    */
    StrVec getDataLines(const std::string& FilePath)
    {
        StrVec res;

        //如果找不到该文件，直接返回
        if (!cocos2d::FileUtils::getInstance()->isFileExist(FilePath))
            return res;

        ssize_t pSize = 0; //pSize用于传参
        unsigned char* chDatas = cocos2d::FileUtils::getInstance()->getFileData(FilePath, "r", &pSize); //调用cocos2d的API，返回该文件的字符串序列

        if (chDatas) //如果chDatas不为空，意味着文件有干货
            res = StringUtil().split((char*)chDatas, "\n"); //进行切割
        return res; //返回最终得到的字符串集

    }
};
#endif // !FILE_LOAD_UTIL_HPP


/** 
*   @Copyright   保卫萝卜
*   @author      陈建彰
*   @date        2018/2/28 
*   @brief       字符串处理工具头文件
*   @details     实现居然在.h里写了，就这样吧
*/

#pragma once
#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include<vector>

#ifndef StrVec
#define StrVec std::vector<std::string> //宏定义StrVec，string向量
#endif // !1StrVec

class StringUtil
{
public:
    /**
    @brief   该函数用于分割字符串，给定分隔符
    @param   第一个参数target是需要切割的字符串, 第二个参数rSSeq是分隔符
    @return  分割后的字符串向量(StrVec, 即std::vector<std::string>)
    *
    */
    StrVec split(const std::string& target, const std::string& rSSeq)
    {
        StrVec stringList;
        int size = target.size();
        std::string str_temp(target);
        int startIndex = 0, endIndex = 0;
        endIndex = str_temp.find(rSSeq);
        std::string splitStr = "";
        while (endIndex > 0)
        {
            splitStr = str_temp.substr(startIndex, endIndex);
            stringList.push_back(splitStr);
            str_temp = std::string(str_temp.substr(endIndex + 1, size));
            endIndex = str_temp.find(rSSeq);
        }
        if (str_temp != "")
            stringList.push_back(str_temp);

        return stringList;
    }
};

#endif // !STRINGUTIL_H

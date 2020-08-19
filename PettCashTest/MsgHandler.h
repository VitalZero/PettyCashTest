#pragma once
#include <unordered_map>
#include <functional>
#include "includes.h"

using MsgFunction = std::function<LRESULT(UINT, WPARAM, LPARAM)>;
using MessageMap = std::unordered_map<UINT, MsgFunction>;

class MsgHandler
{
public:
  template <class F, class T>
  void Register(UINT msg, F func, T* type)
  {
    if(map.find(msg) == map.end())
    {
      map[msg] = std::bind(func, type, std::placeholders::_1,
        std::placeholders::_2, std::placeholders::_3);
    }
  }
  LRESULT Handle(UINT msg, WPARAM wparam, LPARAM lparam)
  {
    auto itr = map.find(msg);
    if(itr != map.end())
    {
      return itr->second(msg, wparam, lparam);
    }
   
    return map.at(0)(msg, wparam, lparam);
  }
private:
  MessageMap map;
};
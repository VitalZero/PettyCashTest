#pragma once
#include <unordered_map>
#include <functional>
#include "includes.h"

using MsgFunction = std::function<LRESULT(UINT, WPARAM, LPARAM)>;
using MessageMap = std::unordered_map<UINT, MsgFunction>;
using CmdFunction = std::function<void(void)>;
using CommandMap = std::unordered_map<UINT, CmdFunction>;

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
  template <class F, class T>
  void Bind(UINT msg, F func, T* type)
  {
    if (cmdMap.find(msg) == cmdMap.end())
    {
      cmdMap[msg] = std::bind(func, type);
      //cmdMap.insert(std::bind(func, type));
    }
  }
  LRESULT Dispatch(UINT msg, WPARAM wparam, LPARAM lparam)
  {
    auto itr = map.find(msg);
    if(itr != map.end())
    {
      return itr->second(msg, wparam, lparam);
    }
   
    return map.at(0)(msg, wparam, lparam);
  }
  void Dispatch(UINT idCtrl)
  {
    auto itr = cmdMap.find(idCtrl);

    if (itr != cmdMap.end())
    {
      std::wstring info = L"cmdMap first: " + std::to_wstring(itr->first) + L"\n";
      OutputDebugString(info.c_str());

      itr->second();
    }
  }
private:
  MessageMap map;
  CommandMap cmdMap;
};
#include "JsonControl.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include <iostream>


JsonControl::JsonControl()
{

}

void JsonControl::DecodeJsonObject(const char*jsonData)
{
  rapidjson::Document doc;
  doc.Parse(jsonData);

  //parse action

  if()
  {

  }
  else if()
  {

  }

  std::cout << doc["action"].GetString() << std::endl;
  //s.SetInt(s.GetInt());

}

JsonControl::~JsonControl()
{

}

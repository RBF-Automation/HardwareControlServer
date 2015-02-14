#include "JsonControl.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"
#include <iostream>
#include "Actions.h"

JsonControl::JsonControl()
{

}

void JsonControl::DecodeJsonObject(const char*jsonData)
{
  rapidjson::Document doc;
  doc.Parse(jsonData);
  std::cout << doc["nodeid"].GetUint64() << std::endl;

  //s.SetInt(s.GetInt());

}

JsonControl::~JsonControl()
{

}

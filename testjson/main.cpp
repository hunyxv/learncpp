#include <iostream>
#include <string>

#include "json/json.h"

using namespace std;

string strjson = R"delimiter(
{
    "name": "James",
    "nickname": "good boy"
}
)delimiter";

void unmarshal();
void marshal();

int main() {
    cout << "UnmarshalJSON: " << endl;
    unmarshal();
    cout << "MarshalJson: " << endl;
    marshal();
    return 0;
}

void unmarshal() {
    Json::Value dict;
    Json::Reader jreader;
    if (!jreader.parse(strjson, dict)) {
        cout << "json unmarshal fail" << endl;
        return;
    }

    cout << dict.toStyledString() << endl;
    /*
    {
        "name" : "James",
        "nickname" : "good boy"
    }
    */
    for (auto i : dict) {
        cout << "asString: " << i.asString() << endl;
    }

    Json::Value::Members members = dict.getMemberNames();
    for (auto m : members) {
        string key = m.c_str();
        cout << key << ": " << dict[key] << endl;
    }
}

void marshal() {
    Json::Value dict;
    dict["message"] = "OK";
    dict["code"] = 200;
    Json::Value data;
    data["list"].append("Bob");
    data["list"].append("Cary");
    dict["data"] = data;

    // Json::StyledWriter jwriter; // 格式化输出
    Json::FastWriter jwriter;  // 单行输出
    string strjson = jwriter.write(dict);
    cout << strjson << endl;
}
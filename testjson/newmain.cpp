#include <iostream>
#include <sstream>

#include "json/json.h"

using namespace std;

string strjson = R"(
{
    "name": "James",
    "nickname": "good boy"
}
)";

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
    Json::CharReaderBuilder readBuilder;
    unique_ptr<Json::CharReader> jreader(readBuilder.newCharReader());
    if (!jreader) {
        std::cerr << "jsonRead is null" << std::endl;
        return;
    }
    Json::Value dict;
    Json::String parse_err;
    bool succ = jreader->parse(
        strjson.c_str(), strjson.c_str() + strjson.length(), &dict, &parse_err);
    if (!succ || !parse_err.empty()) {
        cout << "parseJsonFromString error!" << parse_err << std::endl;
        return;
    }

    cout << dict.toStyledString() << endl;

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

    Json::StreamWriterBuilder writerBuilder;  // 新式API
    writerBuilder.settings_["indentation"] = ""; // 默认是格式化输出的，这里把缩进设置为空
    unique_ptr<Json::StreamWriter> jwriter(writerBuilder.newStreamWriter());
    ostringstream os;
    jwriter->write(dict, &os);
    string strjson = os.str();

    cout << strjson << endl;
}
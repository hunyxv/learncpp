#include <iostream>
#include <string>

#include "mysqlx/xdevapi.h"

int main() {
    using namespace std;
    cout << "myssql-client version: " << MYSQL_CONCPP_VERSION << endl;

    string username = "root";
    string password = "123456";
    mysqlx::SessionSettings settings(mysqlx::SessionOption::HOST, "localhost",
                                     mysqlx::SessionOption::PORT, 33060);
    settings.set(mysqlx::SessionOption::USER, "root");
    settings.set(mysqlx::SessionOption::PWD, "123456");

    mysqlx::Session session(settings);
    mysqlx::Schema library = session.getSchema("library");

    mysqlx::internal::Schema_detail::TableList tables = library.getTables();

    for (auto table : tables) {
        cout << table.getName() << " ";
    }
    cout << endl;

    session.close();
    return 0;
}
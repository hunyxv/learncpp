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

    session.sql("use library;").execute();

    mysqlx::SqlResult ret = session.sql(R"(
        insert into books(title,author,price,quantity)
        values("C++ 并发编程实战","Anthony Williams",89,1);
    )").execute();
    session.commit();

    cout << "insert return data? " << boolalpha << ret.hasData() << endl;

    mysqlx::SqlResult result = session.sql("select * from books;").execute();
    for (auto item : result) {
        cout << "id: " << item[0] << " title: " << item[1]
             << " author: " << item[2] << " price: " << item[3]
             << " quantity: " << item[4] << endl;
    }

    session.sql(R"(delete from books where title = "C++ 并发编程实战";)").execute();
    session.close();
    return 0;
}
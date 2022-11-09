#include <iostream>

#include "mysqlx/xdevapi.h"

class CliGuard : public mysqlx::Client {
   public:
    CliGuard(mysqlx::ClientSettings settings) : Client(settings) {}
    CliGuard(mysqlx::ClientSettings& settings) : Client(settings) {}
    template <typename... T>
    CliGuard(T... options) : Client(mysqlx::ClientSettings(options...)) {}
    ~CliGuard() { 
        std::cout << "cli pool closing ...";
        close(); 
    }
    CliGuard(const CliGuard&) = delete;
    CliGuard& operator=(const CliGuard&) = delete;
};

int main() {
    using namespace std;
    // 使用 url 直接指定 database
    CliGuard cli("root:123456@localhost/library", mysqlx::ClientOption::POOL_MAX_SIZE, 7);
    mysqlx::Session session = cli.getSession();

    mysqlx::SqlResult ret = session.sql(R"(
        insert into books(title,author,price,quantity)
        values("C++ 并发编程实战","Anthony Williams",89,1);
    )").execute();
    session.commit();

    cout << "insert return data? " << boolalpha << ret.hasData() << endl;

    mysqlx::SqlResult result = session.sql("select * from books;").execute();
    cout << "select return data? " << boolalpha << result.hasData() << endl;
    for (auto item : result) {
        cout << "id: " << item[0] << " title: " << item[1]
             << " author: " << item[2] << " price: " << item[3]
             << " quantity: " << item[4] << endl;
    }

    session.sql(R"(delete from books where title = "C++ 并发编程实战";)")
        .execute();

    return 0;
}
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
    CliGuard cli("root:123456@localhost/library",
                 mysqlx::ClientOption::POOL_MAX_SIZE, 7);
    mysqlx::Session session = cli.getSession();
    // 获取 table 对象
    mysqlx::Table books = session.getDefaultSchema().getTable("books");

    // insert
    mysqlx::Result inret =
        books.insert("title", "author", "price", "quantity")
            .values("C++ 并发编程实战", "Anthony Williams", 89, 1)
            .execute();
    if (inret.getAffectedItemsCount() != 1) {
        cout << "insert fail\n";
    }

    string itemid = to_string(inret.getAutoIncrementValue());

    cout << "new row id = " << itemid << endl;

    // update
    mysqlx::Result upret =
        books.update().set("price", 100).where("id = " + itemid).execute();
    if (upret.getAffectedItemsCount() != 1) {
        cout << "update fail\n";
    }

    // select
    // books.select().where("title = 'C++ 并发编程实战'") 根据条件查询
    mysqlx::RowResult mrows = books.select("*").execute();  // 查询所有
    for (mysqlx::Row row : mrows.fetchAll()) {
        cout << "id: " << row[0] << " title: " << row[1]
             << " author: " << row[2] << " price: " << row[3]
             << " quantity: " << row[4] << endl;
    }

    // delete
    mysqlx::Result delret = books.remove().where("id = " + itemid).execute();
    if (delret.getAffectedItemsCount() != 1) {
        cout << "update fail\n";
    }

    cout << "\n-------------------------------\n";
    // select
    // books.select().where("title = 'C++ 并发编程实战'") 根据条件查询
    mrows = books.select("*").execute();  // 查询所有
    for (mysqlx::Row row : mrows.fetchAll()) {
        cout << "id: " << row[0] << " title: " << row[1]
             << " author: " << row[2] << " price: " << row[3]
             << " quantity: " << row[4] << endl;
    }

    return 0;
}

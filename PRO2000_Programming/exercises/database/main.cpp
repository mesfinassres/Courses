#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <mysql.h>

using namespace std;
/*
CREATE DATABASE studentdb;
USE studentdb;
CREATE TABLE students (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL
);

/*
CREATE USER 'studentapp'@'localhost'
IDENTIFIED WITH mysql_native_password
BY 'studentpass';

GRANT ALL PRIVILEGES ON studentdb.* 
TO 'studentapp'@'localhost';

FLUSH PRIVILEGES

*/
int main() {

    // --------------------------------
    // 1. Open input file
    // --------------------------------

    ifstream file("students.txt");

    if (!file.is_open()) {
        cerr << "Error: Could not open students.txt" << endl;
        return 1;
    }

    // --------------------------------
    // 2. Connect to MySQL
    // --------------------------------

    MYSQL* connection = mysql_init(nullptr);

    if (connection == nullptr) {
        cerr << "Error: MySQL initialization failed." << endl;
        return 1;
    }

    // Disable SSL for local development
    mysql_ssl_mode sslMode = SSL_MODE_DISABLED;

    if (mysql_options(
            connection,
            MYSQL_OPT_SSL_MODE,
            &sslMode
        ) != 0) {
        cerr << "Failed to configure MySQL SSL mode: "
            << mysql_error(connection)
            << endl;

        mysql_close(connection);
        return 1;
    }


    if (!mysql_real_connect(
            connection,
            "localhost",       // MySQL server
            "student",            // username
            "student",   // password
            "studentdb",       // database
            3306,              // port
            nullptr,
            0)) {

        cerr << "MySQL connection failed: "
             << mysql_error(connection)
             << endl;

        mysql_close(connection);
        return 1;
    }

    cout << "Connected to MySQL successfully." << endl;

    // --------------------------------
    // 3. Prepare SQL statement
    // --------------------------------

    string sql =
        "INSERT INTO students (name, grade) VALUES (?, ?)";

    MYSQL_STMT* statement =
        mysql_stmt_init(connection);

    if (statement == nullptr) {
        cerr << "Could not create MySQL statement." << endl;

        mysql_close(connection);
        return 1;
    }

    if (mysql_stmt_prepare(
            statement,
            sql.c_str(),
            sql.length()) != 0) {

        cerr << "Statement preparation failed: "
             << mysql_stmt_error(statement)
             << endl;

        mysql_stmt_close(statement);
        mysql_close(connection);
        return 1;
    }

    // --------------------------------
    // 4. Read file line by line
    // --------------------------------

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string name;
        string gradeText;

        // Read name
        getline(ss, name, ',');

        // Read grade
        getline(ss, gradeText);

        double grade;

        try {
            grade = stod(gradeText);
        }
        catch (...) {
            cerr << "Invalid grade: "
                 << gradeText
                 << endl;
            continue;
        }

        // --------------------------------
        // 5. Bind data to SQL statement
        // --------------------------------

        MYSQL_BIND bind[2];

        memset(bind, 0, sizeof(bind));

        // Student name
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (void*)name.c_str();
        bind[0].buffer_length = name.length();

        // Student grade
        bind[1].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[1].buffer = &grade;

        if (mysql_stmt_bind_param(
                statement,
                bind) != 0) {

            cerr << "Binding failed: "
                 << mysql_stmt_error(statement)
                 << endl;

            continue;
        }

        // --------------------------------
        // 6. Execute INSERT
        // --------------------------------

        if (mysql_stmt_execute(statement) != 0) {

            cerr << "Insert failed for "
                 << name
                 << ": "
                 << mysql_stmt_error(statement)
                 << endl;

        } else {

            cout << "Inserted: "
                 << name
                 << " - "
                 << grade
                 << endl;
        }
    }

    // --------------------------------
    // 7. Clean up
    // --------------------------------

    mysql_stmt_close(statement);

    mysql_close(connection);

    file.close();

    cout << "\nImport completed." << endl;

    return 0;
}
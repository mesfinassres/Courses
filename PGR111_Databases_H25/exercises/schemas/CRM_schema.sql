-- Create a CRM database that contains customers, orders, and items entities
-- Populate the database with small data
-- Retrieve

START TRANSACTION;
DROP SCHEMA IF EXISTS crm;
CREATE SCHEMA crm;
USE crm;

CREATE TABLE customers (
    customer_id int PRIMARY KEY,
    Name varchar(100)
);
CREATE TABLE orders (
   order_id int PRIMARY KEY,
   customer_id int,
   order_date date,
   FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);
CREATE TABLE items (
    item_id int PRIMARY KEY,
    order_id int,
    product_name varchar(70),
    quantity int,
    FOREIGN KEY (order_id) REFERENCES orders(order_id)
);
INSERT INTO customers values
(1, 'Alice'), (2, 'Bob');
INSERT INTO orders VALUES
(101, 1, '2025-09-01'), (102, 2, '2025-09-02');
INSERT INTO items VALUES
(1001, 101, 'Laptop', 1), (1002, 101, 'Mouse', 2), (1003, 102, 'Keyboard', 1);
COMMIT;
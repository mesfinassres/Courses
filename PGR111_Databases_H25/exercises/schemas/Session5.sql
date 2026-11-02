/* 
 * Demo 1- Exercise 4, Task #5: 
 * Retrieve all the countries in the world (names, as CountryName) where the population of the
 * country is less than 1000 people. We also want to retrieve the population of the country (AS
 * CountryPop) and which continent the country belongs to. In addition, show names of cities
 * (as CityName) in each country if any, and the population of these cities (as CityPop). We want
 * the result sorted alphabetically by CountryName. (Hint: My answer returns 10 rows - is that
 * the same number of rows that you get?)
*/

SELECT country.Name AS CountryName, country.Population AS CountryPop, country.Continent, city.Name AS CityName, city.Population AS CityPop
FROM country
LEFT JOIN city ON
Code = CountryCode
WHERE country.Population < 1000
ORDER BY country.Name ASC;


/*
 * Demo 2- Join with more than two tables:
 * Write an SQL query that shows each customer’s name, their order ID, order date, and 
 * the product names with quantities for all items in each order.
 */

SELECT 
    c.name AS customer_name,
    o.order_id,
    o.order_date,
    i.product_name,
    i.quantity
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
JOIN items i ON o.order_id = i.order_id;


/*
 * Demo 3- Sessions 4/5- data manipulation, and subquery
 * Insert two TVs with item_id 1004 for Bob (having unique order_id) into the 'items' table of the CRM database while keeping the same order_date. 
 * (Note: you don’t have to directly enter order_date directly- since that lives in the orders table).
 */

INSERT INTO items (item_id, order_id, product_name, quantity)
SELECT 1004, o.order_id, 'TV', 2
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
WHERE c.name = 'Bob';


/*
 * Demo 4- Creating and using views
 * Create a view called customer_order_details that combines customers, their orders, and the order items (customer name, order_id, order_date, product_name, quantity).
 * Using the view, retrieve all products ordered by 'Alice', showing the order ID, product name, and quantity.
*/

-- Step 1: create the view
CREATE VIEW customer_order_details AS
SELECT 
    c.name AS customer_name,
    o.order_id,
    o.order_date,
    i.product_name,
    i.quantity
FROM customers c
JOIN orders o ON c.customer_id = o.customer_id
JOIN items i ON o.order_id = i.order_id;

-- Step 2: write select query
SELECT order_id, product_name, quantity
FROM customer_order_details
WHERE customer_name = 'Alice';
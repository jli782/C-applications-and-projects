-- ***********************
-- Student1 Name: Jeffrey Li Student1 ID: 160203196
-- Student2 Name: Your Name Student2 ID: #########
-- Student3 Name: Your Name Student3 ID: #########
-- Date: November 25, 2020
-- Purpose: Assignment 2 - DBS311
-- ***********************
SET SERVEROUTPUT ON;
--generate copies of the tables
CREATE TABLE new_orders AS 
SELECT * 
FROM   orders;
  
CREATE TABLE new_order_items AS 
SELECT * 
FROM   order_items;

--select * --count(*)
--from new_order_items;

--select * --count(*)
--from new_orders;
/
--1. 
create or replace procedure find_customer (customer_id IN NUMBER, found OUT NUMBER) as
    c_name VARCHAR2(255); 
begin
    select customers.name 
    into c_name 
    from customers
    where find_customer.customer_id = customer_id;
    if c_name is not null then
        found := 1;
    end if;
EXCEPTION
WHEN no_data_found THEN
 found := 0;
END;
/
declare 
    cust_id NUMBER := 319;  --customer_id ranges from 1 - 319
    val NUMBER := -1;
begin
    find_customer(cust_id, val);
    DBMS_OUTPUT.PUT_LINE ('val returned from find_customer: ' || val);
end;
--select * from customers order by customer_id;
/
--2.
create or replace procedure find_product (product_id IN NUMBER, price OUT products.list_price%TYPE) as
begin
    select list_price 
    into price
    from products
    where find_product.product_id = products.product_id;
EXCEPTION
WHEN no_data_found THEN
 price := 0;
end;
/
declare 
    p_id NUMBER := -1;   --product_id ranges from 1 - 288
    price products.list_price%TYPE;
begin
    find_product (p_id, price);
    dbms_output.put_line('Product ' || p_id || ' has a list_price of ' || price);
end;
--select * from products order by product_id;
/
--3.
create or replace procedure add_order (customer_id IN NUMBER, new_order_id OUT NUMBER) as
    sales_person_id new_orders.salesman_id%TYPE := 56;
    sales_status new_orders.status%TYPE := 'Shipped';
begin
    select max(order_id)
    into new_order_id
    from new_orders;
    new_order_id := new_order_id + 1;
--ORDER_ID
--CUSTOMER_ID
--STATUS
--SALESMAN_ID
--ORDER_DATE
    insert into new_orders values(new_order_id, add_order.customer_id, sales_status, sales_person_id, sysdate);
EXCEPTION
WHEN no_data_found THEN
    dbms_output.put_line('Customer with ' || customer_id || ' not found');
WHEN OTHERS THEN
    dbms_output.put_line('Failed to ship ' || 'customer_id');
end;
/
declare 
    cust_id NUMBER := 1;
    o_id NUMBER := -1;
begin
    add_order (cust_id, o_id);
    dbms_output.put_line('The new order id : ' || o_id);
end;
--select max(order_id) from new_orders;
/
--4.
create or replace procedure 
add_order_item (orderId IN order_items.order_id%type,
 itemId IN order_items.item_id%type,
 productId IN order_items.product_id%type,
 quantity IN order_items.quantity%type,
 price IN order_items.unit_price%type)
as
begin
--ORDER_ID
--ITEM_ID
--PRODUCT_ID
--QUANTITY
--UNIT_PRICE    
    insert into new_order_items values(orderId, itemId, productId, quantity, price);
EXCEPTION
WHEN OTHERS THEN
    dbms_output.put_line('Failed to stored order ' || orderId);
end;
/
declare
    o_id new_order_items.order_id%type := 106;
    i_id new_order_items.item_id%type := 1;
    p_id new_order_items.product_id%type := 1;
    qty new_order_items.quantity%type := 20;
    i_price new_order_items.unit_price%type := 65.05;
begin
    add_order_item (o_id, i_id, p_id, qty, i_price);
end;
--select * from new_order_items;

/
drop table new_orders;
/
drop table new_order_items;
# Write your MySQL query statement below
select Product.product_name , Sales.year, Sales.price 
from Product INNER JOIN Sales
on Sales.product_id  =Product.product_id ;
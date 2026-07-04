# Write your MySQL query statement below
SELECT c.customer_id
FROM Customer as c
GROUP BY c.customer_id
HAVING COUNT(DISTINCT(c.product_key)) = 
    (
    SELECT COUNT(p.product_key)
    FROM product as p
    );
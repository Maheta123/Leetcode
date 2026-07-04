/* Write your T-SQL query statement below */
WITH CTE1 AS
(
    SELECT
        visited_on,
        SUM(amount) AS amount
    FROM  Customer
    GROUP BY visited_on
)
, CTE2 AS
(
    SELECT
        ROW_NUMBER()OVER(ORDER BY visited_on) AS id,
        visited_on,
        SUM(amount)OVER(ORDER BY visited_on ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS amount_sum,
        AVG(amount*1.0)OVER(ORDER BY visited_on ROWS BETWEEN 6 PRECEDING AND CURRENT ROW) AS average_amount
    FROM CTE1
)

SELECT
        visited_on,
        amount_sum AS amount,
        ROUND(average_amount,2) AS average_amount
FROM CTE2
WHERE id >= 7
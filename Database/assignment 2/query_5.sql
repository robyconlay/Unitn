SELECT beer
FROM "Sells"
WHERE ROUND(price::numeric, 2) = (
  SELECT MAX(ROUND(price::numeric, 2))
  FROM "Sells"
);

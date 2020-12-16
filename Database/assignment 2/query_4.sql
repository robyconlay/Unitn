SELECT B.name
FROM "Beers" B
WHERE B.manf IN (
  SELECT manf
  FROM (
    SELECT manf, COUNT(name)
    FROM "Beers"
    GROUP BY manf
    HAVING COUNT(name) = 1
  ) AS R
);

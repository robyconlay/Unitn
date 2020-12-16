SELECT DISTINCT F.drinker
FROM "Frequents" F
WHERE F.drinker NOT IN (
  SELECT F.drinker                
  FROM "Frequents" F
  WHERE F.bar NOT IN (
    SELECT S.bar
    FROM "Sells" S
        JOIN "Likes" L ON S.beer = L.beer
    WHERE F.drinker = L.drinker
  )
);

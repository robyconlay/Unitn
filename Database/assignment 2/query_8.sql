SELECT DISTINCT S.bar
FROM "Sells" S
      JOIN "Likes" L ON (S.beer = L.beer)
WHERE L.drinker = 'Joe';

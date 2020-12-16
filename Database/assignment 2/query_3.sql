SELECT B.name, B.manf
FROM "Beers" B
    JOIN "Likes" L ON (L.beer = B.name)
WHERE L.drinker = 'Fred';

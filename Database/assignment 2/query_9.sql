SELECT DISTINCT L.drinker
FROM "Likes" L
    JOIN "Sells" S ON (L.beer = S.beer)
    JOIN "Frequents" F ON ((F.bar = S.bar)
                  AND (F.drinker = L.drinker));

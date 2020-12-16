SELECT S1.bar
FROM "Sells" S1, "Sells" S2
WHERE S1.bar = S2.bar AND
      ROUND(S1.price::numeric, 2) = ROUND(S2.price::numeric, 2)  AND
      S1.beer = 'Bud' AND
      S2.beer = 'Miller';

SELECT avg(r.rating) as Average FROM ratings r
INNER JOIN movies m  ON m.id = r.movie_id 
WHERE year = 2012
SELECT m.title, r.rating FROM movies m
INNER JOIN ratings r  ON m.id = r.movie_id 
WHERE year = 2010 and r.rating IS NOT NULL
ORDER BY rating DESC, title ASC
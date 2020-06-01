SELECT DISTINCT (m.title) FROM movies m
INNER JOIN people p ON p.id = s.person_id
INNER JOIN stars s ON s.movie_id = m.id
WHERE p.name =   'Johnny Depp'
INTERSECT
SELECT DISTINCT (m.title) FROM movies m
INNER JOIN people p ON p.id = s.person_id
INNER JOIN stars s ON s.movie_id = m.id
WHERE p.name =   'Helena Bonham Carter'
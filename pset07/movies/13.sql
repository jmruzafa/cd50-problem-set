SELECT DISTINCT (p.name) FROM people p
INNER JOIN stars s ON p.id = s.person_id
INNER JOIN movies m ON s.movie_id = m.id
WHERE p.name <> 'Kevin Bacon'  and m.id  in ( 
	SELECT m.id from movies m
	INNER JOIN stars s ON m.id = s.movie_id
	INNER JOIN people p ON s.person_id = p.id
	WHERE p.name = 'Kevin Bacon' and p.birth = 1958
)
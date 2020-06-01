SELECT  DISTINCT (p.name) FROM stars s
INNER JOIN people p on p.id = s.person_id
INNER JOIN movies m  ON m.id = s.movie_id
WHERE m.year = 2004 
ORDER by p.birth
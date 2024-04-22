SELECT  p.name FROM people p
INNER JOIN stars s on p.id = s.person_id
INNER JOIN movies m  ON m.id = s.movie_id
    WHERE m.title = "Toy Story"
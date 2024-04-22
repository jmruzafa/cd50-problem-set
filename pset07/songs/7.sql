SELECT AVG(s.energy) FROM songs s
JOIN artists a on a.id = s.artist_id
WHERE a.name = 'Drake';

SELECT name FROM people
JOIN stars on people.id = person_id
JOIN ratings on stars.movie_id = 
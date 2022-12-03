SELECT title FROM movies
WHERE id IN (
            SELECT stars.movie_id FROM stars WHERE stars.person_id IN (
                                                                     SELECT name FROM people WHERE id = 'Johnny Depp'
                                                                     )
            )
;
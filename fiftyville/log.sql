-- Identify thief
SELECT name
FROM people
WHERE passport_number IN
    (SELECT passport_number
     FROM passengers
     WHERE flight_id IN
         (SELECT id
          FROM flights
          WHERE destination_airport_id IN
              (SELECT destination_airport_id
               FROM flights
               JOIN airports ON flights.origin_airport_id = airports.id
               WHERE YEAR = "2021"
                 AND MONTH = "07"
                 AND DAY = "29"
               ORDER BY HOUR,
                        MINUTE
               LIMIT 1) ) )
  AND id IN
    (SELECT person_id
     FROM bank_accounts
     WHERE account_number IN
         (SELECT account_number
          FROM atm_transactions
          WHERE YEAR = "2021"
            AND MONTH = "07"
            AND DAY = "28"
            AND transaction_type = "withdraw"
            AND atm_location = "Leggett Street" ) )
  AND phone_number IN
    (SELECT caller
     FROM phone_calls
     WHERE YEAR = "2021"
       AND MONTH = "07"
       AND DAY = "28"
       AND duration < 60 )
  AND license_plate IN
    (SELECT license_plate
     FROM bakery_security_logs
     WHERE YEAR = "2021"
       AND MONTH = "07"
       AND DAY = "28"
       AND HOUR = "10"
       AND MINUTE BETWEEN 16 AND 27 );

-- Identify destination
SELECT city FROM airports
JOIN airports.id ON flights.destination_airport_id
WHERE 

-- Identify accomplice
SELECT name
FROM people
WHERE phone_number =
    (SELECT receiver
     FROM phone_calls
     WHERE year = "2021"
     AND month = "07"
     AND day = "28"
     AND duration < 60
     AND caller =
         (SELECT phone_number
          FROM people
          WHERE passport_number IN
              (SELECT passport_number
               FROM passengers
               WHERE flight_id IN
                   (SELECT id
                    FROM flights
                    WHERE destination_airport_id IN
                        (SELECT destination_airport_id
                         FROM flights
                         JOIN airports ON flights.origin_airport_id = airports.id
                         WHERE YEAR = "2021"
                           AND MONTH = "07"
                           AND DAY = "29"
                         ORDER BY HOUR,
                                  MINUTE
                         LIMIT 1) ) )
            AND id IN
              (SELECT person_id
               FROM bank_accounts
               WHERE account_number IN
                   (SELECT account_number
                    FROM atm_transactions
                    WHERE YEAR = "2021"
                      AND MONTH = "07"
                      AND DAY = "28"
                      AND transaction_type = "withdraw"
                      AND atm_location = "Leggett Street" ) )
            AND phone_number IN
              (SELECT caller
               FROM phone_calls
               WHERE YEAR = "2021"
                 AND MONTH = "07"
                 AND DAY = "28"
                 AND duration < 60 )
            AND license_plate IN
              (SELECT license_plate
               FROM bakery_security_logs
               WHERE YEAR = "2021"
                 AND MONTH = "07"
                 AND DAY = "28"
                 AND HOUR = "10"
                 AND MINUTE BETWEEN 16 AND 27 ) ) );
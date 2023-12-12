-- Search for a crime scene report that matches the date and the location of the crime
SELECT description
FROM "crime_scene_reports"
WHERE month = 7 and day = 28 and year = 2021 and street = "Humphrey Street";

-- Search in interviews tables all the reference to "bakery" that day
SELECT transcript
FROM interviews
WHERE day = 28 and month = 7 and year = 2021 and transcript like "%bakery%";

-- Look up for the footage within the range of time indicated (10:15 - 10:25)
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021 AND hour = 10 AND minute BETWEEN 15 AND 25 and activity = "exit";

-- Find the name of the people that have those licence plates
SELECT p.name from people p
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
WHERE bsl.day = 28 AND bsl.month = 7
AND bsl.year = 2021 AND bsl.hour = 10
AND bsl.minute BETWEEN 15 AND 25 AND bsl.activity = "exit";
                                                              |
-- Find All withdraws from the specific ATM referenced in the crime report
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7
AND day = 28 AND atm_location = 'Leggett Street';

-- Find people that are associated with the ATM account Number
SELECT p.name FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions at ON ba.account_number = at.account_number
WHERE year = 2021 AND month = 7
AND day = 28 AND atm_location = 'Leggett Street';
                                                                                             |
-- Check phone calls that had a duration less than a minute
SELECT caller FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28
AND duration <= 60;

-- Find the Names of the Callers
SELECT p.name FROM people p
JOIN phone_calls pc ON p.phone_number = pc.caller
WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28
AND pc.duration <= 60;

-- Finding the ariport ID (== 8)
SELECT * FROM airports
WHERE city = 'Fiftyville';

-- Finding flights that departure on the day after (29th)
SELECT * FROM flights
WHERE origin_airport_id = 8 AND flights.year = 2021 AND flights.month = 7 AND flights.day = 29
ORDER BY hour LIMIT 1;;

-- Find Passenger Names for the flight 
SELECT p.name FROM people p
JOIN passengers pg ON p.passport_number = pg.passport_number
JOIN flights f ON pg.flight_id = f.id
JOIN airports a ON f.origin_airport_id = a.id
WHERE a.city = 'Fiftyville'
AND f.year = 2021 AND f.month = 7 AND f.day = 29 AND f.hour = 8 AND f.minute = 20;

-- Find flight arrival airport (New York City)
SELECT a.city FROM airports a
JOIN flights f ON a.id = f.destination_airport_id
WHERE f.origin_airport_id = 8
AND f.year = 2021 AND f.month = 7 AND f.day = 29 AND f.hour = 8 AND f.minute = 20;

-- Find Bruce's phone noumber (== (367) 555-5533)
SELECT phone_number FROM people
WHERE name = 'Bruce';

-- Searching the phone of Bruce to find who was the accomplice (== Robin)
SELECT p.name FROM people p
JOIN phone_calls pc ON p.phone_number = pc.receiver
WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28
AND pc.duration <= 60 AND pc.caller = '(367) 555-5533';

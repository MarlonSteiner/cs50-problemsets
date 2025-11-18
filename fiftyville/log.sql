-- Keep a log of any SQL queries you execute as you solve the mystery
/*Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time
 each of their interview transcripts mentions the bakery.
 Littering took place at 16:36. No known witnesses. */
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

/*Earlier this morning, before I arrived at Emma's bakery,
I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
*/

SELECT transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND transaction_type LIKE '%withdraw%' AND atm_location LIKE '%Leggett Street%';

/*Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
I don't know the thief's name, but it was someone I recognized.*/
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- License_plate to people
SELECT people.license_plate, people.name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2023 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25;

-- atm_transactions to bank_accounts
SELECT DISTINCT people.name
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE people.name IN
    (SELECT people.name
    FROM people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25)
AND atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';


/* In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.
I saw Richard take a bite out of his pastry at the bakery before his pastry was stolen from him. */
-- flights
SELECT * FROM flights
WHERE year = 2023
AND month = 07
AND day = 29
ORDER BY hour ASC LIMIT 1;

-- airports / city
SELECT * FROM airports WHERE id =
(SELECT destination_airport_id  FROM flights WHERE year = 2023 AND month = 07 AND day = 29 ORDER BY hour ASC LIMIT 1);

-- passengers
SELECT * FROM passengers WHERE flight_id =
(SELECT id FROM flights
WHERE year = 2023
AND month = 07
AND day = 29
ORDER BY hour ASC LIMIT 1);

-- name from passengers through people
SELECT * FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights
WHERE year = 2023
AND month = 07
AND day = 29
ORDER BY hour ASC LIMIT 1));

-- the thief
SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE people.name IN
    (SELECT people.name
    FROM people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25)
AND atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND people.name IN
(SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights
WHERE year = 2023
AND month = 07
AND day = 29
ORDER BY hour ASC LIMIT 1)));

--phone_calls
SELECT * FROM phone_calls WHERE caller =
(SELECT people.phone_number FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE people.name IN
    (SELECT people.name
    FROM people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25)
AND atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND people.name IN
(SELECT name FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id =
(SELECT id FROM flights
WHERE year = 2023
AND month = 07
AND day = 29
ORDER BY hour ASC LIMIT 1)))
AND people.name = 'Bruce');


-- Accomplice Phone Number
SELECT * FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60
AND caller =
(SELECT phone_number FROM people WHERE name = 'Bruce');

--Phone Number to Name
SELECT name FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration < 60
AND caller =
(SELECT phone_number FROM people WHERE name = 'Bruce'));

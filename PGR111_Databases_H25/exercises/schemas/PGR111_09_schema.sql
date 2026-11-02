DROP SCHEMA IF EXISTS flightReservation;
CREATE SCHEMA flightReservation;
USE flightReservation;

CREATE TABLE flight
(
	flightNumber int NOT NULL,
	departureTime char(4) NOT NULL,
	fromCode char(3) NOT NULL,
	fromAirport varchar(50) NOT NULL,
	fromCity varchar(50) NOT NULL,
	arrivalTime char(4) NOT NULL,
	toCode char(3) NOT NULL,
	toAirport varchar (50) NOT NULL,
	toCity varchar (50) NOT NULL,
	CONSTRAINT flight_flightNumber_pk PRIMARY KEY (flightNumber)
);

CREATE TABLE reservation
(
	reservationNumber int NOT NULL AUTO_INCREMENT,
	flightNumber int NOT NULL,
	flightDate date NOT NULL,
	ticketCount smallint NOT NULL,
	capacity smallint NOT NULL,
	name varchar(50) NOT NULL,
	CONSTRAINT reservation_reservationNumber_pk PRIMARY KEY (reservationNumber),
	CONSTRAINT reservation_flightNumber_fk FOREIGN KEY (flightNumber) REFERENCES flight(flightNumber)
);

/*
Original tables:
-- Flight(flightNumber*, departureTime, fromCode, fromAirport, fromCity, arrivalTime, toCode, toAirport, toCity)
-- Reservation (reservationNumber*, flightNumber(FK), flightDate, ticketCount, capacity, name)

Determinants: 
-- table flight -- 
flightNumber → departureTime, fromCode, fromAirport, fromCity, arrivalTime, toCode, toAirport, toCity 
fromCode → fromAirport, fromCity 
toCode → toAirport, toCity 

-- table reservation -- 
reservationNumber → flightNumber, flightDate, ticketCount, capacity, name 
flightNumber, flightDate → capacity
*/ 
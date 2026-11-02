DROP SCHEMA IF EXISTS car_and_owner;
CREATE SCHEMA car_and_owner;
USE car_and_owner;

CREATE TABLE owner (
  Id int AUTO_INCREMENT,
  Name varchar(50) NOT NULL,
  PRIMARY KEY (Id)
);

CREATE TABLE car (
  RegNr char(7) NOT NULL UNIQUE,
  Model varchar(50) NOT NULL,
  Owner_Id INT NULL,
  PRIMARY KEY (RegNr),
  FOREIGN KEY (Owner_Id) REFERENCES owner(Id)
);

INSERT INTO owner (Name) VALUES 
('Per Persen'), 
('Ola Olsen'),
('Kari Nordmann');

INSERT INTO car VALUES 
('EL22222', 'Tesla Model S', 1), 
('KH33333', 'Ferrari Spider', 3),
('ZX22222', 'Volvo V70', NULL);

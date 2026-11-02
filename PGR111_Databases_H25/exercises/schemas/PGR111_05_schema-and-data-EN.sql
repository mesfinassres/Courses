DROP SCHEMA IF EXISTS school;
CREATE SCHEMA school;
USE school;

CREATE TABLE student
(
  snr     INT(4), 
  name    VARCHAR(12),
  address VARCHAR(12),
  dateofbirth   DATE,
  CONSTRAINT student_snr_pk PRIMARY KEY (snr)
);

CREATE TABLE course
(
  cnr         INT(4),
  cname       VARCHAR(10),
  studypoints FLOAT(3,1),
  CONSTRAINT course_cnr_pk PRIMARY KEY (cnr)
);

CREATE TABLE exam
(
  snr      INT(4),
  cnr      INT(4),
  date     DATE,
  grade FLOAT(2,1) NOT NULL,
  CONSTRAINT exam_snr_cnr_date_pk PRIMARY KEY (snr, cnr, date),
  CONSTRAINT exam_cnr_fk FOREIGN KEY (cnr) REFERENCES course(cnr),
  CONSTRAINT exam_snr_fk FOREIGN KEY (snr) REFERENCES student(snr)
);

INSERT INTO student VALUES
(1,'EVA',  'AVEIEN 1', STR_TO_DATE('01-01-1987', '%d-%m-%Y')),
(3,'OLA',  NULL,       STR_TO_DATE('10-02-1989', '%d-%m-%Y')),
(5,'KARI', 'BVEIEN 2', STR_TO_DATE('05-06-1982', '%d-%m-%Y')),
(7,'PER',  'AVEIEN 4', STR_TO_DATE('02-10-1986', '%d-%m-%Y')),
(9,'GURI', 'CVEIEN 5', STR_TO_DATE('15-11-1977', '%d-%m-%Y'));

INSERT INTO course VALUES
(1, 'PROG',  7.5),
(2, 'SYS',  15.0),
(3, 'DB',    7.5),
(4, 'MAT',   5.0);

INSERT INTO exam VALUES
(1, 1, STR_TO_DATE('20-05-2008', '%d-%m-%Y'), 4.0),
(3, 1, STR_TO_DATE('20-05-2008', '%d-%m-%Y'), 2.0),
(7, 1, STR_TO_DATE('20-05-2008', '%d-%m-%Y'), 1.5),
(9, 1, STR_TO_DATE('20-05-2008', '%d-%m-%Y'), 4.5),
(1, 2, STR_TO_DATE('10-12-2008', '%d-%m-%Y'), 3.0),
(5, 2, STR_TO_DATE('10-12-2008', '%d-%m-%Y'), 2.5),
(7, 2, STR_TO_DATE('10-12-2008', '%d-%m-%Y'), 4.0),
(3, 3, STR_TO_DATE('01-06-2009', '%d-%m-%Y'), 3.5),
(5, 3, STR_TO_DATE('01-06-2009', '%d-%m-%Y'), 5.0),
(7, 3, STR_TO_DATE('01-06-2009', '%d-%m-%Y'), 2.0),
(9, 3, STR_TO_DATE('01-06-2009', '%d-%m-%Y'), 3.0),
(1, 4, STR_TO_DATE('05-12-2009', '%d-%m-%Y'), 5.0),
(7, 4, STR_TO_DATE('05-12-2009', '%d-%m-%Y'), 1.5),
(9, 4, STR_TO_DATE('05-12-2009', '%d-%m-%Y'), 2.0),
(5, 1, STR_TO_DATE('01-12-2009', '%d-%m-%Y'), 2.5),
(9, 1, STR_TO_DATE('01-12-2009', '%d-%m-%Y'), 3.0),
(1, 3, STR_TO_DATE('25-08-2009', '%d-%m-%Y'), 3.5),
(3, 3, STR_TO_DATE('25-08-2009', '%d-%m-%Y'), 2.0),
(5, 3, STR_TO_DATE('25-08-2009', '%d-%m-%Y'), 4.5),
(1, 1, STR_TO_DATE('10-06-2010', '%d-%m-%Y'), 3.0),
(1, 1, STR_TO_DATE('12-12-2010', '%d-%m-%Y'), 1.5),
(1, 1, STR_TO_DATE('08-08-2010', '%d-%m-%Y'), 1.5),
(3, 2, STR_TO_DATE('10-12-2008', '%d-%m-%Y'), 2.5),
(3, 2, STR_TO_DATE('12-05-2010', '%d-%m-%Y'), 4.0);

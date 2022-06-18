CREATE DATABASE company;

USE company;

CREATE TABLE employees (
    ID bigint(20) unsigned NOT NULL auto_increment,
    NAME varchar(50),
    AGE int,
    POSITION varchar(50)
    PRIMARY KEY (ID)
);

INSERT INTO employees(NAME, AGE, POSITION) VALUES("Esneider", 35, "full-stack");
INSERT INTO employees(NAME, AGE, POSITION) VALUES("Naty", 27, "full-stack");

SELECT * FROM employees;

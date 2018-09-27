/*THIS WILL create Course table inside 09feb2018 databases with course_id as primary key*/
CREATE TABLE Department
(
    department_id VARCHAR(4) NOT NULL PRIMARY KEY,
    name VARCHAR(50) NOT NULL
);
INSERT INTO Department VALUES ('BSBE','Department of Biosciences and Bioengineering');
INSERT INTO Department VALUES ('CL','Department of Chemical Engineering');
INSERT INTO Department VALUES ('CH','Department of Chemistry');
INSERT INTO Department VALUES ('CE','Department of Civil Engineering');
INSERT INTO Department VALUES ('CSE','Department of Computer Science and Engineering');
INSERT INTO Department VALUES ('DD','Department of Design');
INSERT INTO Department VALUES ('EEE','Department of Electronics & Electrical Engineering');
INSERT INTO Department VALUES ('HSS','Department of Humanities and Social Sciences');
INSERT INTO Department VALUES ('PH','Department of Physics');
INSERT INTO Department VALUES ('MA','Department of Mathematics');
INSERT INTO Department VALUES ('ME','Department of Mechanical Engineering');
INSERT INTO Department VALUES ('CRT','Center for Rural Technology');

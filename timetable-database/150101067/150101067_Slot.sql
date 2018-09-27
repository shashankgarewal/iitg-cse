/*create Department table inside 09feb2018 databases with department_id as primary key*/
CREATE TABLE Slot(
	letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1','E1') NOT NULL,
	day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday') NOT NULL, 
	start_time VARCHAR(8) NOT NULL, 
	end_time VARCHAR(8) NOT NULL,
	PRIMARY KEY (letter,day)
	);
INSERT INTO Slot VALUES ('A','Monday','08:00:00','08:55:00');
INSERT INTO Slot VALUES ('B','Monday','09:00:00','09:55:00');
INSERT INTO Slot VALUES ('C','Monday','10:00:00','10:55:00');
INSERT INTO Slot VALUES ('D','Monday','11:00:00','11:55:00');
INSERT INTO Slot VALUES ('F','Monday','12:00:00','12:55:00');
INSERT INTO Slot VALUES ('G','Monday','13:00:00','13:55:00');
INSERT INTO Slot VALUES ('D1','Monday','14:00:00','14:55:00');
INSERT INTO Slot VALUES ('C1','Monday','15:00:00','15:55:00');
INSERT INTO Slot VALUES ('B1','Monday','16:00:00','16:55:00');
INSERT INTO Slot VALUES ('A1','Monday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('E','Tuesday','08:00:00','08:55:00');
INSERT INTO Slot VALUES ('A','Tuesday','09:00:00','09:55:00');
INSERT INTO Slot VALUES ('B','Tuesday','10:00:00','10:55:00');
INSERT INTO Slot VALUES ('C','Tuesday','11:00:00','11:55:00');
INSERT INTO Slot VALUES ('H','Tuesday','12:00:00','12:55:00');
INSERT INTO Slot VALUES ('J','Tuesday','13:00:00','13:55:00');
INSERT INTO Slot VALUES ('C1','Tuesday','14:00:00','14:55:00');
INSERT INTO Slot VALUES ('B1','Tuesday','15:00:00','15:55:00');
INSERT INTO Slot VALUES ('A1','Tuesday','16:00:00','16:55:00');
INSERT INTO Slot VALUES ('E1','Tuesday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('D','Wednesday','08:00:00','08:55:00');
INSERT INTO Slot VALUES ('E','Wednesday','09:00:00','09:55:00');
INSERT INTO Slot VALUES ('A','Wednesday','10:00:00','10:55:00');
INSERT INTO Slot VALUES ('B','Wednesday','11:00:00','11:55:00');
INSERT INTO Slot VALUES ('F','Wednesday','12:00:00','12:55:00');
INSERT INTO Slot VALUES ('G','Wednesday','13:00:00','13:55:00');
INSERT INTO Slot VALUES ('B1','Wednesday','14:00:00','14:55:00');
INSERT INTO Slot VALUES ('A1','Wednesday','15:00:00','15:55:00');
INSERT INTO Slot VALUES ('E1','Wednesday','16:00:00','16:55:00');
INSERT INTO Slot VALUES ('D1','Wednesday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('C','Thursday','08:00:00','08:55:00');
INSERT INTO Slot VALUES ('D','Thursday','09:00:00','09:55:00');
INSERT INTO Slot VALUES ('E','Thursday','10:00:00','10:55:00');
INSERT INTO Slot VALUES ('A','Thursday','11:00:00','11:55:00');
INSERT INTO Slot VALUES ('H','Thursday','12:00:00','12:55:00');
INSERT INTO Slot VALUES ('J','Thursday','13:00:00','13:55:00');
INSERT INTO Slot VALUES ('A1','Thursday','14:00:00','14:55:00');
INSERT INTO Slot VALUES ('E1','Thursday','15:00:00','15:55:00');
INSERT INTO Slot VALUES ('D1','Thursday','16:00:00','16:55:00');
INSERT INTO Slot VALUES ('C1','Thursday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('B','Friday','08:00:00','08:55:00');
INSERT INTO Slot VALUES ('C','Friday','09:00:00','09:55:00');
INSERT INTO Slot VALUES ('D','Friday','10:00:00','10:55:00');
INSERT INTO Slot VALUES ('E','Friday','11:00:00','11:55:00');
INSERT INTO Slot VALUES ('F','Friday','12:00:00','12:55:00');
INSERT INTO Slot VALUES ('G','Friday','13:00:00','13:55:00');
INSERT INTO Slot VALUES ('E1','Friday','14:00:00','14:55:00');
INSERT INTO Slot VALUES ('D1','Friday','15:00:00','15:55:00');
INSERT INTO Slot VALUES ('C1','Friday','16:00:00','16:55:00');
INSERT INTO Slot VALUES ('B1','Friday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('K','Monday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('K','Wednesday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('K','Friday','17:00:00','17:55:00');
INSERT INTO Slot VALUES ('I','Tuesday','12:00:00','13:25:00');
INSERT INTO Slot VALUES ('I','Thursday','12:00:00','13:25:00');
INSERT INTO Slot VALUES ('L','Tuesday','17:00:00','18:25:00');
INSERT INTO Slot VALUES ('L','Thursday','17:00:00','18:25:00');

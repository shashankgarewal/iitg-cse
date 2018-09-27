CREATE DATABASE 16feb2018;
/*THIS WILL CREATE 09feb2018 DATABASE*/
USE 16feb2018;
/*WE'RE INSIDE 09feb2018 DATABASE*/

/*first perform other sql for creating datatables*/
/*a*/
SELECT course_id
FROM ScheduledIn
WHERE room_number = '2001';

/*b*/
SELECT course_id
FROM ScheduledIn
WHERE letter = 'C';

/*c*/
SELECT division
FROM ScheduledIn
WHERE room_number = 'L2'
UNION
SELECT division
FROM ScheduledIn
WHERE room_number = 'L3';

/*d*/
SELECT course_id
FROM ScheduledIn
GROUP BY course_id
WHERE COUNT(room_number) > 1;

/*e*/
SELECT name
FROM Department
WHERE department_id IN (
	SELECT department_id
	FROM Department
	WHERE room_number = 'L1'
	UNION
	SELECT department_id
	FROM Department
	WHERE room_number = 'L2'
	UNION
	SELECT department_id
	FROM Department
	WHERE room_number = 'L3'
	UNION
	SELECT department_id
	FROM Department
	WHERE room_number = 'L4'
	);

/*f*/
SELECT name
FROM Department
WHERE department_id = (
	SELECT department_id
	FROM ScheduledIn
	WHERE room_number != 'L1'
	UNION
	SELECT department_id
	FROM Department
	WHERE room_number != 'L2'
	);

/*g*/
SELECT name
FROM Department
WHERE department_id = (
/**/
	SELECT department_id
	FROM ScheduledIn
	WHERE letter, day = ALL(
		SELECT letter, day
		FROM Slot
	)
);

/*h*/
SELECT COUNT(course_id), letter, day
FROM ScheduledIn
GROUP BY letter, day
ORDER BY COUNT(course_id);
/*by default it assend*/

/*i*/
SELECT COUNT(course_id), room_number
FROM ScheduledIn
GROUP BY room_number
ORDER BY  COUNT(course_id) DESC;

/*j*/
SELECT letter, day, MIN(COUNT(course_id))
FROM ScheduledIn
GROUP BY letter, day;

/*k*/
SELECT letter, day
FROM ScheduledIn
WHERE CHARINDEX('M', REVERSE(course_id)) = 1;

/*l*/
SELECT name, letter, day
FROM Department AS D
INNER JOIN ScheduledIn ON D.department_id = Sch.department_id(
	SELECT department_id, letter, day
	FROM ScheduledIn AS Sch
	GROUP BY department_id
	WHERE NOT letter, day = (
		SELECT letter, day
		FROM Slot
	)
); 
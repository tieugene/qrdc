CREATE TABLE IF NOT EXISTS p (
	id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	name		TEXT NOT NULL UNIQUE,
	programm	TEXT NOT NULL,
	port		INTEGER NOT NULL,
	term		BOOLEAN NOT NULL DEFAULT False,
	cmdline		TEXT NOT NULL,
	logo		BLOB NULL DEFAULT NULL
	);
CREATE TABLE IF NOT EXISTS v (
	id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	name		TEXT NOT NULL UNIQUE,
	val		TEXT NULL
	);
CREATE TABLE IF NOT EXISTS h (
	id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	name		TEXT NOT NULL UNIQUE,
	val		TEXT NOT NULL UNIQUE
	);
CREATE TABLE IF NOT EXISTS c (
	id		INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	name		TEXT NOT NULL,
	protoid		INTEGER NOT NULL,
	hostid		INTEGER NOT NULL,
	port		INTEGER NULL,
	varid		INTEGER NULL,
	cmdline		TEXT NULL,
	comments	TEXT NULL
	);
CREATE TRIGGER IF NOT EXISTS p_d
	BEFORE
	DELETE
	ON main.p
	FOR EACH ROW
	BEGIN
		DELETE FROM c WHERE protoid=old.id;
	END;
CREATE TRIGGER IF NOT EXISTS v_d
	BEFORE
	DELETE
	ON main.v
	FOR EACH ROW
	BEGIN
		UPDATE c SET varid = NULL WHERE varid=old.id;
	END;
CREATE TRIGGER IF NOT EXISTS h_d
	BEFORE
	DELETE
	ON main.h
	FOR EACH ROW
	BEGIN
		DELETE FROM c WHERE hostid=old.id;
	END;
CREATE VIEW IF NOT EXISTS view_c AS
	SELECT
		c.id		AS id,
		c.name		AS name,
		c.protoid	AS protoid,
		c.hostid	AS hostid,
		c.port		AS port,
		c.varid		AS varid,
		c.cmdline	AS cmdline,
		c.comments	AS comments,
		p.name		AS p_name,
		p.programm	AS p_programm,
		p.port		AS p_port,
		p.term		AS p_term,
		p.cmdline	AS p_cmdline,
		p.logo		AS p_logo,
		h.name		AS h_name,
		h.val		AS h_val,
		v.name		AS v_name,
		v.val		AS v_val
	FROM c
		JOIN p		ON p.id = c.protoid
		JOIN h		ON h.id = c.hostid
		JOIN v		ON v.id = c.varid
	;

INSERT INTO p VALUES (1, 'RDP',	'rdesktop',	3389,	False,	'%h:%p',	NULL);
INSERT INTO p VALUES (2, 'VNC',	'vncviewer',	5900,	False,	'%h::%p',	NULL);
INSERT INTO p VALUES (3, 'NX',		'nxssh',	22,	False,	'-p %p %h',	NULL);
INSERT INTO p VALUES (4, 'SSH',	'ssh',		22,	True,	'-p %p %h',	NULL);
INSERT INTO p VALUES (5, 'Telnet',	'telnet',	23,	False,	'%h %p',	NULL);
INSERT INTO p VALUES (6, 'FTP',	'ftp',		21,	False,	'%h:%p',	NULL);
INSERT INTO v VALUES (1, 'NULL',	'NULL',		NULL);

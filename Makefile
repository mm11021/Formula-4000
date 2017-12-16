CC	= gcc
CFLAGS	= -g -Wall `mysql_config --cflags --libs`

program: 1.c
	$(CC) $(CFLAGS) 1.c -o $@

create: create.sql
	mysql -u root <$<
insert: insert.sql
	mysql -u root <$<

CC	= gcc
CFLAGS	= -g -Wall `mysql_config --cflags --libs`

program: program.c
	$(CC) $(CFLAGS) $< -o $@

create: create.sql
	mysql -u root <$<
insert: insert.sql
	mysql -u root <$<

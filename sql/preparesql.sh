#!/bin/sh
# convert human-readable sql scripts into Qt-compatible (1 sql string per line)default_src.sql
echo "BEGIN TRANSACTION;" > data.sql
./src2sql.sh scheme_src.sql >> data.sql
./src2sql.sh default_src.sql >> data.sql
echo "COMMIT TRANSACTION;" >> data.sql

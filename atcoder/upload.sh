#!/bin/bash
set -ue

./copy.sh

php ./imojudge_upload.php 2308 ./A
php ./imojudge_upload.php 2309 ./B
php ./imojudge_upload.php 2310 ./C
php ./imojudge_upload.php 2311 ./D
php ./imojudge_upload.php 2312 ./E
php ./imojudge_upload.php 2313 ./F
php ./imojudge_upload.php 2314 ./G
php ./imojudge_upload.php 2315 ./H

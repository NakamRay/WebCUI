# https://qiita.com/kurkuru/items/fa7401a01c4d5dd98e4a

sudo service docker start
sudo docker run -d -p 80:80 -v .:/var/www/html --name php70-apache php:7.0-apache

# sudo docker exec -it php70-apache bash

# apt-get update
# apt-get install python3
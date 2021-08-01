sudo docker build -t webcui-sample .
sudo docker run -d -p 80:80 -v "$(pwd):/var/www/html" --name webcui-sample webcui-sample

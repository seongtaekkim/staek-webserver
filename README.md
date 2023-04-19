# webserv



### log

log는 class 내부에 작성하여 기록된다.
log 객체는 클래스당 최초에 한번만 생성되어야 한다.



## Diagram
connect
recv
response
send

## nginx example
Doc root is: /opt/homebrew/var/www
port set : /opt/homebrew/etc/nginx/nginx.conf to 8080 so that nginx can run without sudo.

nginx will load all files in /opt/homebrew/etc/nginx/servers/.

## directory
/var/www/ 			: default page call
/var/www/index.html
/var/www/50x.html

/etc/nginx/nginx.conf
/etc/nginx/mime.types
/etc/nginx/cgi.conf

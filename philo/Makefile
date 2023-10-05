CC = gcc

SRC = 	main.c \
		functions.c \
		init.c \
		monitor.c \
		routine.c \
		time.c \
		time_busy.c

CFLAGS = -Wall -Werror -Wextra

all:
	clear
	$(CC) $(CFLAGS) $(SRC) -o philo -lpthread

git:
	cmd.exe /c start $$(git remote get-url origin | sed 's/.git$$//')

push:
	git add . && \
	git commit -m "ok" && \
	git push && \
	git ls-tree -r HEAD \

email:
	mutt -s "Hi" dsheng1993@gmail.com shenghero1993@gmail.com -a "./philo.h" -a "./main.c" < body.txt

zip:
	zip -r sheng.zip *
	@read -p "Enter email address: " email; \
	mutt -s "Hi" $$email -a "sheng.zip" < body.txt
	rm sheng.zip

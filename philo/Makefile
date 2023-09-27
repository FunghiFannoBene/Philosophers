CC = gcc

SRC = 	main.c \
		functions.c \

CFLAGS = -Wall -Werror -Wextra

all:
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
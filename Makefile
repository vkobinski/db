EXEC=main

build:
	gcc -o $(EXEC) main.c

run: build
	./$(EXEC)

test: build
	bundle exec rspec rspec/

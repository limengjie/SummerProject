input = calc.c
output = calculate
CC = gcc

$(output): $(input)
	$(CC) -o $@ $(input)

clean:
	$(RM) $(output)

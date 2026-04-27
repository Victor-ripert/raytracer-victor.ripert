##
## EPITECH PROJECT, 2026
## cPoolDay4
## File description:
## Makefile
##

NAME = raytracing

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I.

SRC =	main.cpp \
		src/Vector3D.cpp \
		src/Point3D.cpp	\
		src/Ray.cpp \
		src/Sphere.cpp \
		src/Rectangle3D.cpp \
		src/Camera.cpp \
		src/Plain.cpp \
		src/Scene.cpp \
		src/Color.cpp \
		src/AmbiantLight.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) -g3

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	rm -f $(OBJ)


.PHONY: all clean fclean re

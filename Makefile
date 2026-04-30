##
## EPITECH PROJECT, 2026
## Raytracer
## File description:
## Makefile for Core and Plugins
##

NAME = raytracer

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I./include -fPIC -g3
LDFLAGS = -ldl

# Core Source Files
CORE_SRC =	main.cpp \
			src/Math/Vector3D.cpp \
			src/Math/Point3D.cpp	\
			src/Math/Ray.cpp \
			src/Core/Scene.cpp \
			src/Core/Camera.cpp \
			src/Core/Color.cpp \
			src/Core/PointLight.cpp \
			src/Core/Rectangle3D.cpp

CORE_OBJ = $(CORE_SRC:.cpp=.o)

# Plugins
PLUGINS_DIR = plugins
SPHERE_NAME = sphere.so
PLANE_NAME = plane.so

SPHERE_SRC = plugins/Primitives/Sphere/Sphere.cpp
PLANE_SRC = plugins/Primitives/Plane/Plane.cpp

# Shared source files needed by plugins (Math, Color)
SHARED_SRC = src/Math/Vector3D.cpp \
             src/Math/Point3D.cpp \
             src/Math/Ray.cpp \
             src/Core/Color.cpp

all: $(NAME) plugins

$(NAME): $(CORE_OBJ)
	$(CXX) $(CXXFLAGS) $(CORE_OBJ) -o $(NAME) $(LDFLAGS)

plugins: $(PLUGINS_DIR)/$(SPHERE_NAME) $(PLUGINS_DIR)/$(PLANE_NAME)

$(PLUGINS_DIR)/$(SPHERE_NAME): $(SPHERE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_DIR)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

$(PLUGINS_DIR)/$(PLANE_NAME): $(PLANE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_DIR)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

clean:
	rm -f $(CORE_OBJ)
	rm -rf $(PLUGINS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re plugins

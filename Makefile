##
## EPITECH PROJECT, 2026
## Raytracer
## File description:
## Makefile (FIXED: Isolated Plugin Sources)
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

# Plugins (Sources in src_plugins, Binaries in plugins)
PLUGINS_OUT_DIR = plugins
PLUGINS_SRC_DIR = src_plugins

SPHERE_NAME = sphere.so
PLANE_NAME = plane.so

SPHERE_SRC = $(PLUGINS_SRC_DIR)/Primitives/Sphere/Sphere.cpp
PLANE_SRC = $(PLUGINS_SRC_DIR)/Primitives/Plane/Plane.cpp

# Shared source files needed by plugins
SHARED_SRC = src/Math/Vector3D.cpp \
             src/Math/Point3D.cpp \
             src/Math/Ray.cpp \
             src/Core/Color.cpp

all: $(NAME) plugins

$(NAME): $(CORE_OBJ)
	$(CXX) $(CXXFLAGS) $(CORE_OBJ) -o $(NAME) $(LDFLAGS)

plugins: $(PLUGINS_OUT_DIR)/$(SPHERE_NAME) $(PLUGINS_OUT_DIR)/$(PLANE_NAME)

$(PLUGINS_OUT_DIR)/$(SPHERE_NAME): $(SPHERE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_OUT_DIR)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

$(PLUGINS_OUT_DIR)/$(PLANE_NAME): $(PLANE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_OUT_DIR)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(PLUGINS_OUT_DIR)

re: fclean all

.PHONY: all clean fclean re plugins

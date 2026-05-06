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

LIBCONFIG_LDFLAGS = $(shell pkg-config --silence-errors --libs libconfig++ 2>/dev/null)
LIBCONFIG_CFLAGS  = $(shell pkg-config --silence-errors --cflags libconfig++ 2>/dev/null)
ifeq ($(strip $(LIBCONFIG_LDFLAGS)),)
LIBCONFIG_HOME = $(shell brew --prefix libconfig 2>/dev/null)
ifneq ($(strip $(LIBCONFIG_HOME)),)
LIBCONFIG_CFLAGS  = -I$(LIBCONFIG_HOME)/include
LIBCONFIG_LDFLAGS = -L$(LIBCONFIG_HOME)/lib -lconfig++
else
LIBCONFIG_LDFLAGS = -lconfig++
endif
endif

CXXFLAGS += $(LIBCONFIG_CFLAGS)
LDFLAGS += $(LIBCONFIG_LDFLAGS)

# Core Source Files
CORE_SRC =	main.cpp \
			src/Math/Vector3D.cpp \
			src/Math/Point3D.cpp	\
			src/Math/Ray.cpp \
			src/Core/Scene/Scene.cpp \
			src/Core/Render/Camera.cpp \
			src/Core/Render/Color.cpp \
			src/Core/Lights/PointLight.cpp \
			src/Core/Lights/DirectionalLight.cpp \
			src/Core/Render/Rectangle3D.cpp \
			src/Core/Config/LibConfigLoader.cpp \
			src/Core/Config/ConfigParse.cpp \
			src/Core/Factory/PrimitiveFactory.cpp \
			src/Core/Lights/LightFactory.cpp \
			src/Core/Scene/SceneBuilder.cpp

CORE_OBJ = $(CORE_SRC:.cpp=.o)

# Plugins (Sources in src_plugins, Binaries in plugins)
PLUGINS_OUT_DIR = plugins
PLUGINS_SRC_DIR = src_plugins
PLUGINS_PRIMITIVES_INCLUDES = $(PLUGINS_SRC_DIR)/primitives

SPHERE_NAME = sphere.so
PLANE_NAME = plane.so

SPHERE_SRC = $(PLUGINS_SRC_DIR)/Primitives/Sphere/Sphere.cpp
PLANE_SRC = $(PLUGINS_SRC_DIR)/Primitives/Plane/Plane.cpp

# Shared source files needed by plugins
SHARED_SRC = src/Math/Vector3D.cpp \
             src/Math/Point3D.cpp \
             src/Math/Ray.cpp \
             src/Core/Render/Color.cpp

all: $(NAME) plugins

$(NAME): $(CORE_OBJ)
	$(CXX) $(CXXFLAGS) $(CORE_OBJ) -o $(NAME) $(LDFLAGS)

plugins: $(PLUGINS_OUT_DIR)/$(SPHERE_NAME) $(PLUGINS_OUT_DIR)/$(PLANE_NAME)

$(PLUGINS_OUT_DIR)/$(SPHERE_NAME): $(SPHERE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_OUT_DIR)
	$(CXX) $(CXXFLAGS) -I$(PLUGINS_PRIMITIVES_INCLUDES) -shared $^ -o $@

$(PLUGINS_OUT_DIR)/$(PLANE_NAME): $(PLANE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_OUT_DIR)
	$(CXX) $(CXXFLAGS) -I$(PLUGINS_PRIMITIVES_INCLUDES) -shared $^ -o $@

clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(PLUGINS_OUT_DIR)

re: fclean all

.PHONY: all clean fclean re plugins

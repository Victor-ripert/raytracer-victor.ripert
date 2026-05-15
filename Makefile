##
## EPITECH PROJECT, 2026
## Raytracer
## File description:
## Makefile (FIXED: Isolated Plugin Sources)
##

NAME = raytracer

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I./include -fPIC -g3 -pthread
LDFLAGS = -ldl -pthread

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
			src/Core/Render/Renderer.cpp \
			src/Core/Config/LibConfigLoader.cpp \
			src/Core/Config/ConfigUtils.cpp \
			src/Core/Factory/PrimitiveFactory.cpp \
			src/Core/Factory/MaterialFactory.cpp \
			src/Core/Lights/LightFactory.cpp \
			src/Core/Scene/SceneBuilder.cpp

CORE_OBJ = $(CORE_SRC:.cpp=.o)

# Plugins (Sources in src_plugins; binaries under plugins/primitives vs plugins/materials)
PLUGINS_ROOT = plugins
PLUGINS_PRIMITIVE_DIR = $(PLUGINS_ROOT)/primitives
PLUGINS_MATERIAL_DIR = $(PLUGINS_ROOT)/materials
PLUGINS_SRC_DIR = src_plugins

SPHERE_NAME = sphere.so
PLANE_NAME = plane.so

SPHERE_DIR = $(PLUGINS_SRC_DIR)/Primitives/Sphere
PLANE_DIR = $(PLUGINS_SRC_DIR)/Primitives/Plane

SPHERE_SRC = $(SPHERE_DIR)/Sphere.cpp
PLANE_SRC = $(PLANE_DIR)/Plane.cpp

MIRROR_NAME = mirror.so
TINTED_MIRROR_NAME = tinted_mirror.so
SILVER_NAME = silver.so
ROCK_NAME = rock.so

MIRROR_DIR = $(PLUGINS_SRC_DIR)/Materials/Mirror
TINTED_MIRROR_DIR = $(PLUGINS_SRC_DIR)/Materials/TintedMirror
SILVER_DIR = $(PLUGINS_SRC_DIR)/Materials/Silver
ROCK_DIR = $(PLUGINS_SRC_DIR)/Materials/Rock

MIRROR_SRC = $(MIRROR_DIR)/Mirror.cpp
TINTED_MIRROR_SRC = $(TINTED_MIRROR_DIR)/TintedMirror.cpp
SILVER_SRC = $(SILVER_DIR)/Silver.cpp
ROCK_SRC = $(ROCK_DIR)/Rock.cpp

# Shared source files needed by plugins
SHARED_SRC = src/Math/Vector3D.cpp \
             src/Math/Point3D.cpp \
             src/Math/Ray.cpp \
             src/Core/Render/Color.cpp \
             src/Core/Config/ConfigUtils.cpp

all: $(NAME) plugins

$(NAME): $(CORE_OBJ)
	$(CXX) $(CXXFLAGS) $(CORE_OBJ) -o $(NAME) $(LDFLAGS)

plugins: $(PLUGINS_PRIMITIVE_DIR)/$(SPHERE_NAME) $(PLUGINS_PRIMITIVE_DIR)/$(PLANE_NAME) \
         $(PLUGINS_MATERIAL_DIR)/$(MIRROR_NAME) $(PLUGINS_MATERIAL_DIR)/$(TINTED_MIRROR_NAME) \
         $(PLUGINS_MATERIAL_DIR)/$(SILVER_NAME) $(PLUGINS_MATERIAL_DIR)/$(ROCK_NAME)

$(PLUGINS_PRIMITIVE_DIR)/$(SPHERE_NAME): $(SPHERE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_PRIMITIVE_DIR)
	$(CXX) $(CXXFLAGS) -I$(SPHERE_DIR) -shared $^ -o $@ $(LDFLAGS)

$(PLUGINS_PRIMITIVE_DIR)/$(PLANE_NAME): $(PLANE_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_PRIMITIVE_DIR)
	$(CXX) $(CXXFLAGS) -I$(PLANE_DIR) -shared $^ -o $@ $(LDFLAGS)

$(PLUGINS_MATERIAL_DIR)/$(MIRROR_NAME): $(MIRROR_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_MATERIAL_DIR)
	$(CXX) $(CXXFLAGS) -I$(MIRROR_DIR) -shared $^ -o $@ $(LDFLAGS)

$(PLUGINS_MATERIAL_DIR)/$(TINTED_MIRROR_NAME): $(TINTED_MIRROR_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_MATERIAL_DIR)
	$(CXX) $(CXXFLAGS) -I$(TINTED_MIRROR_DIR) -shared $^ -o $@ $(LDFLAGS)

$(PLUGINS_MATERIAL_DIR)/$(SILVER_NAME): $(SILVER_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_MATERIAL_DIR)
	$(CXX) $(CXXFLAGS) -I$(SILVER_DIR) -shared $^ -o $@ $(LDFLAGS)

$(PLUGINS_MATERIAL_DIR)/$(ROCK_NAME): $(ROCK_SRC) $(SHARED_SRC)
	@mkdir -p $(PLUGINS_MATERIAL_DIR)
	$(CXX) $(CXXFLAGS) -I$(ROCK_DIR) -shared $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(PLUGINS_ROOT)

re: fclean all

.PHONY: all clean fclean re plugins

#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>
#include <LucyGL/Texture.h>

#include <glad/glad.h>
#include <iostream>

lgl::Texture::Texture(TextureMode mode) {
	this->mode = mode;

	glGenTextures(1, &id);
}

lgl::Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void lgl::Texture::LoadTexture(const char* filename) {
	assert(mode == TEXTURE_2D);

	SetWrapMode(WrapMode_MIRRORED_REPEAT, WrapMode_MIRRORED_REPEAT);
	SetFilteringMode(FilterMode_NEAREST, FilterMode_NEAREST);

	unsigned char* data = nullptr;
	if (filename) data = stbi_load(filename, &width, &height, &channels, 0);
		
	if (!data) {
		static uint8_t default_data[] = {
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
			255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255,
			  0,   0,   0, 255, 255,   0, 255, 255,   0,   0,   0, 255, 255,   0, 255, 255,
		};

		Load2D(0, RGBA, 4, 4, 0, RGBA, UNSIGNED_BYTE, default_data);
	} else {
		if (channels == 4) Load2D(0, RGBA, width, height, 0, RGBA, UNSIGNED_BYTE, data);
		if (channels == 3) Load2D(0, RGBA, width, height, 0, RGB, UNSIGNED_BYTE, data);
	}

	stbi_image_free(data);
}

void lgl::Texture::LoadSpriteSheet(const char* filename, int x, int y, int w, int h) {
	
}

void lgl::Texture::Load2D(int level, Format internalformat, int width, int height, int border, Format format, Type type, void* data) {
	glTexImage2D(Map(mode), level, Map(internalformat), width, height, border, Map(format), Map(type), data);
}

void lgl::Texture::Load3D(int level, Format internalformat, int width, int height, int depth, int border, Format format, Type type, void* data) {
	glTexImage3D(Map(mode), level, Map(internalformat), width, height, depth, border, Map(format), Map(type), data);
}

void lgl::Texture::LoadSub3D(int level, Format internalformat, int x, int y, int z, int width, int height, int depth, Format format, Type type, void* data) {
	glTexSubImage3D(Map(mode), level, x, y, z, width, height, depth, Map(format), Map(type), data);
}

void lgl::Texture::GenerateMimmap() {
	glGenerateMipmap(id);
}

void lgl::Texture::SetWrapMode(TextureWrapMode wrap_s, TextureWrapMode wrap_t, TextureWrapMode wrap_r) {
	if (this->wrap_s != wrap_s && wrap_s != WrapMode_None) {
		this->wrap_s = wrap_s;
		glTexParameteri(Map(mode), GL_TEXTURE_WRAP_S, Map(wrap_s));
	}
	if (this->wrap_t != wrap_t && wrap_t != WrapMode_None) {
		this->wrap_t = wrap_t;
		glTexParameteri(Map(mode), GL_TEXTURE_WRAP_T, Map(wrap_t));
	}
	if (this->wrap_r != wrap_r && wrap_r != WrapMode_None) {
		this->wrap_r = wrap_r;
		glTexParameteri(Map(mode), GL_TEXTURE_WRAP_R, Map(wrap_r));
	}
}

void lgl::Texture::SetFilteringMode(TextureFilteringMode mag, TextureFilteringMode min) {
	if (this->mag != mag && mag != FilterMode_None) {
		this->mag = mag;
		glTexParameteri(Map(mode), GL_TEXTURE_MAG_FILTER, Map(mag));
	}
	if (this->min != min && min != FilterMode_None) {
		this->min = min;
		glTexParameteri(Map(mode), GL_TEXTURE_MIN_FILTER, Map(min));
	}
}

void lgl::Texture::Bind() {
	glBindTexture(Map(mode), id);
}

void lgl::Texture::BindUnit(const unsigned int unit) {
	glBindTextureUnit(unit, id);
}

void lgl::Texture::UnBind() {
	glBindTexture(Map(mode), 0);
}

void lgl::BindTextureUnit(const TextureId id, const unsigned int unit) {
	glBindTextureUnit(unit, id);
}

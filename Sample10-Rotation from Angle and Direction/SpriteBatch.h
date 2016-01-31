#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Vertex.h"

using namespace std;

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

struct Glyph
{
	GLuint texture;
	float depth;

	Vertex tl;
	Vertex bl;
	Vertex tr;
	Vertex br;
};

class RenderBatch
{
public:
	RenderBatch(GLuint Offset, GLuint NumVertext, GLuint Texture) : offset(Offset), numVertext(NumVertext), texture(Texture){}

	GLuint offset;
	GLuint numVertext;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(GlyphSortType st = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, const glm::vec2 direction);
	
	glm::vec2 rotatePoint(glm::vec2 pos, float angle);

	void render();
private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	GLuint vbo;
	GLuint vao;

	GlyphSortType sortType;
	vector<Glyph*> glyph;
	vector<RenderBatch> renderBatches;
};

#endif
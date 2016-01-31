#include "SpriteBatch.h"

#include <algorithm>

SpriteBatch::SpriteBatch()
{
	vbo = 0;
	vao = 0;
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType st)
{
	sortType = st;
	renderBatches.clear();

	for(int i = 0; i < glyph.size(); i++)
		delete glyph[i];

	glyph.clear();
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	Glyph* newG = new Glyph;
	newG->texture = texture;
	newG->depth = depth;

	newG->tl.color = color;
	newG->tl.setPosition(destRect.x, destRect.y + destRect.w);
	newG->tl.setUV(uvRect.x, uvRect.y + uvRect.w);

	newG->bl.color = color;
	newG->bl.setPosition(destRect.x, destRect.y);
	newG->bl.setUV(uvRect.x, uvRect.y);

	newG->br.color = color;
	newG->br.setPosition(destRect.x + destRect.z, destRect.y);
	newG->br.setUV(uvRect.x + uvRect.z, uvRect.y);

	newG->tr.color = color;
	newG->tr.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newG->tr.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	glyph.push_back(newG);
}

void SpriteBatch::render()
{
	glBindVertexArray(vao);

	for(int i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertext);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	vector<Vertex> vertices;
	vertices.resize(glyph.size() * 6);

	if(glyph.empty())
		return;

	int offset = 0;
	int cv = 0;

	renderBatches.emplace_back(offset, 6, glyph[0]->texture);
	vertices[cv++] = glyph[0]->tl;
	vertices[cv++] = glyph[0]->bl;
	vertices[cv++] = glyph[0]->br;
	vertices[cv++] = glyph[0]->br;
	vertices[cv++] = glyph[0]->tr;
	vertices[cv++] = glyph[0]->tl;

	offset += 6;

	for(int cg = 1; cg < glyph.size(); cg++)
	{
		if(glyph[cg]->texture != glyph[cg - 1]->texture)
			renderBatches.emplace_back(offset, 6, glyph[cg]->texture);
		else
			renderBatches.back().numVertext += 6;

		vertices[cv++] = glyph[cg]->tl;
		vertices[cv++] = glyph[cg]->bl;
		vertices[cv++] = glyph[cg]->br;
		vertices[cv++] = glyph[cg]->br;
		vertices[cv++] = glyph[cg]->tr;
		vertices[cv++] = glyph[cg]->tl;
		
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if(vao == 0)
		glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	if(vbo == 0)
		glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
	switch (sortType)
	{
	case GlyphSortType::FRONT_TO_BACK:
		stable_sort(glyph.begin(), glyph.end(), compareFrontToBack);
		break;
	case GlyphSortType::BACK_TO_FRONT:
		stable_sort(glyph.begin(), glyph.end(), compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		stable_sort(glyph.begin(), glyph.end(), compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}
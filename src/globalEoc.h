#include "scene.h"
#include "textureManager.h"
#include "edgeShader.h"
#include "gbufferShader.h"
#include "eocCamera.h"
#include "eocVolumn.h"
#include "fbo.h"
#include "blender.h"
#ifndef EOC_H
#define EOC_H
class EOCrender
{
public:
	EOCrender() ;
	EOCrender(int w, int h);
	~EOCrender()= default;
	inline void setOriginCamera( Camera * pCamera)
	{
		pOriginCam = pCamera;
		m_eocRightCam.setOriginCamera(pCamera);
	}
	void render(textureManager & manager);
	inline void setScene( Scene *pScene)
	{
		m_pScene = pScene;
	}
	inline Fbo& getFbo() 
	{
		return m_renderFbo;
	}
	inline Fbo* getGbufferP()
	{
		return &m_gbufferFbo;
	}
	inline Fbo* getEdgeBufferP()
	{
		return &m_edgeFbo;
	}
	inline GLuint getRenderImage() 
	{
		return m_renderFbo.getTexture(0);
	}
	inline void debugSwap()
	{
		m_debugSwap = !m_debugSwap;
	}
	inline Fbo* getOccludeFbo()
	{
		return &m_occludedBuffer;
	}
private:
	bool m_debugSwap;
	EocCamera m_eocRightCam;
	Camera * pOriginCam;
	EdgeShader m_edgeShader;
	GbufferShader m_gbufferShader;
	BlendShader m_blendShader;
	EocVolumnShader m_volumnShader;
	 Scene * m_pScene,*m_pQuad;
	GLuint m_width, m_height, m_k;
	int m_total_pixel;
	GLuint m_head_pointer_texture, m_head_pointer_initializer, m_atomic_counter_buffer, m_fragment_storage_buffer, m_linked_list_texture, m_computerShader, dispatch_buffer;
	GLuint *m_data;
	Fbo m_renderFbo;
	Fbo m_edgeFbo;
	Fbo m_gbufferFbo;
	Fbo m_occludedBuffer;
	Fbo debugFbo;
};
#endif
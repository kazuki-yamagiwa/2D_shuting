//--------------------------------------------------------------//
//	"vn_Direct3D.h"												//
//		Direct3D�Ǘ�											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

class vnDirect3D
{
private:
	//DirectX�C���^�[�t�F�C�X
	static ID3D11Device				*pDevice;			//Direct3D11�f�o�C�X
	static ID3D11DeviceContext		*pDeviceContext;	//Direct3D11�f�o�C�X�R���e�L�X�g
	static IDXGIDevice				*pDXGI;				//DXGI�f�o�C�X
	static IDXGIAdapter				*pAdapter;			//�A�_�v�^
	static IDXGIFactory				*pDXGIFactory;		//�t�@�N�g��
	static IDXGISwapChain			*pDXGISwpChain;		//�X���b�v�`�F�C��
	static ID3D11RenderTargetView	*pRenderTargetView;	//�����_�[�^�[�Q�b�g�r���[
	static ID3D11DepthStencilView	*pDepthStencilView;	//�f�v�X�X�e���V���r���[

	//�e�N�X�`��
	static ID3D11Texture2D			*pWhiteTexture;
	static ID3D11ShaderResourceView	*pWhiteTextureView;

public:
	//�t���[�����[�N�Ǘ�
	static int initialize(void *hdl, int width, int height);
	static void terminate(void);

	//�C���^�[�t�F�C�X�̎擾
	static ID3D11Device* getDevice(void);
	static ID3D11DeviceContext* getDeviceContext(void);
	static IDXGISwapChain* getSwapChain(void);

	//�`��R�[��
	static void draw(UINT vertexCount, UINT startVertexLocation = 0);
	static void drawIndexed(UINT indexCount, UINT startIndexLocation = 0, INT baseVertexLocation = 0);

	//��ʊǗ�
	static void clear(void);
	static void present(UINT SyncInterval = 0);

	//�V�F�[�_�[�̃Z�b�g
	static void setVShader(vnShader::eVertexShader vs);
	static void setPShader(vnShader::ePixelShader ps);

	//�V�F�[�_�[���\�[�X�̃Z�b�g
	static void setShaderResource(ID3D11ShaderResourceView* p, int slot = 0);
};

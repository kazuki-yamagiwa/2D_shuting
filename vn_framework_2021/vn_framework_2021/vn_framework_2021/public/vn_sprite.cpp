//--------------------------------------------------------------//
//	"vn_sprite.cpp"												//
//		�X�v���C�g�N���X										//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../framework.h"
#include "../framework/vn_environment.h"

//���_�v�f
D3D11_INPUT_ELEMENT_DESC hInElementDesc_vnSprite[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//�ÓI���ʃf�[�^
ID3D11RasterizerState	*vnSprite::pRasterizerState = NULL;
ID3D11BlendState		*vnSprite::pBlendState = NULL;
ID3D11SamplerState		*vnSprite::pSamplerState = NULL;
ID3D11DepthStencilState	*vnSprite::pDepthStencilState;
ID3D11InputLayout		*vnSprite::pInputLayout = NULL;
ID3D11Buffer			*vnSprite::pConstantBuffer = NULL;
UINT					vnSprite::VertexStrides = sizeof(vnVertex2D);
UINT					vnSprite::VertexOffsets = 0;


//�ÓI���ʃf�[�^������
bool vnSprite::initializeCommon()
{
	HRESULT hr;

	//���X�^���C�U�̐ݒ�
	D3D11_RASTERIZER_DESC hRasterizerDesc = {
		D3D11_FILL_SOLID,	//�t�B�����[�h
		D3D11_CULL_NONE,	//�J�����O���[�h
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};

	//���X�^���C�U�̍쐬
	hr = vnDirect3D::getDevice()->CreateRasterizerState(&hRasterizerDesc, &pRasterizerState);
	if (hr != S_OK)
	{
		return false;
	}

	//�u�����h�X�e�[�g�̐ݒ�
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN | D3D11_COLOR_WRITE_ENABLE_BLUE;

	//�u�����h�X�e�[�g�̍쐬
	hr = vnDirect3D::getDevice()->CreateBlendState(&BlendDesc, &pBlendState);
	if (hr != S_OK)
	{
		return false;
	}

	// �T���v���X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���X�e�[�g�̐���
	hr = vnDirect3D::getDevice()->CreateSamplerState(&smpDesc, &pSamplerState);
	if (hr != S_OK)
	{
		return false;
	}

	//�[�x�X�e���V���X�e�[�g�̐ݒ�
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;

	//�[�x�X�e���V���X�e�[�g�̍쐬
	hr = vnDirect3D::getDevice()->CreateDepthStencilState(&dsDesc, &pDepthStencilState);
	if (hr != S_OK)return false;

	//���_���C�A�E�g�̍쐬
	vnShader::vnVertexShader *vs = vnShader::getVShader(vnShader::eVertexShader::VS_2D);
	hr = vnDirect3D::getDevice()->CreateInputLayout(hInElementDesc_vnSprite, ARRAYSIZE(hInElementDesc_vnSprite), vs->getCode(), vs->getLength(), &pInputLayout);
	if (hr != S_OK)
	{
		return false;
	}

	//�R���X�^���g�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(float) * 4;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float) * 4;

	//�R���X�^���g�o�b�t�@�̍쐬
	hr = vnDirect3D::getDevice()->CreateBuffer(&hBufferDesc, NULL, &pConstantBuffer);
	if (hr != S_OK)
	{
		return false;
	}

	//�X�N���[�����W���r���[�|�[�g���W�֕ϊ�����W��
	float w = (float)SCREEN_WIDTH;
	float h = (float)SCREEN_HEIGHT;
	float scr[4];
	scr[0] = 2.0f / w;
	scr[1] = -2.0f / h;
	scr[2] = -w * 0.5f;
	scr[3] = -h * 0.5f;
	//�萔�o�b�t�@�֒l���Z�b�g
	vnDirect3D::getDeviceContext()->UpdateSubresource(pConstantBuffer, 0, NULL, scr, 0, 0);

	return true;
}

//�ÓI���ʃf�[�^�폜
void vnSprite::terminateCommon()
{
	SAFE_RELEASE(pRasterizerState);
	SAFE_RELEASE(pBlendState);
	SAFE_RELEASE(pSamplerState);
	SAFE_RELEASE(pDepthStencilState);
	SAFE_RELEASE(pInputLayout);
	SAFE_RELEASE(pConstantBuffer);
}


//�R���X�g���N�^
vnSprite::vnSprite(float x, float y, float width, float height, const WCHAR *texture_file, float left_u, float right_u, float top_v, float bottom_v)
{
	//��{����ۑ�
	posX = x;
	posY = y;
	sizeX = width;
	sizeY = height;
	scaleX = 1.0f;
	scaleY = 1.0f;

	//���_���W��ݒ�
	setVertexPosition();

	//���_�J���[��ݒ�
	for (int i = 0; i < VertexNum; i++)
	{
		vtx[i].r = 1.0f;
		vtx[i].g = 1.0f;
		vtx[i].b = 1.0f;
		vtx[i].a = 1.0f;
	}

	//uv��ݒ�
	vtx[0].u = left_u;	vtx[0].v = top_v;
	vtx[1].u = right_u;	vtx[1].v = top_v;
	vtx[2].u = left_u;	vtx[2].v = bottom_v;
	vtx[3].u = right_u;	vtx[3].v = bottom_v;

	HRESULT hr;

	//�e�N�X�`���̓ǂݍ���
	hr = DirectX::CreateWICTextureFromFile(vnDirect3D::getDevice(), texture_file, &pTexture, &pTextureView);
	if (hr != S_OK)
	{
		pTexture = NULL;
		pTextureView = NULL;
	}

	//���_�o�b�t�@�̐ݒ�
	D3D11_BUFFER_DESC		hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(vnVertex2D) * VertexNum;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	//�T�u���\�[�X�f�[�^�̐ݒ�
	D3D11_SUBRESOURCE_DATA hSubResourceData;
	hSubResourceData.pSysMem = vtx;
	hSubResourceData.SysMemPitch = 0;
	hSubResourceData.SysMemSlicePitch = 0;

	//���_�o�b�t�@�̍쐬
	hr = vnDirect3D::getDevice()->CreateBuffer(&hBufferDesc, &hSubResourceData, &pVertexBuffer);
	if (hr != S_OK)
	{
		assert(false);
	}

	executeEnable = true;
	renderEnable = true;

	renderPriority = 0;
}

//�f�X�g���N�^
vnSprite::~vnSprite()
{
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pTextureView);
	SAFE_RELEASE(pVertexBuffer);
}

//�����֐�
void vnSprite::execute()
{
}

//�`��֐�
void vnSprite::render()
{
	//���_���W�̐ݒ�
	setVertexPosition();

	//���_�o�b�t�@�̍X�V
	vnDirect3D::getDeviceContext()->UpdateSubresource(pVertexBuffer, 0, NULL, vtx, 0, 0);

	//�u�����h�X�e�[�g���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->OMSetBlendState(pBlendState, NULL, 0xffffffff);
	//�[�x�X�e���V���X�e�[�g���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->OMSetDepthStencilState(pDepthStencilState, 0);
	//���X�^���C�U�[���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->RSSetState(pRasterizerState);
	//���_���C�A�E�g���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->IASetInputLayout(pInputLayout);
	//�R���X�^���g�o�b�t�@���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	//���_�o�b�t�@���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->IASetVertexBuffers(0, 1, &pVertexBuffer, &VertexStrides, &VertexOffsets);
	//�v���~�e�B�u(�|���S���̌`��)���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�T���v���[�X�e�[�g���R���e�L�X�g�ɐݒ�
	vnDirect3D::getDeviceContext()->PSSetSamplers(0, 1, &pSamplerState);
	//�e�N�X�`���[���R���e�L�X�g�ɐݒ�
	vnDirect3D::setShaderResource(pTextureView);

	//���_�V�F�[�_�[���R���e�L�X�g�ɐݒ�
	vnDirect3D::setVShader(vnShader::eVertexShader::VS_2D);
	//�s�N�Z���V�F�[�_�[���R���e�L�X�g�ɐݒ�
	vnDirect3D::setPShader(vnShader::ePixelShader::PS_2D);

	//�`��R�[��
	vnDirect3D::draw(VertexNum);
}

//���_���W�̐ݒ�
void vnSprite::setVertexPosition()
{
	//�W����Ԃł̊e���_�̍��W
	float v0x = (-sizeX * 0.5f) * scaleX, v0y = (-sizeY * 0.5f) * scaleY;
	float v1x = (+sizeX * 0.5f) * scaleX, v1y = (-sizeY * 0.5f) * scaleY;
	float v2x = (-sizeX * 0.5f) * scaleX, v2y = (+sizeY * 0.5f) * scaleY;
	float v3x = (+sizeX * 0.5f) * scaleX, v3y = (+sizeY * 0.5f) * scaleY;

	//��]��K�p
	float v0x_r = v0x * cosf(rot) - (v0y * sinf(rot));	//���_0�̉�]���x���W
	float v0y_r = v0y * cosf(rot) + (v0x * sinf(rot));	//���_0�̉�]���y���W
	float v1x_r = v1x * cosf(rot) - (v1y * sinf(rot));	//���_1�̉�]���x���W
	float v1y_r = v1y * cosf(rot) + (v1x * sinf(rot));	//���_1�̉�]���y���W
	float v2x_r = v2x * cosf(rot) - (v2y * sinf(rot));	//���_2�̉�]���x���W
	float v2y_r = v2y * cosf(rot) + (v2x * sinf(rot));	//���_2�̉�]���y���W
	float v3x_r = v3x * cosf(rot) - (v3y * sinf(rot));	//���_3�̉�]���x���W
	float v3y_r = v3y * cosf(rot) + (v3x * sinf(rot));	//���_3�̉�]���y���W

	//�e���_�ɒ��S���W��K�p���A��΍��W��ݒ�
	vtx[0].x = v0x_r + posX;	vtx[0].y = v0y_r + posY;
	vtx[1].x = v1x_r + posX;	vtx[1].y = v1y_r + posY;
	vtx[2].x = v2x_r + posX;	vtx[2].y = v2y_r + posY;
	vtx[3].x = v3x_r + posX;	vtx[3].y = v3y_r + posY;
}

//���s��Ԃ̐ݒ�
void vnSprite::setExecuteEnable(bool flag)
{
	executeEnable = flag;
}

//�`���Ԃ̐ݒ�
void vnSprite::setRenderEnable(bool flag)
{
	renderEnable = flag;
}

//���s��Ԃ̎擾
bool vnSprite::isExecuteEnable()
{
	return executeEnable;
}

//�`���Ԃ̎擾
bool vnSprite::isRenderEnable()
{
	return renderEnable;
}

//�`��D�揇�ʂ̐ݒ�
void vnSprite::setRenderPriority(int value)
{
	renderPriority = value;

	//�\�[�g���K�v�ł��邱�Ƃ�`����
	vnScene::setUpdateRenderPriority();
}

//�`��D�揇�ʂ̎擾
int vnSprite::getRenderPriority(void)
{
	return renderPriority;
}

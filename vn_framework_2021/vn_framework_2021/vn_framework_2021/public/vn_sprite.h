//--------------------------------------------------------------//
//	"vn_sprite.h"												//
//		�X�v���C�g�N���X										//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

//�|���S�����_�\����
struct vnVertex2D
{
	float x, y;			//���W
	float r, g, b, a;	//�J���[
	float u, v;			//uv
};

//�X�v���C�g�N���X
class vnSprite
{
public:
	//���W
	float posX;
	float posY;
	//�T�C�Y
	float sizeX;
	float sizeY;
	//�X�P�[��
	float scaleX;
	float scaleY;
	//��]
	float rot;

	//���_��
	static const int VertexNum = 4;
	//���_�f�[�^
	vnVertex2D	vtx[4];

private:
	//�`��D�揇��(���l���傫���قǎ�O�ɕ`�悳���)
	int renderPriority;

	//���s��Ԃ̊Ǘ�(execute�֐������s����)
	bool executeEnable;

	//�`���Ԃ̊Ǘ�(render�֐������s����)
	bool renderEnable;

protected:
	//���_�f�[�^�ւ̊e����̐ݒ�
	virtual void setVertexPosition();

private:
	//���_�o�b�t�@
	ID3D11Buffer				*pVertexBuffer;

	//�e�N�X�`��
	ID3D11Resource				*pTexture;
	ID3D11ShaderResourceView	*pTextureView;

	//�ÓI���ʃf�[�^
	static ID3D11RasterizerState	*pRasterizerState;
	static ID3D11SamplerState		*pSamplerState;
	static ID3D11BlendState			*pBlendState;
	static ID3D11DepthStencilState	*pDepthStencilState;
	static ID3D11InputLayout		*pInputLayout;
	static ID3D11Buffer				*pConstantBuffer;
	static UINT						VertexStrides;
	static UINT						VertexOffsets;

public:
	//�ÓI���ʃf�[�^������
	static bool initializeCommon();

	//�ÓI���ʃf�[�^�폜
	static void terminateCommon();

	//�R���X�g���N�^
	vnSprite(float x, float y, float width, float height, const WCHAR *texture_file, float left_u = 0.0f, float right_u = 1.0f, float top_v = 0.0f, float bottom_v = 1.0f);

	//�f�X�g���N�^
	virtual ~vnSprite();

	//����
	virtual void execute();

	//�`��
	virtual void render();

	//�`��D�揇�ʂ̐ݒ�
	void setRenderPriority(int value);

	//�`��D�揇�ʂ̎擾
	int getRenderPriority(void);

	//���s��Ԃ̐ݒ�
	void setExecuteEnable(bool flag);

	//�`���Ԃ̐ݒ�
	void setRenderEnable(bool flag);

	//���s��Ԃ̎擾
	bool isExecuteEnable();

	//�`���Ԃ̎擾
	bool isRenderEnable();
};

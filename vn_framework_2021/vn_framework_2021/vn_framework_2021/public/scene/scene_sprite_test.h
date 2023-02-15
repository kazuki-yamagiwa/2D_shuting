#pragma once

class SceneSpriteTest : public vnScene
{
private:
	vnSprite	*pSprite;

	vnSprite	*pPoint[4];

	//����̎��
	enum eOperation
	{
		PositionX,
		PositionY,
		ScaleX,
		ScaleY,
		Rotate,
		OperationMax,
	};

	int	Cursor;
	
public:
	//������
	bool initialize();

	//�I��
	void terminate();

	//����
	void execute();

	//�`��
	void render();
};

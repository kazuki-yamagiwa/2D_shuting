//--------------------------------------------------------------//
//	"vn_sceneTable.h"											//
//		�V�[���e�[�u��											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

//�V�[���̎��
enum class eSceneTable
{
	Boot,
	ActionTest,
	BlockTest,
	SpriteTest,
	PriorityTest,
	JoystickTest,
	SeTest,
	FontTest,
	SceneMax,
};

//�V�[���N���X��`�t�@�C��
#include "vn_scene.h"
#include "scene_boot.h"
#include "scene_action_test.h"
#include "scene_block_test.h"
#include "scene_sprite_test.h"
#include "scene_priority_test.h"
#include "scene_joystick_test.h"
#include "scene_se_test.h"
#include "scene_font_test.h"

//�V�[���؂�ւ��֐�(�\��)
void switchScene(eSceneTable scene);
//�V�[���؂�ւ��֐�(������)
void switchScene();
//�V�[���폜
void deleteScene();
